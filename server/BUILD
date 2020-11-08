load("@bazel_rules//cc_embed_data:cc_embed_data.bzl", "cc_embed_data")
load("@io_bazel_rules_closure//closure:defs.bzl", "closure_js_library", "closure_js_binary")

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
        ":static_embed",
        "@com_github_etr_libhttpserver//:libhttpserver",
        "@com_github_open_source_parsers_jsoncpp//:json",
    ],
)

closure_js_library(
    name = "tbd_js",
    srcs = [
        "tbd.js",
        "tbd_main.js"
    ],
)

closure_js_binary(
    name = "tbd_main_js",
    deps = [":tbd_js"],
    entry_points = ["TBD.Start"],
)

cc_embed_data(
    name = "static_embed",
    namespace = "tbd_server",
    srcs = [
        "main.html",
        "tbd_main_js.js",
    ],
)
