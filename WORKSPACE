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
    commit = "827c769e5fc98e0f2a34c47cef953cc6328abced",  # current as of 2020/11/28
    shallow_since = "1604052972 +0000",
    remote = "git://github.com/gflags/gflags.git",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "c8f8135a5720aee7de8328b42e4c43f8aa2e60aa",  # current as of 2020/11/28
    shallow_since = "1601711556 +0200",
    remote = "git://github.com/google/glog.git",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "5d8fc9192245f0ea67094af57399d7931d6bd53f",  # current as of 2020/11/28
    shallow_since = "1606203805 -0500",
    remote = "git://github.com/abseil/abseil-cpp.git",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "abedeb83ecbfca3448205de85dcd7281d70f05b4",  # current as of 2020/11/28
    shallow_since = "1605677400 -0800",
    remote = "git://github.com/bcsgh/bazel_rules.git",
)

#############################################
git_repository(
    name = "com_github_bcsgh_tbd",
    commit = "115a59d5c465b218cfdff6fb45b3bdd8aedd6a26",  # current as of 2020/11/28
    shallow_since = "1606281544 -0800",
    remote = "git://github.com/bcsgh/tbd.git",
)

#############################################
new_git_repository(
    name = "eigen",
    build_file = "@//:extern/BUILD.eigen",
    commit = "68f69414f7d358deac4876ede5be15e990da496b",
    shallow_since = "1606531936 -0700",
    remote = "https://gitlab.com/libeigen/eigen.git",
)


#############################################
new_git_repository(
    name = "com_github_open_source_parsers_jsoncpp",
    commit = "8954092f0af9538f3cde47aceb459dbe4d6e2241",  # current as of 2020/11/28
    shallow_since = "1604698551 -0800",
    remote = "git://github.com/open-source-parsers/jsoncpp.git",
    build_file = "//:extern/BUILD.jsoncpp",
)

#############################################
new_git_repository(
    name = "com_github_etr_libhttpserver",
    build_file = "//:extern/BUILD.libhttpserver",
    commit = "7cb4eb8454ab936fcf2c54a61cc4d71a65f14680",  # current as of 2020/11/28
    shallow_since = "1605998057 -0800",
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
