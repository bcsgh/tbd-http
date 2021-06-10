workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_foreign_cc",
    commit = "2407938f22aaf09e5705e726037cf61e2003b291",  # current as of 2021/06/09
    remote = "git://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1623082150 -0700"
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies([])

#############################################
git_repository(
    name = "bazel_rules",
    commit = "7471bb0206a8620db466bdaada1e30f6f42064ee",  # current as of 2021/06/10
    remote = "git://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1623353151 -0700",
)

load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "microhttpd")

#############################################
git_repository(
    name = "io_bazel_rules_docker",
    commit = "1b75b778b457a827efe665bad8fb36ea4c6392b7",  # current as of 2021/06/10
    remote = "git://github.com/bazelbuild/rules_docker.git",
    shallow_since = "1623300313 -0700",
)

load("@io_bazel_rules_docker//repositories:repositories.bzl", container_repositories = "repositories")

container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")

container_deps()

#############################################
# https://github.com/bazelbuild/rules_closure
git_repository(
    name = "io_bazel_rules_closure",
    remote = "git://github.com/bazelbuild/rules_closure.git",
    tag = "0.11.0",
)

load("@io_bazel_rules_closure//closure:repositories.bzl", "rules_closure_dependencies", "rules_closure_toolchains")

rules_closure_dependencies()

rules_closure_toolchains()

#############################################
# needed by com_github_glog_glog
git_repository(
    name = "com_github_gflags_gflags",
    commit = "827c769e5fc98e0f2a34c47cef953cc6328abced",  # current as of 2021/02/17
    remote = "git://github.com/gflags/gflags.git",
    shallow_since = "1604052972 +0000",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "c1499f64a8fb2eae2de79ed7195cf248e706efc9",  # current as of 2021/06/09
    remote = "git://github.com/google/glog.git",
    shallow_since = "1623050920 +0200"
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "8f92175783c9685045c50f227e7c10f1cddb4d58",  # current as of 2021/06/10
    remote = "git://github.com/abseil/abseil-cpp.git",
    shallow_since = "1623281200 -0400",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "aa533abfd4232b01f9e57041d70114d5a77e6de0",  # current as of 2021/06/09
    remote = "git://github.com/google/googletest.git",
    shallow_since = "1623242719 -0400"
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "54105184f10460f8d2aa194f38943af7bdef62fc",  # current as of 2021/06/10
    remote = "git://github.com/bcsgh/tbd.git",
    shallow_since = "1623356214 -0700",
)

#############################################
eigen()

jsoncpp()

libhttpserver()

microhttpd()

#############################################
load("@io_bazel_rules_docker//container:container.bzl", "container_pull")

container_pull(
    name = "ubuntu_20_04",
    registry = "index.docker.io",
    repository = "ubuntu",
    tag = "20.04",
)
