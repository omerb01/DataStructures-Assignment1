//
// Created by Omer on 06/05/2018.
//

#include "testMacros.h"
#include <iostream>
#include "AVLTree.h"

bool areArraysEqual(int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
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
    int *inArray1 = tree1.inOrderToArray();
    int *preArray1 = tree1.preOrderToArray();

    AVLTree<int, int> tree2;
    tree2.insert(2, 2);
    tree2.insert(5, 5);
    tree2.insert(1, 1);
    tree2.insert(7, 7);
    tree2.insert(3, 3);
    int *inArray2 = tree2.inOrderToArray();
    int *preArray2 = tree2.preOrderToArray();

    ASSERT_TRUE(areArraysEqual(inArray1, inArray2, 5));
    ASSERT_TRUE(areArraysEqual(preArray1, preArray2, 5));

    delete[] inArray1;
    delete[] inArray2;
    delete[] preArray1;
    delete[] preArray2;

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

    AVLTree<int, int> merged_tree = AVLTree<int, int>::merge(tree1, tree2);

    int *inArray1 = merged_tree.inOrderToArray();
    int *preArray1 = merged_tree.preOrderToArray();

    AVLTree<int, int> tree3;
    tree3.insert(11, 11);
    tree3.insert(12, 12);
    tree3.insert(9, 9);
    tree3.insert(10, 10);
    tree3.insert(8, 8);

    int *inArray2 = tree3.inOrderToArray();
    int *preArray2 = tree3.preOrderToArray();

    ASSERT_TRUE(areArraysEqual(inArray1, inArray2, 5));
    ASSERT_TRUE(areArraysEqual(preArray1, preArray2, 5));

    return true;
}

int main() {
    RUN_TEST(testInsertLL);
    RUN_TEST(testMerge);
    return 0;
}