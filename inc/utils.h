/**
 * @file utils.h
 * @brief Contains various helper functions not specific to this assignment.
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */

#ifndef ASSIGNMENT_3_UTILS_H
#define ASSIGNMENT_3_UTILS_H

#include <string>

// remove non-alphabet characters from provided string
std::string remove_non_alpha(const std::string& str) {

    std::string corrected;

    for (char c : str) {
        if (std::isalpha(c)) {
            corrected += c;
        }
    }

    return corrected;
}

// return a vector of all words found in a text file
std::vector<std::string> get_vec_from_file(const std::string& file_path) {
    // read the file at the provided file path into vector
    std::ifstream ifs;
    std::string line;
    std::vector<std::string> words;

    // attempt to open the provided file and read its contents into the dictionary list
    try {
        ifs.open(file_path, std::fstream::in);

        while (getline(ifs, line, ' ')) {
            words.push_back(line);
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading file to dynamic array" << std::endl;
    }

    return words;
}

#endif //ASSIGNMENT_3_UTILS_H
