#pragma once

#include <stdexcept>
#include <optional>
#include "AVLNode.h"

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int getHeight(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(AVLNode<T>* node) {
        if (node)
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    AVLNode<T>* findMin(AVLNode<T>* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    AVLNode<T>* findMax(AVLNode<T>* node) {
        while (node && node->right)
            node = node->right;
        return node;
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        x->right = y;
        y->left = T2;
        if (T2) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        y->left = x;
        x->right = T2;
        if (T2) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode<T>* rebalance(AVLNode<T>* node) {
        updateHeight(node);
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode<T>* insert(AVLNode<T>* node, T& key) {
        if (!node) return new AVLNode<T>(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
            node->left->parent = node;
        }
        else if (key > node->key) {
            node->right = insert(node->right, key);
            node->right->parent = node;
        }
        else
            return node; // ƒубликаты не вставл€ютс€
        return rebalance(node);
    }

    AVLNode<T>* remove(AVLNode<T>* node, T& key) {
        if (!node) return node;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode<T>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else {
                AVLNode<T>* temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }
        if (!node) return node;
        return rebalance(node);
    }

    AVLNode<T>* search(AVLNode<T>* node, T& key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert( T& key) {
        root = insert(root, key);
    }

    void remove( T& key) {
        root = remove(root, key);
    }

    T findSuccessor(T key) {
        AVLNode<T>* keyNode = search(root, key);
        T value = T();
        if (keyNode != nullptr) {
            if (keyNode->right != nullptr)
                value = findMin(keyNode->right)->key;
            else {
                AVLNode<T>* current = keyNode;
                AVLNode<T>* parent = keyNode->parent;
                while (parent != nullptr && parent->right == current) {
                    current = parent;
                    parent = parent->parent;
                }
                if (parent != nullptr)
                    value = parent->key;
            }
        }
        return value;
    }

    T findPredecessor(T key) {
        AVLNode<T>* keyNode = search(root, key);
        T value = T();
        if (keyNode != nullptr) {
            if (keyNode->left != nullptr)
                value = findMax(keyNode->left)->key;
            else {
                AVLNode<T>* current = keyNode;
                AVLNode<T>* parent = keyNode->parent;
                while (parent != nullptr && parent->left == current) {
                    current = parent;
                    parent = parent->parent;
                }
                if (parent != nullptr)
                    value = parent->key;
            }
        }
        return value;
    }
};
