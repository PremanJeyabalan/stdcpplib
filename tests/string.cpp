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

TEST(StringTest, FromCStringCtorShortValid) {
    CustomStd::string k {"abcdefg"};

    ASSERT_EQ(k.size(), 7);
    ASSERT_EQ(k.capacity(), 22);
}

TEST(StringTest, FromCStringCtorLongValid) {
    CustomStd::string k {"abcdefghijklmnopqrstuvwxyz"};

    ASSERT_EQ(k.size(), 26);
    ASSERT_EQ(k.capacity(), 26+1);
}

TEST(StringTest, CStringCtorShortValid) {
    //SHORT STRING CASE
    CustomStd::string k {"abcdefg"};

    EXPECT_EQ(k.size(), 7);
    EXPECT_EQ(k.capacity(), 22);

}
TEST(StringTest, CStringCtorLongValid) {
    //  LONG STRING CASE
    CustomStd::string h{"abcdefghijklmnopqrstuvwxyz"};

    EXPECT_EQ(h.size(), 26);
    EXPECT_EQ(h.capacity(), 27) << "capacity should be odd";
}

TEST(StringTest, CopyCtorShortValid) {
    CustomStd::string k {"abcdefg"};
    CustomStd::string copy_k {k};

    ASSERT_EQ(k.size(), copy_k.size());
    EXPECT_EQ(k.capacity(), copy_k .capacity());

    for (int i = 0; i < k.size(); i++) ASSERT_EQ(k.data()[i], copy_k.data()[i]);
}

TEST(StringTest, CopyCtorLongValid) {
    CustomStd::string k {"abcdefghijklmnopqrstuvwxyz"};
    CustomStd::string copy_k {k};

    ASSERT_EQ(k.size(), copy_k.size());
    EXPECT_EQ(k.capacity(), copy_k .capacity());

    for (int i = 0; i < k.size(); i++) ASSERT_EQ(k.data()[i], copy_k.data()[i]);
}

TEST(StringTest, SubstringCtorShortPartialValid) {
    CustomStd::string k {"abcdefg"};
    CustomStd::string sub_2_3_k {k, 2, 3};

    std::string k_s {"abcdefg"};
    std::string sub_2_3_k_s {k_s, 2, 3};

    ASSERT_EQ(sub_2_3_k.size(), sub_2_3_k_s.size());
    ASSERT_EQ(sub_2_3_k.capacity(), 22);
}

TEST(StringTest, SubstringCtorShortFullValid) {
    CustomStd::string k {"abcdefg"};
    CustomStd::string sub_2_5_k {k, 2, 5};
    CustomStd::string sub_2_8_k {k, 2, 8};

    std::string k_s {"abcdefg"};
    std::string sub_2_5_k_s {k_s, 2, 5};
    std::string sub_2_8_k_s {k_s, 2, 8};

    ASSERT_EQ(sub_2_5_k.size(), sub_2_5_k_s.size());
    ASSERT_EQ(sub_2_5_k.capacity(), 22);

    ASSERT_EQ(sub_2_8_k.size(), sub_2_8_k_s.size());
    ASSERT_EQ(sub_2_8_k.capacity(), 22);
}

TEST(StringTest, SubstringCtorLongPartialValid) {
    CustomStd::string k {"abcdefghijklmnopqrstuvwxys"};
    CustomStd::string sub_k_1_23 {k, 1, 23};

    std::string k_s {"abcdefghijklmnopqrstuvwxys"};
    std::string sub_k_s_1_23 {k_s, 1, 23};

    ASSERT_EQ(sub_k_1_23.size(), sub_k_s_1_23.size());
    ASSERT_EQ(sub_k_1_23.capacity(), 23);
}

TEST(StringTest, SubstringCtorLongFullValid) {
    CustomStd::string k {"abcdefghijklmnopqrstuvwxyz"};
    CustomStd::string sub_1_25_k {k, 1, 25};
    CustomStd::string sub_1_30_k {k, 1, 30};

    std::string k_s {"abcdefghijklmnopqrstuvwxyz"};
    std::string sub_1_25_k_s {k_s, 1, 25};
    std::string sub_1_30_k_s {k_s, 1, 30};

    ASSERT_EQ(sub_1_25_k.size(), sub_1_25_k_s.size());
    ASSERT_EQ(sub_1_25_k.capacity(), 25);

    ASSERT_EQ(sub_1_30_k.size(), sub_1_30_k_s.size());
    ASSERT_EQ(sub_1_30_k.capacity(), 25);
}

TEST(StringTest, FromBufferCtorShortValid) {
    CustomStd::string k {"abcdefg", 2};
    std::string k_s {"abcdefg", 2};

    ASSERT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);
}

TEST(StringTest, FromBufferCtorLongValid) {
    CustomStd::string k {"abcdefghijklmnopqrstuvwxyz", 24};
    std::string k_s {"abcdefghijklmnopqrstuvwxyz", 24};

    ASSERT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);
}

TEST(StringTest, FillCtorShortValid) {
    CustomStd::string k(1, 'k');
    CustomStd::string r_0 (0, 'r');
    CustomStd::string p_24(24, 'p');

    std::string k_s (1, 'k');
    std::string r_0_s (0, 'r');
    std::string p_24_s (24, 'p');

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(r_0.size(), r_0_s.size());
    EXPECT_EQ(p_24.size(),  p_24_s.size());

    EXPECT_EQ(k.capacity(), 22);
    EXPECT_EQ(r_0.capacity(), 22);
    EXPECT_EQ(p_24.capacity(), 25);
}

TEST(StringTest, InitListCtorShortValid) {
    CustomStd::string k {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::string k_s = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);
}

TEST(StringTest, InitListCtorLongValid) {
    CustomStd::string k {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    std::string k_s {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), k.size() % 2 ? k.size() : k.size() + 1);
}

TEST(StringTest, MoveCtorShortValid) {
    CustomStd::string k {"abcdefg"};
    CustomStd::string k_move {std::move(k)};

    std::string k_s {"abcdefg"};
    std::string k_s_move {std::move(k_s)};

    EXPECT_EQ(k_move.size(), k_s_move.size());
    EXPECT_EQ(k_move.capacity(), 22);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);
}

TEST(StringTest, MoveCtorLongValid) {
    CustomStd::string k ("abcdefghijklmnopqrstuvwxyz");
    CustomStd::string k_move {std::move(k)};

    std::string k_s ("abcdefghijklmnopqrstuvwxyz");
    std::string k_s_move {std::move(k_s)};

    EXPECT_EQ(k_move.size(), k_s_move.size());
    EXPECT_EQ(k_move.capacity(), 27);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);

    EXPECT_EQ(k_s, k_s_move) << "Test assign " << k_s_move;
    k_s_move.assign(5, 'a');
    EXPECT_EQ(k_s, k_s_move) << "Test assign " << k_s_move;
}