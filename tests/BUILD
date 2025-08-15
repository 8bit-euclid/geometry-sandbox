load("@rules_cc//cc:defs.bzl", "cc_test")

# Separate test targets per external library for clearer isolation and faster
# incremental builds.

cc_test(
    name = "eigen_tests",
    size = "small",
    srcs = ["eigen_tests.cpp"],
    deps = [
        "@eigen",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "triangle_tests",
    size = "small",
    srcs = ["triangle_tests.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "@triangle",
    ],
)

cc_test(
    name = "cgal_tests",
    size = "small",
    srcs = ["cgal_tests.cpp"],
    deps = [
        "@boost//:boost_headers",
        "@cgal//:free",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "geogram_tests",
    srcs = ["geogram_tests.cpp"],
    deps = [
        "@geogram//:headers",
        "@googletest//:gtest_main",
    ],
)
