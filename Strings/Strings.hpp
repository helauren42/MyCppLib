#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>

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

inline std::wstring StringToWString(const std::string& str)
{
	std::wstring wstr;
	wstr.resize(str.length());
	mbstowcs(&wstr[0], str.c_str(), str.size());
	return wstr;
}

inline std::string WStringToString(const std::wstring& wstr)
{
	std::string str;
	str.resize(wstr.length());
	wcstombs(&str[0], &wstr[0], wstr.size());
	return str;
}

inline bool isWhiteSpace(const char& c) {
	const std::string white_spaces = WHITE_SPACES;

	if(white_spaces.find(c) != std::string::npos)
		return true;
	return false;
}

inline bool isAlpha(const std::string& str) {
	for (auto& elem : str) {
		if(!std::isalpha(elem))
			return false;
	}
	return true;
}

inline bool isNumeric(const std::string& str) {
	for (auto& elem : str) {
		if(!std::isdigit(elem))
			return false;
	}
	return true;
}

inline bool isAlphaNumeric(const std::string& str) {
	for (auto& elem : str) {
		if(!std::isdigit(elem) && !std::isalpha(elem))
			return false;
	}
	return true;
}

inline bool hasDelim(const std::string& str, const char& delimiter) {
    return str.find(delimiter) != std::string::npos;
}

inline bool hasDelim(const std::string& str, const std::string& delimiter) {
    return str.find_first_of(delimiter) != std::string::npos;
}

inline int countChar(const std::string& str, const char& c) {
	int count = 0;
	for(int i = 0; str[i]; i++) {
		if(str[i] == c)
			count++;
	}
	return count;
}

template<template<typename T> class Container>
inline std::string joinStrings(const Container<std::string>& container, const std::string& sep = " ") {
	std::string ret;
	for (auto it : container) {
		ret += it;
		ret += sep;
	}
	ret = ret.substr(0, ret.length() - sep.length());
	return ret;
}

template<template<typename T> class Container>
inline Container<std::string> split(const std::string& str, const std::string& delimiter = "\n") {
	Container<std::string> container;

	size_t start = 0;
	size_t end = 0;

	while(true) {
		if((start = str.find_first_not_of(delimiter, start)) == std::string::npos)
			break;
		end = str.find_first_of(delimiter, start);
		if(end == std::string::npos)
			end = str.length();
		container.push_back(str.substr(start, end - start));
		start = end+1;
	}
	return(container);
}

template<template<typename T> class Container>
inline Container<std::wstring> wsplit(const std::wstring& str, const std::wstring& delimiter = L"\n") {
	Container<std::wstring> container;

	size_t start = 0;
	size_t end = 0;

	while(true) {
		if((start = str.find_first_not_of(delimiter, start)) == std::wstring::npos)
			break;
		end = str.find_first_of(delimiter, start);
		if(end == std::wstring::npos)
			end = str.length();
		container.push_back(str.substr(start, end - start));
		start = end+1;
	}
	return(container);
}

inline std::string toLowerCase(const std::string& str) {
	std::string result = str;
	std::string upper_case = UPPER_CASE;
	for (char& c : result) {
		if(upper_case.find(c) != std::string::npos)
			c = std::tolower(c);
	}
	return result;
}

inline std::string toUpperCase(const std::string& str) {
	std::string result = str;
	std::string lower_case = LOWER_CASE;

	for (char& c : result) {
		if(lower_case.find(c) != std::string::npos)
			c = std::toupper(c);
	}
	return result;
}

inline std::string lstrip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	size_t i = 0;

	while(i < str.length()) {
		size_t found = remove.find(str[i]);
		if(found ==  std::string::npos) {
			break;
		}
		i++;
	}

	std::string ret = str.substr(i, str.length() - i);
	return ret;
}

inline std::string rstrip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	int i = str.length() - 1;

	while(i >= 0) {
		if(remove.find(str[i]) == std::string::npos)
			break;
		i--;
	}

	std::string ret = str.substr(0, i +1);
	return ret;
}

inline std::string strip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	std::string ret = lstrip(str, remove);
	ret = rstrip(ret, remove);
	return ret;
}

inline void replaceSubstr(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;

	while (true) {
		start_pos = str.find(from, start_pos);
		if (start_pos == std::string::npos)
			break;
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

inline void removeAll(std::string& str, const std::string& remove) {
	for(int i = str.size()-1; i >= 0; i--){
		if(remove.find(str[i]) != std::string::npos)
			str.erase(i, 1);
	}
}

inline std::wstring wremoveAll(const std::wstring& str, const std::wstring& remove) {
    std::wstring wret;
    for(int i = 0; str[i]; i++){
        if (remove.find((str[i]) == std::wstring::npos))
            wret += str[i];
    }
    return wret;
}

inline void removeWhiteSpaces(std::string& str) {
	removeAll(str, WHITE_SPACES);
}

inline void removeIntruder(std::string& str, const std::string& valid_characters) {
	for (auto it = str.begin(); it != str.end(); it++) {
		if(valid_characters.find(*it) == std::string::npos) {
			str.erase(it);
			it--;
		}
	}
}

inline void removeNonAlphaNumeric(std::string& str) {
	removeIntruder(str, ALPHA_NUMERIC);
}

inline bool stringCompareIgnoreCase(const std::string& s1, const std::string& s2) {
	std::string lower_s1 = toLowerCase(s1);
	std::string lower_s2 = toLowerCase(s2);

	return lower_s1 == lower_s2;
}

#endif
