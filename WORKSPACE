workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_foreign_cc",
    commit = "f76d9281bd7ae1f36179740ba20db3d58cd3b7a3",  # current as of 2021/12/17
    remote = "https://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1639486112 +0000",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies([])

#############################################
git_repository(
    name = "bazel_rules",
    commit = "69f0ea11bbea5166cf0e735cda098736c2386aca",  # current as of 2021/12/17
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1639764084 -0800",
)

load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "microhttpd")

#############################################
git_repository(
    name = "io_bazel_rules_docker",
    commit = "8a4f73fb29a64ba813087220b200f49a1ca10faa",  # current as of 2021/12/17
    remote = "https://github.com/bazelbuild/rules_docker.git",
    shallow_since = "1639679529 -0800",
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
# needed by com_github_glog_glog
git_repository(
    name = "com_github_gflags_gflags",
    commit = "827c769e5fc98e0f2a34c47cef953cc6328abced",  # current as of 2021/02/17
    remote = "https://github.com/gflags/gflags.git",
    shallow_since = "1604052972 +0000",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "9dc1107f88d3a1613d61b80040d83c1c1acbac3d",  # current as of 2021/12/17
    remote = "https://github.com/google/glog.git",
    shallow_since = "1639566274 +0100",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "52d41a9ec23e39db7e2cbce5c9449506cf2d3a5c",  # current as of 2021/12/17
    remote = "https://github.com/abseil/abseil-cpp.git",
    shallow_since = "1639580175 -0500",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "97a467571a0f615a4d96e79e4399c43221ca1232",  # current as of 2021/12/17
    remote = "https://github.com/google/googletest.git",
    shallow_since = "1639586168 -0800",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "a3d9fc595c29dfa26783d4dcd5cc99e1798712ed",  # current as of 2021/12/17
    remote = "https://github.com/bcsgh/tbd.git",
    shallow_since = "1639765987 -0800",
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
