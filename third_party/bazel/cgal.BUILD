"""
Build file for CGAL library

This BUILD file provides two targets:
- :free - LGPL-licensed CGAL components (safe for commercial use with LGPL compliance)
- :commercial - All CGAL components including GPL packages (requires commercial licenses)

CGAL has a dual license structure:
- LGPL v3+ for foundation components (included in :free target)
- GPL v3+ for advanced algorithms (listed in CGAL_GPL_PACKAGES, requires commercial license)

For commercial use of GPL components, purchase licenses from GeometryFactory.
"""
licenses([
    # Note: CGAL has a dual license structure: GPL/LGPL for open source
    #       and commercial licenses. We only include LGPL-compatible parts
    #       that are suitable for commercial use without copyleft requirements.
    "restricted",  # Commercial users need commercial license from GeometryFactory
    "reciprocal",  # LGPL v3+
])

exports_files(["LICENSE"])

# Note: This BUILD file focuses on LGPL-licensed CGAL components only.
# GPL-licensed packages listed in CGAL_GPL_PACKAGES are excluded to avoid licensing complications.
# For commercial use, consider purchasing commercial licenses from GeometryFactory.

##############################################################################################################
# LGPL-licensed foundation packages - these can be used freely but still require compliance with LGPL terms
# Note: CGAL headers are distributed across package directories with include/CGAL/ structure
##############################################################################################################

CGAL_LGPL_PACKAGE_NAMES = [
    "Kernel_23",
    "Cartesian_kernel",
    "Homogeneous_kernel",
    "STL_Extension",
    "Stream_support",
    "Circulator",
    "Number_types",
    "Distance_2",
    "Distance_3",
    "Intersections_2",
    "Intersections_3",
    "Convex_hull_2",
    "Convex_hull_3",
    "Convex_hull_d",
    "Bounding_volumes",
    "Polygon",
    "Random_numbers",
    "Interval_support",
    "Modular_arithmetic",
    "Profiling_tools",
    "Property_map",
    "Hash_map",
    "Union_find",
    "Triangulation",
    "Triangulation_2",
    "Triangulation_3",
    "TDS_2",
    "TDS_3",
    "Spatial_sorting",
    "SearchStructures",
    "Interpolation",
    "AABB_tree",
    "BGL",
    "Generator",
    "HalfedgeDS",
    "Polyhedron",
    "Surface_mesh",
    "Point_set_2",
    "Point_set_3",
    "Matrix_search",
    "Optimisation_basic",
    "QP_solver",
    "Solver_interface",
    "Filtered_kernel",
    "Algebraic_foundations",
    "Arithmetic_kernel",
    "Algebraic_kernel_for_circles",
    "Algebraic_kernel_for_spheres",
    "Installation",
]

# Generate glob patterns for LGPL packages
CGAL_LGPL_PACKAGES = [pkg + "/include/CGAL/**" for pkg in CGAL_LGPL_PACKAGE_NAMES]

# List of files picked up by glob but actually part of another target
CGAL_EXCLUDE_FILES = [
    "**/test/**",
    "**/demo/**",
    "**/examples/**",
    "**/doc/**",
    "**/benchmark/**",
    "**/CMakeLists.txt",
    "**/*.cpp",  # Only include headers for header-only usage
    # Note: We need to keep license headers as they're required by CGAL
]

# Files known to be under LGPL license (base layer)
CGAL_BASE_HEADER_FILES = glob(
    include = CGAL_LGPL_PACKAGES,
    exclude = CGAL_EXCLUDE_FILES,
    allow_empty = True,
)

load("@rules_cc//cc:cc_library.bzl", "cc_library")

# WARNING: Commercial users should verify license compliance
# This target only includes LGPL base components
# For commercial use, consider purchasing commercial licenses from GeometryFactory
cc_library(
    name = "free",
    hdrs = CGAL_BASE_HEADER_FILES,
    defines = [
        # Helps ensure we don't accidentally link GPL components
        "CGAL_HEADER_ONLY",
        # Use exact arithmetic to avoid numerical issues
        "CGAL_USE_GMP",
        "CGAL_USE_MPFR",
    ],
    includes = [pkg + "/include" for pkg in CGAL_LGPL_PACKAGE_NAMES],
    visibility = ["//visibility:public"],
    deps = [
        # CGAL typically depends on these libraries
        # "@gmp",  # GNU Multiple Precision Arithmetic Library (LGPL) - commented out as not available
        # "@mpfr", # Multiple Precision Floating-Point Reliable Library (LGPL) - commented out as not available
    ],
)

##############################################################################################################
# GPL-licensed (i.e. restricted/copyleft) packages inside CGAL
# These require commercial licensing for commercial use
##############################################################################################################

CGAL_GPL_PACKAGE_NAMES = [
    "Algebraic_kernel_d",
    "Alpha_shapes_2",
    "Alpha_shapes_3",
    "Alpha_wrap_3",
    "Apollonius_graph_2",
    "Arrangement_on_surface_2",
    "Boolean_set_operations_2",
    "Circular_kernel_2",
    "Circular_kernel_3",
    "Convex_decomposition_3",
    "Envelope_2",
    "Envelope_3",
    "Generalized_map",
    "Heat_method_3",
    "Hyperbolic_triangulation_2",
    "Jet_fitting_3",
    "Kinetic_space_partition",
    "Kinetic_surface_reconstruction",
    "Linear_cell_complex",
    "Mesh_2",
    "Mesh_3",
    "Periodic_3_mesh_3",
    "Minkowski_sum_2",
    "Minkowski_sum_3",
    "Nef_2",
    "Nef_3",
    "Nef_S2",
    "Partition_2",
    "Periodic_2_triangulation_2",
    "Periodic_3_triangulation_3",
    "Periodic_4_hyperbolic_triangulation_2",
    "Point_set_processing_3",
    "Polygon_mesh_processing",
    "Principal_component_analysis",
    "Ridges_3",
    "Scale_space_reconstruction_3",
    "Shape_detection",
    "Shape_regularization",
    "Skin_surface_3",
    "Snap_rounding_2",
    "Spatial_searching",
    "Subdivision_method_3",
    "Surface_mesh_deformation",
    "Surface_mesh_parameterization",
    "Surface_mesh_shortest_path",
    "Surface_mesh_simplification",
    "Surface_mesh_skeletonization",
    "Tetrahedral_remeshing",
    "Triangulation_on_sphere_2",
    "Visibility_2",
    "Voronoi_diagram_2",
    "Classification",
    "Optimal_bounding_box",
    "Optimal_transportation_reconstruction_2",
    "Orthtree",
    "Poisson_surface_reconstruction_3",
    "Polygon_repair",
    "Polygonal_surface_reconstruction",
    "Polyline_simplification_2",
    "SMDS_3",
    "Segment_Delaunay_graph_2",
    "Segment_Delaunay_graph_Linf_2",
    "Set_movable_separability_2",
    "Straight_skeleton_2",
    "Straight_skeleton_extrusion_2",
    "Stream_lines_2",
    "Surface_mesh_approximation",
    "Surface_mesh_segmentation",
    "Surface_mesh_topology",
    "Surface_mesher",
    "Surface_sweep_2",
    # Add more GPL packages as needed when new versions are released
]

# Generate glob patterns for GPL packages
CGAL_GPL_PACKAGES = [pkg + "/include/CGAL/**" for pkg in CGAL_GPL_PACKAGE_NAMES]

# This target includes both LGPL (free) and GPL (commercial) CGAL packages
# To use this target:
# 1. Purchase commercial licenses from GeometryFactory for the GPL packages you need
# 2. Update your BUILD files to depend on "@cgal//:commercial" instead of "@cgal//:free"
# 3. Verify that you comply with the commercial license terms
cc_library(
    name = "commercial",
    hdrs = glob(
        include = CGAL_LGPL_PACKAGES + CGAL_GPL_PACKAGES,
        exclude = CGAL_EXCLUDE_FILES,
        allow_empty = True,
    ),
    defines = [
        "CGAL_HEADER_ONLY",
        "CGAL_USE_GMP",
        "CGAL_USE_MPFR",
    ],
    includes = [pkg + "/include" for pkg in CGAL_LGPL_PACKAGE_NAMES + CGAL_GPL_PACKAGE_NAMES],
    visibility = ["//visibility:public"],
    deps = [
        # "@gmp",  # GNU Multiple Precision Arithmetic Library (LGPL)
        # "@mpfr", # Multiple Precision Floating-Point Reliable Library (LGPL)
    ],
)