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
     * @brief Build a dictionary from a file and return it.
     *
     * @param dictionary_path The path to the file containing dictionary data.
     * @param tree_output_path The path to save the binary search tree for review.
     * @return A Dictionary object representing the built and balanced dictionary.
     *
     * @note The function prints the time taken to build and balance the dictionary using cout.
     */
    static Dictionary build_and_save(const std::string& dictionary_path, const std::string& tree_output_path);

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

    /**
     * @brief see if a word exists in the dictionary's search tree
     *
     * @param data the word to find
     * @return true if the word can be found, false if not
     */
    bool find(std::string data);

    /**
     * @brief find the closest word in the dictionary's search tree
     *
     * @param data the word to find a suggestion for
     * @return std::string
     * @note not accurate
     */
    std::string find_closest_value(std::string data);

    /**
     * @brief Check if the dictionary is empty
     *
     * @return true if empty, false if not
     */
    bool is_empty();
};

#endif //ASSIGNMENT_3_DICTIONARY_H
