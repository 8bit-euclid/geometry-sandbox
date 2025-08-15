"""
Build file for the Geogram library with explicit licensing and clear targets.

License
- Geogram is distributed under the BSD 3-Clause License (permissive).
- We mark it as a notice-based license in Bazel and export the upstream LICENSE.

Targets
- :headers      Header-only view for simple inclusion without linking.
- :third_party  Conservative subset of vendored 3rd-party code used by Geogram
                (excludes triangle, tetgen, lua, HLBFGS by default).
- :geogram      Core Geogram library (no gfx/vorpalib/exploragram) that depends
                on :third_party; defines GEOGRAM_WITH_PDEL and NL_WITH_AMGCL.

Notes
- Optional components (Triangle/TetGen/Lua/HLBFGS, geogram_gfx, vorpalib, exploragram) are
  excluded by default to keep licensing/binary size under control. If/when needed, add optional
  targets and make their licenses explicit.
"""

load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

# BSD 3-Clause is a permissive, notice-based license.
licenses([
    "notice",
])

# Export upstream license file for visibility in Bazel queries.
exports_files(["LICENSE"])

# Minimal, header-only view of Geogram. This keeps things simple and avoids
# accidental linkage against optional/compiled sub-libraries.
cc_library(
    name = "headers",
    hdrs = glob(
        [
            "src/lib/**/*.h",
            "src/lib/**/*.hpp",
            "src/lib/**/*.hh",
            "src/lib/**/*.inl",
        ],
        allow_empty = True,
    ),
    includes = [
        # Geogram headers are typically under src/lib/<module>/...
        "src/lib",
    ],
)

# Compiled targets (see "Targets" above for names)
# Exclusions by default to keep licenses/size under control:
# - triangle, tetgen, lua, HLBFGS
# - geogram_gfx, vorpalib, exploragram
# - tests/examples/docs
# Note: amgcl is header-only here.

GEOGRAM_THIRD_PARTY_EXCLUDES = [
    "src/lib/geogram/third_party/triangle/**",
    "src/lib/geogram/third_party/tetgen/**",
    "src/lib/geogram/third_party/lua/**",
    "src/lib/geogram/third_party/HLBFGS/**",
]

cc_library(
    name = "third_party",
    srcs = glob(
        include = [
            "src/lib/geogram/third_party/**/*.c",
            "src/lib/geogram/third_party/**/*.cc",
            "src/lib/geogram/third_party/**/*.cpp",
        ],
        allow_empty = True,
        exclude = GEOGRAM_THIRD_PARTY_EXCLUDES + [
            "**/CMakeLists.txt",
            "**/README*",
            "**/readme*",
            "**/LICENSE*",
            "**/license*",
            "**/doc/**",
            "**/docs/**",
            "**/test/**",
            "**/tests/**",
            "**/example/**",
            "**/examples/**",
        ],
    ),
    hdrs = glob(
        include = [
            "src/lib/geogram/third_party/**/*.h",
            "src/lib/geogram/third_party/**/*.hpp",
        ],
        allow_empty = True,
        exclude = GEOGRAM_THIRD_PARTY_EXCLUDES,
    ),
    copts = [
        "-std=c++17",
        # Tone down warnings in vendored third-party code
        "-Wno-deprecated",
        "-Wno-maybe-uninitialized",
        "-Wno-sign-compare",
        "-Wno-unused-parameter",
    ],
    includes = [
        "src/lib/geogram/third_party",
    ],
)

# Core Geogram library (without gfx/vorpalib/exploragram)
GEOGRAM_CORE_EXCLUDES = [
    "src/lib/geogram/third_party/**",  # compiled separately above
    "src/lib/geogram/geogram_gfx/**",
    "src/lib/vorpalib/**",
    "src/lib/exploragram/**",
    "src/bin/**",
    "src/tests/**",
    "src/examples/**",
    "tests/**",
    "doc/**",
    "**/CMakeLists.txt",
]

cc_library(
    name = "geogram",
    srcs = glob(
        include = [
            "src/lib/geogram/**/*.c",
            "src/lib/geogram/**/*.cc",
            "src/lib/geogram/**/*.cpp",
        ],
        allow_empty = True,
        exclude = GEOGRAM_CORE_EXCLUDES,
    ),
    hdrs = glob(
        include = [
            "src/lib/geogram/**/*.h",
            "src/lib/geogram/**/*.hpp",
        ],
        allow_empty = True,
        exclude = GEOGRAM_CORE_EXCLUDES,
    ),
    copts = [
        "-std=c++17",
        # Upstream enables these features by default
        "-DGEOGRAM_WITH_PDEL",
        "-DNL_WITH_AMGCL",
    ],
    includes = [
        # Public include so downstream can `#include <geogram/...>`
        "src/lib",
        # Private include for amgcl headers used in OpenNL
        "src/lib/geogram/third_party/amgcl",
    ],
    deps = [
        ":third_party",
    ],
)
