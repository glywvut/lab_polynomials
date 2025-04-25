#include "gtest.h"
#include "List.h"

TEST(TestList, can_create_list) {
    Unit<int>* unit = new Unit<int>(8, nullptr);
    List<int> list(unit);
    ASSERT_TRUE(list.get_first() != nullptr);
}

TEST(TestList, can_push_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    EXPECT_EQ(*list.begin(), 2);
    EXPECT_EQ(list.get_size(), 2);
}

TEST(TestList, can_pop_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.pop_front();
    EXPECT_EQ(*list.begin(), 1);
    EXPECT_EQ(list.get_size(), 1);
}

TEST(TestList, can_push_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(*list.begin(), 1);
    EXPECT_EQ(list.get_size(), 2);
}

TEST(TestList, can_insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    auto it = list.begin();
    list.insert(2, it.get_current());  

    it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2); 
    ++it;
    EXPECT_EQ(*it, 3);  
}

TEST(TestList, can_get_last_element) {
    List<int> list;
    EXPECT_EQ(list.get_last(), nullptr);

    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.get_last()->value, 2);
}

TEST(TestList, can_clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.get_first(), nullptr);
}

TEST(TestList, pop_front_empty_list_throws) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::logic_error);
}