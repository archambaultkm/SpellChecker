//
// Created by Kaitlyn Archambault on 2023-10-31.
//

#ifndef ASSIGNMENT_3_UTILS_H
#define ASSIGNMENT_3_UTILS_H

#include <string>

// util function to remove non-alpha characters from provided string
std::string remove_non_alpha(std::string str) {
    std::string corrected;

    for (char c : str) {
        if (std::isalpha(c)) {
            corrected += c;
        }
    }

    return corrected;
}

#endif //ASSIGNMENT_3_UTILS_H
