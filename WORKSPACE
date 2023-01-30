workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "rules_foreign_cc",
    commit = "c923238c6dc5a35c233a4acca28d90a0b1816836",  # current as of 2022/10/27
    remote = "https://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1666910343 +0100",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies([])

#############################################
git_repository(
    name = "io_bazel_rules_docker",
    commit = "e981b2a294a05a613fe3099d1b7d39e29479cb34",  # current as of 2022/10/25
    remote = "https://github.com/bazelbuild/rules_docker.git",
    shallow_since = "1665056147 +0100",
)

load("@io_bazel_rules_docker//repositories:repositories.bzl", container_repositories = "repositories")

container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")

container_deps()

#############################################
# https://github.com/bazelbuild/rules_closure
git_repository(
    name = "io_bazel_rules_closure",
    remote = "https://github.com/bazelbuild/rules_closure.git",
    tag = "0.11.0",
)

load("@io_bazel_rules_closure//closure:repositories.bzl", "rules_closure_dependencies", "rules_closure_toolchains")

rules_closure_dependencies()

rules_closure_toolchains()

#############################################
git_repository(
    name = "com_google_absl",
    commit = "827940038258b35a29279d8c65b4b4ca0a676f8d",  # current as of 2022/10/27
    remote = "https://github.com/abseil/abseil-cpp.git",
    shallow_since = "1666903548 -0700",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "3026483ae575e2de942db5e760cf95e973308dd5",  # current as of 2022/10/25
    remote = "https://github.com/google/googletest.git",
    shallow_since = "1666712359 -0700",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "4e3ad2fb78c2c7c127417e38431cfc9f91894819",  # current as of 2023/01/30
    remote = "https://github.com/bcsgh/tbd.git",
    shallow_since = "1675099224 -0800",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "3404db100ba321134ef63c6c872ce8dca6db024d",  # current as of 2023/01/29
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1675037889 -0800",
)

load("@bazel_rules//cc_embed_data:cc_embed_data_deps.bzl", cc_embed_data_deps = "get_deps")
load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "microhttpd")

#############################################
register_toolchains("@bazel_rules//parser:linux_flex_bison")

#############################################
eigen()

jsoncpp()

libhttpserver()

microhttpd()

cc_embed_data_deps()

load("@com_github_bcsgh_tbd//tbd:deps.bzl", tbd_deps = "get_deps")
tbd_deps()

#############################################
load("@io_bazel_rules_docker//container:container.bzl", "container_pull")

container_pull(
    name = "ubuntu_20_04",
    registry = "index.docker.io",
    repository = "ubuntu",
    tag = "20.04",
)
