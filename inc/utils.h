/**
 * @file utils.h
 * @brief Contains various helper functions not specific to this assignment.
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */

#ifndef ASSIGNMENT_3_UTILS_H
#define ASSIGNMENT_3_UTILS_H

#include <string>
#include <regex>
#include <fstream>
#include <iostream>

// remove non-alphabet characters from a provided string
inline std::string remove_non_alpha(const std::string& str) {

    std::string corrected;

    for (char c : str) {
        if (std::isalpha(c)) {
            corrected += c;
        }
    }

    return corrected;
}

// return a vector of all words found in a text file
inline std::vector<std::string> get_vec_from_file(const std::string& file_path) {
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

/**
 * Validate provided file path with regex
 *
 * @param provided_file_path file path input by user
 * @param extension desired file extension
 *
 * @returns true if the provided file path is in a valid format, false otherwise
 * @note in the future it would be nice to be able to provide multiple extensions
 */
inline bool is_valid_file_path(const std::string &provided_file_path, std::string extension) {

    std::string extension_regex = extension.empty() ? "" : ("\\." + extension);
    std::string path_regex = R"(^(?:..)?\/?(?:[a-zA-Z0-9_-]+[\/])?(?:[a-zA-Z0-9_-]+)" + extension_regex + "$)";
    std::regex valid_file_path(path_regex);

    return std::regex_match(provided_file_path, valid_file_path);
}

#endif //ASSIGNMENT_3_UTILS_H
