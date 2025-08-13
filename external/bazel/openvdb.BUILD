"""
Build file for OpenVDB library
"""
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "openvdb",
    hdrs = glob([
        "openvdb/**/*.h",
    ]),
    includes = ["."],
    copts = ["-std=c++17"],
)
