//
// Created by Omer on 03/05/2018.
//

#include <exception>
#include <cmath>
#include <rpcdce.h>
#include <string>
#include <array>
#include <vector>

#ifndef DATASTRUCTURES_HW1_AVLTREE_H
#define DATASTRUCTURES_HW1_AVLTREE_H

using std::string;
using std::array;
using std::vector;

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

        Node() : data(), key1(-1), key2(-1),
                 parent(nullptr), left(nullptr), right(nullptr),
                 h_right(-1), h_left(-1) {}

        Node(T data, int key1, int key2) : data(data), key1(key1), key2(key2),
                                           parent(nullptr), left(nullptr), right(nullptr),
                                           h_right(-1), h_left(-1) {}
    };

    Node *root;

    explicit AVLTree(Node *root) : root(root) {}

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

    Node *createVertex(Node *parent, const T &data, int key1, int key2) {
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
        if (vertex->h_left > vertex->h_right) return vertex->h_left + 1;
        return vertex->h_right + 1;
    }

    static void roll_LL(Node *unbalanced) {
        Node *left, *right, *n_parent;
        right = unbalanced;

        n_parent = unbalanced->left; // new parent - left node of the unbalanced node
        unbalanced->left = n_parent->right; // if new node has right children, move to to old parent
        n_parent->right = right;
        n_parent->parent = unbalanced->parent;
        right->parent = n_parent;

    }

    static void roll_RR(Node *unbalanced) {
        Node *left, *right, *n_parent;
        left = unbalanced;

        n_parent = unbalanced->right; // new parent - left node of the unbalanced node
        unbalanced->right = n_parent->left; // if new node has right children, move to to old parent
        n_parent->left = unbalanced;
        n_parent->parent = unbalanced->parent;
        left->parent = n_parent;
    }

    static void roll_RL(Node *unbalanced) {
        Node *old_parent, *right_left, *unbalanced_right;
        unbalanced_right = unbalanced->right;
        right_left = unbalanced->right->left;
        unbalanced->right->left = right_left->right;
        unbalanced->right = right_left->left;
        unbalanced->parent = right_left;
        right_left->left = unbalanced;
        right_left->right = unbalanced_right;
    }

    static void roll_LR(Node *unbalanced) {
        Node *old_parent, *left_right, *unbalanced_left;
        unbalanced_left = unbalanced->left;
        left_right = unbalanced->left->right;
        unbalanced->right->left = left_right->left;
        unbalanced->left = left_right->right;
        unbalanced->parent = left_right;
        left_right->right = unbalanced;
        left_right->left = unbalanced_left;
    }

    static int getSize(Node *vertex) {
        if (vertex == nullptr) return 0;
        return 1 + getSize(vertex->left) + getSize(vertex->right);
    }

    static void toArray(Node *vertex, vector<Node *> &result) {
        if (vertex == nullptr) return;
        toArray(vertex->left, result);
        result.push_back(vertex);
        toArray(vertex->right, result);
    }

    static vector<Node *> mergeNodeArrays(const vector<Node *> a, const vector<Node *> b) {
        vector<Node *>::iterator i = a.begin();
        vector<Node *>::iterator j = b.begin();
        vector<Node *> result;
        while (i != a.end() && j != b.end()) {
            int i_key1 = (*i)->key1;
            int i_key2 = (*i)->key2;
            int j_key1 = (*j)->key1;
            int j_key2 = (*j)->key2;
            if (j_key1 < i_key1 || (j_key1 == i_key1 && j_key2 > j_key2)) {
                result.push_back(*i);
                i++;
            } else {
                result.push_back(*j);
                j++;
            }
        }
        while (i != a.end()) {
            result.push_back(*i);
            i++;
        }
        while (j != b.end()) {
            result.push_back(*j);
            j++;
        }
        return result;
    }

    static vector<Node *> clearSameElements(const vector<Node *> &sorted_array) {
        vector<Node *> result;

        vector<Node *>::iterator j;
        for (vector<Node *>::iterator i = sorted_array.begin(); i != sorted_array.end(); i++) {
            auto temp = i;
            if (temp++ == sorted_array.end()) j = i;
        }

        for (vector<Node *>::iterator i = sorted_array.begin(); i != j; i++) {
            auto temp = i;
            temp++;
            if ((*i)->key1 != (*temp)->key1 ||
                ((*i)->key1 == (*temp)->key1 && (*i)->key2 != (*temp)->key2)) {
                result.push_back(*i);
            }
        }

        return result;
    }

    static Node *buildEmptyCompleteTree(int height) {
        if (height == 0) return nullptr;

        Node *left = buildEmptyCompleteTree(height - 1);
        Node *right = buildEmptyCompleteTree(height - 1);

        Node *root = new Node();
        root->right = right;
        right->parent = root;
        root->left = left;
        left->parent = root;

        return root;
    }

    static void removeVerticesFromCompleteTree(Node *root, int *leaves_to_remove) {
        if (root == nullptr) return;

        removeVerticesFromCompleteTree(root->right, leaves_to_remove);
        if (root->left == nullptr && root->right == nullptr && *leaves_to_remove > 0) {
            Node *parent = root->parent;
            if (parent->left == root) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            (*leaves_to_remove)--;
            delete root;
        }
        removeVerticesFromCompleteTree(root->left, leaves_to_remove);
    }

    static void putValuesInEmptyIncompleteTree(Node *root, vector<Node *>::const_iterator *i) {
        if (root == nullptr) return;

        putValuesInEmptyIncompleteTree(root->left, i);
        Node *current = *(*i);
        root->data = current->data;
        root->key1 = current->key1;
        root->key2 = current->key2;
        (*i)++;
        putValuesInEmptyIncompleteTree(root->right, i);
    }

    static Node *buildIncompleteTree(const vector<Node *> &sorted_array) {
        int complete_height = (int) (ceil(log2(sorted_array.size())));
        Node *root = buildEmptyCompleteTree(complete_height);
        int leaves_to_remove = (int) (pow(2, complete_height) - sorted_array.size());
        removeVerticesFromCompleteTree(root, &leaves_to_remove);
        putValuesInEmptyIncompleteTree(root, &sorted_array.begin());
        return root;
    }

public:
    AVLTree() : root(nullptr) {}

    bool insert(const T &data, int key1, int key2) {
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
                break;
            } else {
                v = p;
            }

        }
        return true;
    }

    static AVLTree merge(const AVLTree &tree1, const AVLTree &tree2) {

        vector<Node *> a;
        tree1.toArray(tree1.root, a);

        vector<Node *> b;
        tree1.toArray(tree2.root, b);

        vector<Node *> temp = mergeNodeArrays(a, b);
        vector<Node *> c = clearSameElements(temp);

        return AVLTree(buildIncompleteTree(c));
    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
