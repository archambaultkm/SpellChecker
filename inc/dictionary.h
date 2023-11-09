/**
 * @file Dictionary.h
 * @brief Definition of Dictionary class.
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#ifndef ASSIGNMENT_3_DICTIONARY_H
#define ASSIGNMENT_3_DICTIONARY_H

#include "bst.h"
#include "avl.h"
#include "timer.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

/**
 * @class Dictionary
 * @brief An extension of a BST that reads a list of strings from a file and builds a balanced tree.
 */
class Dictionary : public BST<std::string> {
protected:
    Timer<> m_timer; // timer using default clock to time building the dictionary

public:
    explicit Dictionary(const std::string& file_name);

    /**
    * @brief Get the elapsed time for building the dictionary tree.
    *
    * @return The elapsed time in microseconds.
    */
    long get_elapsed_time();

    /**
     * @brief Save a nicely formatted representation of the BST to a file.
     *
     * @param file_path The file path where the BST visualization will be saved.
     */
    void save_to_file(const std::string& file_path);
};

//// Constructor specialization for AVL tree
//template <>
//class Dictionary<AVL<std::string>> : public DictionaryBase<AVL<std::string>> {
//public:
//    explicit Dictionary(const std::string& file_name) {
//        //start the timer
//        m_timer.start();
//
//        // read the file at the provided file path into vector
//        std::ifstream ifs;
//        std::string line;
//
//        // attempt to open the provided file and read its contents into the tree
//        try {
//            ifs.open(file_name, std::fstream::in);
//
//            while (getline(ifs, line)) {
//                // Split the line into words
//                std::istringstream iss(line);
//                std::string word;
//                while (iss >> word) {
//                    this->insert(word);
//                }
//            }
//
//        } catch (std::ifstream::failure &e) {
//            std::cout << "Exception reading file to AVL" << std::endl;
//        }
//
//        //stop the timer
//        m_timer.stop();
//    }
//};

#endif //ASSIGNMENT_3_DICTIONARY_H
