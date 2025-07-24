#pragma once

#include <vector>
#include <cmath>

namespace geometry {

/**
 * @brief A simple 2D point class
 */
class Point2D {
public:
    double x, y;
    
    Point2D(double x = 0.0, double y = 0.0);
    
    /**
     * @brief Calculate distance to another point
     * @param other The other point
     * @return Distance between this point and other
     */
    double distanceTo(const Point2D& other) const;
    
    /**
     * @brief Add two points (vector addition)
     * @param other The other point
     * @return New point representing the sum
     */
    Point2D operator+(const Point2D& other) const;
    
    /**
     * @brief Subtract two points (vector subtraction)
     * @param other The other point
     * @return New point representing the difference
     */
    Point2D operator-(const Point2D& other) const;
    
    /**
     * @brief Scale point by a scalar
     * @param scalar The scaling factor
     * @return New scaled point
     */
    Point2D operator*(double scalar) const;
};

/**
 * @brief A simple circle class
 */
class Circle {
public:
    Point2D center;
    double radius;
    
    Circle(const Point2D& center, double radius);
    Circle(double x, double y, double radius);
    
    /**
     * @brief Calculate the area of the circle
     * @return Area of the circle
     */
    double area() const;
    
    /**
     * @brief Calculate the circumference of the circle
     * @return Circumference of the circle
     */
    double circumference() const;
    
    /**
     * @brief Check if a point is inside the circle
     * @param point The point to check
     * @return True if point is inside or on the circle boundary
     */
    bool contains(const Point2D& point) const;
};

/**
 * @brief Utility functions for geometric calculations
 */
namespace utils {
    /**
     * @brief Calculate the area of a triangle given three points
     * @param p1 First point
     * @param p2 Second point
     * @param p3 Third point
     * @return Area of the triangle
     */
    double triangleArea(const Point2D& p1, const Point2D& p2, const Point2D& p3);
    
    /**
     * @brief Calculate the centroid of a set of points
     * @param points Vector of points
     * @return Centroid point
     */
    Point2D centroid(const std::vector<Point2D>& points);
}

} // namespace geometry
