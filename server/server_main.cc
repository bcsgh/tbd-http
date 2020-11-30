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

  return tbd_server::Main(8080);
}