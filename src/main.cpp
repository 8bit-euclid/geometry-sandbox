#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== Eigen 3.4.0 Example ===" << std::endl;
    
    // Create a 3x3 matrix
    Eigen::Matrix3d matrix;
    matrix << 1, 2, 3,
              4, 5, 6,
              7, 8, 9;
    
    std::cout << "Matrix A:" << std::endl;
    std::cout << matrix << std::endl << std::endl;
    
    // Create a 3D vector
    Eigen::Vector3d vector(1, 2, 3);
    std::cout << "Vector b:" << std::endl;
    std::cout << vector << std::endl << std::endl;
    
    // Matrix-vector multiplication
    Eigen::Vector3d result = matrix * vector;
    std::cout << "A * b = " << std::endl;
    std::cout << result << std::endl << std::endl;
    
    // Calculate determinant
    std::cout << "Determinant of A: " << matrix.determinant() << std::endl;
    
    // Calculate transpose
    std::cout << "Transpose of A:" << std::endl;
    std::cout << matrix.transpose() << std::endl << std::endl;
    
    // Example with dynamic size matrix
    Eigen::MatrixXd dynamic_matrix = Eigen::MatrixXd::Random(2, 3);
    std::cout << "Random 2x3 matrix:" << std::endl;
    std::cout << dynamic_matrix << std::endl;
    
    return 0;
}
