load("@com_github_bcsgh_cc_embed_data//cc_embed_data:cc_embed_data.bzl", "cc_embed_data")

cc_binary(
    name = "server",
    srcs = ["server_main.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":server_lib",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log:initialize",
        "@abseil-cpp//absl/log:log",
    ],
)

cc_library(
    name = "server_lib",
    srcs = ["server.cc"],
    hdrs = ["server.h"],
    deps = [
        ":tbd",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/log:log",
        "@com_github_etr_libhttpserver//:libhttpserver",
    ],
)

cc_library(
    name = "tbd",
    srcs = [
        "tbd.cc",
        "tbd_impl.h",
    ],
    hdrs = ["tbd.h"],
    local_defines = select({
        "//:debug_build": ["APP_JS=server_ui_app_bundel_js"],
        "//conditions:default": ["APP_JS=server_ui_app_min_js"],
    }),
    deps = [
        ":static_embed",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/log:log",
        "@abseil-cpp//absl/strings",
        "@com_github_bcsgh_tbd//tbd:tbd_lib",
        # "@com_github_bcsgh_tbd//tbd:preamble",
        "@com_github_etr_libhttpserver//:libhttpserver",
        "@jsoncpp",
    ],
)

cc_test(
    name = "tbd_test",
    srcs = ["tbd_test.cc"],
    deps = [
        ":tbd",
        "@abseil-cpp//absl/memory",
        "@abseil-cpp//absl/strings",
        "@com_github_bcsgh_test_base//test_base:test_main",
        "@com_github_etr_libhttpserver//:libhttpserver",
        "@googletest//:gtest",
        "@jsoncpp",
    ],
)

cc_embed_data(
    name = "static_embed",
    srcs = [
        "//server/ui:main.html",
        "//server/ui:app_bin",
    ],
    namespace = "tbd_server",
)
