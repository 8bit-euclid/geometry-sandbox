#include <CGAL/Kernel/global_functions.h>
#include <CGAL/Simple_cartesian.h>
#include <gtest/gtest.h>

TEST(CGALSuite, SegmentMidpoint)
{
    using Kernel = CGAL::Simple_cartesian<double>;
    using Point = Kernel::Point_2;
    Point a(0.0, 0.0);
    Point b(2.0, 0.0);
    // Use CGAL midpoint utility for two points
    auto mid = CGAL::midpoint(a, b);
    EXPECT_DOUBLE_EQ(mid.x(), 1.0);
    EXPECT_DOUBLE_EQ(mid.y(), 0.0);
}
