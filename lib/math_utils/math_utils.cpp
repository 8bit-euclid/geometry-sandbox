#include "math_utils.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cmath>

namespace math_utils {

// Statistics implementation
namespace statistics {

std::optional<double> mean(const std::vector<double>& data) {
    if (data.empty()) {
        return std::nullopt;
    }
    
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

std::optional<double> median(std::vector<double> data) {
    if (data.empty()) {
        return std::nullopt;
    }
    
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    
    if (n % 2 == 0) {
        return (data[n/2 - 1] + data[n/2]) / 2.0;
    } else {
        return data[n/2];
    }
}

std::optional<double> standard_deviation(const std::vector<double>& data, bool sample_std) {
    if (data.empty() || (sample_std && data.size() == 1)) {
        return std::nullopt;
    }
    
    auto mean_val = mean(data);
    if (!mean_val) {
        return std::nullopt;
    }
    
    double sum_squared_diff = 0.0;
    for (double value : data) {
        double diff = value - *mean_val;
        sum_squared_diff += diff * diff;
    }
    
    size_t denominator = sample_std ? data.size() - 1 : data.size();
    return std::sqrt(sum_squared_diff / denominator);
}

std::optional<std::pair<double, double>> min_max(const std::vector<double>& data) {
    if (data.empty()) {
        return std::nullopt;
    }
    
    auto [min_it, max_it] = std::minmax_element(data.begin(), data.end());
    return std::make_pair(*min_it, *max_it);
}

} // namespace statistics

// Numerical implementation
namespace numerical {

unsigned long long factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Factorial is not defined for negative numbers");
    }
    
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return std::abs(a * b) / gcd(a, b);
}

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

std::vector<unsigned long long> fibonacci_sequence(int n) {
    std::vector<unsigned long long> fib;
    if (n <= 0) return fib;
    
    fib.push_back(0);
    if (n == 1) return fib;
    
    fib.push_back(1);
    for (int i = 2; i < n; ++i) {
        fib.push_back(fib[i-1] + fib[i-2]);
    }
    return fib;
}

double fast_power(double base, int exponent) {
    if (exponent == 0) return 1.0;
    if (exponent < 0) return 1.0 / fast_power(base, -exponent);
    
    double result = 1.0;
    double current_power = base;
    
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= current_power;
        }
        current_power *= current_power;
        exponent /= 2;
    }
    return result;
}

} // namespace numerical

// Interpolation implementation
namespace interpolation {

double linear_interpolate(double x0, double y0, double x1, double y1, double x) {
    if (x1 == x0) {
        return y0; // Avoid division by zero
    }
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}

double trapezoidal_integration(const std::function<double(double)>& func, 
                             double a, double b, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of subdivisions must be positive");
    }
    
    double h = (b - a) / n;
    double sum = (func(a) + func(b)) / 2.0;
    
    for (int i = 1; i < n; ++i) {
        sum += func(a + i * h);
    }
    
    return sum * h;
}

std::optional<double> newton_raphson(const std::function<double(double)>& func,
                                   const std::function<double(double)>& derivative,
                                   double initial_guess,
                                   double tolerance,
                                   int max_iterations) {
    double x = initial_guess;
    
    for (int i = 0; i < max_iterations; ++i) {
        double fx = func(x);
        double fpx = derivative(x);
        
        if (std::abs(fpx) < tolerance) {
            return std::nullopt; // Derivative too small, might not converge
        }
        
        double x_new = x - fx / fpx;
        
        if (std::abs(x_new - x) < tolerance) {
            return x_new;
        }
        
        x = x_new;
    }
    
    return std::nullopt; // Did not converge
}

} // namespace interpolation

// Matrix2x2 implementation
Matrix2x2::Matrix2x2(double a11, double a12, double a21, double a22) 
    : a11(a11), a12(a12), a21(a21), a22(a22) {}

double Matrix2x2::determinant() const {
    return a11 * a22 - a12 * a21;
}

std::optional<Matrix2x2> Matrix2x2::inverse() const {
    double det = determinant();
    if (std::abs(det) < 1e-10) {
        return std::nullopt; // Matrix is singular
    }
    
    return Matrix2x2(a22 / det, -a12 / det, -a21 / det, a11 / det);
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
    return Matrix2x2(a11 + other.a11, a12 + other.a12, 
                     a21 + other.a21, a22 + other.a22);
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& other) const {
    return Matrix2x2(
        a11 * other.a11 + a12 * other.a21,
        a11 * other.a12 + a12 * other.a22,
        a21 * other.a11 + a22 * other.a21,
        a21 * other.a12 + a22 * other.a22
    );
}

Matrix2x2 Matrix2x2::operator*(double scalar) const {
    return Matrix2x2(a11 * scalar, a12 * scalar, a21 * scalar, a22 * scalar);
}

} // namespace math_utils
