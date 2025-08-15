"""
Build file for Boost library.
"""

# Boost headers only (no compiled libs) sufficient for current CGAL usage.
# If later you need compiled Boost libraries (filesystem, program_options, etc.)
# you'll either add builds here or switch to a fuller Bazelized Boost distribution.
load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

# Boost uses the Boost Software License 1.0, a permissive, notice-based license.
licenses([
    "notice",
])

# Export the upstream license file for visibility in Bazel.
exports_files(["LICENSE_1_0.txt"])

cc_library(
    name = "boost_headers",
    hdrs = glob([
        "boost/**/*.hpp",
        "boost/**/*.h",
        "boost/**/*.ipp",
    ]),
    includes = ["."],
)
