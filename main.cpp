#include <iostream>
#include "BinarySearchTree.h"


int main() {
    BinarySearchTree<int, int> tree;
    tree.recursiveAdd(10, 1);
    tree.recursiveAdd(7, 1);
    tree.recursiveAdd(5, 1);
    tree.recursiveAdd(8, 1);
    tree.recursiveAdd(15, 1);
    tree.recursiveAdd(11, 1);
    tree.recursiveAdd(18, 1);
    tree.recursiveShow();
    tree.recursiveDeleteByKey(11);
    tree.recursiveShow();
    tree.recursiveDeleteByKey(15);
    tree.recursiveShow();
    tree.recursiveDeleteByKey(10);
    tree.recursiveDeleteByKey(7);
    tree.recursiveAdd(55, 1);
    tree.recursiveShow();
    try {
        std::cout << tree.recursiveSearch(20) << std::endl;
    } catch (std::exception&) {
        std::cout << "Exception!\n";
    }
    tree.clear();
    tree.show();
    tree.add(10, 1);
    tree.show();
}
