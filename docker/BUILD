load("@io_bazel_rules_docker//container:container.bzl", "container_image")
load("@bazel_skylib//rules:expand_template.bzl", "expand_template")
load(":env.bzl", "env")

# bazel run //docker:tbd_http
# docker image tag local/docker:tbd_http tbd_http  # the rules don't
#
# See //docker/docker-compose.yml.tpl for pushing.

ENV = {
    "PORT_HTTP": "8080",
}

container_image(
    name = "tbd_http",
    base = "@ubuntu_20_04//image",
    entrypoint = env(ENV, [
      "/server",
      "--http_port={PORT_HTTP}"
    ]),
    files = ["//server"],
    repository = "local",
    tags = ["manual"],
)

expand_template(
    name = "docker-compose",
    template = "docker-compose.yml.tpl",
    out = "docker-compose.yml",
    substitutions = dict([
      ("{%s}" % k, v)
      for k,v in ENV.items()
    ]),
)
