/**
 * @file Dictionary.h
 * @brief Definition of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#ifndef ASSIGNMENT_3_DICTIONARY_H
#define ASSIGNMENT_3_DICTIONARY_H

#include "bst.h"
#include "timer.h"
#include "avl.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

/**
 * @class Dictionary
 * @brief An extension of a BST that includes file i/o functionality.
 */
class Dictionary {
private:
    Timer<> m_timer; // timer using default high-res clock to time building the dictionary
    SearchTreeBase<std::string>* m_tree;

public:
    /**
     * @brief Using a sorted vector of words from the provided file path,
     * builds a balanced BST
     *
     * @param file_name validated file path for dictionary words
     */
    Dictionary(const std::string& file_name, SearchTreeBase<std::string>* tree_ptr);

    /**
    * @brief Get the elapsed time for building the dictionary tree.
    *
    * @return The elapsed time in microseconds.
    */
    long get_elapsed_time();

    /**
     * @brief Save a nicely formatted representation of the BST to a file.
     *
     * @param file_path The file path where the BST visualization will be saved.
     */
    void save_to_file(const std::string& file_path);

    bool find(std::string data);

    std::string find_closest_value(std::string data);

    bool is_empty();
};

#endif //ASSIGNMENT_3_DICTIONARY_H
