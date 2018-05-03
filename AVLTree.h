//
// Created by Omer on 03/05/2018.
//

#include <exception>

#ifndef DATASTRUCTURES_HW1_AVLTREE_H
#define DATASTRUCTURES_HW1_AVLTREE_H

template<typename T>
class AVLTree {
    struct Node {
        T data;
        int key1;
        int key2;
        Node *left;
        Node *right;
    };

    Node *root;

    static Node *findNode(Node *root, int key1, int key2) {
        if (root == nullptr) return nullptr;

        if (root->key1 == key1 && root->key2 == key2) {
            return root;
        } else if (key1 < root->key1 ||
                   (key1 == root->key1 && key2 > root->key2)) {
            return findNode(root->left, key1, key2);
        } else {
            return findNode(root->right, key1, key2);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T data, int key1, int key2) {

    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
