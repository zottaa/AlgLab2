#include <iostream>
#include "BinarySearchTree.h"
#include <gtest/gtest.h>

TEST(TreeTest, AddTest) {
    BinarySearchTree<int, int> tree;
    tree.recursiveAdd(8, 1);
    tree.recursiveAdd(4,1);
    tree.recursiveAdd(2,1);
    tree.recursiveAdd(3,1);
    tree.recursiveAdd(10,1);
    tree.recursiveAdd(6,1);
    tree.recursiveAdd(7,1);
    tree.add(1, 1);
    ASSERT_EQ(tree.toString(), "123467810");
}

TEST(TreeTest, DeleteTest) {
    BinarySearchTree<int, int> tree;
    tree.recursiveAdd(8, 1);
    tree.recursiveAdd(4,1);
    tree.recursiveAdd(2,1);
    tree.recursiveAdd(3,1);
    tree.recursiveAdd(10,1);
    tree.recursiveAdd(6,1);
    tree.recursiveAdd(7,1);
    tree.recursiveAdd(1, 1);
    tree.recursiveDeleteByKey(10);
    ASSERT_EQ(tree.toString(), "1234678");
    tree.recursiveDeleteByKey(4);
    ASSERT_EQ(tree.toString(), "123678");
    tree.recursiveDeleteByKey(20);
    ASSERT_EQ(tree.toString(), "123678");
}

TEST(TreeTest, ClearTest) {
    BinarySearchTree<int, int> tree;
    tree.recursiveAdd(8, 1);
    tree.recursiveAdd(4,1);
    tree.recursiveAdd(2,1);
    tree.recursiveAdd(3,1);
    tree.recursiveAdd(10,1);
    tree.recursiveAdd(6,1);
    tree.recursiveAdd(7,1);
    tree.recursiveAdd(1, 1);
    ASSERT_EQ(tree.toString(), "123467810");
    tree.clear();
    ASSERT_EQ(tree.toString(),"");
}

TEST(TreeTest, SearchTest) {
    BinarySearchTree<int, int> tree;
    tree.recursiveAdd(8, 1);
    tree.recursiveAdd(4,1);
    tree.recursiveAdd(2,1);
    tree.recursiveAdd(3,1);
    tree.recursiveAdd(10,1);
    tree.recursiveAdd(6,1);
    tree.recursiveAdd(7,1);
    tree.recursiveAdd(1, 1);
    ASSERT_EQ(tree.recursiveSearch(10),1);
    ASSERT_EQ(tree.recursiveSearch(1),1);
    ASSERT_ANY_THROW(tree.recursiveSearch(33));
}