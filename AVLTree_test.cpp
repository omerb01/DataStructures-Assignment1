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
    AVLTree<int> tree1;
    tree1.insert(2, 2, 0);
    tree1.insert(1, 1, 0);
    tree1.insert(7, 7, 0);
    tree1.insert(5, 5, 0);

    // LL roll
    tree1.insert(3, 3, 0);
    int *inArray1 = tree1.inOrderToArray();
    int *preArray1 = tree1.preOrderToArray();

    AVLTree<int> tree2;
    tree2.insert(2, 2, 0);
    tree2.insert(5, 5, 0);
    tree2.insert(1, 1, 0);
    tree2.insert(7, 7, 0);
    tree2.insert(3, 3, 0);
    int *inArray2 = tree2.inOrderToArray();
    int *preArray2 = tree2.preOrderToArray();

    ASSERT_TRUE(areArraysEqual(inArray1, inArray2, 5));
    ASSERT_TRUE(areArraysEqual(preArray1, preArray2, 5));

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

int main() {
    RUN_TEST(testInsertLL);
    return 0;
}