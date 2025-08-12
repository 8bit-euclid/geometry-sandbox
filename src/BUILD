load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    copts = ["-std=c++23"],
    deps = [
        "@eigen//:eigen",
        "@libigl//:igl",
    ],
    linkopts = [],
)
