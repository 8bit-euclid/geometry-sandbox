#include <geogram/basic/argused.h>
#include <gtest/gtest.h>

TEST(GeogramHeadersOnly, ArgusedInlineCompilesAndLinks)
{
    int x = 42;
    GEO::geo_argused(x); // inline template defined in header; no linking to compiled libs
    SUCCEED();
}
