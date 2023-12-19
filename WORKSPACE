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
    name = "io_bazel_rules_docker",
    commit = "3040e1fd74659a52d1cdaff81359f57ee0e2bb41",  # current as of 2023/11/12
    remote = "https://github.com/bazelbuild/rules_docker.git",
    shallow_since = "1696279906 -0700",
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


load("@io_bazel_rules_docker//repositories:repositories.bzl", container_repositories = "repositories")
container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")
container_deps()

#############################################
load("@io_bazel_rules_docker//container:container.bzl", "container_pull")

container_pull(
    name = "ubuntu_20_04",
    registry = "index.docker.io",
    repository = "ubuntu",
    tag = "20.04",
)
