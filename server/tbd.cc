// Copyright (c) 2020, Benjamin Shropshire,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "server/tbd.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <httpserver.hpp>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "json/json.h"
#include "server/static_embed_emebed_data.h"
#include "server/tbd_impl.h"
#include "tbd/preamble_emebed_data.h"
#include "tbd/tbd.h"

ABSL_FLAG(std::string, tbd_post_log_dir, "",
          "Where to stash POST bodies while processing them. "
          "This allows debuging crashes");

namespace tbd_server {
using httpserver::http_request;
using httpserver::http_response;
using httpserver::http::http_utils;

namespace impl {

class Sink : public tbd::ProcessOutput {
 public:
  Sink(std::vector<std::string> &e) : errs(e) {}

 private:
  void Error(const std::string &str) const override { errs.push_back(str); }

  std::vector<std::string> &errs;
};

std::shared_ptr<http_response> TbdServer_JSON::render(const http_request& req) {
  const auto body = req.get_content();
  auto ret = render(body);
  return std::make_unique<httpserver::string_response>(
      ret.first, ret.second, "application/json");
}

std::pair<std::string, int> TbdServer_JSON::render(const std::string_view body) {
  std::shared_ptr<void> cleanup_log_file;
  if (!absl::GetFlag(FLAGS_tbd_post_log_dir).empty()) {
    std::shared_ptr<char[]> tmp(
        tempnam(absl::GetFlag(FLAGS_tbd_post_log_dir).c_str(), "tbd."),
        std::free);
    std::string tmp_name(tmp.get());

    std::ofstream body_log;
    body_log.open(tmp_name);
    body_log << body;
    body_log.close();

    LOG(INFO) << "Logged body in '" << tmp_name << "'";
    cleanup_log_file.reset(&cleanup_log_file, [tmp_name](void*){
      std::remove(tmp_name.c_str());
    });
  }

  Json::Value ret(Json::objectValue);
  int code = 500;

  std::vector<std::string> errs;
  Sink sink{errs};
  auto processed = tbd::ProcessInput("source.tbd", std::string{body}, sink);

  if (!processed) {
    ret["errors"] = absl::StrJoin(errs, "");
    code = http_utils::http_bad_request;
  } else {
    Json::Value vals(Json::arrayValue);

    for (const auto* node : processed->sem.nodes()) {
      if (node->node && node->node->location().filename == tbd::kPreamble) continue;
      if (node->name == "") continue;

      Json::Value val(Json::objectValue);
      val["name"] = node->name;

      if (!std::isnan(node->value)) {
        double v = node->value;
        if (node->unit.has_value()) v /= node->unit->scale;
        val["value"] = v;
      }

      if (node->unit.has_value()) {
        val["unit"] = absl::StrCat("[", node->unit_name, "]");
      } else if (node->dim.has_value()) {
        val["unit"] = node->dim->to_str();
      }

      vals.append(val);
    }

    ret["values"] = vals;
    code = http_utils::http_ok;
  }

  std::stringstream out;
  out << ret;
  return {out.str(), code};
}

class JsonSink : public tbd::UnitsOutput {
 public:
  JsonSink(Json::Value *out) : out_(out) {}

  void Output(const std::string& a, const tbd::Unit& u) const override {
    Json::Value ret(Json::objectValue);
    ret["scale"] = u.scale;
    // Dump these as strins to avoid needing to worry about fractions.
    { auto v = u.dim.l(); if (v != "0") ret["L"] = v; }
    { auto v = u.dim.m(); if (v != "0") ret["M"] = v; }
    { auto v = u.dim.t(); if (v != "0") ret["T"] = v; }
    { auto v = u.dim.i(); if (v != "0") ret["I"] = v; }
    { auto v = u.dim.k(); if (v != "0") ret["K"] = v; }
    { auto v = u.dim.n(); if (v != "0") ret["N"] = v; }
    { auto v = u.dim.j(); if (v != "0") ret["J"] = v; }

    (*out_)["types"][u.dim.to_str()].append(a);
    (*out_)["units"][a] = ret;
  }

 private:
  Json::Value *const out_;
};


std::string PreambleUnits() {
  std::vector<std::string> errs;
  Sink sink{errs};
  auto processed = tbd::ProcessInput("NULL", "", sink);
  LOG_IF(FATAL, !processed) << "Failed to process embeded preamble";

  Json::Value ret(Json::objectValue);
  JsonSink out(&ret);

  processed->sem.LogUnits(out);

  Json::StreamWriterBuilder builder;
  builder.settings_["indentation"] = "";
  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

  std::stringstream str;
  writer->write(ret, &str);
  return str.str();
}

}  // namespace impl

TbdServer::Impl::Impl() :
    html(std::string{server_ui_main_html()}, "text/html"),
    js("", "text/plain"),
    units(impl::PreambleUnits(), "application/json"),
    preamble(std::string{::tbd_preamble_tbd()}, "text/x.tbd") {
  // Grab whichever version of the JS exists.
  std::set<std::string> keep{
      "server/ui/app_min.js",
      "server/ui/app_bundel.js",
  };
  for (const auto &i : EmbedIndex()) {
    if (keep.find(std::string{i.first}) != keep.end()) {
      js = impl::Static{std::string{i.second}, "text/javascript"};
      return;
    }
  }
  LOG(FATAL) << "JS not found";
}

TbdServer::TbdServer() : impl_(std::make_unique<TbdServer::Impl>()) {}
TbdServer::~TbdServer() = default;

void TbdServer::RegisterResources(httpserver::webserver *ws) {
  ws->register_resource("/", &impl_->html, true);
  ws->register_resource("/json", &impl_->json, true);
  ws->register_resource("/tbd.js", &impl_->js, true);
  ws->register_resource("/preamble.tbd", &impl_->preamble, true);
  ws->register_resource("/units", &impl_->units, true);
};

} // namespace tbd_server
