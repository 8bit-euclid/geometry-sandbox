# Geometry Sandbox

A C++ geometry library and sandbox for experimenting with geometric algorithms and data structures.

## Architecture

This project follows a modular architecture where each library is self-contained within its own directory:

- **Self-contained libraries**: Each library (`geometry`, `math_utils`) has its own directory containing source code, headers, tests, and build configuration
- **Co-located tests**: Unit tests are placed alongside the code they test, making it easier to maintain and discover tests
- **Independent building**: Each library can be built and tested independently
- **Clear dependencies**: The modular structure makes dependencies between components explicit

## Project Structure

```
geometry-sandbox/
├── main.cpp              # Main application demonstrating both libraries
├── lib/                  # Libraries directory
│   ├── geometry/         # Geometry library
│   │   ├── geometry.h    # Geometry library header
│   │   ├── geometry.cpp  # Geometry library implementation
│   │   ├── geometry_test.cpp # GoogleTest unit tests for geometry
│   │   └── BUILD.bazel   # Bazel build configuration for geometry
│   └── math_utils/       # Math utilities library
│       ├── math_utils.h  # Math utilities library header
│       ├── math_utils.cpp # Math utilities library implementation
│       ├── math_utils_test.cpp # GoogleTest unit tests for math utilities
│       └── BUILD.bazel   # Bazel build configuration for math utilities
├── examples/             # Additional examples
│   ├── cpp23_demo.cpp    # C++23 features demonstration
│   └── BUILD.bazel       # Bazel build configuration for examples
├── BUILD.bazel           # Root Bazel build configuration
├── MODULE.bazel          # Bazel module configuration
└── README.md             # This file
```

## Features

### Geometry Library (`lib/geometry/`)

#### Point2D Class
- 2D point representation with x, y coordinates
- Distance calculation between points
- Vector operations (addition, subtraction, scalar multiplication)

#### Circle Class
- Circle representation with center point and radius
- Area and circumference calculations
- Point containment testing

#### Utility Functions
- Triangle area calculation using three points
- Centroid calculation for a set of points

### Math Utils Library (`lib/math_utils/`)

#### Statistics Module
- Mean, median, and standard deviation calculations
- Min/max value finding
- Support for both population and sample statistics

#### Numerical Module
- Factorial calculation
- Greatest Common Divisor (GCD) and Least Common Multiple (LCM)
- Prime number checking
- Fibonacci sequence generation
- Fast exponentiation

#### Interpolation Module
- Linear interpolation between points
- Numerical integration using trapezoidal rule
- Root finding using Newton-Raphson method

#### Matrix2x2 Class
- 2x2 matrix operations (addition, multiplication, scalar multiplication)
- Determinant calculation
- Matrix inversion

## Building and Running

### Prerequisites
- Bazel build system
- C++23 compatible compiler

### Build the main application
```bash
bazel build //:main
```

### Run the main application
```bash
bazel run //:main
```

### Run the tests
```bash
# Run all tests
bazel test //lib/geometry:geometry_test //lib/math_utils:math_utils_test

# Run individual test suites
bazel test //lib/geometry:geometry_test
bazel test //lib/math_utils:math_utils_test

# Run all tests in a library directory
bazel test //lib/geometry:all
bazel test //lib/math_utils:all
```

### Build and run the C++23 demo
```bash
bazel run //examples:cpp23_demo
```

## Example Output

When you run the main application, you'll see output demonstrating both geometric calculations and mathematical utilities:

```
=== Geometry Sandbox Demo ===
Point 1: (0, 0)
Point 2: (3, 4)
Point 3: (6, 0)
Distance from P1 to P2: 5.00
Distance from P2 to P3: 5.00
Distance from P1 to P3: 6.00
P1 + P2 = (3, 4)
P2 - P1 = (3, 4)
P2 * 2 = (6, 8)
Triangle area (P1, P2, P3): 12.00
Centroid of triangle: (3.00, 1.33)
Circle at (3.00, 1.33) with radius 3.00
Circle area: 28.27
Circle circumference: 18.85
Does circle contain P1? No
Does circle contain P2? Yes
Does circle contain P3? No
Does larger circle (radius 5.0) contain all points? Yes

=== Math Utils Demo ===
Mean: 2.98
Median: 3.00
Standard deviation: 0.85
Min: 1.50, Max: 4.20
Factorial of 7: 5040
GCD of 48 and 18: 6
LCM of 12 and 15: 60
Is 17 prime? Yes
2^10 = 1024
First 10 Fibonacci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
Matrix multiplication result: [2, 5; 3, 10]
Matrix determinant: 5.00
Linear interpolation at x=5 between (0,0) and (10,100): 50.0
Integral of x^2 from 0 to 2: 2.667 (exact: 2.667)
```