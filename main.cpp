#include <iostream>
#include <vector>
#include <format>
#include "lib/geometry/geometry.h"
#include "lib/math_utils/math_utils.h"

int main() {
    std::cout << "=== Geometry Sandbox Demo ===" << std::endl;
    
    // Create some points
    geometry::Point2D p1(0.0, 0.0);
    geometry::Point2D p2(3.0, 4.0);
    geometry::Point2D p3(6.0, 0.0);
    
    std::cout << std::format("Point 1: ({}, {})", p1.x, p1.y) << std::endl;
    std::cout << std::format("Point 2: ({}, {})", p2.x, p2.y) << std::endl;
    std::cout << std::format("Point 3: ({}, {})", p3.x, p3.y) << std::endl;
    
    // Calculate distances
    double dist_12 = p1.distanceTo(p2);
    double dist_23 = p2.distanceTo(p3);
    double dist_13 = p1.distanceTo(p3);
    
    std::cout << std::format("Distance from P1 to P2: {:.2f}", dist_12) << std::endl;
    std::cout << std::format("Distance from P2 to P3: {:.2f}", dist_23) << std::endl;
    std::cout << std::format("Distance from P1 to P3: {:.2f}", dist_13) << std::endl;
    
    // Point operations
    geometry::Point2D sum = p1 + p2;
    geometry::Point2D diff = p2 - p1;
    geometry::Point2D scaled = p2 * 2.0;
    
    std::cout << std::format("P1 + P2 = ({}, {})", sum.x, sum.y) << std::endl;
    std::cout << std::format("P2 - P1 = ({}, {})", diff.x, diff.y) << std::endl;
    std::cout << std::format("P2 * 2 = ({}, {})", scaled.x, scaled.y) << std::endl;
    
    // Triangle area
    double triangle_area = geometry::utils::triangleArea(p1, p2, p3);
    std::cout << std::format("Triangle area (P1, P2, P3): {:.2f}", triangle_area) << std::endl;
    
    // Centroid calculation
    std::vector<geometry::Point2D> points = {p1, p2, p3};
    geometry::Point2D center = geometry::utils::centroid(points);
    std::cout << std::format("Centroid of triangle: ({:.2f}, {:.2f})", center.x, center.y) << std::endl;
    
    // Circle operations
    geometry::Circle circle(center, 3.0);
    std::cout << std::format("Circle at ({:.2f}, {:.2f}) with radius {:.2f}", 
                            circle.center.x, circle.center.y, circle.radius) << std::endl;
    std::cout << std::format("Circle area: {:.2f}", circle.area()) << std::endl;
    std::cout << std::format("Circle circumference: {:.2f}", circle.circumference()) << std::endl;
    
    // Test point containment
    std::cout << std::format("Does circle contain P1? {}", 
                            circle.contains(p1) ? "Yes" : "No") << std::endl;
    std::cout << std::format("Does circle contain P2? {}", 
                            circle.contains(p2) ? "Yes" : "No") << std::endl;
    std::cout << std::format("Does circle contain P3? {}", 
                            circle.contains(p3) ? "Yes" : "No") << std::endl;
    
    // Create a larger circle that should contain all points
    geometry::Circle large_circle(center, 5.0);
    std::cout << std::format("Does larger circle (radius 5.0) contain all points? {}",
                            (large_circle.contains(p1) && large_circle.contains(p2) && large_circle.contains(p3))
                            ? "Yes" : "No") << std::endl;

    // Math utilities demonstration
    std::cout << "\n=== Math Utils Demo ===" << std::endl;

    // Statistics
    std::vector<double> data = {1.5, 2.3, 3.7, 2.1, 4.2, 3.8, 2.9, 3.1, 2.7, 3.5};
    auto mean_val = math_utils::statistics::mean(data);
    auto median_val = math_utils::statistics::median(data);
    auto std_dev = math_utils::statistics::standard_deviation(data);
    auto min_max_val = math_utils::statistics::min_max(data);

    if (mean_val) std::cout << std::format("Mean: {:.2f}", *mean_val) << std::endl;
    if (median_val) std::cout << std::format("Median: {:.2f}", *median_val) << std::endl;
    if (std_dev) std::cout << std::format("Standard deviation: {:.2f}", *std_dev) << std::endl;
    if (min_max_val) {
        std::cout << std::format("Min: {:.2f}, Max: {:.2f}", min_max_val->first, min_max_val->second) << std::endl;
    }

    // Numerical functions
    std::cout << std::format("Factorial of 7: {}", math_utils::numerical::factorial(7)) << std::endl;
    std::cout << std::format("GCD of 48 and 18: {}", math_utils::numerical::gcd(48, 18)) << std::endl;
    std::cout << std::format("LCM of 12 and 15: {}", math_utils::numerical::lcm(12, 15)) << std::endl;
    std::cout << std::format("Is 17 prime? {}", math_utils::numerical::is_prime(17) ? "Yes" : "No") << std::endl;
    std::cout << std::format("2^10 = {:.0f}", math_utils::numerical::fast_power(2.0, 10)) << std::endl;

    // Fibonacci sequence
    auto fib = math_utils::numerical::fibonacci_sequence(10);
    std::cout << "First 10 Fibonacci numbers: ";
    for (size_t i = 0; i < fib.size(); ++i) {
        std::cout << fib[i];
        if (i < fib.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    // Matrix operations
    math_utils::Matrix2x2 m1(2, 1, 3, 4);
    math_utils::Matrix2x2 m2(1, 2, 0, 1);
    auto m3 = m1 * m2;

    std::cout << std::format("Matrix multiplication result: [{:.0f}, {:.0f}; {:.0f}, {:.0f}]",
                            m3.a11, m3.a12, m3.a21, m3.a22) << std::endl;
    std::cout << std::format("Matrix determinant: {:.2f}", m1.determinant()) << std::endl;

    // Interpolation
    double interpolated = math_utils::interpolation::linear_interpolate(0, 0, 10, 100, 5);
    std::cout << std::format("Linear interpolation at x=5 between (0,0) and (10,100): {:.1f}", interpolated) << std::endl;

    // Numerical integration (integrate x^2 from 0 to 2)
    auto quadratic = [](double x) { return x * x; };
    double integral = math_utils::interpolation::trapezoidal_integration(quadratic, 0, 2, 1000);
    std::cout << std::format("Integral of x^2 from 0 to 2: {:.3f} (exact: 2.667)", integral) << std::endl;

    return 0;
}
