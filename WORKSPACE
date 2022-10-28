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
# Bazel Skylib.
http_archive(
    name = "bazel_skylib",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "44423acf159eade80e8daee0db8ad81246052c91",  # current as of 2022/10/27
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1653616779 -0700",
)

load("@bazel_rules//repositories:repositories.bzl", "eigen", "jsoncpp", "libhttpserver", "microhttpd")

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
# needed by com_github_glog_glog
git_repository(
    name = "com_github_gflags_gflags",
    commit = "a738fdf9338412f83ab3f26f31ac11ed3f3ec4bd",  # current as of 2022/10/25
    remote = "https://github.com/gflags/gflags.git",
    shallow_since = "1658955969 +0100",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "05fbc65278db1aa545ca5cb743c31bc717a48d0f",  # current as of 2022/10/25
    remote = "https://github.com/google/glog.git",
    shallow_since = "1663772402 +0200",
)

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
    commit = "873e3ca410fecc3882ed69e388accbf82469672a",  # current as of 2022/10/27
    remote = "https://github.com/bcsgh/tbd.git",
    shallow_since = "1666918747 -0700",
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
