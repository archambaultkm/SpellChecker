/**
 * @file utils.h
 * @brief Contains various helper functions not specific to this assignment.
 * @author Kaitlyn Archambault
 * @date 2023-10-31
 */

#ifndef ASSIGNMENT_3_UTILS_H
#define ASSIGNMENT_3_UTILS_H

#include <string>
#include <concepts>

int levenshtein_distance(const std::string& a, const std::string& b);

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// handles numeric and string types
template <typename T>
auto difference(T a, T b) {
    if constexpr (!std::is_arithmetic_v<T>) {
        return levenshtein_distance(a, b);
    } else {
        return (a > b) ? (a - b) : (b - a);
    }
}

/**
 * Remove non-alphabet characters from a provided string
 *
 * @param str the string to operate on
 *
 * @returns corrected string with no special characters
 */
std::string remove_non_alpha(const std::string& str);

/**
 * Get a vector of all words found in a text file
 *
 * @param file_path file path in .txt format
 *
 * @returns vector<string> of each word in the file
 */
std::vector<std::string> get_vec_from_file(const std::string& file_path);

/**
 * Validate provided file path with regex
 *
 * @param provided_file_path file path input by user
 * @param extension desired file extension
 *
 * @returns true if the provided file path is in a valid format, false otherwise
 * @note in the future it would be nice to be able to provide multiple extensions
 */
bool is_valid_file_path(const std::string &provided_file_path, std::string extension);

#endif //ASSIGNMENT_3_UTILS_H
