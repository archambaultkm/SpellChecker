//
// Created by Kaitlyn Archambault on 2023-11-08.
//

#ifndef ASSIGNMENT_3_AVL_H
#define ASSIGNMENT_3_AVL_H

#include "bst.h"

template <class T>
class AVL : public BST<T> {
public:
    void insert(T data) {
        this-> m_root = insert(data, this->m_root);
    }

private:
    int get_height(Node<T>* node) {
        return node ? node->m_height : -1;
    }

    int get_balance(Node<T>* node) {
        return node ? (get_height(node->m_left) - get_height(node->m_right)) : 0;
    }

    Node<T>* rotate_right(Node<T>* y) {
        Node<T>* x = y->m_left;
        Node<T>* T2 = x->m_right;

        // Perform rotation
        x->m_right = y;
        y->m_left = T2;

        // Update heights
        y->m_height = std::max(get_height(y->m_left),
                               get_height(y->m_right)) + 1;
        x->m_height = std::max(get_height(x->m_left),
                               get_height(x->m_right)) + 1;

        // Return new root
        return x;
    }

    Node<T>* rotate_left(Node<T>* x)
    {
        Node<T>* y = x->m_right;
        Node<T>* T2 = y->m_left;

        // Perform rotation
        y->m_left = x;
        x->m_right = T2;

        // Update heights
        x->m_height = std::max(get_height(x->m_left),
                               get_height(x->m_right)) + 1;

        y->m_height = std::max(get_height(y->m_left),
                               get_height(y->m_right)) + 1;

        // Return new root
        return y;
    }

    Node<T>* insert(const T data, Node<T>*& node) {
        node = BST<T>::insert(data, node);

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
