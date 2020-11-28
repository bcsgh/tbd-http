#include "server/tbd.h"

#include <memory>

#include <httpserver.hpp>

#include "absl/strings/str_join.h"
#include "glog/logging.h"
#include "json/json.h"
#include "server/static_embed_emebed_data.h"
#include "tbd/preamble_emebed_data.h"
#include "tbd/tbd.h"

namespace tbd_server {
using httpserver::http_request;
using httpserver::http_response;
using httpserver::http::http_utils;

namespace {
class Static : public httpserver::http_resource {
 public:
  Static(const std::string data, const std::string mime) :
    data_(std::move(data)),
    mime_(std::move(mime)) {}

  const std::shared_ptr<http_response> render(const http_request&) override {
    return std::shared_ptr<http_response>{new httpserver::string_response(
        data_, http_utils::http_ok, mime_)};
  }

 private:
  const std::string data_, mime_;
};

class TbdServer_JSON : public httpserver::http_resource {
 public:
  const std::shared_ptr<http_response> render(const http_request&) override;
};

class Sink : public tbd::ProcessOutput {
 public:
  Sink(std::vector<std::string> &e) : errs(e) {}

 private:
  void Error(const std::string &str) const override { errs.push_back(str); }

  std::vector<std::string> &errs;
};

const std::shared_ptr<http_response> TbdServer_JSON::render(const http_request& req) {
  const auto body = req.get_content();

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
        val["unit"] = node->unit_name;
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
  return std::shared_ptr<http_response>{new httpserver::string_response(
      out.str(), code, "application/json")};
}

}  // namespace

struct TbdServer::Impl {
  TbdServer_JSON json;
  Static html, js, preamble;

  Impl() :
    html(std::string{server_main_html()}, "text/html"),
    js(std::string{server_tbd_main_js_js()}, "text/javascript"),
    preamble(std::string{::tbd_preamble_tbd()}, "text/x.tbd") {}
};

TbdServer::TbdServer() : impl_(new TbdServer::Impl) {}
TbdServer::~TbdServer() = default;

void TbdServer::RegisterResources(httpserver::webserver *ws) {
  ws->register_resource("/", &impl_->html, true);
  ws->register_resource("/json", &impl_->json, true);
  ws->register_resource("/tbd.js", &impl_->js, true);
  ws->register_resource("/preamble.tbd", &impl_->preamble, true);
};

} // namespace tbd_server
