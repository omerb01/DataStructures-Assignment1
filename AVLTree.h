//
// Created by Omer on 03/05/2018.
//

#include <exception>
#include <cmath>
#include <string>
#include "exceptions.h"

#ifndef DATASTRUCTURES_HW1_AVLTREE_H
#define DATASTRUCTURES_HW1_AVLTREE_H

using std::string;

template<typename T>
class AVLTree {
    struct Node {
        T data;
        // TODO: change key to be generic
        int key1;
        int key2;
        Node *parent;
        Node *left;
        int h_left;
        Node *right;
        int h_right;

        Node() {
            key1 = -1;
            key2 = -1;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            h_right = -1;
            h_left = -1;
        }

        Node(T data, int key1, int key2) {
            this->data = data;
            this->key1 = key1;
            this->key2 = key2;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            h_right = -1;
            h_left = -1;
        }
    };

    Node *root;

    explicit AVLTree(Node *root) {
        this->root = root;
    }

    Node *binarySearch(int key1, int key2) {
        if (root == nullptr) return nullptr;
        Node *iterator = root;
        while (true) {
            if (iterator->key1 == key1 && iterator->key2 == key2) break;
            else if (key1 < iterator->key1 ||
                     (key1 == iterator->key1 && key2 > iterator->key2)) {
                if (iterator->left == nullptr) return iterator;
                iterator = iterator->left;
            } else {
                if (iterator->right == nullptr) return iterator;
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
        if (vertex == nullptr) return -1;
        if (vertex->h_left > vertex->h_right) return vertex->h_left + 1;
        return vertex->h_right + 1;
    }

    void roll_LL(Node *unbalanced) {
        Node *new_parent;

        new_parent = unbalanced->left; // new parent - left node of the unbalanced node
        unbalanced->left = new_parent->right; // if new node has right children, move to to old parent
        unbalanced->h_left = new_parent->h_right;
        if (unbalanced->parent != nullptr) {
            if (unbalanced->parent->left == unbalanced) {
                unbalanced->parent->left = new_parent;
            } else {
                unbalanced->parent->right = new_parent;
            }
        }
        new_parent->right = unbalanced;
        new_parent->h_right = getHeight(unbalanced);

        new_parent->parent = unbalanced->parent;
        if (unbalanced->parent == nullptr) root = new_parent;
        unbalanced->parent = new_parent;
    }

    void roll_RR(Node *unbalanced) {
        Node *new_parent;

        new_parent = unbalanced->right; // new parent - left node of the unbalanced node
        unbalanced->right = new_parent->left; // if new node has right children, move to to old parent
        unbalanced->h_right = new_parent->h_left;
        if (unbalanced->parent->left == unbalanced) {
            unbalanced->parent->left = new_parent;
        } else {
            unbalanced->parent->right = new_parent;
        }
        new_parent->left = unbalanced;
        new_parent->h_left = getHeight(unbalanced);

        new_parent->parent = unbalanced->parent;
        if (unbalanced->parent == nullptr) root = new_parent;
        unbalanced->parent = new_parent;
    }

    void roll_RL(Node *A) {
        Node *B = A->right;
        Node *C = A->right->left;

        if (A->parent == nullptr) root = C;

        B->left = C->right;
        B->h_left = C->h_right;
        if (C->right != nullptr) C->right->parent = B;

        A->right = C->left;
        A->h_right = C->h_left;
        if (C->left != nullptr) C->left->parent = A;

        C->left = A;
        C->h_left = getHeight(A);
        C->right = B;
        C->h_right = getHeight(B);
        C->parent = A->parent;
        if (C->parent != nullptr) A->parent->left = C;
        A->parent = C;
        B->parent = C;
    }

    void roll_LR(Node *A) {
        Node *B = A->left;
        Node *C = A->left->right;

        if (A->parent == nullptr) root = C;

        B->right = C->left;
        B->h_right = C->h_left;
        if (C->left != nullptr) C->left->parent = B;

        A->left = C->right;
        A->h_left = C->h_right;
        if (C->right != nullptr) C->right->parent = A;

        C->right = A;
        C->h_right = getHeight(A);
        C->left = B;
        C->h_left = getHeight(B);
        C->parent = A->parent;
        if (C->parent != nullptr) A->parent->right = C;
        A->parent = C;
        B->parent = C;
    }

    static int getSize(Node *vertex) {
        if (vertex == nullptr) return 0;
        return 1 + getSize(vertex->left) + getSize(vertex->right);
    }

    static void sortToArray(Node *vertex, Node ***result) {
        if (vertex == nullptr) return;
        sortToArray(vertex->left, result);
        **result = vertex;
        (*result)++;
        sortToArray(vertex->right, result);
    }

    static Node **mergeNodeArrays(Node **a, int size_a, Node **b, int size_b) {
        //vector<Node *>::iterator i = a.begin();
        //vector<Node *>::iterator j = b.begin();
        Node **result = new Node *[size_a + size_b];
        while (a != a + size_a && b != b + size_b) {
            int a_key1 = (*a)->key1;
            int a_key2 = (*a)->key2;
            int b_key1 = (*b)->key1;
            int b_key2 = (*b)->key2;
            if (b_key1 < a_key1 || (b_key1 == a_key1 && b_key2 > b_key2)) {
                *result = *a;
                a++;
            } else {
                *result = *b;
                b++;
            }
        }
        while (a != a + size_a) {
            *result = *a;
            a++;
        }
        while (b != b + size_b) {
            *result = *b;
            b++;
        }
        return result;
    }

    static Node **clearSameElements(Node **sorted_array, int size, int *new_size) {
        *new_size = size;
        for (int i = 0; i < size - 1; i++) {
            if (sorted_array[i] == sorted_array[i + 1]) {
                (*new_size)--;
            }
        }
        Node **result = new Node *[*new_size];
        Node **p = sorted_array;
        *result = *p;
        p++;

        while (p != sorted_array + size) {
            if (*p != *result) {
                *result = *p;
                result++;
            }
            p++;
        }

        return result;
    }

    static Node *buildEmptyCompleteTree(int height) {
        if (height == 0) return nullptr;

        Node *left = buildEmptyCompleteTree(height - 1);
        Node *right = buildEmptyCompleteTree(height - 1);

        Node *root = new Node();
        if (right != nullptr) {
            root->right = right;
            root->h_right = getHeight(right);
            right->parent = root;
        }
        if (left != nullptr) {
            root->left = left;
            root->h_left = getHeight(left);
            left->parent = root;
        }

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

    static void putValuesInEmptyIncompleteTree(Node *root, Node ***sorted_array) {
        if (root == nullptr) return;

        putValuesInEmptyIncompleteTree(root->left, sorted_array);
        Node *current = *(*sorted_array);
        root->data = current->data;
        root->key1 = current->key1;
        root->key2 = current->key2;
        (*sorted_array)++;
        putValuesInEmptyIncompleteTree(root->right, sorted_array);
    }

    static Node *buildIncompleteTree(Node **sorted_array, int size) {
        int complete_height = (int) (ceil(log2(size)));
        Node *root = buildEmptyCompleteTree(complete_height);
        int leaves_to_remove = (int) (pow(2, complete_height) - size);
        removeVerticesFromCompleteTree(root, &leaves_to_remove);
        putValuesInEmptyIncompleteTree(root, &sorted_array);
        return root;
    }

    void swapNodesData(Node *v1, Node *v2) {
        T temp_data = v1->data;
        int temp_key1 = v1->key1;
        int temp_key2 = v1->key2;

        v1->data = v2->data;
        v1->key1 = v2->key1;
        v1->key2 = v2->key2;

        v2->data = temp_data;
        v2->key1 = temp_key1;
        v2->key2 = temp_key2;
    }

    void deleteVertexLeaf(Node *node) {
        Node *parent = node->parent;
        if (parent == nullptr) {
            root = nullptr;
        } else if (parent->right == node) {
            parent->right = nullptr;
        } else {
            parent->left = nullptr;
        }
        delete node;
    }

    void deleteVertexOneSon(Node *node, string flag) {
        Node *parent = node->parent;
        Node *son;
        if (flag.compare("right") == 0) {
            son = node->right;
        } else { // "left"
            son = node->left;
        }

        if (parent == nullptr) {
            root = son;
            son->parent = nullptr;
        } else if (parent->right == node) {
            parent->right = son;
        } else {
            parent->left = son;
        }
        son->parent = parent;
        delete node;

    }

    Node *deleteVertex(Node *node) {
        Node *parent = node->parent;
        if (node->left == nullptr && node->right == nullptr) {
            deleteVertexLeaf(node);
        } else if (node->left == nullptr && node->right != nullptr) {
            deleteVertexOneSon(node, "right");
        } else if (node->right == nullptr && node->left != nullptr) {
            deleteVertexOneSon(node, "left");
        } else { // Two sons
            Node *iterator = node->right;
            while (iterator->left != nullptr) iterator = iterator->left;
            swapNodesData(iterator, node);
            parent = iterator->parent;
            deleteVertex(iterator); // one son or a leaf
        }
        return parent;
    }

    static int getBalanceFactor(Node *vertex) {
        return vertex->h_left - vertex->h_right;
    }

    static void deleteTree(Node *root) {
        if (root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    static void inOrderToArrayRecursive(Node *root, T **array) {
        if (root == nullptr) return;
        inOrderToArrayRecursive(root->left, array);
        **array = root->data;
        (*array)++;
        inOrderToArrayRecursive(root->right, array);
    }

    static void preOrderToArrayRecursive(Node *root, T **array) {
        if (root == nullptr) return;
        **array = root->data;
        (*array)++;
        preOrderToArrayRecursive(root->left, array);
        preOrderToArrayRecursive(root->right, array);
    }

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        deleteTree(root);
    }

    T find(int key1, int key2) {
        Node *node = binarySearch(key1, key2);
        if (key1 != node->key1 || key2 != node->key2) {
            throw AVLElementNotFound();
        }
        return node->data;
    }

    bool insert(const T &data, int key1, int key2) {
        Node *parent = binarySearch(key1, key2);
        Node *new_node;
        if (parent != nullptr) {
            if (parent->key1 == key1 && parent->key2 == key2) return false;
            new_node = createVertex(parent, data, key1, key2);
        } else {
            new_node = new Node(data, key1, key2);
            root = new_node;
        }

        Node *p, *v = new_node;
        while (v != root) {
            p = v->parent;

            if (getHeight(p) >= getHeight(v) + 1) {
                if (p->right == v) {
                    p->h_right++;
                } else {
                    p->h_left++;
                }
                return true;
            }

            if (p->right == v) {
                p->h_right++;
            } else {
                p->h_left++;
            }

            if (abs(getBalanceFactor(p)) > 1) {
                if (getBalanceFactor(p) < 0) {
                    if (getBalanceFactor(p->right) < 0) {
                        roll_RR(p);
                    } else if (getBalanceFactor(p->right) > 0) {
                        roll_RL(p);
                    }
                } else if (getBalanceFactor(p) > 0) {
                    if (getBalanceFactor(p->left) < 0) {
                        roll_LR(p);
                    } else if (getBalanceFactor(p->left) > 0) {
                        roll_LL(p);
                    }
                }
                break;
            } else {
                v = p;
            }
        }
        return true;
    }

    bool remove(int key1, int key2) {
        Node *node = binarySearch(key1, key2);
        if (node == nullptr) return false;
        if (node->key1 != key1 || node->key2 != key2) return false;

        Node *v = deleteVertex(node);
        Node *p = nullptr;
        while (v != nullptr) {
            p = v->parent;

            v->h_right = getHeight(v->right);
            v->h_left = getHeight(v->left);

            if (abs(getBalanceFactor(v)) > 1) {
                int old_v_height = getHeight(v);
                if (getBalanceFactor(v) < 0) {
                    if (getBalanceFactor(v->right) < 0) {
                        roll_RR(v);
                    } else if (getBalanceFactor(v->right) > 0) {
                        roll_RL(v);
                    }
                } else if (getBalanceFactor(v) > 0) {
                    if (getBalanceFactor(v->left) < 0) {
                        roll_LR(v);
                    } else if (getBalanceFactor(v->left) > 0) {
                        roll_LL(v);
                    }
                }
                if (old_v_height == getHeight(v)) break;
                if (v == root) break;
            } else {
                if (v == root) break;
                v = p;
            }
        }
        return true;
    }

    static AVLTree merge(const AVLTree &tree1, const AVLTree &tree2) {
        int size_a = getSize(tree1.root);
        Node **a = new Node *[size_a];
        sortToArray(tree1.root, &a);

        int size_b = getSize(tree2.root);
        Node **b = new Node *[size_b];
        sortToArray(tree2.root, &b);

        int new_size = 0;
        Node **temp = mergeNodeArrays(a, size_a, b, size_b);
        Node **c = clearSameElements(temp, size_a + size_b, &new_size);

        return AVLTree(buildIncompleteTree(c, new_size));
    }

    T *inOrderToArray() {
        T *temp = new T[getSize(root)];
        T* result = temp;
        inOrderToArrayRecursive(root, &temp);
        return result;
    }

    T *preOrderToArray() {
        T *temp = new T[getSize(root)];
        T* result = temp;
        preOrderToArrayRecursive(root, &temp);
        return result;
    }
};

#endif //DATASTRUCTURES_HW1_AVLTREE_H
