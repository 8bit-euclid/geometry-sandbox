"""
Module extension for non-module dependencies.
This handles third-party dependencies that may not have official Bazel modules.
"""

load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def _non_module_deps_impl(module_ctx):
    """Implementation of the non_module_deps module extension."""

    # Eigen library v3.4.0
    http_archive(
        name = "eigen",
        build_file = "//third_party/bazel:eigen.BUILD",
        strip_prefix = "eigen-3.4.0",
        urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
        integrity = "sha256-hYYIT3H5veVF7n+m0AKIsmSit6w2B7l05U0T5xYsHHI=",
    )

    # Boost v1.89.0
    http_archive(
        name = "boost",
        build_file = "//third_party/bazel:boost.BUILD",
        strip_prefix = "boost_1_89_0",
        urls = ["https://archives.boost.io/release/1.89.0/source/boost_1_89_0.tar.gz"],
        integrity = "sha256-nedY23VegzCgHZlbCiTQl5gEhACsJcA/xeqb42SxPJM=",
    )

    # CGAL v6.0.1 (header-only parts primarily; CGAL has optional 3rd party deps)
    http_archive(
        name = "cgal",
        build_file = "//third_party/bazel:cgal.BUILD",
        strip_prefix = "cgal-6.0.1",
        urls = [
            "https://github.com/CGAL/cgal/archive/refs/tags/v6.0.1.tar.gz",
        ],
        integrity = "sha256-F+6GdQuYsO/vNWtw8b7WtUGzVzvSkR9A/UAzjTVFJvU=",
    )

    # Geogram library v1.9.6
    new_git_repository(
        name = "geogram",
        remote = "https://github.com/BrunoLevy/geogram.git",
        build_file = "//third_party/bazel:geogram.BUILD",
        tag = "v1.9.6",
    )

    # OpenVDB library
    new_git_repository(
        name = "openvdb",
        remote = "https://github.com/AcademySoftwareFoundation/openvdb.git",
        build_file = "//third_party/bazel:openvdb.BUILD",
        tag = "v11.0.0",
    )

    # Triangle library (J. Shewchuk)
    http_archive(
        name = "triangle",
        build_file = "//third_party/bazel:triangle.BUILD",
        strip_prefix = "triangle-master",
        urls = [
            "https://github.com/libigl/triangle/archive/refs/heads/master.zip",
        ],
        integrity = "sha256-e0iDKs1rZYdea27xnXrf4aLiHUmyL2t3ZsrMmlwbX8M=",
    )

    return module_ctx.extension_metadata(
        root_module_direct_deps = ["eigen", "boost", "cgal", "geogram", "openvdb", "triangle"],
        root_module_direct_dev_deps = [],
    )

non_module_deps = module_extension(
    implementation = _non_module_deps_impl,
)
