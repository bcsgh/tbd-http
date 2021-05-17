workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "rules_foreign_cc",
    commit = "b136e6c52da63da300b0f588c8a214d97b0d15cd",  # current as of 2021/05/06
    remote = "git://github.com/bazelbuild/rules_foreign_cc.git",
    shallow_since = "1620262045 -0700",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies([])

#############################################
git_repository(
    name = "bazel_rules",
    commit = "51c9ca0ea5306cbc06f8f1113cc42df7068adbe9",  # current as of 2021/05/17
    remote = "git://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1621268673 -0700",
)

load("@bazel_rules//repositories:repositories.bzl", "jsoncpp", "libhttpserver", "microhttpd")

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
    commit = "e370cd51661892cb3bd5ba80541d0739c0d219b4",  # current as of 2021/02/17
    remote = "git://github.com/google/glog.git",
    shallow_since = "1613215412 +0100",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "143a27800eb35f4568b9be51647726281916aac9",  # current as of 2021/02/17
    remote = "git://github.com/abseil/abseil-cpp.git",
    shallow_since = "1613186346 -0500",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "609281088cfefc76f9d0ce82e1ff6c30cc3591e5",  # current as of 2021/02/17
    remote = "git://github.com/google/googletest.git",
    shallow_since = "1613065794 -0500",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "5186cc910d475bd1a1894076b1b86ab8ccd7c302",  # current as of 2020/12/02
    remote = "git://github.com/bcsgh/tbd.git",
    shallow_since = "1617327006 -0700",
)

#############################################
new_git_repository(
    name = "eigen",
    build_file = "@//:extern/BUILD.eigen",
    commit = "9b51dc7972c9f64727e9c8e8db0c60aaf9aae532",  # current as of 2021/02/17
    remote = "https://gitlab.com/libeigen/eigen.git",
    shallow_since = "1613584163 +0000",
)

#############################################
jsoncpp()

libhttpserver()

microhttpd()
