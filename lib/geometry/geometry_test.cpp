#include <gtest/gtest.h>
#include <cmath>
#include "geometry.h"

using namespace geometry;

class GeometryTest : public ::testing::Test {
protected:
    void SetUp() override {
        p1 = Point2D(0.0, 0.0);
        p2 = Point2D(3.0, 4.0);
        p3 = Point2D(6.0, 0.0);
    }
    
    Point2D p1, p2, p3;
    const double EPSILON = 1e-9;
};

// Point2D Tests
TEST_F(GeometryTest, Point2DConstruction) {
    Point2D origin;
    EXPECT_DOUBLE_EQ(origin.x, 0.0);
    EXPECT_DOUBLE_EQ(origin.y, 0.0);
    
    Point2D point(3.5, -2.1);
    EXPECT_DOUBLE_EQ(point.x, 3.5);
    EXPECT_DOUBLE_EQ(point.y, -2.1);
}

TEST_F(GeometryTest, Point2DDistance) {
    double distance = p1.distanceTo(p2);
    EXPECT_NEAR(distance, 5.0, EPSILON);
    
    double distance_self = p1.distanceTo(p1);
    EXPECT_NEAR(distance_self, 0.0, EPSILON);
}

TEST_F(GeometryTest, Point2DOperators) {
    Point2D sum = p1 + p2;
    EXPECT_DOUBLE_EQ(sum.x, 3.0);
    EXPECT_DOUBLE_EQ(sum.y, 4.0);
    
    Point2D diff = p2 - p1;
    EXPECT_DOUBLE_EQ(diff.x, 3.0);
    EXPECT_DOUBLE_EQ(diff.y, 4.0);
    
    Point2D scaled = p2 * 2.0;
    EXPECT_DOUBLE_EQ(scaled.x, 6.0);
    EXPECT_DOUBLE_EQ(scaled.y, 8.0);
}

// Circle Tests
TEST_F(GeometryTest, CircleConstruction) {
    Circle circle1(p1, 5.0);
    EXPECT_DOUBLE_EQ(circle1.center.x, 0.0);
    EXPECT_DOUBLE_EQ(circle1.center.y, 0.0);
    EXPECT_DOUBLE_EQ(circle1.radius, 5.0);
    
    Circle circle2(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(circle2.center.x, 1.0);
    EXPECT_DOUBLE_EQ(circle2.center.y, 2.0);
    EXPECT_DOUBLE_EQ(circle2.radius, 3.0);
}

TEST_F(GeometryTest, CircleNegativeRadius) {
    EXPECT_THROW(Circle(p1, -1.0), std::invalid_argument);
    EXPECT_THROW(Circle(0.0, 0.0, -5.0), std::invalid_argument);
}

TEST_F(GeometryTest, CircleArea) {
    Circle unit_circle(p1, 1.0);
    EXPECT_NEAR(unit_circle.area(), M_PI, EPSILON);
    
    Circle circle(p1, 2.0);
    EXPECT_NEAR(circle.area(), 4.0 * M_PI, EPSILON);
}

TEST_F(GeometryTest, CircleCircumference) {
    Circle unit_circle(p1, 1.0);
    EXPECT_NEAR(unit_circle.circumference(), 2.0 * M_PI, EPSILON);
    
    Circle circle(p1, 3.0);
    EXPECT_NEAR(circle.circumference(), 6.0 * M_PI, EPSILON);
}

TEST_F(GeometryTest, CircleContains) {
    Circle circle(p1, 5.0);
    
    EXPECT_TRUE(circle.contains(p1));  // Center point
    EXPECT_TRUE(circle.contains(p2));  // Point at distance 5.0
    EXPECT_FALSE(circle.contains(p3)); // Point at distance 6.0
    
    // Test boundary
    Point2D boundary_point(5.0, 0.0);
    EXPECT_TRUE(circle.contains(boundary_point));
}

// Utility function tests
TEST_F(GeometryTest, TriangleArea) {
    double area = utils::triangleArea(p1, p2, p3);
    EXPECT_NEAR(area, 12.0, EPSILON);
    
    // Degenerate triangle (collinear points)
    Point2D collinear(3.0, 0.0);
    double zero_area = utils::triangleArea(p1, collinear, p3);
    EXPECT_NEAR(zero_area, 0.0, EPSILON);
}

TEST_F(GeometryTest, Centroid) {
    std::vector<Point2D> points = {p1, p2, p3};
    Point2D center = utils::centroid(points);
    
    EXPECT_NEAR(center.x, 3.0, EPSILON);
    EXPECT_NEAR(center.y, 4.0/3.0, EPSILON);
}

TEST_F(GeometryTest, CentroidEmptyVector) {
    std::vector<Point2D> empty_points;
    EXPECT_THROW(utils::centroid(empty_points), std::invalid_argument);
}

TEST_F(GeometryTest, CentroidSinglePoint) {
    std::vector<Point2D> single_point = {p2};
    Point2D center = utils::centroid(single_point);
    
    EXPECT_DOUBLE_EQ(center.x, p2.x);
    EXPECT_DOUBLE_EQ(center.y, p2.y);
}
