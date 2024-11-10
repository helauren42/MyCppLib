#pragma once
#include "../Printer/Printer.hpp"

std::string vectorToString(const std::vector<std::string> vec, const std::string& sep = "") {
	std::string ret;
	for (auto it : vec) {
		ret += it;
	}
	return ret;
}
