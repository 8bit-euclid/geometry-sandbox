#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

namespace geometry::mesh {

// Type traits and concepts
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

// Field value types
template<Numeric ValueT>
using ScalarField = ValueT;

template<Numeric ValueT, std::size_t Dim>
using VectorField = std::array<ValueT, Dim>;

template<Numeric ValueT, std::size_t Rows, std::size_t Cols = Rows>
using TensorField = std::array<std::array<ValueT, Cols>, Rows>;

// Interpolation methods
enum class InterpolationMethod {
    Nearest,
    Linear,
    Cubic,
    Spline
};

// Grid partitioning strategies
enum class PartitioningStrategy {
    None,
    Hilbert,
    Morton,
    Custom
};

// Background mesh types
enum class MeshType {
    CartesianGrid,
    QuadTree,
    OctTree,
    OpenVDB,
    Custom
};

/**
 * @brief Point class representing coordinates in N-dimensional space
 */
template<Numeric ValueT, std::size_t Dim>
class Point {
public:
    using value_type = ValueT;
    static constexpr std::size_t dimension = Dim;

    Point() = default;
    explicit Point(const std::array<ValueT, Dim>& coords) : coords_(coords) {}
    Point(std::initializer_list<ValueT> coords) {
        std::size_t i = 0;
        for (auto it = coords.begin(); it != coords.end() && i < Dim; ++it, ++i) {
            coords_[i] = *it;
        }
    }

    ValueT& operator[](std::size_t index) { return coords_[index]; }
    const ValueT& operator[](std::size_t index) const { return coords_[index]; }

    const std::array<ValueT, Dim>& coordinates() const { return coords_; }
    std::array<ValueT, Dim>& coordinates() { return coords_; }

    ValueT distance_to(const Point& other) const {
        ValueT sum = ValueT{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ValueT diff = coords_[i] - other.coords_[i];
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }
    
    ValueT squared_distance_to(const Point& other) const {
        ValueT sum = ValueT{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ValueT diff = coords_[i] - other.coords_[i];
            sum += diff * diff;
        }
        return sum;
    }

private:
    std::array<ValueT, Dim> coords_{};
};

/**
 * @brief Bounding box class for spatial queries
 */
template<Numeric ValueT, std::size_t Dim>
class BoundingBox {
public:
    using point_type = Point<ValueT, Dim>;

    BoundingBox() = default;
    BoundingBox(const point_type& min, const point_type& max) 
        : min_(min), max_(max) {}

    const point_type& min() const { return min_; }
    const point_type& max() const { return max_; }
    
    bool contains(const point_type& point) const {
        for (std::size_t i = 0; i < Dim; ++i) {
            if (point[i] < min_[i] || point[i] > max_[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool intersects(const BoundingBox& other) const {
        for (std::size_t i = 0; i < Dim; ++i) {
            if (max_[i] < other.min_[i] || min_[i] > other.max_[i]) {
                return false;
            }
        }
        return true;
    }
    
    BoundingBox intersection(const BoundingBox& other) const {
        BoundingBox result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.min_[i] = std::max(min_[i], other.min_[i]);
            result.max_[i] = std::min(max_[i], other.max_[i]);
        }
        return result;
    }
    
    BoundingBox union_with(const BoundingBox& other) const {
        BoundingBox result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.min_[i] = std::min(min_[i], other.min_[i]);
            result.max_[i] = std::max(max_[i], other.max_[i]);
        }
        return result;
    }

    ValueT volume() const {
        ValueT vol = ValueT{1};
        for (std::size_t i = 0; i < Dim; ++i) {
            vol *= (max_[i] - min_[i]);
        }
        return vol;
    }
    
    point_type center() const {
        point_type result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result[i] = (min_[i] + max_[i]) / ValueT{2};
        }
        return result;
    }
    
    std::array<ValueT, Dim> extent() const {
        std::array<ValueT, Dim> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result[i] = max_[i] - min_[i];
        }
        return result;
    }

private:
    point_type min_{}, max_{};
};

/**
 * @brief Abstract base class for all background mesh implementations
 * 
 * This base class contains only the common functionality that all mesh types
 * can reasonably implement, regardless of their underlying structure.
 */
template<Numeric ValueT, std::size_t Dim>
class BackgroundMesh {
public:
    using value_type = ValueT;
    using point_type = Point<ValueT, Dim>;
    using bbox_type = BoundingBox<ValueT, Dim>;
    using scalar_type = ScalarField<ValueT>;
    using vector_type = VectorField<ValueT, Dim>;
    
    static constexpr std::size_t dimension = Dim;

    virtual ~BackgroundMesh() = default;

    // Core mesh properties (all mesh types can provide these)
    virtual MeshType mesh_type() const = 0;
    virtual bbox_type bounding_box() const = 0;
    
    // Spatial queries (all mesh types support point queries and interpolation)
    virtual bool contains_point(const point_type& point) const = 0;
    
    // Field operations (all mesh types can store and interpolate fields)
    virtual std::optional<scalar_type> interpolate_scalar_field(
        const std::string& name, 
        const point_type& point,
        InterpolationMethod method = InterpolationMethod::Linear) const = 0;
    
    virtual std::optional<vector_type> interpolate_vector_field(
        const std::string& name,
        const point_type& point,
        InterpolationMethod method = InterpolationMethod::Linear) const = 0;

    // Field management
    virtual std::vector<std::string> list_scalar_fields() const = 0;
    virtual std::vector<std::string> list_vector_fields() const = 0;
    virtual std::vector<std::string> list_tensor_fields() const = 0;
    virtual void remove_field(const std::string& name) = 0;
    virtual void clear_all_fields() = 0;

    // I/O operations (all mesh types can be serialized)
    virtual void save_to_file(const std::string& filename) const = 0;
    virtual void load_from_file(const std::string& filename) = 0;
    
    // Serialization support
    virtual std::vector<std::uint8_t> serialize() const = 0;
    virtual void deserialize(const std::vector<std::uint8_t>& data) = 0;

    // Memory and performance
    virtual std::size_t memory_usage() const = 0;
    virtual void optimize() = 0;

protected:
    // Protected methods for derived classes
    virtual void on_field_added(const std::string& name) {}
    virtual void on_field_removed(const std::string& name) {}
};

/**
 * @brief Interface for mesh types that use discrete cells/elements
 * 
 * This interface is for mesh types that have a concept of discrete cells
 * that can be individually addressed and manipulated (cartesian grids, quadtrees, octrees).
 */
template<Numeric ValueT, std::size_t Dim>
class CellBasedMesh : public virtual BackgroundMesh<ValueT, Dim> {
public:
    using base_type = BackgroundMesh<ValueT, Dim>;
    using typename base_type::point_type;
    using typename base_type::bbox_type;
    using typename base_type::scalar_type;
    using typename base_type::vector_type;

    // Cell-specific properties
    virtual std::size_t cell_count() const = 0;
    virtual std::size_t max_depth() const = 0;
    virtual PartitioningStrategy partitioning_strategy() const = 0;

    // Cell-based spatial queries
    virtual std::vector<std::size_t> find_cells_in_region(const bbox_type& region) const = 0;
    virtual std::vector<std::size_t> find_nearest_cells(const point_type& point, std::size_t count = 1) const = 0;
    virtual bbox_type cell_bounds(std::size_t cell_id) const = 0;
    virtual point_type cell_center(std::size_t cell_id) const = 0;
    virtual std::size_t cell_level(std::size_t cell_id) const = 0;

    // Cell-based field operations
    virtual void set_scalar_field(const std::string& name, std::size_t cell_id, scalar_type value) = 0;
    virtual std::optional<scalar_type> get_scalar_field(const std::string& name, std::size_t cell_id) const = 0;
    
    virtual void set_vector_field(const std::string& name, std::size_t cell_id, const vector_type& value) = 0;
    virtual std::optional<vector_type> get_vector_field(const std::string& name, std::size_t cell_id) const = 0;

    // Cache management for cell-based operations
    virtual void clear_cache() = 0;

protected:
    virtual void on_mesh_structure_changed() {}
};

/**
 * @brief Interface for adaptive mesh types that support refinement/coarsening
 * 
 * This interface extends CellBasedMesh for mesh types that can dynamically
 * adapt their structure (quadtrees, octrees).
 */
template<Numeric ValueT, std::size_t Dim>
class AdaptiveMesh : public virtual CellBasedMesh<ValueT, Dim> {
public:
    using base_type = CellBasedMesh<ValueT, Dim>;
    using typename base_type::bbox_type;

    // Adaptive mesh operations
    virtual void refine_cell(std::size_t cell_id) = 0;
    virtual void refine_region(const bbox_type& region, std::size_t max_level) = 0;
    virtual void coarsen_cell(std::size_t cell_id) = 0;
    virtual void adapt_to_field(const std::string& field_name, ValueT threshold, std::size_t max_level) = 0;
    
    // Adaptive mesh queries
    virtual bool can_refine_cell(std::size_t cell_id) const = 0;
    virtual bool can_coarsen_cell(std::size_t cell_id) const = 0;
    virtual std::vector<std::size_t> get_children(std::size_t cell_id) const = 0;
    virtual std::optional<std::size_t> get_parent(std::size_t cell_id) const = 0;

protected:
    virtual void on_mesh_refined() {}
    virtual void on_mesh_coarsened() {}
};

/**
 * @brief Interface for structured grid mesh types
 * 
 * This interface is for regular/structured grids (cartesian grids)
 * that have a regular indexing scheme.
 */
template<Numeric ValueT, std::size_t Dim>
class StructuredMesh : public virtual CellBasedMesh<ValueT, Dim> {
public:
    using base_type = CellBasedMesh<ValueT, Dim>;
    using index_type = std::array<std::size_t, Dim>;
    
    // Bring base class methods into scope to avoid hiding warnings
    using base_type::set_scalar_field;
    using base_type::get_scalar_field;

    // Structured grid properties
    virtual std::array<std::size_t, Dim> resolution() const = 0;
    virtual std::array<ValueT, Dim> spacing() const = 0;
    
    // Structured indexing
    virtual std::size_t linear_index(const index_type& grid_index) const = 0;
    virtual index_type grid_index(std::size_t linear_index) const = 0;
    virtual index_type point_to_grid_index(const typename base_type::point_type& point) const = 0;
    
    // Structured field access (more efficient than cell_id based access)
    virtual void set_scalar_field(const std::string& name, const index_type& grid_index, ValueT value) = 0;
    virtual std::optional<ValueT> get_scalar_field(const std::string& name, const index_type& grid_index) const = 0;
};

/**
 * @brief Interface for sparse grid mesh types
 * 
 * This interface is for sparse data structures like OpenVDB grids
 * where only active voxels are stored.
 */
template<Numeric ValueT, std::size_t Dim>
class SparseGridMesh : public virtual BackgroundMesh<ValueT, Dim> {
public:
    using base_type = BackgroundMesh<ValueT, Dim>;
    using typename base_type::point_type;
    using typename base_type::bbox_type;
    using coord_type = std::array<int, Dim>;

    // Sparse grid properties
    virtual ValueT voxel_size() const = 0;
    virtual std::size_t active_voxel_count() const = 0;
    virtual bbox_type active_bounds() const = 0;

    // Sparse grid coordinate operations
    virtual coord_type world_to_index(const point_type& world_pos) const = 0;
    virtual point_type index_to_world(const coord_type& index) const = 0;
    
    // Active voxel queries
    virtual bool is_active(const coord_type& coord) const = 0;
    virtual void set_active(const coord_type& coord, bool active = true) = 0;
    virtual std::vector<coord_type> get_active_coordinates() const = 0;
    
    // Sparse field operations (only for active voxels)
    virtual void set_value(const coord_type& coord, ValueT value) = 0;
    virtual std::optional<ValueT> get_value(const coord_type& coord) const = 0;
    virtual ValueT get_value_or_default(const coord_type& coord, ValueT default_value = ValueT{}) const = 0;
    
    // Sparse grid specific operations
    virtual void fill_region(const bbox_type& region, ValueT value) = 0;
    virtual void clear_region(const bbox_type& region) = 0;
    
    // Level set operations (for implicit surfaces)
    virtual void union_with(const SparseGridMesh& other) = 0;
    virtual void intersect_with(const SparseGridMesh& other) = 0;
    virtual void difference_with(const SparseGridMesh& other) = 0;

protected:
    virtual void on_topology_changed() {}
};

// Factory functions for creating specific mesh types
namespace factory {

template<Numeric ValueT, std::size_t Dim>
std::unique_ptr<StructuredMesh<ValueT, Dim>> create_cartesian_grid(
    const BoundingBox<ValueT, Dim>& bounds, 
    const std::array<std::size_t, Dim>& resolution,
    PartitioningStrategy strategy = PartitioningStrategy::None);

template<Numeric ValueT, std::size_t Dim>
std::unique_ptr<AdaptiveMesh<ValueT, Dim>> create_adaptive_grid(
    const BoundingBox<ValueT, Dim>& bounds,
    std::size_t max_depth,
    MeshType type = (Dim == 2) ? MeshType::QuadTree : MeshType::OctTree);

template<Numeric ValueT, std::size_t Dim>
std::unique_ptr<SparseGridMesh<ValueT, Dim>> create_openvdb_grid(
    const BoundingBox<ValueT, Dim>& bounds,
    ValueT voxel_size);

} // namespace factory

// Convenience type aliases for different mesh types
using BackgroundMesh2D = BackgroundMesh<double, 2>;
using BackgroundMesh3D = BackgroundMesh<double, 3>;
using BackgroundMesh2Df = BackgroundMesh<float, 2>;
using BackgroundMesh3Df = BackgroundMesh<float, 3>;

using CellBasedMesh2D = CellBasedMesh<double, 2>;
using CellBasedMesh3D = CellBasedMesh<double, 3>;
using CellBasedMesh2Df = CellBasedMesh<float, 2>;
using CellBasedMesh3Df = CellBasedMesh<float, 3>;

using AdaptiveMesh2D = AdaptiveMesh<double, 2>;
using AdaptiveMesh3D = AdaptiveMesh<double, 3>;
using AdaptiveMesh2Df = AdaptiveMesh<float, 2>;
using AdaptiveMesh3Df = AdaptiveMesh<float, 3>;

using StructuredMesh2D = StructuredMesh<double, 2>;
using StructuredMesh3D = StructuredMesh<double, 3>;
using StructuredMesh2Df = StructuredMesh<float, 2>;
using StructuredMesh3Df = StructuredMesh<float, 3>;

using SparseGridMesh2D = SparseGridMesh<double, 2>;
using SparseGridMesh3D = SparseGridMesh<double, 3>;
using SparseGridMesh2Df = SparseGridMesh<float, 2>;
using SparseGridMesh3Df = SparseGridMesh<float, 3>;

using Point2D = Point<double, 2>;
using Point3D = Point<double, 3>;
using Point2Df = Point<float, 2>;
using Point3Df = Point<float, 3>;

using BoundingBox2D = BoundingBox<double, 2>;
using BoundingBox3D = BoundingBox<double, 3>;
using BoundingBox2Df = BoundingBox<float, 2>;
using BoundingBox3Df = BoundingBox<float, 3>;

} // namespace geometry::mesh
