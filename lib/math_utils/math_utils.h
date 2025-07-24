#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include <optional>

namespace math_utils {

/**
 * @brief Statistical operations for numerical data
 */
namespace statistics {
    /**
     * @brief Calculate the mean (average) of a dataset
     * @param data Vector of numerical values
     * @return Mean value, or nullopt if data is empty
     */
    std::optional<double> mean(const std::vector<double>& data);
    
    /**
     * @brief Calculate the median of a dataset
     * @param data Vector of numerical values
     * @return Median value, or nullopt if data is empty
     */
    std::optional<double> median(std::vector<double> data);
    
    /**
     * @brief Calculate the standard deviation of a dataset
     * @param data Vector of numerical values
     * @param sample_std If true, calculates sample standard deviation (n-1), otherwise population (n)
     * @return Standard deviation, or nullopt if data is empty or has only one element for sample_std
     */
    std::optional<double> standard_deviation(const std::vector<double>& data, bool sample_std = true);
    
    /**
     * @brief Find the minimum and maximum values in a dataset
     * @param data Vector of numerical values
     * @return Pair of (min, max), or nullopt if data is empty
     */
    std::optional<std::pair<double, double>> min_max(const std::vector<double>& data);
}

/**
 * @brief Numerical analysis and mathematical functions
 */
namespace numerical {
    /**
     * @brief Calculate factorial of a non-negative integer
     * @param n Non-negative integer
     * @return Factorial of n
     * @throws std::invalid_argument if n is negative
     */
    unsigned long long factorial(int n);
    
    /**
     * @brief Calculate the greatest common divisor of two integers
     * @param a First integer
     * @param b Second integer
     * @return GCD of a and b
     */
    int gcd(int a, int b);
    
    /**
     * @brief Calculate the least common multiple of two integers
     * @param a First integer
     * @param b Second integer
     * @return LCM of a and b
     */
    int lcm(int a, int b);
    
    /**
     * @brief Check if a number is prime
     * @param n Integer to check
     * @return True if n is prime, false otherwise
     */
    bool is_prime(int n);
    
    /**
     * @brief Generate Fibonacci sequence up to n terms
     * @param n Number of terms to generate
     * @return Vector containing the Fibonacci sequence
     */
    std::vector<unsigned long long> fibonacci_sequence(int n);
    
    /**
     * @brief Calculate power using fast exponentiation
     * @param base Base value
     * @param exponent Non-negative exponent
     * @return base^exponent
     */
    double fast_power(double base, int exponent);
}

/**
 * @brief Interpolation and approximation methods
 */
namespace interpolation {
    /**
     * @brief Linear interpolation between two points
     * @param x0 First x coordinate
     * @param y0 First y coordinate
     * @param x1 Second x coordinate
     * @param y1 Second y coordinate
     * @param x Target x coordinate
     * @return Interpolated y value at x
     */
    double linear_interpolate(double x0, double y0, double x1, double y1, double x);
    
    /**
     * @brief Numerical integration using the trapezoidal rule
     * @param func Function to integrate
     * @param a Lower bound
     * @param b Upper bound
     * @param n Number of subdivisions
     * @return Approximate integral value
     */
    double trapezoidal_integration(const std::function<double(double)>& func, 
                                 double a, double b, int n = 1000);
    
    /**
     * @brief Find root using Newton-Raphson method
     * @param func Function for which to find root
     * @param derivative Derivative of the function
     * @param initial_guess Initial guess for the root
     * @param tolerance Convergence tolerance
     * @param max_iterations Maximum number of iterations
     * @return Root if found, nullopt if not converged
     */
    std::optional<double> newton_raphson(const std::function<double(double)>& func,
                                       const std::function<double(double)>& derivative,
                                       double initial_guess,
                                       double tolerance = 1e-10,
                                       int max_iterations = 100);
}

/**
 * @brief Matrix operations for small matrices
 */
class Matrix2x2 {
public:
    double a11, a12, a21, a22;
    
    Matrix2x2(double a11 = 0, double a12 = 0, double a21 = 0, double a22 = 0);
    
    /**
     * @brief Calculate determinant of the matrix
     * @return Determinant value
     */
    double determinant() const;
    
    /**
     * @brief Calculate inverse of the matrix
     * @return Inverse matrix, or nullopt if matrix is singular
     */
    std::optional<Matrix2x2> inverse() const;
    
    /**
     * @brief Matrix addition
     */
    Matrix2x2 operator+(const Matrix2x2& other) const;
    
    /**
     * @brief Matrix multiplication
     */
    Matrix2x2 operator*(const Matrix2x2& other) const;
    
    /**
     * @brief Scalar multiplication
     */
    Matrix2x2 operator*(double scalar) const;
};

} // namespace math_utils
