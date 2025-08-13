load("@rules_cc//cc:defs.bzl", "cc_library")

# Boost headers only (no compiled libs) sufficient for current CGAL usage.
# If later you need compiled Boost libraries (filesystem, program_options, etc.)
# you'll either add builds here or switch to a fuller Bazelized Boost distribution.
cc_library(
    name = "boost_headers",
    hdrs = glob([
        "boost/**/*.hpp",
        "boost/**/*.h",
        "boost/**/*.ipp",
    ]),
    includes = ["."],
    visibility = ["//visibility:public"],
)
