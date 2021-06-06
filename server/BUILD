load("@bazel_rules//cc_embed_data:cc_embed_data.bzl", "cc_embed_data")
load("@io_bazel_rules_closure//closure:defs.bzl", "closure_js_binary", "closure_js_library")
load("@io_bazel_rules_closure//closure/testing:closure_js_test.bzl", "closure_js_test")

cc_binary(
    name = "server",
    srcs = ["server_main.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":server_lib",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_library(
    name = "test_main",
    srcs = ["test_main.cc"],
    deps = [
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/time",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "server_lib",
    srcs = ["server.cc"],
    hdrs = ["server.h"],
    deps = [
        ":tbd",
        "@com_github_etr_libhttpserver//:libhttpserver",
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/flags:flag",
    ],
)

cc_library(
    name = "tbd",
    srcs = [
        "tbd.cc",
        "tbd_impl.h",
    ],
    hdrs = ["tbd.h"],
    deps = [
        ":static_embed",
        "@com_github_bcsgh_tbd//tbd:tbd_lib",
        # "@com_github_bcsgh_tbd//tbd:preamble",
        "@com_github_etr_libhttpserver//:libhttpserver",
        "@com_github_glog_glog//:glog",
        "@com_github_open_source_parsers_jsoncpp//:json",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/strings",
    ],
)

cc_test(
    name = "tbd_test",
    srcs = ["tbd_test.cc"],
    deps = [
        ":tbd",
        ":test_main",
        "@com_github_etr_libhttpserver//:libhttpserver",
        "@com_github_open_source_parsers_jsoncpp//:json",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest",
    ],
)

closure_js_library(
    name = "tbd_js",
    srcs = [
        "tbd.js",
        "tbd_main.js",
    ],
    deps = [
        "@io_bazel_rules_closure//closure/library/dom",
    ],
)

closure_js_test(
    name = "tbd_js_test",
    srcs = ["tbd_test.js"],
    entry_points = ["server/tbd_test.js"],
    suppress = ["moduleLoad"],
    deps = [
        ":tbd_js",
        "@io_bazel_rules_closure//closure/library/testing:asserts",
        "@io_bazel_rules_closure//closure/library/testing:jsunit",
        "@io_bazel_rules_closure//closure/library/testing:testsuite",
    ],
)

closure_js_binary(
    name = "tbd_main_js",
    entry_points = ["TBD.Start"],
    deps = [":tbd_js"],
)

cc_embed_data(
    name = "static_embed",
    srcs = [
        "main.html",
        "tbd_main_js.js",
    ],
    namespace = "tbd_server",
)
