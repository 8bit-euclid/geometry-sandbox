#include <Eigen/Dense>
#include <cmath>
#include <gtest/gtest.h>
#include <igl/doublearea.h>
#include <igl/volume.h>

TEST(LibIGLSuite, TetrahedronAreaAndVolume)
{
    Eigen::MatrixXd V(4, 3);
    V << 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.5, 0.866, 0.0, 0.5, 0.289, 0.816;
    Eigen::MatrixXi F(4, 3);
    F << 0, 1, 2, 0, 1, 3, 1, 2, 3, 0, 2, 3;

    Eigen::VectorXd dblA; // double areas
    igl::doublearea(V, F, dblA);
    ASSERT_EQ(dblA.rows(), 4);
    double total_area = dblA.sum() / 2.0;
    EXPECT_GT(total_area, 0.0);

    Eigen::VectorXd vol; // per-tetra volume contributions (should be 1 entry?)
    igl::volume(V, F, vol);
    double total_volume = vol.sum();
    EXPECT_GT(std::abs(total_volume), 0.0);
}
