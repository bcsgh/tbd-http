#include "server/tbd.h"

#include <memory>

#include <httpserver.hpp>

#include "glog/logging.h"
#include "json/json.h"
#include "server/static_embed_emebed_data.h"

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

const std::shared_ptr<http_response> TbdServer_JSON::render(const http_request& req) {
  LOG(INFO) << "method        = '" << req.get_method() << "'";
  const auto body = req.get_content();
  LOG(INFO) << "Content:\n------\n" << body << "\n------";

  Json::Value ret(Json::objectValue);

  std::stringstream out;
  out << ret;
  return std::shared_ptr<http_response>{new httpserver::string_response(
      out.str(), http_utils::http_ok, "application/json")};
}

}  // namespace

struct TbdServer::Impl {
  TbdServer_JSON json;
  Static html, js;

  Impl() :
    html(std::string{server_main_html()}, "text/html"),
    js(std::string{server_tbd_main_js_js()}, "text/javascript") {}
};

TbdServer::TbdServer() : impl_(new TbdServer::Impl) {}
TbdServer::~TbdServer() = default;

void TbdServer::RegisterResources(httpserver::webserver *ws) {
  ws->register_resource("/", &impl_->html, true);
  ws->register_resource("/json", &impl_->json, true);
  ws->register_resource("/tbd.js", &impl_->js, true);
};

} // namespace tbd_server
