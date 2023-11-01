/**
 * @file BST.h
 * @brief A Binary Search Tree (BST) implementation.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 *
 * This file contains the definition of a Binary Search Tree (BST) class template.
 */

#ifndef ASSIGNMENT_3_BINARY_SEARCH_TREE_H
#define ASSIGNMENT_3_BINARY_SEARCH_TREE_H

#include <memory>
#include <iomanip>
#include <fstream> // TODO I don't want this here
#include <iostream> // or this

/**
 * @class BST
 * @brief A class template for Binary Search Tree (BST).
 * @tparam T The type of data to be stored in the BST.
 */
template <class T>
class BST {
private:
    /**
     * @struct Node
     */
    struct Node {
        T m_data; // the data stored in the node
        Node* m_left; // pointer to left subtree root
        Node* m_right; // pointer to right subtree root
    };

    Node* m_root; // pointer to root node of the entire tree

    /**
     * @brief Recursively search for data in the BST.
     *
     * @param data The data to search for.
     * @param node The current node being searched.
     * @return A pointer to the node where the data was found, or nullptr if not found.
     */
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

    /**
     * @brief Recursively try to find the value closest to the given data in the BST.
     *
     * @param given_value The data to find the closest match for.
     * @param node The current node being searched.
     * @param closest_match The closest matching node found so far.
     * @return A pointer to the closest matching node.
     *
     * @note this doesn't work very accurately because if the value isn't found it just tunnels to the end of that branch
     */
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

    /**
     * @brief Print the tree with attractive formatting.
     *
     * @param output The output stream where the tree will be printed.
     * @param node The current node being printed.
     * @param indent The current indentation- will be smallest for root node, largest for leaf nodes.
     */
    void print_tree(std::ostream& output, Node*& node, int indent) {
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
    Node* find_min(Node* node) {
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
    Node* remove(const T data, Node*& node) {
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
            // always replace with right side + don't keep track of parent
            Node* temp = find_min(node->m_right);
            node->m_data = temp->m_data;
            node->m_right = remove(node->m_data, node->m_right);
        }

        return node;
    }

    /**
     * @brief Recursively attempt to insert a node at the appropriate spot in an existing tree.
     *
     * @param data The data to be inserted into the BST.
     * @param node A reference to the current node in the BST.
     */
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

        }
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
        remove(m_root->m_data);
        delete m_root;
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
     * @note this doesn't work yet
     */
    T find_closest_value(T data) {
        Node* closest_node = find_closest_value(data, m_root, m_root);

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

    /**
     * @brief Entry point to recursive insert()
     *
     * @param data The data to insert
     */
    void insert(T data) {
        insert(data, m_root);
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
     * @brief Save a nicely formatted representation of the BST to a file.
     *
     * @param file_path The file path where the BST visualization will be saved.
     * @return True if the save operation was successful, false otherwise.
     */
    void save_to_file(const std::string& file_path) {
        std::ofstream ofs;
        std::string line;

        try {
            //overwrite the file completely if it already exists
            ofs.open(file_path, std::fstream::trunc);

            //copy the bst into the file
            print_tree(ofs, m_root, 5);

        } catch (std::ofstream::failure &e) {
            std::cerr << "Exception saving BST to provided file path: " << file_path << std::endl;
        }

        std::cout << "Visualization of BST saved to " << file_path << "\n\n";
    }
};
#endif //ASSIGNMENT_3_BINARY_SEARCH_TREE_H
