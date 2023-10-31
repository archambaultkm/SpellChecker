//
// Created by Kaitlyn Archambault on 2023-10-30.
//

#ifndef ASSIGNMENT_3_DICTIONARY_H
#define ASSIGNMENT_3_DICTIONARY_H

#include <vector>
#include <string>
#include "binary_search_tree.h"

class Dictionary : public BST<std::string> {
public:
    Dictionary() = default;
    Dictionary(std::string file_name);
    ~Dictionary() = default;
};


#endif //ASSIGNMENT_3_DICTIONARY_H
