#include <iostream>
#include "spell_checker.h"
#include "../inc/colours.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    string dictionary_path;
    string sample_text_path;
    string balanced_tree_output_path; // todo ask if you even need this

    // TODO parse arguments for dictionary and sample text file paths
    dictionary_path = "../docs/dictionary.txt";
    sample_text_path = "../docs/mispelled.txt";
    balanced_tree_output_path = "balanced_tree.txt";

    Dictionary dictionary(dictionary_path);

    // todo it would be cool to do this+ the checking on different threads
    dictionary.save_to_file(balanced_tree_output_path);
    // todo check if dictionary is empty?

    SpellChecker spell_checker(dictionary);

    if (spell_checker.run_check(sample_text_path)) {
        cout << GREEN << "No spelling errors detected." << RESET << endl;

    } else {
        cerr << RED << "\nSpelling mistakes detected!" << RESET << endl;
        cout << "The following words were not found in the dictionary: " << std::endl;

        for (const string& word : spell_checker.get_misspelled_words()) {
            cout << word << endl;
        }
    }

    return 0;
}
