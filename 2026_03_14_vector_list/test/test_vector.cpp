#include <gtest/gtest.h>
#include "vector.hpp"

using tar::Vector;

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);
    EXPECT_FALSE(v.has_item(42));
}

TEST(VectorTest, PushBack) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(20));
    EXPECT_FALSE(v.has_item(99));
}

TEST(VectorTest, InsertAtBeginning) {
    Vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.insert(0, 1);
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(1));
}

TEST(VectorTest, InsertAtMiddle) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.insert(1, 2);
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(2));
}

TEST(VectorTest, InsertInvalidPosition) {
    Vector<int> v;
    v.push_back(1);
    EXPECT_FALSE(v.insert(5, 99));
    EXPECT_EQ(v.get_size(), 1);
}

TEST(VectorTest, RemoveFirst) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    EXPECT_TRUE(v.remove_first(2));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_FALSE(v.has_item(2));
}

TEST(VectorTest, RemoveNonExistent) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    
    EXPECT_FALSE(v.remove_first(999));
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, GetSizeAfterOperations) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.remove_first(1);
    v.push_back(3);
    
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, Expansion) {
    Vector<int> v;
    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
    }
    EXPECT_EQ(v.get_size(), 20);
    EXPECT_TRUE(v.has_item(15));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}