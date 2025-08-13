#include "triangle.h"
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>

TEST(TriangleSuite, SquareTriangulation)
{
    struct triangulateio in;
    std::memset(&in, 0, sizeof(in));
    struct triangulateio out;
    std::memset(&out, 0, sizeof(out));

    in.numberofpoints = 4;
    in.pointlist = (TRI_REAL*) std::malloc(in.numberofpoints * 2 * sizeof(TRI_REAL));
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
    in.segmentlist = (int*) std::malloc(in.numberofsegments * 2 * sizeof(int));
    int segs[8] = {0, 1, 1, 2, 2, 3, 3, 0};
    for (int i = 0; i < 8; ++i)
        in.segmentlist[i] = segs[i];

    triangulate(const_cast<char*>("pqz"), &in, &out, nullptr); // 'z' => use 0-based indexing

    EXPECT_GT(out.numberoftriangles, 0);
    EXPECT_LE(out.numberoftriangles,
              4); // a square should not need more than 2-4 triangles given constraints

    std::free(in.pointlist);
    std::free(in.segmentlist);
    std::free(out.pointlist);
    std::free(out.trianglelist);
    std::free(out.segmentlist);
    std::free(out.edgelist);
}
