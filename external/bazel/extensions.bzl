"""
Module extension for non-module dependencies.
This handles external dependencies that don't have official Bazel modules.
"""
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

def _non_module_deps_impl(module_ctx):
    """Implementation of the non_module_deps module extension."""
    
    # OpenVDB library
    new_git_repository(
        name = "openvdb",
        remote = "https://github.com/AcademySoftwareFoundation/openvdb.git",
        build_file = "//external/bazel:BUILD.openvdb",
        tag = "v11.0.0",
    )

    # Eigen library
    http_archive(
        name = "eigen",
        build_file = "//external/bazel:BUILD.eigen",
        strip_prefix = "eigen-3.4.0",
        urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
        integrity = "sha256-hYYIT3H5veVF7n+m0AKIsmSit6w2B7l05U0T5xYsHHI=",
    )

    # Triangle library
    http_archive(
        name = "triangle",
        build_file = "//external/bazel:BUILD.triangle",
        strip_prefix = "triangle-master",
        urls = [
            "https://github.com/libigl/triangle/archive/refs/heads/master.zip",
        ],
        integrity = "sha256-e0iDKs1rZYdea27xnXrf4aLiHUmyL2t3ZsrMmlwbX8M=",
    )

    # Libigl library
    new_git_repository(
        name = "libigl",
        build_file = "//external/bazel:BUILD.libigl",
        remote = "https://github.com/libigl/libigl.git",
        tag = "v2.4.0",
    )

    return module_ctx.extension_metadata(
        root_module_direct_deps = ["openvdb", "eigen", "libigl", "triangle"],
        root_module_direct_dev_deps = [],
    )

non_module_deps = module_extension(
    implementation = _non_module_deps_impl,
)
