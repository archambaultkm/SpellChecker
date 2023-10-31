//
// Created by Kaitlyn Archambault on 2023-10-30.
//

#include "dictionary.h"
#include <fstream>
#include <iostream>

Dictionary::Dictionary(std::string file_name) {
    std::ifstream ifs;
    std::string line;
    std::vector<std::string> ordered_list;

    //attempt to open the provided file and read its contents into the dictionary list
    try {
        ifs.open(file_name, std::fstream::in);

        while (getline(ifs, line)) {
            ordered_list.push_back(line);
        }

        build_balanced(ordered_list);

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading dictionary file" << std::endl;
    }
}