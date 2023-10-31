//
// Created by Kaitlyn Archambault on 2023-10-31.
//

#include "spell_checker.h"
#include "../inc/utils.h"

SpellChecker::SpellChecker(const Dictionary& dictionary) {
    m_dictionary = dictionary;
}

std::vector<std::string> SpellChecker::get_misspelled_words() {
    return m_misspelled_words;
}

std::vector<std::string> SpellChecker::get_vec_from_file(std::string file_path) {
    // read the file at the provided file path into vector
    std::ifstream ifs;
    std::string line;
    std::vector<std::string> words_to_check;

    // attempt to open the provided file and read its contents into the dictionary list
    try {
        ifs.open(file_path, std::fstream::in);

        //todo split at the space
        while (getline(ifs, line, ' ')) {
            words_to_check.push_back(line);
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "Exception reading sample file" << std::endl;
    }

    return words_to_check;
}

bool SpellChecker::run_check(std::string sample_file_path) {

    std::vector<std::string> words_to_check = get_vec_from_file(sample_file_path);

    // for every word in the vector, check if it is contained in m_dictionary
    for (auto& word : words_to_check) {
        // convert the word to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // remove special characters
        word = remove_non_alpha(word);
        if (empty(word)) {
            continue;
        }

        if (!m_dictionary.find(word)) {
            m_misspelled_words.push_back(word);
        }
    }

    // if no words were misspelled, the check passed
    if (empty(m_misspelled_words)) {
        return true;
    }

    return false;
}
