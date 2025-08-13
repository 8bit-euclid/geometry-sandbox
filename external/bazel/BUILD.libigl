"""
Build file for libigl library
"""

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "igl",
    hdrs = glob([
        "include/igl/**/*.h",
        "include/igl/**/*.cpp",
    ]),
    includes = ["include"],
    copts = ["-std=c++17"],
    deps = ["@eigen"],
)
