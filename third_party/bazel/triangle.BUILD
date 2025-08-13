"""
Build file for Triangle library
"""
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

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
        "-Wno-maybe-uninitialized",
        "-Wno-sign-compare",
    ],
    defines = [
        "TRILIBRARY",
        "ANSI_DECLARATORS",
        "NO_TIMER",
    ],
    visibility = ["//visibility:public"],
)
