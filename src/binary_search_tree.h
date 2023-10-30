//
// Created by Kaitlyn Archambault on 2023-10-30.
//

#ifndef ASSIGNMENT_3_BINARY_SEARCH_TREE_H
#define ASSIGNMENT_3_BINARY_SEARCH_TREE_H

#include <memory>
#include <iomanip>

template <class T>
class BST {
private:
    struct Node {
        T m_data;
        std::unique_ptr<Node> m_left;
        std::unique_ptr<Node> m_right;
    };

    std::unique_ptr<Node> m_root;
    int m_height;

protected:
    bool find(const T data, std::unique_ptr<Node>& node) {
        if (!node) {
            // reached the bottom without finding data
            return false;
        } else if (data < node->m_data) {
            find(data, node->m_left);
        } else if (data > node->m_data) {
            find(data, node->m_right);
        } else {
            // data is present at the current node
            return true;
        }
    }

    void print_tree(std::ostream& output, std::unique_ptr<Node>& node, int indent) {
        if (node) {
            print_tree(output, node->m_right, indent + 8);
            output << std::setw(indent) << node->m_data << std::endl;
            print_tree(output, node->m_left, indent + 8);
        }
    }

    friend std::ostream& operator<<(std::ostream& output, BST& bst){
        bst.print_tree(output, bst.m_root, 0);
        return output;
    }

    // tunnel as far left as possible
    Node* find_min(std::unique_ptr<Node>& node) {
        while (node->m_left) {
            node = node->m_left;
        }

        return node;
    }

    Node* remove(const T data, std::unique_ptr<Node>& node) {

        if (data < node->m_data) {
            node-> m_left = remove(node->m_left, data);
        } else if (data > node->m_data) {
            node-> m_right = remove(node->m_right, data);
        } else {
            //have reached the desired node to delete
            if (!node->m_right) {
                // node only has left child
                Node* temp = node->m_left;
                free(node);
                return temp;
            } else if (!node->m_left) {
                // Node only has right child
                Node* temp = node->m_right;
                free(node);
                return temp;
            }

            // node has two children
            //always replace with right side to avoid keeping track of parent
            Node* temp = find_min(node->m_right);
            node->m_data = temp->m_data;
            node->m_right = remove(node->m_right, node->m_data);
        }

        return node;
    }

    void insert(const T data, std::unique_ptr<Node>& node) {
        if (!node) {
            // reached the bottom of the tree
            node = std::make_unique<Node>();
            node-> m_data = data;
        } else if (data < node->m_data) {
            // left leaf
            insert(data, node-> m_left);
        } else if (data > node->m_data) {
            // right leaf
            insert(data, node-> m_right);
        } else {
            // data is already present in tree
            // todo do anything?
        }
    }

public:
    BST(){
        m_root = nullptr;
        m_height = 0;
    };

    ~BST() = default;

    void balance() {
        // just balance it idk
    }

    bool find(T data) {
        find(data, m_root);
    }

    void remove(T data) {
        remove(data, m_root);
    }

    void insert(T data) {
        insert(data, m_root);
    }
};
#endif //ASSIGNMENT_3_BINARY_SEARCH_TREE_H
