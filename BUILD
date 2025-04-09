load("@npm//:defs.bzl", "npm_link_all_packages")

npm_link_all_packages(name = "node_modules")

config_setting(
    name = "debug_build",
    values = {"compilation_mode": "dbg"},
)
