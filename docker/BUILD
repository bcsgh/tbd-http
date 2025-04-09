load("@bazel_skylib//rules:expand_template.bzl", "expand_template")
load("@rules_oci//oci:defs.bzl", "oci_image", "oci_load")
load("@rules_pkg//:pkg.bzl", "pkg_tar")
load(":env.bzl", "env")

# bazel run //docker:tbd_http_local
#
# See //docker/docker-compose.yml.tpl for pushing.

IMAGE = "local/docker:tbd_http"

ENV = {
    "PORT_HTTP": "8080",
    "IMAGE": IMAGE,
    "NAME": "tbd",
}

pkg_tar(
    name = "tbd_http_tar",
    srcs = ["//server"],
)

oci_image(
    name = "tbd_http",
    base = "@ubuntu_22_04",
    entrypoint = env(ENV, [
      "/server",
      "--http_port={PORT_HTTP}",
    ]),
    tars = [":tbd_http_tar"],
)

oci_load(
    name = "tbd_http_local",
    image = ":tbd_http",
    repo_tags = [IMAGE],
)

#############################################
expand_template(
    name = "docker-compose",
    out = "docker-compose.yml",
    substitutions = dict([
      ("{%s}" % k, v)
      for k,v in ENV.items()
    ]),
    template = "docker-compose.yml.tpl",
)
