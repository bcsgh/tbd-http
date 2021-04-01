workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "rules_foreign_cc",
    commit = "d54c78ab86b40770ee19f0949db9d74a831ab9f0",  # current as of 2020/11/28
    shallow_since = "1603722361 +0100",
    remote = "git://github.com/bazelbuild/rules_foreign_cc.git",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies([])

# https://github.com/bazelbuild/rules_closure
git_repository(
    name = "io_bazel_rules_closure",
    tag = "0.11.0",
    remote = "git://github.com/bazelbuild/rules_closure.git",
)

load("@io_bazel_rules_closure//closure:repositories.bzl", "rules_closure_dependencies", "rules_closure_toolchains")
rules_closure_dependencies()
rules_closure_toolchains()

#############################################
# needed by com_github_glog_glog
git_repository(
    name = "com_github_gflags_gflags",
    commit = "827c769e5fc98e0f2a34c47cef953cc6328abced",  # current as of 2021/02/17
    shallow_since = "1604052972 +0000",
    remote = "git://github.com/gflags/gflags.git",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "e370cd51661892cb3bd5ba80541d0739c0d219b4",  # current as of 2021/02/17
    shallow_since = "1613215412 +0100",
    remote = "git://github.com/google/glog.git",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "143a27800eb35f4568b9be51647726281916aac9",  # current as of 2021/02/17
    shallow_since = "1613186346 -0500",
    remote = "git://github.com/abseil/abseil-cpp.git",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "609281088cfefc76f9d0ce82e1ff6c30cc3591e5",  # current as of 2021/02/17
    shallow_since = "1613065794 -0500",
    remote = "git://github.com/google/googletest.git",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "7bedda9b65feaa1efab8d9cd77c4c1a8b667b042",  # current as of 2021/02/17
    shallow_since = "1606611670 -0800",
    remote = "git://github.com/bcsgh/bazel_rules.git",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "866ef2a0da74476129912d13ce21bff6ab177c20",  # current as of 2020/12/02
    shallow_since = "1606974250 -0800",
    remote = "git://github.com/bcsgh/tbd.git",
)

#############################################
new_git_repository(
    name = "eigen",
    build_file = "@//:extern/BUILD.eigen",
    commit = "9b51dc7972c9f64727e9c8e8db0c60aaf9aae532",  # current as of 2021/02/17
    shallow_since = "1613584163 +0000",
    remote = "https://gitlab.com/libeigen/eigen.git",
)


#############################################
new_git_repository(
    name = "com_github_open_source_parsers_jsoncpp",
    commit = "fda274ddd297a53110d43189c2d69fee8f748da9",  # current as of 2021/02/17
    shallow_since = "1612932637 -0500",
    remote = "git://github.com/open-source-parsers/jsoncpp.git",
    build_file = "//:extern/BUILD.jsoncpp",
)

#############################################
new_git_repository(
    name = "com_github_etr_libhttpserver",
    build_file = "//:extern/BUILD.libhttpserver",
    commit = "ec973dc883b0d33f81c7f69b66dd5770ba14e695",  # current as of 2021/02/17
    shallow_since = "1607724471 -0800",
    remote = "git://github.com/etr/libhttpserver.git"
)

#############################################
DOMAINS = [
    # GNU mirrors
    "ftp.wayne.edu",
    "mirrors.tripadvisor.com",
    "mirrors.kernel.org",
    "mirror.clarkson.edu",
    "mirrors.syringanetworks.net",
    "mirror.us-midwest-1.nexcess.net",
    "mirrors.ocf.berkeley.edu",
    # primary
    "ftp.gnu.org",
]
LIBMICROHTTPD_VERSION = "libmicrohttpd-0.9.71"
HASH = {
    "libmicrohttpd-0.9.71": "e8f445e85faf727b89e9f9590daea4473ae00ead38b237cf1eda55172b89b182",
}

http_archive(
    name = "org_gnu_microhttpd",
    build_file = "//:extern/BUILD.microhttpd",
    sha256 = HASH[LIBMICROHTTPD_VERSION],
    strip_prefix = LIBMICROHTTPD_VERSION,
    urls = [
        "https://%s/gnu/libmicrohttpd/%s.tar.gz" % (domain, LIBMICROHTTPD_VERSION)
        for domain in DOMAINS
    ],
)
