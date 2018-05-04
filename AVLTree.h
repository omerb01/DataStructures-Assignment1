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

    void roll_LL(Node *unbalanced) {
        Node *left, *right, *n_parent;
        right = unbalanced;

        n_parent = unbalanced->left; // new parent - left node of the unbalanced node
        unbalanced->left = n_parent->right; // if new node has right children, move to to old parent
        n_parent->right = right;
        n_parent->parent = unbalanced->parent;
        right->parent = n_parent;

    }

    void roll_RR(Node *unbalanced) {
        Node *left, *right, *n_parent;
        left = unbalanced;

        n_parent = unbalanced->right; // new parent - left node of the unbalanced node
        unbalanced->right = n_parent->left; // if new node has right children, move to to old parent
        n_parent->left = unbalanced;
        n_parent->parent = unbalanced->parent;
        left->parent = n_parent;
    }

    void roll_RL(Node *unbalanced){
        Node *old_parent,*right_left,*unbalanced_right;
        unbalanced_right=unbalanced->right;
        right_left=unbalanced->right->left;
        unbalanced->right->left=right_left->right;
        unbalanced->right=right_left->left;
        unbalanced->parent=right_left;
        right_left->left=unbalanced;
        right_left->right=unbalanced_right;
    }
    void roll_LR(Node *unbalanced){
        Node *old_parent,*left_right,*unbalanced_left;
        unbalanced_left=unbalanced->left;
        left_right=unbalanced->left->right;
        unbalanced->right->left=left_right->left;
        unbalanced->left=left_right->right;
        unbalanced->parent=left_right;
        left_right->right=unbalanced;
        left_right->left=unbalanced_left;
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
                // update the height ??
            } else {
                v = p;
            }

        }
        return true;
    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
