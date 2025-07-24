#include <gtest/gtest.h>
#include <cmath>
#include "math_utils.h"

using namespace math_utils;

class MathUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_data = {1.0, 2.0, 3.0, 4.0, 5.0};
        empty_data = {};
    }
    
    std::vector<double> test_data;
    std::vector<double> empty_data;
    const double EPSILON = 1e-9;
};

// Statistics Tests
TEST_F(MathUtilsTest, StatisticsMean) {
    auto result = statistics::mean(test_data);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(*result, 3.0, EPSILON);
    
    auto empty_result = statistics::mean(empty_data);
    EXPECT_FALSE(empty_result.has_value());
}

TEST_F(MathUtilsTest, StatisticsMedian) {
    auto result = statistics::median(test_data);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(*result, 3.0, EPSILON);
    
    std::vector<double> even_data = {1.0, 2.0, 3.0, 4.0};
    auto even_result = statistics::median(even_data);
    ASSERT_TRUE(even_result.has_value());
    EXPECT_NEAR(*even_result, 2.5, EPSILON);
    
    auto empty_result = statistics::median(empty_data);
    EXPECT_FALSE(empty_result.has_value());
}

TEST_F(MathUtilsTest, StatisticsStandardDeviation) {
    auto result = statistics::standard_deviation(test_data, false); // Population std
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(*result, std::sqrt(2.0), EPSILON);
    
    auto sample_result = statistics::standard_deviation(test_data, true); // Sample std
    ASSERT_TRUE(sample_result.has_value());
    EXPECT_NEAR(*sample_result, std::sqrt(2.5), EPSILON);
    
    auto empty_result = statistics::standard_deviation(empty_data);
    EXPECT_FALSE(empty_result.has_value());
}

TEST_F(MathUtilsTest, StatisticsMinMax) {
    auto result = statistics::min_max(test_data);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(result->first, 1.0, EPSILON);
    EXPECT_NEAR(result->second, 5.0, EPSILON);
    
    auto empty_result = statistics::min_max(empty_data);
    EXPECT_FALSE(empty_result.has_value());
}

// Numerical Tests
TEST_F(MathUtilsTest, NumericalFactorial) {
    EXPECT_EQ(numerical::factorial(0), 1ULL);
    EXPECT_EQ(numerical::factorial(1), 1ULL);
    EXPECT_EQ(numerical::factorial(5), 120ULL);
    EXPECT_EQ(numerical::factorial(7), 5040ULL);
    
    EXPECT_THROW(numerical::factorial(-1), std::invalid_argument);
}

TEST_F(MathUtilsTest, NumericalGCD) {
    EXPECT_EQ(numerical::gcd(48, 18), 6);
    EXPECT_EQ(numerical::gcd(17, 13), 1);
    EXPECT_EQ(numerical::gcd(0, 5), 5);
    EXPECT_EQ(numerical::gcd(-12, 8), 4);
}

TEST_F(MathUtilsTest, NumericalLCM) {
    EXPECT_EQ(numerical::lcm(12, 15), 60);
    EXPECT_EQ(numerical::lcm(7, 13), 91);
    EXPECT_EQ(numerical::lcm(0, 5), 0);
    EXPECT_EQ(numerical::lcm(-6, 4), 12);
}

TEST_F(MathUtilsTest, NumericalIsPrime) {
    EXPECT_FALSE(numerical::is_prime(1));
    EXPECT_TRUE(numerical::is_prime(2));
    EXPECT_TRUE(numerical::is_prime(3));
    EXPECT_FALSE(numerical::is_prime(4));
    EXPECT_TRUE(numerical::is_prime(17));
    EXPECT_FALSE(numerical::is_prime(25));
    EXPECT_TRUE(numerical::is_prime(97));
}

TEST_F(MathUtilsTest, NumericalFibonacci) {
    auto fib = numerical::fibonacci_sequence(8);
    std::vector<unsigned long long> expected = {0, 1, 1, 2, 3, 5, 8, 13};
    EXPECT_EQ(fib, expected);
    
    auto empty_fib = numerical::fibonacci_sequence(0);
    EXPECT_TRUE(empty_fib.empty());
    
    auto single_fib = numerical::fibonacci_sequence(1);
    EXPECT_EQ(single_fib.size(), 1);
    EXPECT_EQ(single_fib[0], 0ULL);
}

TEST_F(MathUtilsTest, NumericalFastPower) {
    EXPECT_NEAR(numerical::fast_power(2.0, 0), 1.0, EPSILON);
    EXPECT_NEAR(numerical::fast_power(2.0, 3), 8.0, EPSILON);
    EXPECT_NEAR(numerical::fast_power(3.0, 4), 81.0, EPSILON);
    EXPECT_NEAR(numerical::fast_power(2.0, -3), 0.125, EPSILON);
    EXPECT_NEAR(numerical::fast_power(5.0, 2), 25.0, EPSILON);
}

// Interpolation Tests
TEST_F(MathUtilsTest, InterpolationLinear) {
    double result = interpolation::linear_interpolate(0, 0, 10, 100, 5);
    EXPECT_NEAR(result, 50.0, EPSILON);
    
    double result2 = interpolation::linear_interpolate(1, 2, 3, 6, 2);
    EXPECT_NEAR(result2, 4.0, EPSILON);
    
    // Test with same x values
    double result3 = interpolation::linear_interpolate(5, 10, 5, 20, 5);
    EXPECT_NEAR(result3, 10.0, EPSILON);
}

TEST_F(MathUtilsTest, InterpolationTrapezoidalIntegration) {
    // Integrate x^2 from 0 to 2 (exact answer is 8/3 ≈ 2.667)
    auto quadratic = [](double x) { return x * x; };
    double result = interpolation::trapezoidal_integration(quadratic, 0, 2, 1000);
    EXPECT_NEAR(result, 8.0/3.0, 0.01);
    
    // Integrate constant function
    auto constant = [](double x) { return 5.0; };
    double constant_result = interpolation::trapezoidal_integration(constant, 0, 3, 100);
    EXPECT_NEAR(constant_result, 15.0, EPSILON);
    
    EXPECT_THROW(interpolation::trapezoidal_integration(quadratic, 0, 2, 0), std::invalid_argument);
}

TEST_F(MathUtilsTest, InterpolationNewtonRaphson) {
    // Find root of x^2 - 4 = 0 (root should be 2)
    auto func = [](double x) { return x * x - 4.0; };
    auto derivative = [](double x) { return 2.0 * x; };
    
    auto result = interpolation::newton_raphson(func, derivative, 1.0);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(*result, 2.0, 1e-6);
    
    // Test with derivative close to zero
    auto flat_derivative = [](double x) { return 1e-12; };
    auto no_result = interpolation::newton_raphson(func, flat_derivative, 1.0);
    EXPECT_FALSE(no_result.has_value());
}

// Matrix Tests
TEST_F(MathUtilsTest, Matrix2x2Construction) {
    Matrix2x2 m;
    EXPECT_DOUBLE_EQ(m.a11, 0.0);
    EXPECT_DOUBLE_EQ(m.a12, 0.0);
    EXPECT_DOUBLE_EQ(m.a21, 0.0);
    EXPECT_DOUBLE_EQ(m.a22, 0.0);
    
    Matrix2x2 m2(1, 2, 3, 4);
    EXPECT_DOUBLE_EQ(m2.a11, 1.0);
    EXPECT_DOUBLE_EQ(m2.a12, 2.0);
    EXPECT_DOUBLE_EQ(m2.a21, 3.0);
    EXPECT_DOUBLE_EQ(m2.a22, 4.0);
}

TEST_F(MathUtilsTest, Matrix2x2Determinant) {
    Matrix2x2 m(1, 2, 3, 4);
    EXPECT_NEAR(m.determinant(), -2.0, EPSILON);
    
    Matrix2x2 identity(1, 0, 0, 1);
    EXPECT_NEAR(identity.determinant(), 1.0, EPSILON);
}

TEST_F(MathUtilsTest, Matrix2x2Inverse) {
    Matrix2x2 m(1, 2, 3, 4);
    auto inv = m.inverse();
    ASSERT_TRUE(inv.has_value());
    EXPECT_NEAR(inv->a11, -2.0, EPSILON);
    EXPECT_NEAR(inv->a12, 1.0, EPSILON);
    EXPECT_NEAR(inv->a21, 1.5, EPSILON);
    EXPECT_NEAR(inv->a22, -0.5, EPSILON);
    
    // Test singular matrix
    Matrix2x2 singular(1, 2, 2, 4);
    auto no_inv = singular.inverse();
    EXPECT_FALSE(no_inv.has_value());
}

TEST_F(MathUtilsTest, Matrix2x2Operations) {
    Matrix2x2 m1(1, 2, 3, 4);
    Matrix2x2 m2(5, 6, 7, 8);
    
    // Addition
    auto sum = m1 + m2;
    EXPECT_DOUBLE_EQ(sum.a11, 6.0);
    EXPECT_DOUBLE_EQ(sum.a12, 8.0);
    EXPECT_DOUBLE_EQ(sum.a21, 10.0);
    EXPECT_DOUBLE_EQ(sum.a22, 12.0);
    
    // Multiplication
    auto product = m1 * m2;
    EXPECT_DOUBLE_EQ(product.a11, 19.0);
    EXPECT_DOUBLE_EQ(product.a12, 22.0);
    EXPECT_DOUBLE_EQ(product.a21, 43.0);
    EXPECT_DOUBLE_EQ(product.a22, 50.0);
    
    // Scalar multiplication
    auto scaled = m1 * 2.0;
    EXPECT_DOUBLE_EQ(scaled.a11, 2.0);
    EXPECT_DOUBLE_EQ(scaled.a12, 4.0);
    EXPECT_DOUBLE_EQ(scaled.a21, 6.0);
    EXPECT_DOUBLE_EQ(scaled.a22, 8.0);
}
