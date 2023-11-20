/**
 * @file SpellChecker.cpp
 * @brief Implementation of the SpellChecker class.
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */
#include "../inc/utils.h"
#include "../inc/colours.h"
#include "../inc/spell_checker.h"

#include <utility>

SpellChecker::SpellChecker(const Dictionary& dictionary) : m_dictionary(dictionary)
{ }

std::vector<std::string> SpellChecker::get_misspelled_words() {
    return m_misspelled_words;
}

long SpellChecker::get_elapsed_time() {
    return m_timer.get_elapsed_time();
}

void SpellChecker::run_check(const std::string& sample_file_path) {
    std::vector<std::string> words_to_check = get_vec_from_file(sample_file_path);

    // start the timer
    m_timer.start();

    // for every word in the vector, check if it is contained in m_dictionary
    for (auto& word : words_to_check) {
        // convert the word to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // remove special characters
        word = remove_non_alpha(word);
        if (empty(word)) {
            // continue if the word *only* contained special characters
            continue;
        }

        // keep track of any word not found in the dictionary (it is misspelled)
        if (!m_dictionary.find(word)) {
            m_misspelled_words.push_back(word);
        }
    }

    // stop the timer
    m_timer.stop();
}

void SpellChecker::print_results() {
    std::cout << "\nSpell check took " << m_timer.get_elapsed_time() << " ms.\n" << std::endl;

    if (empty(m_misspelled_words)) {
        std::cout << GREEN << "No spelling errors detected." << RESET << std::endl;

    } else {
        std::cout << RED << "Spelling errors detected!" << RESET << std::endl;
        // if the spell checker found errors, print out the word and a suggestion
        for (auto& word : m_misspelled_words) {
            std::cout << word << " -> did you mean \"" << m_dictionary.find_closest_value(word) << "\"?" << std::endl;
        }
    }
}
