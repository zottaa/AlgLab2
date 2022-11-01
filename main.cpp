#include <iostream>
#include "BinarySearchTree.h"
#include <gtest/gtest.h>

TEST(TreeTest, AddTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(12, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    ASSERT_EQ(tree.toString(), "12346781012");
}

TEST(TreeTest, AddReduceNTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(12, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(2, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    tree.add(8, 1);
    ASSERT_EQ(tree.toStringN(), "131621921");
}

TEST(TreeTest, DeleteReduceNTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(12, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.deleteByKey(1);
    tree.deleteByKey(12);
    tree.deleteByKey(12);
    tree.deleteByKey(1);
    tree.deleteByKey(12);
    tree.deleteByKey(1);
    tree.deleteByKey(12);
    tree.deleteByKey(1);
    tree.deleteByKey(1);
    tree.deleteByKey(1);
    tree.deleteByKey(1);
    tree.deleteByKey(1);
    tree.deleteByKey(1);
    tree.deleteByKey(8);
    tree.deleteByKey(10);
    ASSERT_EQ(tree.toStringN(), "21521");
}

TEST(TreeTest, DeleteTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.deleteByKey(10);
    ASSERT_EQ(tree.toString(), "1234678");
    tree.deleteByKey(4);
    ASSERT_EQ(tree.toString(), "123678");
    tree.deleteByKey(20);
    ASSERT_EQ(tree.toString(), "123678");
}

TEST(TreeTest, ClearTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    ASSERT_EQ(tree.toString(), "123467810");
    tree.clear();
    ASSERT_EQ(tree.toString(), "");
}

TEST(TreeTest, SearchTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.add(9, 1);
    ASSERT_EQ(tree.search(10), 1);
    ASSERT_EQ(tree.search(1), 1);
    ASSERT_ANY_THROW(tree.search(33));
}

TEST(TreeTest, SearchIndexTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(11, 1);
    tree.add(10, 1);
    tree.add(12, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.add(9, 1);
    tree.deleteByKey(11);
    tree.deleteByKey(2);
    ASSERT_EQ(tree.findIndex(4), 2);
    tree.deleteByKey(4);
    ASSERT_EQ(tree.findIndex(1), 0);
    ASSERT_EQ(tree.findIndex(8), 4);
    ASSERT_EQ(tree.findIndex(4), -1);
}

TEST(TreeTest, CopyTest) {
    BinarySearchTree<int, int> tree;
    tree.add(8, 1);
    tree.add(4, 1);
    tree.add(2, 1);
    tree.add(3, 1);
    tree.add(10, 1);
    tree.add(12, 1);
    tree.add(6, 1);
    tree.add(7, 1);
    tree.add(1, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    tree.add(10, 1);
    BinarySearchTree<int, int> tree2(tree);
    ASSERT_EQ(tree2.toString(), "12346781012");
}

TEST(TreeTest, IteratorTest) {

}

TEST(TreeTest, ReverseIteratorTest) {

}