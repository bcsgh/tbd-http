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

#include <cstdlib>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "server/server.h"

// TODO: Dump this once absl gets logging.

// Note: copied (with edits) from absl/flags/flag.h
#define ABSL_FLAG_X(T, n, d, h) ABSL_FLAG_IMPL_X(T, n, d, h)
#define ABSL_FLAG_IMPL_X(Type, name, default_value, help)                     \
  ABSL_FLAG_IMPL_DECLARE_DEF_VAL_WRAPPER(name, Type, default_value)           \
  ABSL_FLAG_IMPL_DECLARE_HELP_WRAPPER(name, help)                             \
  ABSL_CONST_INIT absl::Flag<Type> FLAGSx_##name{                             \
      ABSL_FLAG_IMPL_FLAGNAME(#name), ABSL_FLAG_IMPL_FILENAME(),              \
      ABSL_FLAG_IMPL_HELP_ARG(name), ABSL_FLAG_IMPL_DEFAULT_ARG(Type, name)}; \
  extern absl::flags_internal::FlagRegistrarEmpty FLAGSx_no##name;            \
  absl::flags_internal::FlagRegistrarEmpty FLAGSx_no##name =                  \
      ABSL_FLAG_IMPL_REGISTRAR(Type, FLAGSx_##name)

DECLARE_bool(alsologtostderr);
ABSL_FLAG_X(bool, alsologtostderr, false,
          "log messages go to stderr in addition to logfiles");

DECLARE_bool(logtostderr);
ABSL_FLAG_X(bool, logtostderr, false, "log messages go to stderr instead of logfiles");

DECLARE_int32(v);
ABSL_FLAG_X(int32_t, v, 0, "Show all VLOG(m) messages for m <= this.");

int main(int argc, char **argv) {
  auto args = absl::ParseCommandLine(argc, argv);
  // Forward flags to glog (it doesn't use absl::Flags).
  FLAGS_alsologtostderr = absl::GetFlag(FLAGSx_alsologtostderr);
  FLAGS_logtostderr = absl::GetFlag(FLAGSx_logtostderr);
  FLAGS_v = absl::GetFlag(FLAGSx_v);
  google::InitGoogleLogging(args[0]);
  google::InstallFailureSignalHandler();

  return tbd_server::Main();
}