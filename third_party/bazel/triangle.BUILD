"""
Build file for Triangle library.
"""

load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

# Triangle (J. R. Shewchuk) has a custom license that is not OSI-approved.
# Commercial distribution is by arrangement with the author; research/private use is free.
# Treat as restricted to make the license constraints explicit to Bazel.
licenses([
    "restricted",
])

# Export the readme file which contains the license terms.
exports_files(["README"])

cc_library(
    name = "triangle",
    srcs = ["triangle.cpp"],
    hdrs = ["triangle.h"],
    copts = [
        "-std=c++17",
        "-DTRILIBRARY",
        "-DANSI_DECLARATORS",
        "-DNO_TIMER",
        # Suppress noisy warnings from 3rd-party Triangle source
        "-Wno-unused-parameter",
        "-Wno-unused-but-set-variable",
        "-Wno-uninitialized",  # Clang equivalent of -Wno-maybe-uninitialized
        "-Wno-sign-compare",
    ],
    defines = [
        "TRILIBRARY",
        "ANSI_DECLARATORS",
        "NO_TIMER",
    ],
)
