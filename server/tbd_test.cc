#include "server/tbd.h"
#include "server/tbd_impl.h"

#include <set>
#include <string>

#include "absl/memory/memory.h"
#include "absl/strings/str_join.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "httpserver.hpp"
#include "json/json.h"

namespace tbd_server {

class ServiceTest : public ::testing::Test {
 protected:
  TbdServer server_;
};

namespace {
using http_utils = httpserver::http::http_utils;

TEST_F(ServiceTest, StaticSmoke) {
  impl::Static static_smoke{"hello world!", "text/text"};

  auto resp = static_smoke.render();

  EXPECT_EQ("text/text", resp->get_header(http_utils::http_header_content_type));
  EXPECT_EQ(200, resp->get_response_code());
}

TEST_F(ServiceTest, JsonError) {
  impl::TbdServer_JSON json;

  auto resp = json.render(R"(
    syntax error
  )");

  ASSERT_EQ(400, resp.second);

  ////////////////////////////////////////
  Json::Value root;
  std::string err;
  ASSERT_TRUE(absl::WrapUnique(Json::CharReaderBuilder().newCharReader())
                  ->parse(resp.first.c_str(),
                          resp.first.c_str() + resp.first.size(),
                          &root, &err)) << err;
  ASSERT_TRUE(root.isObject()) << root;

  ////////////////////////////////////////
  ASSERT_TRUE(root.isMember("errors")) << root;
  Json::Value errors;
  ASSERT_TRUE(root.removeMember("errors", &errors));

  ASSERT_TRUE(errors.isString()) << errors;
  auto error = errors.asString();
  EXPECT_THAT(error, testing::HasSubstr("error source.tbd:2:"));

  ////////////////////////////////////////
  EXPECT_TRUE(root.empty()) << "Unexpected keys: " << root;
}

TEST_F(ServiceTest, JsonSuccess) {
  impl::TbdServer_JSON json;

  auto resp = json.render(R"(
    x = y;
    y = z;
    z := 1[m];
  )");

  ASSERT_EQ(200, resp.second);

  ////////////////////////////////////////
  Json::Value root;
  std::string err;
  ASSERT_TRUE(absl::WrapUnique(Json::CharReaderBuilder().newCharReader())
                  ->parse(resp.first.c_str(),
                          resp.first.c_str() + resp.first.size(),
                          &root, &err)) << err;
  ASSERT_TRUE(root.isObject()) << root;

  ////////////////////////////////////////
  ASSERT_TRUE(root.isMember("values")) << root;
  Json::Value val;
  ASSERT_TRUE(root.removeMember("values", &val));

  ASSERT_TRUE(val.isArray()) << val;
  std::set<std::string> vars = {"x", "y", "z"};
  for(const Json::Value &v : val) {
    if (v.isMember("name") && v["name"].isString()) {
      EXPECT_TRUE(vars.find(v["name"].asString()) != vars.end())
          << "Unknown name: " << v["name"];
      vars.erase(v["name"].asString());
    } else {
      EXPECT_TRUE(false) << "Missing 'name': " << v;
    }

    if (v.isMember("unit") && v["unit"].isString()) {
      EXPECT_EQ(v["unit"].asString(), "[m]") << v["unit"];
    } else {
      EXPECT_TRUE(false) << "Missing 'unit': " << v;
    }

    if (v.isMember("value") && v["value"].isNumeric()) {
      EXPECT_EQ(v["value"].asFloat(), 1.0) << v["value"];
    } else {
      EXPECT_TRUE(false) << "Missing 'value': " << v;
    }
  }
  EXPECT_TRUE(vars.empty())
      << "Missing vars in .values: " << absl::StrJoin(vars, ", ");

  ////////////////////////////////////////
  EXPECT_TRUE(root.empty()) << "Unexpected keys: " << root;
}

}  // namespace
}  // namespace tbd_server
