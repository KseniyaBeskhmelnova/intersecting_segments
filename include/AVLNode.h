#pragma once

template <typename T>
class AVLNode {
public:
    T key;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;

    AVLNode(const T& value) : key(value), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};