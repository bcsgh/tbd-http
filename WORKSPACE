workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "rules_foreign_cc",
    commit = "c923238c6dc5a35c233a4acca28d90a0b1816836",  # current as of 2022/10/27
    remote = "https://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1666910343 +0100",
)

#############################################
git_repository(
    name = "rules_oci",
    commit = "35a2baf586d2f30c332a566e71d0c8f0908acb10",  # current release (v1.4.3) as of 2023/12/18
    remote = "https://github.com/bazel-contrib/rules_oci.git",
    shallow_since = "1700591895 -0800",
)

git_repository(
    name = "rules_pkg",
    remote = "https://github.com/bazelbuild/rules_pkg.git",
    commit = "6c2e32553b740aec1d6fb540fb224487b5ce26a2",  # release (v0.9.1) 2023/05/02
    shallow_since = "1683040940 -0400",
)

#############################################
# https://github.com/bazelbuild/rules_closure
git_repository(
    name = "io_bazel_rules_closure",
    remote = "https://github.com/bazelbuild/rules_closure.git",
    tag = "0.11.0",
)

load("@io_bazel_rules_closure//closure:repositories.bzl", "rules_closure_dependencies", "rules_closure_toolchains")

rules_closure_dependencies(omit_bazel_skylib=True, omit_rules_cc=True)

rules_closure_toolchains()

#############################################
git_repository(
    name = "com_google_absl",
    commit = "483a2d59e649179ea9d9bc4d808f6c9d16646f9d",  # current as of 2023/11/12
    remote = "https://github.com/abseil/abseil-cpp.git",
    shallow_since = "1699496241 -0800",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "b10fad38c4026a29ea6561ab15fc4818170d1c10",  # current as of 2023/11/12
    remote = "https://github.com/google/googletest.git",
    shallow_since = "1698701593 -0700",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "c606c32f611abb33f0a7f71d0d2f087c8dbc1288",  # current as of 2023/11/16
    remote = "https://github.com/bcsgh/tbd.git",
    shallow_since = "1700185410 -0800",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "e282d53e3234a6b2260efc3cd4e6426e1a9ed328",  # current as of 2023/12/06
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1701907650 -0800",
)

load("@bazel_rules//cc_embed_data:cc_embed_data_deps.bzl", cc_embed_data_deps = "get_deps")
load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "load_skylib", "microhttpd", "load_rules_cc")

#############################################
register_toolchains("@bazel_rules//parser:linux_flex_bison")

#############################################
eigen()

jsoncpp()

libhttpserver()

load_rules_cc()

load_skylib()

microhttpd()

cc_embed_data_deps()

load("@com_github_bcsgh_tbd//tbd:deps.bzl", tbd_deps = "get_deps")
tbd_deps()

#############################################
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies([])

#############################################
load("@rules_oci//oci:dependencies.bzl", "rules_oci_dependencies")
rules_oci_dependencies()

load("@rules_oci//oci:repositories.bzl", "LATEST_CRANE_VERSION", "oci_register_toolchains")

oci_register_toolchains(
    name = "oci",
    crane_version = LATEST_CRANE_VERSION,
)

#############################################
load("@rules_oci//oci:pull.bzl", "oci_pull")

oci_pull(
    name = "ubuntu_20_04",
    # https://gallery.ecr.aws/docker/library/ubuntu
    digest = "sha256:218bb51abbd1864df8be26166f847547b3851a89999ca7bfceb85ca9b5d2e95d",
    image = "public.ecr.aws/docker/library/ubuntu",#:20.04",
)
