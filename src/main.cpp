#include <iostream>
#include "spell_checker.h"
#include "../inc/colours.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    // parse arguments for dictionary and sample text file paths
    // todo do I want to do this or just make the dictionary here and pass that?
    SpellChecker spell_checker("../docs/dictionary.txt");

    if (spell_checker.run_check("../docs/mispelled.txt")) {
        cout << GREEN << "No spelling errors detected." << RESET << endl;

    } else {
        cerr << RED << "Spelling mistakes detected!" << RESET << endl;
        cout << "The following words were not found in the dictionary: " << endl;

        for (const string& word : spell_checker.get_misspelled_words()) {
            cout << word << endl;
        }
    }

    return 0;
}
