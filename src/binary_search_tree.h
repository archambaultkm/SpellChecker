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
        int m_height;
        Node* m_left;
        Node* m_right;
    };

    Node* m_root;

protected:
    bool find(const T data, Node* node) {
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

    void print_tree(std::ostream& output, Node*& node, int indent) {
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
    Node* find_min(Node* node) {
        while (node->m_left) {
            node = std::move(node->m_left);
        }

        return std::move(node);
    }

    Node* remove(const T data, Node*& node) {

        if (!node) {
            return nullptr;
        }

        if (data < node->m_data) {
            node-> m_left = remove(data, node->m_left);
        } else if (data > node->m_data) {
            node-> m_right = remove(data, node->m_right);
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
            node->m_right = remove(node->m_data, node->m_right);
        }

        return node;
    }

    void insert(const T data, Node*& node) {
        if (!node) {
            // reached the bottom of the tree
            node = new Node();
            node-> m_data = data;

            //return node;

        } else if (data < node->m_data) {
            // left leaf
            insert(data, node-> m_left);

        } else if (data > node->m_data) {
            // right leaf
            insert(data, node-> m_right);

        } else {
            // data is already present in tree
            //return node;
        }

        //node = balance(node, data);
    }

//    Node* right_rotate(SmartNode y) {
//        SmartNode x = y->m_left;
//        SmartNode temp = x->m_right;
//
//        // rotate
//        x->m_right = y;
//        y->m_left = temp;
//
//        // update node height data
//        y->m_height = 1 + max(y->m_left->m_height, y->m_right->m_height);
//        x->m_height = 1 + max(x->m_left->m_height, x->m_right->m_height);
//
//        // return the node that took the place of the passed node's previous location in the tree
//        return x;
//    }
//
//    SmartNode left_rotate(SmartNode x) {
//        SmartNode y = x->m_left;
//        SmartNode temp = y->m_left;
//
//        // rotate
//        y->m_left = x;
//        x->m_right = temp;
//
//        // update node height data
//        x->m_height = 1 + max(x->m_left->m_height, x->m_right->m_height);
//        y->m_height = 1 + max(y->m_left->m_height, y->m_right->m_height);
//
//        // return the node that took the place of the passed node's previous location in the tree
//        return y;
//    }

    Node* balance(Node* node, T data) {
        // total height of subtree at this root is 1 (for itself) + the larger height of its branches
        node->m_height = 1 + max(node->m_left->m_height, node->m_right->m_height);

        // get the balance factor for this subtree
        int balance = node->m_left->m_height - node->m_right->m_height;

        // left left
        if (balance > 1 && data < node->m_left->m_data) {
            return right_rotate(node);
        }
        // left right
        if (balance > 1 && data > node->m_left->m_data) {
            node->m_left = left_rotate(node->m_left);
            return right_rotate(node);
        }
        // right left
        if (balance < -1 && data < node->m_right->m_data) {
            node->m_right = right_rotate(node->m_right);
            return left_rotate(node);
        }
        // right right
        if (balance < -1 && data > node->m_right->m_data) {
            return left_rotate(node);
        }
    }

    // util function to get the larger of two int values
    int max(int a, int b) {
        return (a > b)? a : b;
    }

public:
    BST(){
        m_root = nullptr;
    };

    ~BST() = default;

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
