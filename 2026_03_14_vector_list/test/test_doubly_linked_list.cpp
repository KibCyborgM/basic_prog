#include <gtest/gtest.h>
#include "doubly_linked_list.hpp"

using tar::DoublyLinkedList;

TEST(DoublyLinkedListTest, DefaultConstructor) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_FALSE(list.has_item(42));
}

TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item(20));
    EXPECT_FALSE(list.has_item(99));
}

TEST(DoublyLinkedListTest, RemoveFromEmpty) {
    DoublyLinkedList<int> list;
    EXPECT_FALSE(list.remove_first(10));
}

TEST(DoublyLinkedListTest, RemoveOnlyElement) {
    DoublyLinkedList<int> list;
    list.push_back(42);
    EXPECT_TRUE(list.remove_first(42));
    EXPECT_EQ(list.get_size(), 0);
}

TEST(DoublyLinkedListTest, RemoveFirstElement) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    EXPECT_TRUE(list.remove_first(1));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(1));
}

TEST(DoublyLinkedListTest, RemoveLastElement) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    EXPECT_TRUE(list.remove_first(3));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(3));
}

TEST(DoublyLinkedListTest, RemoveMiddleElement) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    
    EXPECT_TRUE(list.remove_first(2));
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_FALSE(list.has_item(2));
}

TEST(DoublyLinkedListTest, RemoveNonExistent) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    
    EXPECT_FALSE(list.remove_first(999));
    EXPECT_EQ(list.get_size(), 2);
}

TEST(DoublyLinkedListTest, GetSizeAfterOperations) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.remove_first(1);
    list.push_back(3);
    
    EXPECT_EQ(list.get_size(), 2);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}