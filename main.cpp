#include <iostream>
#include "BinarySearchTree.h"


int main() {
    BinarySearchTree<int, int> tree(10, 1);
    tree.add(5, 1);
    tree.add(20, 1);
    tree.add(30, 1);
    tree.add(100, 1);
    tree.add(2, 1);
    tree.add(33, 1);
    tree.add(25, 1);
    tree.add(3, 1);
    tree.show();
    std::cout << "\n\n";
    tree.deleteByKey(30);
    tree.show();

}
