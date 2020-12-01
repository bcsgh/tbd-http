#ifndef SERVER_TBD_IMPL_H_
#define SERVER_TBD_IMPL_H_

#include "server/tbd.h"

#include <string>
#include <memory>
#include <utility>

#include <httpserver.hpp>

namespace tbd_server {
using httpserver::http_request;
using httpserver::http_response;
using httpserver::http::http_utils;

namespace impl {
class Static : public httpserver::http_resource {
 public:
  Static(const std::string data, const std::string mime) :
    data_(std::move(data)),
    mime_(std::move(mime)) {}

  const std::shared_ptr<http_response> render(const http_request&) override {
    return render();
  }
  const std::shared_ptr<http_response> render() {
    return std::shared_ptr<http_response>{new httpserver::string_response(
        data_, http_utils::http_ok, mime_)};
  }

 private:
  const std::string data_, mime_;
};

class TbdServer_JSON : public httpserver::http_resource {
 public:
  const std::shared_ptr<http_response> render(const http_request&) override;
  std::pair<std::string, int> render(const std::string&);
};
}  // namespace impl

struct TbdServer::Impl {
  impl::TbdServer_JSON json;
  impl::Static html, js, preamble;

  Impl();
};

} // namespace tbd_server

#endif // SERVER_TBD_IMPL_H_
