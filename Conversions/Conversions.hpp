#pragma once
#include "../Printer/Printer.hpp"

template<template<typename...> class Container>
std::string joinStrings(const Container<std::string>& container, const std::string& sep = "") {
	std::string ret;
	for (auto it : container) {
		ret += it;
	}
	return ret;
}

std::string joinStrings(std::queue<std::string>& container, const std::string& sep = "") {
	std::string ret;
	while (!container.empty()) {
		ret += container.front();
		container.pop();
		std::cout << "ret: " << ret << std::endl;
	}
	return ret;
}

std::string joinStrings(std::stack<std::string>& container, const std::string& sep = "") {
	std::string ret;
	while (!container.empty()) {
		ret += container.top();
		container.pop();
		std::cout << "ret: " << ret << std::endl;
	}
	return ret;
}
