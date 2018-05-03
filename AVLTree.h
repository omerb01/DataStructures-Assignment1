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

        Node(T d, int k1, int k2) : data(d), key1(k1), key2(k2), left(nullptr),
                                    right(nullptr), parent(nullptr), h_left(-1),
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

public:
    AVLTree() : root(nullptr) {}

    bool insert(T data, int key1, int key2) {
        Node *iterator = root;
        string path="";
        while (iterator->right != nullptr && iterator->left != nullptr) {
            if (iterator->key1 == key1 && iterator->key2 == key2) break;
            else if (key1 < iterator->key1 ||
                     (key1 == iterator->key1 && key2 > iterator->key2)) {
                iterator = iterator->left;
            } else {
                iterator = iterator->right;
            }
        }
        if (iterator->key1 == key1 && iterator->key2 == key2) {
            return false;
        }
        Node *new_node = new Node(data, key1, key2);
        if (key1 < iterator->key1 ||
            (key1 == iterator->key1 && key2 > iterator->key2)) {
            iterator->left = new_node;
        } else {
            iterator->right = new_node;
        }
        new_node->parent = iterator;
        Node *p, *v=new_node;
        while (v != root) {
            int height_p, height_v;
            p = v->parent;
            p->h_left > p->h_right ? height_p = p->h_left + 1 : height_p =
                                                                        p->h_right +
                                                                        1;
            v->h_left > v->h_right ? height_v = v->h_left + 1 : height_v =
                                                                        v->h_right +
                                                                        1;
            if(height_p >= height_v+1){
                return true;
            }
            if(p->right==v){
                path = "R" + path;
                p->h_right++;
            }else{
                path = "L" + path;
                p->h_left++;
            }
            if(abs(p->h_left - p->h_right)>1){
                // switch case n' roll
            }else{
                v=p;
            }

        }
        return true;
    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
