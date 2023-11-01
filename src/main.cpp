/**
 * @file main.cpp
 * @author Kaitlyn Archambault
 * @date 2023-10-30
 */

#include "spell_checker.h"
#include "../inc/colours.h"

#include <iostream>
#include <string>
#include <regex>

using namespace std;

const string expected_arg_format = "\"./check ../tests/test.txt ../tests/dictionary.txt balanced_tree.txt\"";
bool is_valid_file_path(const string &provided_file_path);

int main(int argc, char* argv[]) {

    // validate program arguments for sample and dictionary files
    if (argc != 4) {
        cerr << RED << "Wrong number of arguments: expected input resembling " << expected_arg_format << RESET << endl;

        return 1;
    }

    if (!is_valid_file_path(argv[1]) || !is_valid_file_path(argv[2]) || !is_valid_file_path(argv[3])) {
        cerr << RED << "Must enter a valid .txt format file name for all provided files." << RESET << endl;
        cout << CYAN << "Arguments should resemble " << expected_arg_format << RESET << endl;

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

/**
 * Validate provided file path with regex
 *
 * @param provided_file_path file path input by user
 *
 * @returns true if the provided file path is in a valid format, false otherwise
 * @note Expected file path format is "(/path/)file_name.txt"
 */
bool is_valid_file_path(const string &provided_file_path) {
    regex valid_file_path(R"(^(?:..)?\/?(?:[a-zA-Z0-9_-]+[\/])?(?:[a-zA-Z0-9_-])+\.txt$)");

    return regex_match(provided_file_path, valid_file_path);
}
