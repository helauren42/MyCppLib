#pragma once

#include "../Printer/Printer.hpp"
#include <type_traits>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <queue>
#include <string>

#include <iostream>

std::string executeCommand(const std::string& command) {
	std::string result;
	int status = system(command.c_str());
	if (WIFEXITED(status)) {
		result = std::to_string(WEXITSTATUS(status));
	}
	return result;
}

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
	T value;
	std::cin >> value;
	vec.push_back(value);

    return is;
}