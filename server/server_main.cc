#include "gflags/gflags.h"
#include "glog/logging.h"
#include "server/server.h"

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  return tbd_server::Main(8080);
}