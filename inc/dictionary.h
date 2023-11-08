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
#include <fstream>

/**
 * @class Dictionary
 * @brief An extension of a BST that reads a list of strings from a file and builds a balanced tree.
 */
class Dictionary : public BST<std::string> {
private:
    Timer<> m_timer; // timer using default clock to time building the dictionary

public:
    /**
     * @brief Constructor to create a Dictionary object from a text file.
     *
     * Initializes a balanced BST from values in the provided file.
     *
     * @param file_name The path to the file containing data.
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
