#include "server/tbd.h"

#include <memory>

#include <httpserver.hpp>

namespace tbd_server {
using httpserver::http_request;
using httpserver::http_response;
using httpserver::http::http_utils;

namespace {
class TbdServer_JSON : public httpserver::http_resource {
 public:
  const std::shared_ptr<http_response> render(const http_request&) override;
};

const std::shared_ptr<http_response> TbdServer_JSON::render(const http_request& req) {

  return std::shared_ptr<http_response>{new httpserver::string_response(
      "{}", http_utils::http_ok, "application/json")};
}

}  // namespace

struct TbdServer::Impl {
  TbdServer_JSON json;
};

TbdServer::TbdServer() : impl_(new TbdServer::Impl) {}
TbdServer::~TbdServer() = default;

void TbdServer::RegisterResources(httpserver::webserver *ws) {
  ws->register_resource("/hello", &impl_->json, true);
};

} // namespace tbd_server