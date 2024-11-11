#pragma once

#include <iostream>
#include "../Conversions/Conversions.hpp"

using namespace std;

#define WHITE_SPACES " \t\n\r\v\f\u00A0\u200B"

bool	isWhiteSpace(const char& c) {
	const std::string white_spaces = WHITE_SPACES;

	if(white_spaces.find(c) != std::string::npos)
		return true;
	return false;
}

std::string lstrip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	int i = 0;

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

std::string rstrip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	int i = str.length() - 1;

	while(i >= 0) {
		if(remove.find(str[i]) == std::string::npos)
			break;
		i--;
	}

	std::string ret = str.substr(0, i +1);
	return ret;
}

std::string strip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	std::string ret = lstrip(str, remove);
	ret = rstrip(ret, remove);
	return ret;
}

std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) {
	std::string ret = str;
	size_t start_pos = 0;

	while(true) {
		start_pos = ret.find(from, start_pos);
		if(start_pos == std::string::npos)
			break;
		ret.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return(ret);
}

std::string removeAll(const std::string& str, const std::string& remove) {
	return replaceAll(str, remove, "");
}

// template<typename T>
std::list<std::string> split(const std::string& str, const std::string& delimiter = "\n") {
	std::list<std::string> container;

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
