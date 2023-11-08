/**
 * @file BST.h
 * @brief A Binary Search Tree (BST) implementation.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 *
 * This file contains the definition of a Binary Search Tree (BST) class template.
 */

#ifndef ASSIGNMENT_3_BST_H
#define ASSIGNMENT_3_BST_H

#include "utils.h"

#include <iomanip>
#include <iostream>

/**
* @class Node
* @tparam T the type of data to store in the node
* @brief BST Nodes contain data and pointers to left and right subtree roots
*/
template <class T>
class Node {
public:
    T m_data; // the data stored in the node
    Node* m_left; // pointer to left child
    Node* m_right; // pointer to right child
    int m_height; // the height of the node relative to the root of the tree

    explicit Node(T data) : m_data(data), m_left(nullptr), m_right(nullptr), m_height(1) {}
};

/**
 * @class BST
 * @brief A class template for Binary Search Tree (BST).
 * @tparam T The type of data to be stored in the BST.
 */
template <class T>
class BST {
public:
    /**
     * @brief Default constructor.
     */
    BST() {
        m_root = nullptr;
    };

    /**
     * @brief Destructor removes each node in the tree.
     */
    virtual ~BST() {
        if (m_root) {
            remove(m_root->m_data);
            delete m_root;
        }
        m_root = nullptr;
    }

    /**
     * @brief Entry point to recursive find()
     *
     * @param data The data to search for in the BST
     */
    bool find(T data) {
        return (find(data, m_root) != nullptr);
    }

    /**
     * @brief Check if the BST contains any data
     *
     * @return True if root node is null, false otherwise
     */
    bool is_empty() {
        return m_root == nullptr;
    }

    /**
     * @brief Entry point to recursive find_closest_value()
     *
     * @param data The data to find an approximate match for
     * @return The data that was deemed the closest match
     */
    T find_closest_value(T data) {
        Node<T>* closest_match = nullptr;
        int starting_distance = std::numeric_limits<int>::max();
        Node<T>* closest_node = find_closest_value(data, m_root, closest_match, starting_distance);

        return closest_node->m_data;
    }

    /**
     * @brief Entry point to recursive remove()
     *
     * @param data The data to remove
     */
    void remove(T data) {
        remove(data, m_root);
    }

    virtual /**
     * @brief Entry point to recursive insert()
     *
     * @param data The data to insert
     */
    void insert(T data) {
        m_root = insert(data, m_root);
    }

    /**
     * @brief Entry point to recursive build_balanced()
     *
     * @param sorted_list the sorted vector of information to turn into a tree
     */
    void build_balanced(std::vector<T> sorted_list) {
        build_balanced(sorted_list, 0, sorted_list.size() - 1);
    }

    /**
     * @brief Entry point to recursive print_tree()
     *
     * @param output The output stream where the tree will be printed.
     * @param indent The starting indentation.
     */
    void print_tree(std::ostream& output, int indent) {
        print_tree(output, m_root, indent);
    }

protected:
    Node<T>* m_root; // pointer to root node of the entire tree

    /**
     * @brief Recursively search for data in the BST.
     *
     * @param data The data to search for.
     * @param node The current node being searched.
     * @return A pointer to the node where the data was found, or nullptr if not found.
     */
    Node<T>* find(const T data, Node<T>* node) {
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

    /**
     * @brief Recursively try to find the value closest to the given data in the BST.
     *
     * @param given_value The data to find the closest match for.
     * @param node The current node being searched.
     * @param closest_match The closest matching node found so far.
     * @return A pointer to the closest matching node.
     */
    Node<T>* find_closest_value(T given_value, Node<T>* node, Node<T>*& closest_match, int& min_difference) {
        if (!node) {
            // Reached the end without finding the value, return the last closest match
            return closest_match;
        }

        // determine the difference between values
        int this_difference = difference(given_value, node->m_data);

        // update the smallest difference found if applicable
        if (this_difference <= min_difference) {
            closest_match = node;
            min_difference = this_difference;
        }

        // choose a direction to keep searching the tree
        if (given_value == node->m_data) {
            // value exists in the tree
            return node;

        } else if (given_value < node->m_data) {
            //given value is smaller, move left
            return find_closest_value(given_value, node->m_left, closest_match, min_difference);

        } else {
            //given value is larger, move right
            return find_closest_value(given_value, node->m_right, closest_match, min_difference);
        }
    }

    /**
     * @brief Print the tree with attractive formatting.
     *
     * @param output The output stream where the tree will be printed.
     * @param node The current node being printed.
     * @param indent The current indentation- will be smallest for root node, largest for leaf nodes.
     */
    void print_tree(std::ostream& output, Node<T>*& node, int indent) {
        if (node) {
            print_tree(output, node->m_right, indent + 15);
            output << std::setw(indent) << node->m_data << std::endl;
            print_tree(output, node->m_left, indent + 15);
        }
    }

    /**
     * @brief Overload of the insertion operator to print the BST to an output stream.
     */
    friend std::ostream& operator<<(std::ostream& output, BST& bst){
        bst.print_tree(output, bst.m_root, 0);
        return output;
    }

    /**
     * @brief Find the node with the minimum value in the BST.
     *
     * This function tunnels as far left as possible to find the node with the smallest value.
     *
     * @param node The starting node for the search.
     * @return A pointer to the node with the minimum value.
     */
    Node<T>* find_min(Node<T>* node) {
        while (node->m_left) {
            node = std::move(node->m_left);
        }

        return node;
    }

    /**
    * @brief Remove a node from the BST.
    *
    * This function removes a node with the given data from the BST and handles various cases
    * (i.e., node with no children, one child, or two children).
    *
    * @param data The data to be removed from the BST.
    * @param node A reference to the current node being searched for that data.
    * @return A pointer to the node that took the place of the deleted node.
    */
    Node<T>* remove(const T data, Node<T>*& node) {
        if (data < node->m_data) {
            // data might be found along the left branch
            node-> m_left = remove(data, node->m_left);

        } else if (data > node->m_data) {
            // data might be found along the right branch
            node-> m_right = remove(data, node->m_right);

        } else {
            // have reached the desired node to delete
            if (!node->m_right) {
                // node only has left child
                Node<T>* temp = node->m_left;
                free(node);
                return temp;

            } else if (!node->m_left) {
                // Node only has right child
                Node<T>* temp = node->m_right;
                free(node);
                return temp;
            }

            // node has two children
            // always replace with right side + don't keep track of parent
            Node<T>* temp = find_min(node->m_right);
            node->m_data = temp->m_data;
            node->m_right = remove(node->m_data, node->m_right);
        }

        return node;
    }

    virtual /**
     * @brief Recursively attempt to insert a node at the appropriate spot in an existing tree.
     *
     * @param data The data to be inserted into the BST.
     * @param node A reference to the current node in the BST.
     */
    Node<T>* insert(const T data, Node<T>*& node) {
        if (!node) {
            // reached the bottom of the tree
            return new Node<T>(data);

        } else if (data < node->m_data) {
            // left leaf
            node->m_left = insert(data, node->m_left);

        } else if (data > node->m_data) {
            // right leaf
            node->m_right = insert(data, node-> m_right);

        } else {
            // no duplicate values
            return node;
        }

        return node;
    }

    /**
     * @brief Recursively build a balanced BST from a sorted list.
     *
     * @param sorted_list The sorted list of data to build the balanced BST from.
     * @param left_bound The left boundary of the current sub-list.
     * @param right_bound The right boundary of the current sub-list.
     * @note The initial call should have `left_bound` set to 0 and `right_bound` set to the list's size.
    */
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
};
#endif //ASSIGNMENT_3_BST_H
