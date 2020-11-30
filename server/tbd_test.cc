#include "server/tbd.h"

#include "gtest/gtest.h"

namespace tbd_server {

class ServiceTest : public ::testing::Test {
 protected:
  TbdServer server_;
};

namespace {

TEST_F(ServiceTest, Smoke) {
  // TODO
}

}  // namespace
}  // namespace tbd_server
