#include "utils.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
	std::vector<int> v = {1, 2, 3};
	std::string s = "Hello";

	std::cout << "Is vector a container? " << decltype(TypeChecker::isContainer(&v))::value << std::endl;
	std::cout << "Is string a container? " << decltype(TypeChecker::isContainer(&s))::value << std::endl;
	return 0;
}
