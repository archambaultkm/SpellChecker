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

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

/**
 * @class Dictionary
 * @brief An extension of a BST that includes file i/o functionality.
 */
class Dictionary : public BST<std::string> {
private:
    Timer<> m_timer; // timer using default high-res clock to time building the dictionary

    /**
     * @brief Recursively build a balanced BST from a sorted list.
     *
     * @param sorted_list The sorted list of data to build the balanced BST from.
     * @param left_bound The left boundary of the current sub-list.
     * @param right_bound The right boundary of the current sub-list.
     * @note The initial call should have `left_bound` set to 0 and `right_bound` set to the list's size.
    */
    void build_balanced(std::vector<std::string> sorted_list, int left_bound, int right_bound);

public:
    /**
     * @brief Using a sorted vector of words from the provided file path,
     * builds a balanced BST
     *
     * @param file_name validated file path for dictionary words
     */
    explicit Dictionary(const std::string& file_name);

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
};

#endif //ASSIGNMENT_3_DICTIONARY_H
