/**
 * @file main.cpp
 * @brief A C++ program for spell checking using a balanced binary search tree (BST).
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */
#include "inc/utils.h"
#include "inc/spell_checker.h"
#include "inc/avl.h"
#include "inc/colours.h"

#include <iostream>
#include <string>

using namespace std;

const string EXPECTED_FORMAT = "\"./check ../tests/test.txt ../tests/dictionary.txt bst_output.txt\"";

/**
 * @brief Check if the provided program arguments are valid.
 *
 * @param argc Number of command-line arguments.
 * @param expected_num_args The expected number of arguments.
 * @param argv Array of command-line argument strings.
 * @param expected_format The expected format of program arguments.
 * @return True if arguments are valid, false otherwise.
 */
bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format);

/**
 * @brief The main entry point of the program.
 *
 * Parse command-line arguments and perform
 * spell checking using a balanced binary search tree (BST).
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 0 on successful execution, 1 on failure.
 */
int main(int argc, char* argv[]) {

    // determine if the correct number of program arguments were provided/ all are in the correct format
    if (!valid_arguments(argc, 4, argv, EXPECTED_FORMAT)) {
        return 1;
    }

    AVL<int> avl;

    avl.insert(2);
    avl.insert(3);
    avl.insert(4);
    avl.insert(1);
    avl.insert(7);
    avl.insert(8);
    avl.insert(5);
    avl.insert(9);
    avl.insert(6);
    avl.print_tree(cout, 1);

    avl.remove(1);
    avl.print_tree(cout, 1);


//    // initialize file paths from validated arguments
//    string sample_text_path = argv[1];
//    string dictionary_path = argv[2];
//    string bst_output_path = argv[3];
//
//    // initialize dictionary and validate that it contains data
//    Dictionary dictionary(dictionary_path);
//    if (dictionary.is_empty()) {
//        cerr << RED << "Error: the provided dictionary was empty. Check the file path and try again." << RESET << endl;
//        return 1;
//    }
//
//    // see how long it took to build/ balance the bst
//    cout << "BST Dictionary built and balanced in " << dictionary.get_elapsed_time() << " ms." << endl;
//
//    // save each tree to a file for review
//    dictionary.save_to_file(bst_output_path);
//
//    // Create and use a spell checker with both dictionaries
//    SpellChecker bst_spell_checker(dictionary);
//    bst_spell_checker.run_check(sample_text_path);
//    cout << "\nSpell check took " << bst_spell_checker.get_elapsed_time() << " ms.\n" << endl;
//    bst_spell_checker.print_results();

    return 0;
}

bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format) {
    if (argc != expected_num_args) {
        cerr << RED << "Wrong number of arguments: expected " << expected_num_args << " but " << argc << " were provided." << RESET << endl;
        cout << CYAN << "Arguments should resemble " << expected_format << RESET << endl;

        return false;
    }

    // all program arguments are expected to be txt files
    if (!is_valid_file_path(argv[1], "txt") || !is_valid_file_path(argv[2], "txt") || !is_valid_file_path(argv[3], "txt")) {
        cerr << RED << "Must enter a valid .txt format file name for all provided files." << RESET << endl;
        cout << CYAN << "Arguments should resemble " << expected_format << RESET << endl;

        return false;
    }

    return true;
}
