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

void Dictionary::save_to_file(const std::string& file_path) {
    std::ofstream ofs;
    std::string line;

    try {
        //overwrite the file completely if it already exists
        ofs.open(file_path, std::fstream::trunc);

        //copy the bst into the file
        print_tree(ofs, 5);

    } catch (std::ofstream::failure &e) {
        std::cerr << "Exception saving Dictionary to provided file path: " << file_path << std::endl;
    }

    std::cout << "Visualization of Dictionary saved to " << file_path << "\n\n";
}
