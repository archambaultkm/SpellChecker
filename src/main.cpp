#include <iostream>
#include "spell_checker.h"
#include "../inc/colours.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    // TODO parse arguments for dictionary and sample text file paths
    Dictionary dictionary("../docs/dictionary.txt");
    dictionary.save_to_file("balanced_tree.txt");

    SpellChecker spell_checker(dictionary);

    if (spell_checker.run_check("../docs/mispelled.txt")) {
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
