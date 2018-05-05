#include <iostream>
#include "AVLTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    AVLTree<int> tree;
    tree.insert(24, 24, 0);
    tree.insert(10, 10, 0);
    tree.insert(6, 6, 0);
    tree.insert(29, 29, 0);
    tree.insert(15, 15, 0);
    tree.insert(14, 14, 0);
    tree.insert(8, 8, 0);
    tree.insert(12, 12, 0);
    tree.insert(9, 9, 0);
    tree.insert(19, 19, 0);
    tree.insert(13, 13, 0);
    tree.insert(20, 20, 0);
    tree.insert(4, 4, 0);

    return 0;
}