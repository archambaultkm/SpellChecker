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

//        //TODO debug
//        for (const std::string& word : ordered_list) {
//            std::cout << word << std::endl;
//        }

        build(ordered_list);

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading source file" << std::endl;
    }
}

//void Dictionary::save_to_file(std::string file_name) {
//    std::ofstream ofs;
//    std::string line;
//
//    try {
//        //overwrite the file completely if it already exists
//        ofs.open(file_name, std::fstream::trunc);
//
//        //copy the bst into the file
//        ofs << this;
//
//    } catch (std::ofstream::failure &e) {
//        std::cout << "Exception writing to solution file" << std::endl;
//    }
//
//    std::cout << "Balanced tree saved to " << file_name << std::endl;
//}