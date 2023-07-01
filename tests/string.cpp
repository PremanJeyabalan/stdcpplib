//
// Created by preman on 6/28/23.
//
#include <gtest/gtest.h>
#include <String.h>


struct StringTestFixture : public testing::Test {

};

TEST(StringTest, DefaultCtorValid) {
    CustomStd::string k;
    EXPECT_EQ(k.size(), 0) << " Empty string should have size 0";
    EXPECT_EQ(k.capacity(), 22) << " should instead have capacity 22";
}

TEST(StringTest, CStringCtorValid) {
    CustomStd::string k {"abcdefg"};

    EXPECT_EQ(k.size(), 7);
    EXPECT_EQ(std::string{k.data()}, "abcdefg");
}

