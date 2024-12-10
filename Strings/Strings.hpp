#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include <queue>

// using namespace std;

#define WHITE_SPACES " \t\n\r\v\f\u00A0\u200B"
#define ALPHA_NUMERIC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define UPPER_CASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_CASE "abcdefghijklmnopqrstuvwxyz"

enum {
	spaceSeparated,
	camelCase,
	snakeCase,
	kebabCase,
};

/**
 * @brief Checks if a character is a whitespace character.
 * 
 * This function checks if the given character `c` is a whitespace character by
 * searching for it in a predefined set of whitespace characters.
 * 
 * @param c The character to check.
 * @return true if the character is a whitespace character, false otherwise.
 */
bool	isWhiteSpace(const char& c);

bool hasDelim(const std::string& str, const char& delimiter);

bool hasDelim(const std::string& str, const std::string& delimiter);

/**
 * @brief Joins a container of strings into a single string with an optional separator.
 * 
 * This function concatenates all strings in the input container `container` into a
 * single string, with each string separated by the specified `sep` (separator).
 * The container must hold `std::string` elements.
 * 
 * @tparam Container A template template parameter representing the container type that holds `std::string` elements.
 * @param container The container of strings to join.
 * @param sep The separator string to insert between each string. Defaults to an empty string.
 * @return std::string The concatenated string.
 */
template<typename Container>
std::string joinStrings(const Container& container, const std::string& sep = " ");

/**
 * @brief Joins a queue of strings into a single string with an optional separator.
 * 
 * This function concatenates all strings in the input queue `container` into a
 * single string, with each string separated by the specified `sep` (separator).
 * The queue must hold `std::string` elements. The queue will be emptied as a
 * result of this operation.
 * 
 * @param container The queue of strings to join.
 * @param sep The separator string to insert between each string. Defaults to an empty string.
 * @return std::string The concatenated string.
 */
std::string joinStrings(std::queue<std::string>& container, const std::string& sep = " ");

/**
 * @brief Joins a stack of strings into a single string with an optional separator.
 * 
 * This function concatenates all strings in the input stack `container` into a
 * single string, with each string separated by the specified `sep` (separator).
 * The stack must hold `std::string` elements. The stack will be emptied as a
 * result of this operation.
 * 
 * @param container The stack of strings to join.
 * @param sep The separator string to insert between each string. Defaults to an empty string.
 * @return std::string The concatenated string.
 */
std::string joinStrings(std::stack<std::string>& container, const std::string& sep = " ");
/**
 * @brief Splits a string into substrings based on a delimiter and stores the results in a container.
 * 
 * This function splits the input string `str` into substrings using the specified `delimiter`.
 * The resulting substrings are stored in a container of type `Container<std::string>`.
 * 
 * @tparam Container A template template parameter representing the container type that holds `std::string` elements.
 * @param str The input string to be split.
 * @param delimiter The delimiter string used to split the input string. Defaults to newline character ("\n").
 * @return Container<std::string> A container holding the resulting substrings.
 */
template <typename Container> 
Container split(const std::string& str, const std::string& delimiter = "\n");

/**
 * @brief Splits a string into substrings based on a delimiter and keeps the delimiters in the result.
 * 
 * This function splits the input string `str` into substrings using the specified `delimiter`.
 * Unlike the standard split function, this function keeps the delimiters as part of the resulting substrings.
 * The resulting substrings are stored in a container of type `Container<std::string>`.
 * 
 * @tparam Container A template template parameter representing the container type that holds `std::string` elements.
 * @param str The input string to be split.
 * @param delimiter The delimiter string used to split the input string. Defaults to newline character ("\n").
 * @return Container<std::string> A container holding the resulting substrings, including the delimiters.
 */
template<typename Container>
Container splitKeep(const std::string& str, const std::string& delimiter = "\n");

/**
 * @brief Converts all characters in a string to lowercase.
 * 
 * This function converts all characters in the input string `str` to lowercase.
 * The conversion can be done in different modes, such as space-separated or not.
 * 
 * @param str The input string to convert to lowercase.
 * @param mode The mode of conversion (default is space-separated).
 * @return std::string The input string with all characters converted to lowercase.
 */
std::string toLowerCase(const std::string& str);

/**
 * @brief Converts all characters in a string to uppercase.
 * 
 * This function converts all characters in the input string `str` to uppercase.
 * The conversion can be done in different modes, such as space-separated or not.
 * 
 * @param str The input string to convert to uppercase.
 * @param mode The mode of conversion (default is space-separated).
 * @return std::string The input string with all characters converted to uppercase.
 */
std::string toUpperCase(const std::string& str);
std::string	toCamelCase(const std::string& str, const int& mode = spaceSeparated) {
	std::string ret;
	if(mode == camelCase)
		return(ret = str, ret);

	ret = toLowerCase(str);
	std::string delimiter = [mode]() -> std::string {
		if (mode == kebabCase) return "-";
		if (mode == snakeCase) return "_";
		return WHITE_SPACES;
	}();

	std::vector<std::string> vec = split<std::vector<std::string>>(ret, delimiter);

	for(auto it = vec.begin(); it != vec.end(); it++) {
		if((*it)[0])
			(*it)[0] = std::toupper((*it)[0]);
	}
	ret = joinStrings(vec, "");
	ret[0] = std::tolower(ret[0]);
	return ret;
}

std::string	toSnakeCase(const std::string& str, const int& mode = spaceSeparated) {
	std::string ret;
	if(mode == snakeCase)
		return(ret = str, ret);

	ret = str;
	std::string delimiter = [mode]() -> std::string {
		if (mode == camelCase) return UPPER_CASE;
		if (mode == kebabCase) return "-";
		return WHITE_SPACES;
	}();

	std::vector<std::string> vec;
	if(mode == camelCase)
		vec = splitKeep<std::vector<std::string>>(ret, delimiter);
	else
		vec = split<std::vector<std::string>>(ret, delimiter);

	ret = joinStrings(vec, "_");
	ret = toLowerCase(ret);
	return ret;
}

std::string	toKebabCase(const std::string& str, const int& mode = spaceSeparated) {
	std::string ret;
	if(mode == kebabCase)
		return(ret = str, ret);

	ret = str;
	std::string delimiter = [mode]() -> std::string {
		if (mode == camelCase) return UPPER_CASE;
		if (mode == snakeCase) return "_";
		return WHITE_SPACES;
	}();

	std::vector<std::string> vec;
	if(mode == camelCase)
		vec = splitKeep<std::vector<std::string>>(ret, delimiter);
	else
		vec = split<std::vector<std::string>>(ret, delimiter);

	ret = joinStrings(vec, "-");
	ret = toLowerCase(ret);
	return ret;
}

/**
 * @brief Removes leading whitespace characters from a string.
 * 
 * This function removes all leading characters from the input string `str` that
 * are found in the `remove` string. If `remove` is not provided, it defaults to
 * a predefined set of whitespace characters.
 * 
 * @param str The input string to strip.
 * @param remove The string containing characters to remove. Defaults to whitespace characters.
 * @return std::string The input string with leading characters removed.
 */
std::string lstrip(const std::string& str, const std::string& remove = WHITE_SPACES);
/**
 * @brief Removes trailing whitespace characters from a string.
 * 
 * This function removes all trailing characters from the input string `str` that
 * are found in the `remove` string. If `remove` is not provided, it defaults to
 * a predefined set of whitespace characters.
 * 
 * @param str The input string to strip.
 * @param remove The string containing characters to remove. Defaults to whitespace characters.
 * @return std::string The input string with trailing characters removed.
 */
std::string rstrip(const std::string& str, const std::string& remove = WHITE_SPACES);

/**
 * @brief Removes leading and trailing whitespace characters from a string.
 * 
 * This function removes all leading and trailing characters from the input string `str`
 * that are found in the `remove` string. If `remove` is not provided, it defaults to
 * a predefined set of whitespace characters.
 * 
 * @param str The input string to strip.
 * @param remove The string containing characters to remove. Defaults to whitespace characters.
 * @return std::string The input string with leading and trailing characters removed.
 */
std::string strip(const std::string& str, const std::string& remove = WHITE_SPACES);

/**
 * @brief Replaces all occurrences of a substring with another substring in place.
 * 
 * This function replaces all occurrences of the substring `from` in the input string `str`
 * with the substring `to`. The modifications are made directly to the input string.
 * 
 * @param str The input string to modify.
 * @param from The substring to be replaced.
 * @param to The substring to replace `from` with.
 */
void	replaceAll(std::string& str, const std::string& from, const std::string& to);

/**
 * @brief Removes all occurrences of a substring from a string in place.
 * 
 * This function removes all occurrences of the substring `remove` from the input string `str`.
 * The modifications are made directly to the input string.
 * 
 * @param str The input string to modify.
 * @param remove The substring of characters to be removed.
 */
void	removeAll(std::string& str, const std::string& remove);

bool	stringCompareIgnoreCase(const std::string& s1, const std::string& s2);
