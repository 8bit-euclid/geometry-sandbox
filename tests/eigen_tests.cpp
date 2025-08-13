#include <Eigen/Dense>
#include <gtest/gtest.h>

TEST(EigenSuite, BasicMatrixVectorOps)
{
    Eigen::Matrix3d mat;
    mat << 1, 2, 3, 4, 5, 6, 7, 8, 9; // singular matrix
    Eigen::Vector3d vec(1, 2, 3);
    Eigen::Vector3d result = mat * vec;
    EXPECT_EQ(result, Eigen::Vector3d(14, 32, 50));
    EXPECT_DOUBLE_EQ(mat.determinant(), 0.0); // known singular
    Eigen::Matrix3d transposed = mat.transpose();
    EXPECT_EQ(transposed(0, 1), 4);
}
