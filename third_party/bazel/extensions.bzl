"""
Module extension for non-module dependencies.
This handles third-party dependencies that may not have official Bazel modules.
"""
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

def _non_module_deps_impl(module_ctx):
    """Implementation of the non_module_deps module extension."""
    
    # Eigen library
    http_archive(
        name = "eigen",
        build_file = "//third_party/bazel:eigen.BUILD",
        strip_prefix = "eigen-3.4.0",
        urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
        integrity = "sha256-hYYIT3H5veVF7n+m0AKIsmSit6w2B7l05U0T5xYsHHI=",
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

    # Boost 1.86.0
    http_archive(
        name = "boost",
        build_file = "//third_party/bazel:boost.BUILD",
        strip_prefix = "boost_1_86_0",
        urls = ["https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz"],
        integrity = "sha256-JXXnT/w+8c0Lq6wsHui9tXgqDuZysZEtpA5bS1kcoB8=",
    )

    # CGAL 6.0.1 (header-only parts primarily; CGAL has optional 3rd party deps)
    http_archive(
        name = "cgal",
        build_file = "//third_party/bazel:cgal.BUILD",
        strip_prefix = "cgal-6.0.1",
        urls = [
            "https://github.com/CGAL/cgal/archive/refs/tags/v6.0.1.tar.gz",
        ],
        integrity = "sha256-F+6GdQuYsO/vNWtw8b7WtUGzVzvSkR9A/UAzjTVFJvU=",
    )

    # OpenVDB library
    new_git_repository(
        name = "openvdb",
        remote = "https://github.com/AcademySoftwareFoundation/openvdb.git",
        build_file = "//third_party/bazel:openvdb.BUILD",
        tag = "v11.0.0",
    )

    return module_ctx.extension_metadata(
    root_module_direct_deps = ["eigen", "triangle", "boost", "cgal", "openvdb"],
        root_module_direct_dev_deps = [],
    )

non_module_deps = module_extension(
    implementation = _non_module_deps_impl,
)
