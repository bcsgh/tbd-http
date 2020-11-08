workspace(name = "tbd_server")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "rules_foreign_cc",
    commit = "d54c78ab86b40770ee19f0949db9d74a831ab9f0",  # current as of 2020/11/07
    remote = "git://github.com/bazelbuild/rules_foreign_cc.git",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies([])

#############################################
# needed by com_github_glog_glog
git_repository(
    name = "com_github_gflags_gflags",
    commit = "827c769e5fc98e0f2a34c47cef953cc6328abced",  # current as of 2020/11/07
    shallow_since = "1604052972 +0000",
    remote = "git://github.com/gflags/gflags.git",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "c8f8135a5720aee7de8328b42e4c43f8aa2e60aa",  # current as of 2020/11/07
    shallow_since = "1601711556 +0200",
    remote = "git://github.com/google/glog.git",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "e96d49687d9c078f2d47356b6723c3b5715493f7",  # current as of 2020/11/07
    shallow_since = "1604603876 -0500",
    remote = "git://github.com/abseil/abseil-cpp.git",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "d2dcb62093486e3c920b6a37c3835ca33dc247bc",  # current as of 2020/11/07
    remote = "git://github.com/bcsgh/bazel_rules.git",
)

#############################################
new_git_repository(
    name = "com_github_etr_libhttpserver",
    build_file = "//:extern/BUILD.libhttpserver",
    commit = "c9746044d4b5c849f2b484087e110dd2a6e55308",  # current as of 2020/11/07
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
libmicrohttpd_VERSION = "libmicrohttpd-0.9.71"
HASH = {
    "libmicrohttpd-0.9.71": "e8f445e85faf727b89e9f9590daea4473ae00ead38b237cf1eda55172b89b182",
}

http_archive(
    name = "org_gnu_microhttpd",
    build_file = "//:extern/BUILD.microhttpd",
    sha256 = HASH[libmicrohttpd_VERSION],
    strip_prefix = libmicrohttpd_VERSION,
    urls = [
        "https://%s/gnu/libmicrohttpd/%s.tar.gz" % (domain, libmicrohttpd_VERSION)
        for domain in DOMAINS
    ],
)
