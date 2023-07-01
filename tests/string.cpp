//
// Created by preman on 6/28/23.
//
#include <gtest/gtest.h>
#include <String.h>


struct StringTest : public testing::Test {

};

TEST_F(StringTest, foo) {
    CustomStd::string k;
    CustomStd::string l {k};
    CustomStd::string m {k.data(), 0};

    EXPECT_EQ(l.size(), 0);
}
