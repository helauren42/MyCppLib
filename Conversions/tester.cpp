#include "Conversions.hpp"

int main() {
	std::vector<std::string> vec;
	vec.push_back("hello ");
	vec.push_back("hello ");
	vec.push_back("Zorld ");
	vec.push_back("World!");
	std::string str = joinStrings(vec);
	Printer::all("vector: ", str);

	std::queue<std::string> q1;
	q1.push("hello ");
	q1.push("hello ");
	q1.push("Zorld ");
	q1.push("World!");
	str = joinStrings(q1);

	Printer::all("queue: ", str);
}