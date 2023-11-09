/**
 * @file Dictionary.h
 * @brief Definition of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#ifndef ASSIGNMENT_3_DICTIONARY_H
#define ASSIGNMENT_3_DICTIONARY_H

#include "bst.h"
#include "avl.h"
#include "timer.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

/**
 * @class Dictionary
 * @brief An extension of a BST that reads a list of strings from a file and builds a balanced tree.
 */
template <typename Tree = BST<std::string>>
class DictionaryBase : public Tree {
protected:
    Timer<> m_timer; // timer using default clock to time building the dictionary

public:
    // type must be string for a dictionary
    using T = std::string;

    DictionaryBase() = default;

    /**
     * @brief Constructor for Dictionary when Tree is BST<std::string>
     *
     * Create a Dictionary object from a text file.
     *
     * Initializes a balanced BST from a vector of values in the provided file.
     *
     * @param file_name The path to the file containing data.
     */
//    explicit DictionaryBase(const std::string& file_name) : Tree() {
//        //start the timer
//        m_timer.start();
//
//        // build a balanced BST using an ordered list
//        std::vector<std::string> ordered_list = get_vec_from_file(file_name);
//        //  make sure it's in alphabetical order
//        std::sort(ordered_list.begin(), ordered_list.end());
//        Tree::build_balanced(ordered_list);
//
//        // stop the timer
//        m_timer.stop();
//    }

    /**
    * @brief Get the elapsed time for building the dictionary tree.
    *
    * @return The elapsed time in microseconds.
    */
    long get_elapsed_time() {
        return m_timer.get_elapsed_time();
    }

    /**
     * @brief Save a nicely formatted representation of the BST to a file.
     *
     * @param file_path The file path where the BST visualization will be saved.
     */
    void save_to_file(const std::string& file_path) {
        std::ofstream ofs;
        std::string line;

        try {
            //overwrite the file completely if it already exists
            ofs.open(file_path, std::fstream::trunc);

            //copy the bst into the file
            Tree::print_tree(ofs, 5);

        } catch (std::ofstream::failure &e) {
            std::cerr << "Exception saving Dictionary to provided file path: " << file_path << std::endl;
        }

        std::cout << "Visualization of dictionary saved to " << file_path << std::endl;
    }
};

// Primary template for Dictionary with a generic Tree type.
template <typename Tree = BST<std::string>>
class Dictionary : public Tree {
public:
    Dictionary() : Tree() {
    }
};

// Constructor specialization for AVL tree
template <>
class Dictionary<AVL<std::string>> : public DictionaryBase<AVL<std::string>> {
public:
    explicit Dictionary(const std::string& file_name) {
        //start the timer
        m_timer.start();

        // read the file at the provided file path into vector
        std::ifstream ifs;
        std::string line;

        // attempt to open the provided file and read its contents into the tree
        try {
            ifs.open(file_name, std::fstream::in);

            while (getline(ifs, line)) {
                // Split the line into words based on spaces
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    this->insert(word);
                }
            }

        } catch (std::ifstream::failure &e) {
            std::cout << "Exception reading file to AVL" << std::endl;
        }

        //stop the timer
        m_timer.stop();
    }
};

// Constructor specialization for BST tree.
template <>
class Dictionary<BST<std::string>> : public DictionaryBase<BST<std::string>> {
public:
    explicit Dictionary(const std::string& file_name) {
        //start the timer
        m_timer.start();

        // build a balanced BST using an ordered list
        std::vector<std::string> ordered_list = get_vec_from_file(file_name);
        //  make sure it's in alphabetical order
        std::sort(ordered_list.begin(), ordered_list.end());
        build_balanced(ordered_list);

        // stop the timer
        m_timer.stop();
    }
};


#endif //ASSIGNMENT_3_DICTIONARY_H
