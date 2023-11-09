/**
 * @file SpellChecker.h
 * @brief Definition of the SpellChecker class.
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */

#ifndef ASSIGNMENT_3_SPELL_CHECKER_H
#define ASSIGNMENT_3_SPELL_CHECKER_H

#include "dictionary.h"
#include "timer.h"

#include <memory>

/**
 * @class SpellChecker
 * @brief Uses a dictionary and a sample file to check for misspelled words.
 */
class SpellChecker {
private:
    Dictionary m_dictionary; // Tree containing correctly-spelled words
    std::vector<std::string> m_misspelled_words; // list of misspelled words found during last check
    Timer<> m_timer; // timer using template default (chrono high resolution clock)

public:
    /**
     * @brief Constructor that initializes the checker's dictionary.
     *
     * @param dictionary The dictionary to use for spell checking.
     */
    explicit SpellChecker(const Dictionary& dictionary);

    /**
     * @brief Get a vector of misspelled words found during the last spell check.
     *
     * @return A vector containing the misspelled words.
     */
    std::vector<std::string> get_misspelled_words();

    /**
     * @brief Run a spell check on a sample text file.
     *
     * This function reads a text file, checks for misspelled words, and stores the results.
     *
     * @param sample_file_path The file path of the sample text file to check.
     * @return True if the spell check passed (no misspelled words found), false otherwise.
     */
    void run_check(const std::string& sample_file_path);

    /**
     * @brief Output the results of the check to the console
     *
     * If errors were found during the last check, indicates all misspelled words and suggested corrections.
     *
     */
    void print_results();

    /**
     * @brief Get the elapsed time for the last spell check.
     *
     * @return The elapsed time in microseconds.
     */
    long get_elapsed_time();
};


#endif //ASSIGNMENT_3_SPELL_CHECKER_H
