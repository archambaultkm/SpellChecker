//
// Created by Kaitlyn Archambault on 2023-10-31.
//

#ifndef ASSIGNMENT_3_SPELL_CHECKER_H
#define ASSIGNMENT_3_SPELL_CHECKER_H


#include "dictionary.h"

class SpellChecker {
private:
    Dictionary m_dictionary;
    std::vector<std::string> m_misspelled_words;

public:
    SpellChecker(const Dictionary& dictionary);
    std::vector<std::string> get_misspelled_words();
    bool run_check(std::string sample_file_path);

};


#endif //ASSIGNMENT_3_SPELL_CHECKER_H
