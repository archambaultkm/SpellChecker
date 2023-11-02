/**
 * @file Dictionary.cpp
 * @brief Implementation of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#include "../inc/dictionary.h"
#include <fstream>
#include <iostream>

Dictionary::Dictionary(std::string file_name) {
    std::ifstream ifs;
    std::string line;
    std::vector<std::string> ordered_list;

    // attempt to open the provided file and read its contents into the dictionary list
    try {
        ifs.open(file_name, std::fstream::in);

        // start the timer
        m_timer.start();

        while (getline(ifs, line)) {
            ordered_list.push_back(line);
        }

        // build a balanced BST using the sorted list
        build_balanced(ordered_list);

        // stop the timer
        m_timer.stop();

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading dictionary file" << std::endl;
    }
}

long Dictionary::get_elapsed_time() {
    return m_timer.get_elapsed_time();
}
