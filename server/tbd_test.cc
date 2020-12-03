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
