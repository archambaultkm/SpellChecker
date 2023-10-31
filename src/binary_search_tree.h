//
// Created by Kaitlyn Archambault on 2023-10-30.
//

#ifndef ASSIGNMENT_3_BINARY_SEARCH_TREE_H
#define ASSIGNMENT_3_BINARY_SEARCH_TREE_H

#include <memory>
#include <iomanip>
#include <fstream> // TODO I don't want this here
#include <iostream> // or this

template <class T>
class BST {
private:
    struct Node {
        T m_data;
        Node* m_left;
        Node* m_right;
    };

    Node* m_root;

protected:
    // recursively search for data, and return the node where it was found
    // nullptr is an acceptable return value
    Node* find(const T data, Node* node) {
        if (!node || data == node->m_data) {
            // either reached the end without finding data, or it's present at the current node
            return node;

        } else if (data < node->m_data) {
            // data might be found along left branch
            return find(data, node->m_left);

        } else {
            // data might be found along right branch
            return find(data, node->m_right);
        }
    }

    // recursively try to find the value closest to the given one (whether it exists in the tree or not)
    Node* find_closest_value(T given_value, Node* node, Node* closest_match) {
        if (!node) {
            // reached the end without finding the value, return the last closest match
            return closest_match;

        } else if (given_value == node->m_data) {
            // value exists in the tree
            return node;

        } else if (given_value < node->m_data) {
            //given value is smaller, move left and update closest match
            return find_closest_value(given_value, node->m_left, node);

        } else {
            //given value is larger, move right and update closest match
            return find_closest_value(given_value, node->m_right, node);
        }
    }

    // print the tree with attractive formatting
    void print_tree(std::ostream& output, Node*& node, int indent) {
        if (node) {
            print_tree(output, node->m_right, indent + 15);
            output << std::setw(indent) << node->m_data << std::endl;
            print_tree(output, node->m_left, indent + 15);
        }
    }

    // << operator
    friend std::ostream& operator<<(std::ostream& output, BST& bst){
        bst.print_tree(output, bst.m_root, 0);
        return output;
    }

    // tunnel as far left as possible
    Node* find_min(Node* node) {
        while (node->m_left) {
            node = std::move(node->m_left);
        }

        return node;
    }

    Node* remove(const T data, Node*& node) {
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
            // always replace with right side to avoid keeping track of parent
            Node* temp = find_min(node->m_right);
            node->m_data = temp->m_data;
            node->m_right = remove(node->m_data, node->m_right);
        }

        return node;
    }

    // recursively attempt to insert a node at the appropriate spot in an existing tree
    void insert(const T data, Node*& node) {
        if (!node) {
            // reached the bottom of the tree
            node = new Node();
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

    // recursively builds a balanced bst from a sorted list
    // initial call will have left_bound set to 0 and right_bound set to sorted_list's size
    void build_balanced(std::vector<T> sorted_list, int left_bound, int right_bound){
        if (left_bound > right_bound) {
            return; //means that list has been depleted
        }

        int midpoint = (left_bound+right_bound) / 2;

        // insert new subtree root
        insert(sorted_list.at(midpoint));
        // branch left
        build_balanced(sorted_list, left_bound, midpoint-1);
        // branch right
        build_balanced(sorted_list, midpoint+1, right_bound);
    }

public:
    BST() {
        m_root = nullptr;
    };

    ~BST() = default;

    bool find(T data) {
        return (find(data, m_root) != nullptr);
    }

    T find_closest_value(T given_value) {
        Node* closest_node = find_closest_value(given_value, m_root, m_root);

        return closest_node->m_data;
    }

    void remove(T data) {
        remove(data, m_root);
    }

    void insert(T data) {
        insert(data, m_root);
    }

    void build_balanced(std::vector<T> sorted_list) {
        build_balanced(sorted_list, 0, sorted_list.size() - 1);
    }

    bool save_to_file(std::string file_name) {
        std::ofstream ofs;
        std::string line;

        try {
            //overwrite the file completely if it already exists
            ofs.open(file_name, std::fstream::trunc);

            //copy the bst into the file
            print_tree(ofs, m_root, 5);

        } catch (std::ofstream::failure &e) {
            return false;
        }

        return true;
    }

};
#endif //ASSIGNMENT_3_BINARY_SEARCH_TREE_H
