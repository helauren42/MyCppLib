#include "utils.hpp"
#include "printer.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <set>

// int main() {
// 	std::vector<int> my_vector = {1, 2, 3, 4, 5};
// 	std::list<int> my_list = {10, 20, 30, 40, 50};
// 	std::forward_list<int> my_fwd_list = {100, 200, 300};
// 	std::set<int> my_set = {5, 1, 3, 2, 4};
// 	std::map<int, std::string> my_map = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
// 	std::deque<int> my_deque = {7, 8, 9, 10};
// 	std::stack<int> my_stack;
// 	std::queue<int> my_queue;
// 	my_stack.push(1);
// 	my_stack.push(2);
// 	my_stack.push(3);
// 	my_queue.push(4);
// 	my_queue.push(5);
// 	my_queue.push(6);
// 	int i = 0;
// 	char c = 'a';
// 	std::string s = "hello";
// 	double d = 3.14;

// 	std::cout << "vector: " <<	TypeChecker::isContainer(&my_vector) << std::endl;
// 	std::cout << "list: " <<	TypeChecker::isContainer(&my_list) << std::endl;
// 	std::cout << "forward_list: " <<	TypeChecker::isContainer(&my_fwd_list) << std::endl;
// 	std::cout << "set: " <<	TypeChecker::isContainer(&my_set) << std::endl;
// 	std::cout << "map: " <<	TypeChecker::isContainer(&my_map) << std::endl;
// 	std::cout << "deque: " <<	TypeChecker::isContainer(&my_deque) << std::endl;
// 	std::cout << "stack: " <<	TypeChecker::isContainer(&my_stack) << std::endl;
// 	std::cout << "queue: " <<	TypeChecker::isContainer(&my_queue) << std::endl;

// 	std::cout << "char: " <<	TypeChecker::isContainer(&c) << std::endl;
// 	std::cout << "string: " <<	TypeChecker::isContainer(&s) << std::endl;
// 	std::cout << "double: " <<	TypeChecker::isContainer(&d) << std::endl;
// 	std::cout << "int: " <<	TypeChecker::isContainer(&i) << std::endl;

// 	Printer::print(my_vector);
// 	Printer::print(my_list);
// 	Printer::print(my_fwd_list);
// 	Printer::print(my_set);
// 	Printer::print(my_map);
// 	Printer::print(my_deque);
// 	Printer::print(my_stack);
// 	Printer::print(my_queue);
// 	Printer::print(c);
// 	Printer::print(s);
// 	Printer::print(d);
// 	Printer::print(i);

// 	return 0;
// }
