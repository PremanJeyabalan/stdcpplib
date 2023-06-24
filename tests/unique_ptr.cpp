#include <UniquePtr.h>
#include <gtest/gtest.h>

struct UniquePtrTest : public testing::Test {

};

TEST_F(UniquePtrTest, foo) {
    CustomStd::unique_ptr k;
    EXPECT_EQ(1, 1);
}
