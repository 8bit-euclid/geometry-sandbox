#include "geometry.h"
#include <cmath>
#include <stdexcept>

namespace geometry {

// Point2D implementation
Point2D::Point2D(double x, double y) : x(x), y(y) {}

double Point2D::distanceTo(const Point2D& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

Point2D Point2D::operator+(const Point2D& other) const {
    return Point2D(x + other.x, y + other.y);
}

Point2D Point2D::operator-(const Point2D& other) const {
    return Point2D(x - other.x, y - other.y);
}

Point2D Point2D::operator*(double scalar) const {
    return Point2D(x * scalar, y * scalar);
}

// Circle implementation
Circle::Circle(const Point2D& center, double radius) 
    : center(center), radius(radius) {
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
}

Circle::Circle(double x, double y, double radius) 
    : center(Point2D(x, y)), radius(radius) {
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
}

double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::circumference() const {
    return 2 * M_PI * radius;
}

bool Circle::contains(const Point2D& point) const {
    return center.distanceTo(point) <= radius;
}

// Utility functions implementation
namespace utils {

double triangleArea(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
    // Using the cross product formula: |AB × AC| / 2
    double ab_x = p2.x - p1.x;
    double ab_y = p2.y - p1.y;
    double ac_x = p3.x - p1.x;
    double ac_y = p3.y - p1.y;
    
    double cross_product = ab_x * ac_y - ab_y * ac_x;
    return std::abs(cross_product) / 2.0;
}

Point2D centroid(const std::vector<Point2D>& points) {
    if (points.empty()) {
        throw std::invalid_argument("Cannot calculate centroid of empty point set");
    }
    
    double sum_x = 0.0;
    double sum_y = 0.0;
    
    for (const auto& point : points) {
        sum_x += point.x;
        sum_y += point.y;
    }
    
    return Point2D(sum_x / points.size(), sum_y / points.size());
}

} // namespace utils

} // namespace geometry
