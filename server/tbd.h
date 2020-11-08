#include <memory>

#include <httpserver.hpp>

namespace tbd_server {

class TbdServer {
 public:
  TbdServer();
  ~TbdServer();

  void RegisterResources(httpserver::webserver *);

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace tbd_server

