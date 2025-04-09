load("@aspect_rules_esbuild//esbuild:defs.bzl", "esbuild")
load("@aspect_rules_terser//terser:defs.bzl", "terser")
load("@aspect_rules_ts//ts:defs.bzl", "ts_project")

PROJECT = "npm_typescript_app"

exports_files(["main.html"])

ts_project(
    name = "app",
    srcs = [
        "tbd.ts",
        "tbd_main.ts",
    ],
    declaration = True,
    tsconfig = "tsconfig.json",
    transpiler = "tsc",
    tsc = "@%s//:tsc" % PROJECT,
    tsc_worker = "@%s//:tsc_worker" % PROJECT,
    validator = "@%s//:validator" % PROJECT,
)

esbuild(
    name = "app_bundel",
    srcs = [":app"],
    tsconfig = "tsconfig.json",
    entry_point = "tbd_main.js",
    output = "app_bundel.js",
)

terser(
    name = "app_min",
    srcs = [":app_bundel"],
    args = ["--mangle"],
    config_file = ":terser.cfg.json",
    node_modules = "//:node_modules",
    sourcemap = False,
)

alias(
    name = "app_bin",
    actual = select({
        "//:debug_build": ":app_bundel.js",
        "//conditions:default": ":app_min",
    }),
    visibility = ["//visibility:public"],
)
