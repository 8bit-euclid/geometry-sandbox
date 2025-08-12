"""
Build file for Eigen library
"""

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
