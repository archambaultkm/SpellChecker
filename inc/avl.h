/**
 * @file AVL.h
 * @brief An AVL tree implementation.
 * @author Kaitlyn Archambault
 * @date 2023-11-08
 *
 * This file contains the definition of an AVL tree class template.
 */

#ifndef ASSIGNMENT_3_AVL_H
#define ASSIGNMENT_3_AVL_H

#include "bst.h"

/**
 * @class AVLNode
 * @brief Represents a node in the AVL tree.
 * @tparam T The type of data stored in the node.
 * @note Differs from BST node due to height factor
 */
template <class T>
class AVLNode {
public:
    T m_data; // the data stored in the node
    AVLNode* m_left; // pointer to left child
    AVLNode* m_right; // pointer to right child
    int m_height; // the height of the node relative to the end of the tree

    /**
    * @brief Constructs an AVLNode with the given data.
    * @param data The data to store in the node.
    */
    explicit AVLNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr), m_height(1) {}
};

/**
 * @class AVL
 * @brief Represents an AVL tree, a self-balancing binary search tree.
 * @tparam T The type of data stored in the tree.
 */
template <class T>
class AVL : public BST<T, AVLNode<T>> {
public:
    /**
     * @brief Inserts a new element with the specified data into the AVL tree.
     * @param data The data to be inserted.
     */
    void insert(T data) {
        this-> m_root = insert(data, this->m_root);
    }

    void remove(T data) {
        this-> m_root = remove(data, this->m_root);
    }

private:
    /**
     * @brief Get the height of a node.
     * @param node The node for which to get the height.
     * @return The height of the node or -1 if the node is nullptr.
     */
    int get_height(AVLNode<T>* node) {
        return node ? node->m_height : -1;
    }

    /**
     * @brief Get the balance factor of a node.
     * @param node The node for which to calculate the balance factor.
     * @return The balance factor (difference in heights of left and right subtrees).
     */
    int get_balance(AVLNode<T>* node) {
        return node ? (get_height(node->m_left) - get_height(node->m_right)) : 0;
    }

    /**
     * @brief Perform a right rotation on the given node.
     * @param node The node to be rotated.
     * @return The new root of the subtree after rotation.
     * @note Used when the tree is left-heavy
     */
    AVLNode<T>* rotate_right(AVLNode<T>* node) {
        AVLNode<T>* left = node->m_left;
        AVLNode<T>* temp = left->m_right;

        // Perform rotation
        left->m_right = node;
        node->m_left = temp;

        // Update heights
        node->m_height = std::max(get_height(node->m_left),
                               get_height(node->m_right)) + 1;
        left->m_height = std::max(get_height(left->m_left),
                               get_height(left->m_right)) + 1;

        // Return new root
        return left;
    }

    /**
     * @brief Perform a left rotation on the given node.
     * @param node The node to be rotated.
     * @return The new root of the subtree after rotation.
     * @note Used when the tree is right-heavy
     */
    AVLNode<T>* rotate_left(AVLNode<T>* node)
    {
        AVLNode<T>* right = node->m_right;
        AVLNode<T>* temp = right->m_left;

        // Perform rotation
        right->m_left = node;
        node->m_right = temp;

        // Update heights
        node->m_height = std::max(get_height(node->m_left),
                               get_height(node->m_right)) + 1;

        right->m_height = std::max(get_height(right->m_left),
                               get_height(right->m_right)) + 1;

        // Return new root
        return right;
    }

    /**
     * @brief Insert a new element with the specified data into the AVL tree.
     * @param data The data to be inserted.
     * @param node The current node in the AVL tree.
     * @return The new root of the subtree after insertion and balancing.
     */
    AVLNode<T>* insert(const T data, AVLNode<T>*& node) {
        // perform normal BST insert
        node = BST<T, AVLNode<T>>::insert(data, node);

        // update height of this node
        node->m_height = 1 + std::max(get_height(node->m_left), get_height(node->m_right));

        // get the balance factor of this node to see if it is unbalanced
        int balance = get_balance(node);

        // Left Left Case
        if (balance > 1 && data < node->m_left->m_data)
            return rotate_right(node);

        // Right Right Case
        if (balance < -1 && data > node->m_right->m_data)
            return rotate_left(node);

        // Left Right Case
        if (balance > 1 && data > node->m_left->m_data)
        {
            node->m_left = rotate_left(node->m_left);
            return rotate_right(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->m_right->m_data)
        {
            node->m_right = rotate_right(node->m_right);
            return rotate_left(node);
        }

        return node;
    }

    AVLNode<T>* remove(const T data, AVLNode<T>*& node) {
        // Perform normal BST remove
        node = BST<T, AVLNode<T>>::remove(data, node);

        // If the tree had only one node, return
        if (node == nullptr) {
            return node;
        }

        // update height of this node
        node->m_height = 1 + std::max(get_height(node->m_left), get_height(node->m_right));

        // get the balance factor of this node to see if it is unbalanced
        int balance = get_balance(node);

        // Left Left Case
        if (balance > 1 && data < node->m_left->m_data)
            return rotate_right(node);

        // Right Right Case
        if (balance < -1 && data > node->m_right->m_data)
            return rotate_left(node);

        // Left Right Case
        if (balance > 1 && data > node->m_left->m_data)
        {
            node->m_left = rotate_left(node->m_left);
            return rotate_right(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->m_right->m_data)
        {
            node->m_right = rotate_right(node->m_right);
            return rotate_left(node);
        }

        return node;
    }
};

#endif //ASSIGNMENT_3_AVL_H
