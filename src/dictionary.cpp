/**
 * @file Dictionary.cpp
 * @brief Implementation of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#include "../inc/dictionary.h"

#include <fstream>
#include <iostream>

Dictionary::Dictionary(const std::string& file_name) {
    //start the timer
    m_timer.start();

    // get a list of words from file
    std::vector<std::string> ordered_list = get_vec_from_file(file_name);
    // make sure it's in alphabetical order
    std::sort(ordered_list.begin(), ordered_list.end());
    // build a balanced bst
    build_balanced(ordered_list, 0, ordered_list.size() - 1);

    // stop the timer
    m_timer.stop();
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

    std::cout << "Visualization of dictionary saved to " << file_path << std::endl;
}


void Dictionary::build_balanced(std::vector<std::string> sorted_list, int left_bound, int right_bound) {
    if (left_bound > right_bound) {
        return; //means that list has been depleted
    }

    int midpoint = (left_bound+right_bound) / 2;

    // insert new subtree root
    insert(sorted_list.at(midpoint));
    // branch left
    build_balanced(sorted_list, left_bound, midpoint-1);
    // branch right
    build_balanced(sorted_list, midpoint+1, right_bound);
}
