# bazel build //docker:docker-compose
# (cd bazel-build/docker ; docker-compose up --detach )

version: "3.3"
services:
  tbd:
    image: tbd_http
    restart: always
    command:
      - "--http_port={PORT_HTTP}"
    ports:
      - "127.0.0.1:{PORT_HTTP}:{PORT_HTTP}"
