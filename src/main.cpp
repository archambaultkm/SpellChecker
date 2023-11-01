#include <iostream>
#include "spell_checker.h"
#include "../inc/colours.h"

#include <string>
#include <regex>

using namespace std;

const string expected_arg_format = "\"./check ../tests/test.txt ../tests/dictionary.txt\"";
bool is_valid_file_path(const string &provided_file_path);

int main(int argc, char* argv[]) {

    // validate program arguments for sample and dictionary files
    if (argc != 3) {
        cerr << RED << "Wrong number of arguments: expected input resembling " << expected_arg_format << RESET << endl;

        return 1;
    }

    if (!is_valid_file_path(argv[1]) || !is_valid_file_path(argv[2])) {
        cerr << RED << "Must enter a valid .txt format file name for all provided files." << RESET << endl;
        cout << CYAN << "Arguments should resemble " << expected_arg_format << RESET << endl;

        return 1;
    }

    // initialize file paths from validated arguments
    string sample_text_path = argv[1];
    string dictionary_path = argv[2];
    string balanced_tree_output_path = "balanced_tree.txt"; // todo ask if this needs to be specified too

    // initialize dictionary and validate it contains data
    Dictionary dictionary(dictionary_path);
    if (dictionary.is_empty()) {
        cerr << RED << "Error: the provided dictionary was empty. Check the file path and try again." << RESET << endl;
        return 1;
    }

    // save a representation of the bst to a file for review
    dictionary.save_to_file(balanced_tree_output_path);

    // initialize spell checker with the provided dictionary
    SpellChecker spell_checker(dictionary);

    // run the spell check and provide details of the outcome
    if (spell_checker.run_check(sample_text_path)) {
        cout << GREEN << "No spelling errors detected." << RESET << endl;

    } else {
        cout << RED << "Spelling errors detected!" << RESET << std::endl;
        spell_checker.print_result();
    }

    // print the time elapsed during the spell check
    cout << "Check took " << spell_checker.get_elapsed_time() << " ms." << endl;

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
