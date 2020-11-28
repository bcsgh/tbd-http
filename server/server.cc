#include "server/server.h"

#include <iostream>

#include <httpserver.hpp>

#include "glog/logging.h"
# include "server/tbd.h"

namespace tbd_server {

int Main(int port) {
  httpserver::webserver ws = httpserver::create_webserver(port)
                .log_error(+[](const std::string& err){
                  std::cout << err << std::endl;
                })
                .start_method(httpserver::http::http_utils::INTERNAL_SELECT)
                .max_threads(5);

  TbdServer server;
  server.RegisterResources(&ws);

  LOG(INFO) << "Serving at http://localhost:" << port << "/";
  ws.start(true);
  return 0;
}

} // namespace tbd_server