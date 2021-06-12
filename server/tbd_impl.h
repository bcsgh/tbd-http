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
    return std::make_unique<httpserver::string_response>(
        data_, http_utils::http_ok, mime_);
  }

 private:
  const std::string data_, mime_;
};

class TbdServer_JSON : public httpserver::http_resource {
 public:
  const std::shared_ptr<http_response> render(const http_request&) override;
  std::pair<std::string, int> render(const std::string&);
};

std::string PreambleUnits();

}  // namespace impl

struct TbdServer::Impl {
  impl::TbdServer_JSON json;
  impl::Static html, js, units, preamble;

  Impl();
};

} // namespace tbd_server

#endif // SERVER_TBD_IMPL_H_
