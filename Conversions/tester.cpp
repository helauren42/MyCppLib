#include "Conversions.hpp"

int main() {
	std::vector<std::string> vec;
	vec.push_back("hello ");
	vec.push_back("hello ");
	vec.push_back("Zorld ");
	vec.push_back("World!");
	std::string str = vectorToString(vec);
	Printer::all(str);
}