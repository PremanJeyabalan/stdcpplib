#include <UniquePtr.h>
#include <memory>
#include <gtest/gtest.h>

struct UniquePtrTest : public testing::Test {

};

TEST_F(UniquePtrTest, foo) {
    auto k = CustomStd::make_unique<int>(5);
    auto p = std::make_unique<int>(5);

    EXPECT_EQ(*(k.get()), 5);
}
