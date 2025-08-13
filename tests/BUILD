load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "integration_tests",
    srcs = ["integration_tests.cpp"],
    size = "small",
    copts = ["-std=c++23"],
    deps = [
        "@eigen//:eigen",
        "@libigl//:igl",
        "@triangle//:triangle",
        "@googletest//:gtest_main",
    ],
)
