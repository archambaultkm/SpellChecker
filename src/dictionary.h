/**
 * @file Dictionary.h
 * @brief Definition of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#ifndef ASSIGNMENT_3_DICTIONARY_H
#define ASSIGNMENT_3_DICTIONARY_H

#include <vector>
#include <string>
#include "binary_search_tree.h"

/**
 * @class Dictionary
 * @brief An extension of a BST that reads a list of strings from a file and builds a balanced tree.
 */
class Dictionary : public BST<std::string> {
public:
    /**
     * @brief Constructor to create a Dictionary object from a text file.
     *
     * Initializes a balanced BST from values in the provided file.
     *
     * @param file_name The path to the file containing data.
     */
    explicit Dictionary(std::string file_name);
};


#endif //ASSIGNMENT_3_DICTIONARY_H
