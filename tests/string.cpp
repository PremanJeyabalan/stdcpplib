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
}

TEST(StringTest, AssignFillShortValid) {
    CustomStd::string k ("abcdefg");
    k.assign(3, 'c');

    std::string k_s ("abcdefg");
    k_s.assign(3, 'c');

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), 22);

    k.assign(10, 'd');
    k_s.assign(10, 'd');

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);
}

TEST(StringTest, AssignFillLongValid) {
    CustomStd::string k ("abcdefghijklmnopqrstuvwwxyz");
    auto old_cap = k.capacity();
    k.assign(24, 'c');

    std::string k_s ("abcdefghijklmnopqrstuvwwxyz");
    k_s.assign(24, 'c');

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), old_cap);

    k.assign(40, 'd');
    k_s.assign(40, 'd');

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(old_cap * 2 + 1, k.capacity());

    k.assign(30, 'c');
    k_s.assign(30, 'c');
    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(old_cap * 2 + 1, k.capacity());
}

TEST(StringTest, AssignFillShortToLongValid) {
    CustomStd::string k ("abcdefg");
    k.assign(24, 'c');

    std::string k_s ("abcdefg");
    k_s.assign(24, 'c');

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), 25);

    k.assign(5, 'd');
    k_s.assign(5, 'd');

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);
}

TEST(StringTest, AssignFromStrShortValid) {
    CustomStd::string k ("abcdefg");
    CustomStd::string l ("abc");
    CustomStd::string m ("abcdefghi");

    std::string k_s ("abcdefg");
    std::string l_s ("abc");
    std::string m_s ("abcdefghi");

    k.assign(l);
    k_s.assign(l_s);

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), 22);

    k.assign(m);
    k_s.assign(m_s);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);
}

TEST(StringTest, AssignFromStrLongValid) {
    CustomStd::string k ("abcdefghijklmnopqrstuvwxyz");
    auto l = CustomStd::string(24, 'c');
    auto m = CustomStd::string(40, 'd');
    auto old_cap = k.capacity();
    k.assign(l);

    std::string k_s ("abcdefghijklmnopqrstuvwxyz");
    auto l_s = std::string(24, 'c');
    auto m_s = std::string(40, 'd');
    k_s.assign(l_s);

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), old_cap);

    k.assign(m);
    k_s.assign(m_s);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(old_cap * 2 + 1, k.capacity());

    auto test = CustomStd::string(30, 'c');
    auto test_s = std::string (30, 'c');
    k.assign(test);
    k_s.assign(test_s);
    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(old_cap * 2 + 1, k.capacity());
}

TEST(StringTest, AssignFromStrShortToLongValid) {
    CustomStd::string k ("abcdefg");
    auto m = CustomStd::string(24, 'c');
    k.assign(m);

    std::string k_s ("abcdefg");
    auto m_s = std::string(24, 'c');
    k_s.assign(m_s);

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), 25);

    auto l = CustomStd::string(5, 'd');
    auto l_s = std::string(5, 'd');

    k.assign(l);
    k_s.assign(l_s);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);
}

TEST(StringTest, AssignFromStrWithPosCountLongValid) {
    //copy from within range (small and long), then try out of range, and with no param
    CustomStd::string k ("abcdefghijklmnopqrstuvwxyz");
    auto l = CustomStd::string(25, 'c');
    auto old_cap = k.capacity();
    k.assign(l, 1, 2);


    std::string k_s ("abcdefghijklmnopqrstuvwxyz");
    auto l_s = std::string(25, 'c');
    k_s.assign(l_s, 1, 2);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap);

    k.assign(l, 1, 24);
    k_s.assign(l_s, 1, 24);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap);

    k.assign(l, 1,  50);
    k_s.assign(l_s, 1, 50);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap);

    k.assign(l, 1);
    k_s.assign(l_s, 1);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap);
}

TEST(StringTest, AssignFromStrWithPosCountShortValid) {
    //copy from within range (small), then try out of range, and with no param
    CustomStd::string k ("abcdefg");
    auto l = CustomStd::string(25, 'c');
    auto old_cap = k.capacity();
    k.assign(l, 1, 2);


    std::string k_s ("abcdefg");
    auto l_s = std::string(25, 'c');
    k_s.assign(l_s, 1, 2);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap);

    k.assign(l, 1, 24);
    k_s.assign(l_s, 1, 24);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);

    k.assign(l, 1,  50);
    k_s.assign(l_s, 1, 50);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);

    k.assign(l, 1);
    k_s.assign(l_s, 1);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);
}

TEST(StringTest, AssignFromMovedStrShortValid) {
    CustomStd::string k ("abcdefg");
    CustomStd::string l ("abc");
    CustomStd::string m ("abcdefghi");

    std::string k_s ("abcdefg");
    std::string l_s ("abc");
    std::string m_s ("abcdefghi");

    auto old_cap_l = l.capacity();

    k.assign(std::move(l));
    k_s.assign(std::move(l_s));

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), old_cap_l);

    auto old_cap_m = m.capacity();

    k.assign(std::move(m));
    k_s.assign(std::move(m_s));

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap_m);
}

TEST(StringTest, AssignFromMovedStrLongValid) {
    CustomStd::string k ("abcdefghijklmnopqrstuvwxyz");
    auto l = CustomStd::string(24, 'c');
    auto m = CustomStd::string(40, 'd');
    auto old_cap_l = l.capacity();
    k.assign(std::move(l));

    std::string k_s ("abcdefghijklmnopqrstuvwxyz");
    auto l_s = std::string(24, 'c');
    auto m_s = std::string(40, 'd');
    k_s.assign(std::move(l_s));

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), old_cap_l);

    auto old_cap_m = m.capacity();

    k.assign(std::move(m));
    k_s.assign(std::move(m_s));

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(old_cap_m, k.capacity());

    auto test = CustomStd::string(30, 'c');
    auto test_s = std::string (30, 'c');

    auto old_cap_test = test.capacity();

    k.assign(std::move(test));
    k_s.assign(std::move(test_s));


    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(old_cap_test, k.capacity());
}

TEST(StringTest, AssignFromMovedStrShortToLongValid) {
    CustomStd::string k ("abcdefg");
    auto m = CustomStd::string(24, 'c');
    auto old_cap_m = m.capacity();
    k.assign(std::move(m));

    std::string k_s ("abcdefg");
    auto m_s = std::string(24, 'c');
    k_s.assign(std::move(m_s));

    ASSERT_EQ(k.size(), k_s.size());
    ASSERT_EQ(k.capacity(), old_cap_m);

    auto l = CustomStd::string(5, 'd');
    auto l_s = std::string(5, 'd');

    auto old_cap_l = l.capacity();

    k.assign(std::move(l));
    k_s.assign(std::move(l_s));

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), old_cap_l);
}

TEST(StringTest, AssignFromCharsWithCountShortValid) {
    CustomStd::string k (4, 'd');
    k.assign("abcd", 1);

    std::string k_s (4, 'd');
    k_s.assign("abcd", 1);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);

    k.assign("abcdefghijklmnopqrstuvwxyz", 24);
    k_s.assign("abcdefghijklmnopqrstuvwxyz", 24);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 25);

    k.assign("abcdefghijklmnopqrstuvwxyz", 29);
    k_s.assign("abcdefghijklmnopqrstuvwxyz", 29);

    EXPECT_EQ(k.size(), 26);
    EXPECT_EQ(k.capacity(), 25 * 2 + 1);
}

TEST(StringTest, AssignFromCharsWithCountLongValid) {
    CustomStd::string k (23, 'd');
    k.assign("abcd", 1);

    std::string k_s (23, 'd');
    k_s.assign("abcd", 1);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 23);

    k.assign("abcdefghijklmnopqrstuvwxyz", 26);
    k_s.assign("abcdefghijklmnopqrstuvwxyz", 26);

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 23 * 2 + 1);
}

TEST(StringTest, AssignFromInitListShortValid) {
    CustomStd::string k (4, 'd');
    k.assign(std::initializer_list<char> {'a'});

    std::string k_s (4, 'd');
    k_s.assign(std::initializer_list<char> {'a'});

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 22);

    k.assign(std::initializer_list<char> {'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a'});
    k_s.assign(std::initializer_list<char> {'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a'});

    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 29);

    k.assign(std::initializer_list<char> {'a'});
    k_s.assign(std::initializer_list<char> {'a'});
    EXPECT_EQ(k.size(), k_s.size());
    EXPECT_EQ(k.capacity(), 29);
}

TEST(StringTest, ReserveFromShortToShort) {
    CustomStd::string k (12, 'd');

    k.reserve(14);

    EXPECT_EQ(22, k.capacity());
    EXPECT_EQ(12, k.size());

    k.reserve();

    EXPECT_EQ(22, k.capacity());
    EXPECT_EQ(12, k.size());
}

TEST(StringTest, ReserveFromShortToLong) {
    CustomStd::string k(12, 'd');
    k.reserve(30);
    EXPECT_EQ(31, k.capacity());
    EXPECT_EQ(12, k.size());
}

TEST(StringTest, ReserveFromLongToLong) {
    CustomStd::string k(30, 'c');
    k.reserve(60);
    EXPECT_EQ(61, k.capacity());
    EXPECT_EQ(30, k.size());

    k.reserve();
    EXPECT_EQ(31, k.capacity());
    EXPECT_EQ(30, k.size());
}

TEST(StringTest, ClearFromShort) {
    CustomStd::string k(3, 'c');
    k.clear();
    EXPECT_EQ(k.size(), 0);
    EXPECT_EQ(k.capacity(), 22);
}

TEST(StringTest, ClearFromLong) {
    CustomStd::string k(30, 'c');
    k.clear();
    EXPECT_EQ(k.size(), 0);
    EXPECT_EQ(k.capacity(), 31);
}

TEST(StringTest, InsertFillFromShort) {
    CustomStd::string k(5, 'd');
    k.insert(2, 2, 'e');
    EXPECT_EQ(k.size(), 7);
    EXPECT_TRUE(k == CustomStd::string("ddeeddd"));
}