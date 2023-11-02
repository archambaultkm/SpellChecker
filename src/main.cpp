/**
 * @file main.cpp
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */
#include "../inc/utils.h"
#include "spell_checker.h"
#include "../inc/colours.h"

#include <iostream>
#include <string>

using namespace std;

bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format);

int main(int argc, char* argv[]) {

    // determine if the right number of program arguments were provided/ all are in the correct format
    string expected_format = "\"./check ../tests/test.txt ../tests/dictionary.txt balanced_tree.txt\"";

    if (!valid_arguments(argc, 4, argv, expected_format)) {
        return 1;
    }

    // initialize file paths from validated arguments
    string sample_text_path = argv[1];
    string dictionary_path = argv[2];
    string balanced_tree_output_path = argv[3];

    // initialize dictionary and validate that it contains data
    Dictionary dictionary(dictionary_path);
    if (dictionary.is_empty()) {
        cerr << RED << "Error: the provided dictionary was empty. Check the file path and try again." << RESET << endl;
        return 1;
    }

    // see how long it took to build/ balance the bst
    cout << "Dictionary built and balanced in " << dictionary.get_elapsed_time() << " ms." << endl;

    // save a representation of the bst to a file for review
    dictionary.save_to_file(balanced_tree_output_path);

    // initialize spell checker with the provided dictionary
    SpellChecker spell_checker(dictionary);

    // run the spell check and provide details of the outcome
    if (spell_checker.run_check(sample_text_path)) {
        cout << GREEN << "No spelling errors detected." << RESET << endl;

    } else {
        cout << RED << "Spelling errors detected!" << RESET << std::endl;

        for (auto& word : spell_checker.get_misspelled_words()) {
            cout << word << endl;
        }
    }

    // print the time elapsed during the spell check
    cout << "\nCheck took " << spell_checker.get_elapsed_time() << " ms." << endl;

    return 0;
}

// validate program arguments for tree destination, sample, and dictionary files
bool valid_arguments(int argc, int expected_num_args, char* argv[], const string& expected_format) {
    if (argc != expected_num_args) {
        cerr << RED << "Wrong number of arguments: expected" << expected_num_args << " but " << argc << "were provided." << RESET << endl;
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
