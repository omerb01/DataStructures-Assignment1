#include <iostream>
#include "AVLTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    AVLTree<int> tree;
    tree.insert(5, 5, 0);
    tree.insert(2, 2, 0);
    tree.insert(8, 8, 0);
    tree.insert(3, 3, 0);
    tree.insert(7, 7, 0);
    tree.insert(11, 11, 0);
    tree.insert(6, 6, 0);
    tree.insert(9, 9, 0);
    tree.insert(13, 13, 0);

    tree.remove(8, 0);
    tree.remove(13, 0);

    return 0;
}