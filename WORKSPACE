workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_foreign_cc",
    commit = "6d1d16d3bb1c09a5154b483de902755ce1f05746",  # current as of 2021/07/01
    remote = "git://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1625108995 -0700",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies([])

#############################################
git_repository(
    name = "bazel_rules",
    commit = "f2344ebcc063a98444ea22b07eb795277543ddff",  # current as of 2021/07/01
    remote = "git://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1625189187 -0700",
)

load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "microhttpd")

#############################################
git_repository(
    name = "io_bazel_rules_docker",
    commit = "d3956263883f702eb9723cd8352f7a164e628277",  # current as of 2021/07/01
    remote = "git://github.com/bazelbuild/rules_docker.git",
    shallow_since = "1624456387 -0700",
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
    commit = "6e46c125e3718ce64570883e2ca558b3c853a125",  # current as of 2021/07/01
    remote = "git://github.com/google/glog.git",
    shallow_since = "1625119458 +0200",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "9a7e447c511dae7276ab65fde4d04f6ed52b39c9",  # current as of 2021/07/01
    remote = "git://github.com/abseil/abseil-cpp.git",
    shallow_since = "1624810227 -0400",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "4ec4cd23f486bf70efcc5d2caa40f24368f752e3",  # current as of 2021/07/01
    remote = "git://github.com/google/googletest.git",
    shallow_since = "1625074437 -0400",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "250d0a39f0a3da48c65568e88873a97d045889ce",  # current as of 2021/07/01
    remote = "git://github.com/bcsgh/tbd.git",
    shallow_since = "1625189901 -0700",
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
