cc_binary(
    name = "server",
    srcs = ["server_main.cc"],
    deps = [
        ":server_lib",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_glog_glog//:glog",
    ],
)

cc_library(
    name = "server_lib",
    hdrs = ["server.h"],
    srcs = ["server.cc"],
    deps = [
        ":tbd",
        "@com_github_etr_libhttpserver//:libhttpserver",
    ],
)

cc_library(
    name = "tbd",
    hdrs = ["tbd.h"],
    srcs = ["tbd.cc"],
    deps = [
        "@com_github_etr_libhttpserver//:libhttpserver",
    ],
)