load("@rules_cc//cc:defs.bzl", "cc_test")

# Separate test targets per external library for clearer isolation and faster
# incremental builds.

cc_test(
    name = "eigen_tests",
    srcs = ["eigen_tests.cpp"],
    size = "small",
    copts = ["-std=c++23"],
    deps = [
        "@eigen//:eigen",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "libigl_tests",
    srcs = ["libigl_tests.cpp"],
    size = "small",
    copts = ["-std=c++23"],
    deps = [
        "@eigen//:eigen",  # libigl headers depend on Eigen
        "@libigl//:igl",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "triangle_tests",
    srcs = ["triangle_tests.cpp"],
    size = "small",
    copts = ["-std=c++23"],
    deps = [
        "@triangle//:triangle",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "cgal_tests",
    srcs = ["cgal_tests.cpp"],
    size = "small",
    copts = ["-std=c++23"],
    deps = [
        "@cgal//:cgal",
        "@boost//:boost_headers",
        "@googletest//:gtest_main",
    ],
)
