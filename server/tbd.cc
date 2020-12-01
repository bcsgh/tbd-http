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
#include "absl/strings/str_join.h"
#include "glog/logging.h"
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

const std::shared_ptr<http_response> TbdServer_JSON::render(const http_request& req) {
  const auto body = req.get_content();
  auto ret = render(body);
  return std::shared_ptr<http_response>{new httpserver::string_response(
      ret.first, ret.second, "application/json")};
}

std::pair<std::string, int> TbdServer_JSON::render(const std::string& body) {
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
  auto processed = tbd::ProcessInput("source.tbd", body, sink);

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

}  // namespace impl
TbdServer::Impl::Impl() :
    html(std::string{server_main_html()}, "text/html"),
    js(std::string{server_tbd_main_js_js()}, "text/javascript"),
    preamble(std::string{::tbd_preamble_tbd()}, "text/x.tbd") {}

TbdServer::TbdServer() : impl_(new TbdServer::Impl) {}
TbdServer::~TbdServer() = default;

void TbdServer::RegisterResources(httpserver::webserver *ws) {
  ws->register_resource("/", &impl_->html, true);
  ws->register_resource("/json", &impl_->json, true);
  ws->register_resource("/tbd.js", &impl_->js, true);
  ws->register_resource("/preamble.tbd", &impl_->preamble, true);
};

} // namespace tbd_server
