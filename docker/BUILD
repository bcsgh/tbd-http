load("@io_bazel_rules_docker//container:container.bzl", "container_image")

# bazel run //docker:tbd_http
# docker image tag local/docker:tbd_http tbd_http  # the rules don't
container_image(
    name = "tbd_http",
    base = "@ubuntu_20_04//image",
    entrypoint = ["/server"],
    repository = "local",
    files = ["//server:server"],
)