load("@bazel_rules//cc_embed_data:cc_embed_data.bzl", "cc_embed_data")

cc_binary(
    name = "server",
    srcs = ["server_main.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":server_lib",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/log:initialize",
        "@com_google_absl//absl/log:log",
    ],
)

cc_library(
    name = "test_main",
    srcs = ["test_main.cc"],
    deps = [
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/log:initialize",
        "@com_google_absl//absl/log:log",
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
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log:log",
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
        "@com_github_open_source_parsers_jsoncpp//:json",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log:log",
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

cc_embed_data(
    name = "static_embed",
    srcs = [
        "main.html",
        "tbd_main_js.js",
    ],
    namespace = "tbd_server",
)
