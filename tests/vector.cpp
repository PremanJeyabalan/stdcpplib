
#include <Vector.h>
#include <gtest/gtest.h>

struct VectorTest : public testing::Test {

};

TEST_F(VectorTest, foo) {
    CustomStd::vector<int, 10> v;

    v.push_back(1);
    EXPECT_EQ(v[0], 1);
}
