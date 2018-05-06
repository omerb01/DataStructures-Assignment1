//
// Created by Omer on 06/05/2018.
//

#include "testMacros.h"
#include <iostream>
#include "AVLTree.h"

template<typename T>
bool areArraysEqual(T *a, T *b, int n) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template<typename T, class Key>
bool areTreesEqual(const AVLTree<T, Key> &tree1, const AVLTree<T, Key> &tree2, int size) {
    T *inArray1 = tree1.inOrderToArray();
    T *preArray1 = tree1.preOrderToArray();
    T *inArray2 = tree2.inOrderToArray();
    T *preArray2 = tree2.preOrderToArray();

    bool result = areArraysEqual(inArray1, inArray2, size) &&
                  areArraysEqual(preArray1, preArray2, size);

    delete[] inArray1;
    delete[] inArray2;
    delete[] preArray1;
    delete[] preArray2;
    return result;
}

bool testInsertRR() {
    return true;
}

bool testInsertRL() {
    return true;
}

bool testInsertLL() {
    AVLTree<int, int> tree1;
    tree1.insert(2, 2);
    tree1.insert(1, 1);
    tree1.insert(7, 7);
    tree1.insert(5, 5);

    // LL roll
    tree1.insert(3, 3);

    AVLTree<int, int> tree2;
    tree2.insert(2, 2);
    tree2.insert(5, 5);
    tree2.insert(1, 1);
    tree2.insert(7, 7);
    tree2.insert(3, 3);

    ASSERT_TRUE(areTreesEqual(tree1, tree2, 5));

    return true;
}

bool testInsertLR() {
    return true;
}

bool testRemoveRR() {
    return true;
}

bool testRemoveRL() {
    return true;
}

bool testRemoveLL() {
    return true;
}

bool testRemoveLR() {
    return true;
}

bool testFind() {
    return true;
}

bool testMerge() {
    AVLTree<int, int> tree1;
    tree1.insert(10, 10);
    tree1.insert(8, 8);
    tree1.insert(12, 12);

    AVLTree<int, int> tree2;
    tree2.insert(10, 10);
    tree2.insert(9, 9);
    tree2.insert(11, 11);

    AVLTree<int, int> merged_tree_1_2 = AVLTree<int, int>::merge(tree1, tree2);

    AVLTree<int, int> tree3;
    tree3.insert(11, 11);
    tree3.insert(12, 12);
    tree3.insert(9, 9);
    tree3.insert(10, 10);
    tree3.insert(8, 8);

    ASSERT_TRUE(areTreesEqual(merged_tree_1_2, tree3, 5));

    AVLTree<int, int> empty_tree1;
    AVLTree<int, int> empty_tree2;
    AVLTree<int, int> empty_merged_tree = AVLTree<int, int>::merge(empty_tree1, empty_tree2);
    ASSERT_TRUE(areTreesEqual(empty_tree1, empty_merged_tree, 0));

    // TODO: check copy constructor, why it doesnt copy properly
    AVLTree<int, int> merged_tree_1_empty = AVLTree<int, int>::merge(tree1, empty_tree2);

    ASSERT_TRUE(areTreesEqual(merged_tree_1_empty,tree1,3));

    return true;
}

int main() {
    RUN_TEST(testInsertLL);
    RUN_TEST(testMerge);
    return 0;
}