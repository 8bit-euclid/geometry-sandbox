"""
Build file for Eigen library
"""
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "eigen",
    hdrs = glob([
        "Eigen/**",
        "unsupported/Eigen/**",
    ]),
    includes = ["."],
    copts = ["-std=c++17"],
)
