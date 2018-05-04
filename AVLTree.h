//
// Created by Omer on 03/05/2018.
//

#include <exception>
#include <cmath>
#include <rpcdce.h>
#include <string>

#ifndef DATASTRUCTURES_HW1_AVLTREE_H
#define DATASTRUCTURES_HW1_AVLTREE_H

using std::string;

template<typename T>
class AVLTree {
    struct Node {
        T data;
        int key1;
        int key2;
        Node *parent;
        Node *left;
        int h_left;
        Node *right;
        int h_right;

        Node(T data, int key1, int key2) : data(data), key1(key1), key2(key2),
                                           left(nullptr), right(nullptr),
                                           h_right(-1) {}
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

    Node *binarySearch(int key1, int key2) {
        Node *iterator = root;
        while (iterator->right != nullptr && iterator->left != nullptr) {
            if (iterator->key1 == key1 && iterator->key2 == key2) break;
            else if (key1 < iterator->key1 ||
                     (key1 == iterator->key1 && key2 > iterator->key2)) {
                iterator = iterator->left;
            } else {
                iterator = iterator->right;
            }
        }
        return iterator;
    }

    Node *createVertex(Node *parent, T data, int key1, int key2) {
        Node *new_node = new Node(data, key1, key2);
        if (key1 < parent->key1 ||
            (key1 == parent->key1 && key2 > parent->key2)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        new_node->parent = parent;
        return new_node;
    }

    static int getHeight(Node *vertex) {
        if(vertex->h_left > vertex->h_right) return vertex->h_left + 1;
        return vertex->h_right +1;
    }

public:
    AVLTree() : root(nullptr) {}

    bool insert(T data, int key1, int key2) {
        Node *parent = binarySearch(key1, key2);
        if (parent->key1 == key1 && parent->key2 == key2) return false;
        Node *new_node = createVertex(parent, data, key1, key2);

        Node *p, *v = new_node;
        string path = "";
        while (v != root) {
            p = v->parent;

            if (getHeight(p) >= getHeight(v) + 1) return true;

            if (p->right == v) {
                path = "R" + path;
                p->h_right++;
            } else {
                path = "L" + path;
                p->h_left++;
            }

            if (abs(p->h_left - p->h_right) > 1) {
                // switch case n' roll
            } else {
                v = p;
            }

        }
        return true;
    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
