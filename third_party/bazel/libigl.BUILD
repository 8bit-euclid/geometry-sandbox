"""
Build file for libigl library
"""
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "igl",
    # libigl is largely header-only; many .cpp files are meant to be included directly
    # inside headers (e.g. EPS.cpp) and compiling them separately causes duplicate
    # symbol / redefinition errors. We therefore expose them as headers so they are
    # only compiled in the including translation units.
    hdrs = glob([
        "include/igl/**/*.h",
        "include/igl/**/*.hpp",
        # Treat .cpp files as textual headers (do not compile separately)
        "include/igl/**/*.cpp",
    ]),
    includes = ["include"],
    copts = ["-std=c++17"],
    deps = ["@eigen"],
)
