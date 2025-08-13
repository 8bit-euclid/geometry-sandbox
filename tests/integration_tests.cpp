#include "triangle.h"
#include <Eigen/Dense>
#include <cmath>
#include <cstring>
#include <gtest/gtest.h>
#include <igl/doublearea.h>
#include <igl/volume.h>
#include <numeric>
#include <vector>

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

TEST(TriangleSuite, SquareTriangulation)
{
    struct triangulateio in;
    memset(&in, 0, sizeof(in));
    struct triangulateio out;
    memset(&out, 0, sizeof(out));

    in.numberofpoints = 4;
    in.pointlist = (TRI_REAL*) malloc(in.numberofpoints * 2 * sizeof(TRI_REAL));
    // square CCW
    in.pointlist[0] = 0.0;
    in.pointlist[1] = 0.0;
    in.pointlist[2] = 1.0;
    in.pointlist[3] = 0.0;
    in.pointlist[4] = 1.0;
    in.pointlist[5] = 1.0;
    in.pointlist[6] = 0.0;
    in.pointlist[7] = 1.0;

    in.numberofsegments = 4;
    in.segmentlist = (int*) malloc(in.numberofsegments * 2 * sizeof(int));
    int segs[8] = {0, 1, 1, 2, 2, 3, 3, 0};
    for (int i = 0; i < 8; ++i)
        in.segmentlist[i] = segs[i];

    triangulate(const_cast<char*>("pqz"), &in, &out, nullptr); // 'z' => use 0-based indexing

    EXPECT_GT(out.numberoftriangles, 0);
    EXPECT_LE(out.numberoftriangles,
              4); // a square should not need more than 2-4 triangles given constraints

    free(in.pointlist);
    free(in.segmentlist);
    free(out.pointlist);
    free(out.trianglelist);
    free(out.segmentlist);
    free(out.edgelist);
}
