workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_foreign_cc",
    commit = "e97f24e701cc33c0e4aa360d59b83eca0aa46111",  # current as of 2021/11/01
    remote = "https://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1634660901 +0000",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies([])

#############################################
git_repository(
    name = "bazel_rules",
    commit = "591a088101314c23c940cc30e4e4081d1338be29",  # current as of 2021/11/01
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1635825075 -0700",
)

load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "microhttpd")

#############################################
git_repository(
    name = "io_bazel_rules_docker",
    commit = "af2b074cc8f488e0dcec6230c63c2a7c34cf3dff",  # current as of 2021/11/01
    remote = "https://github.com/bazelbuild/rules_docker.git",
    shallow_since = "1633992564 -0700",
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
    commit = "17e7679fd9beb95277ccd0708056ba85363f892b",  # current as of 2021/11/01
    remote = "https://github.com/google/glog.git",
    shallow_since = "1635542045 +0200",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "022527c50e0e2bc937f9fa3c516e3e36cbba0845",  # current as of 2021/11/01
    remote = "https://github.com/abseil/abseil-cpp.git",
    shallow_since = "1635537114 -0400",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "16f637fbf4ffc3f7a01fa4eceb7906634565242f",  # current as of 2021/11/01
    remote = "https://github.com/google/googletest.git",
    shallow_since = "1634142500 -0400",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "6c28e66a8a2db8fba57ef6db8aad28660154778d",  # current as of 2021/11/01
    remote = "https://github.com/bcsgh/tbd.git",
    shallow_since = "1635826026 -0700",
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
