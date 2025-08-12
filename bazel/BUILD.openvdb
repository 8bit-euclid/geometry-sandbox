"""
Build file for OpenVDB library
"""

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "openvdb",
    hdrs = glob([
        "openvdb/**/*.h",
    ]),
    includes = ["."],
    copts = ["-std=c++17"],
)
