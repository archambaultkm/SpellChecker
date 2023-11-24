/**
 * @file Dictionary.cpp
 * @brief Implementation of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#include "../inc/dictionary.h"

#include <fstream>
#include <sstream>
#include <iostream>

Dictionary::Dictionary(const std::string& file_name, SearchTreeBase<std::string>* tree_ptr) {
    // deep copy the passed tree pointer
    m_tree = tree_ptr->clone();

    // start the timer
    m_timer.start();

    // Check what kind of tree m_tree points to and build the dictionary tree accordingly
    if (auto* bst_ptr = dynamic_cast<BST<std::string>*>(m_tree)) {
        // get a list of words from file
        std::vector<std::string> ordered_list = get_vec_from_file(file_name);
        // make sure it's in alphabetical order
        std::sort(ordered_list.begin(), ordered_list.end());
        // build a balanced bst
        m_tree->build_balanced(ordered_list, 0, (int) ordered_list.size() - 1);

    } else if (auto* avl_ptr = dynamic_cast<AVL<std::string>*>(m_tree)) {
        // read the file at the provided file path into vector
        std::ifstream ifs;
        std::string line;

        // attempt to open the provided file and read its contents into the tree
        try {
            ifs.open(file_name, std::fstream::in);

            while (getline(ifs, line)) {
                // Split the line into words
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    m_tree->insert(word);
                }
            }

        } catch (std::ifstream::failure &e) {
            std::cout << "Exception reading file to AVL" << std::endl;
        }
    }

    // stop the timer
    m_timer.stop();
}

Dictionary Dictionary::build_and_save(const std::string& dictionary_path, const std::string& tree_output_path, const std::string& tree_type) {

    SearchTreeBase<std::string>* tree;
    // use the appropriate tree
    if (tree_type == "avl") {
        tree = new AVL<std::string>;
    } else {
        tree = new BST<std::string>;
    }

    Dictionary dictionary(dictionary_path, *&tree);

    // see how long it took to build/ balance the dictionary
    std::cout << "Dictionary built and balanced in " << dictionary.get_elapsed_time() << " ms." << std::endl;

    // save tree to a file for review
    dictionary.save_to_file(tree_output_path);

    return dictionary;
}

bool Dictionary::find(std::string data) {
    return m_tree->find(data);
}

std::string Dictionary::find_closest_value(std::string data) {
    return m_tree->find_closest_value(data);
}

bool Dictionary::is_empty() {
    return m_tree->is_empty();
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

        //copy the tree into the file
        m_tree->print_tree(ofs, 5);

    } catch (std::ofstream::failure &e) {
        std::cerr << "Exception saving Dictionary to provided file path: " << file_path << std::endl;
    }

    std::cout << "Visualization of dictionary saved to " << file_path << std::endl;
}

