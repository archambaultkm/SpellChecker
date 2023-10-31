//
// Created by Kaitlyn Archambault on 2023-10-31.
//

#ifndef ASSIGNMENT_3_UTILS_H
#define ASSIGNMENT_3_UTILS_H

#include <string>

// remove non-alphabet characters from provided string
std::string remove_non_alpha(std::string str) {

    std::string corrected;

    for (char c : str) {
        if (std::isalpha(c)) {
            corrected += c;
        }
    }

    return corrected;
}

std::vector<std::string> get_vec_from_file(std::string file_path) {
    // read the file at the provided file path into vector
    std::ifstream ifs;
    std::string line;
    std::vector<std::string> words_to_check;

    // attempt to open the provided file and read its contents into the dictionary list
    try {
        ifs.open(file_path, std::fstream::in);

        //todo split at the space
        while (getline(ifs, line, ' ')) {
            words_to_check.push_back(line);
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading file to dynamic array" << std::endl;
    }

    return words_to_check;
}

#endif //ASSIGNMENT_3_UTILS_H
