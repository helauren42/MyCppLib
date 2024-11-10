#include "printer.hpp"

/**
 * Testing Printing
 */

int	main() {

	std::cout << "CONTAINERS:\n\n";
	// Vector
	std::vector<int> my_vector = {1, 2, 3, 4, 5};
	std::cout << "Vector: ";
	Printer::print(my_vector);

	// List
	std::list<int> my_list = {10, 20, 30, 40, 50};
	std::cout << "List: ";
	Printer::print(my_list);

	// Forward List
	std::forward_list<int> my_fwd_list = {100, 200, 300};
	std::cout << "Forward List: ";
	Printer::print(my_fwd_list);

	// Set
	std::set<int> my_set = {5, 1, 3, 2, 4};
	std::cout << "Set: ";
	Printer::print(my_set);

	// Map
	std::map<int, std::string> my_map = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
	std::cout << "Map: ";
	Printer::print(my_map);

	// Deque
	std::deque<int> my_deque = {7, 8, 9, 10};
	std::cout << "Deque: ";
	Printer::print(my_deque);

	// Stack
	std::stack<int> my_stack;
	my_stack.push(1);
	my_stack.push(2);
	my_stack.push(3);
	std::cout << "Stack: ";
	Printer::print(my_stack);

	// Queue
	std::queue<int> my_queue;
	my_queue.push(10);
	my_queue.push(20);
	my_queue.push(30);
	std::cout << "Queue: ";
	Printer::print(my_queue);

	std::cout << std::endl;
	std::cout << "Scalar Types:\n\n";

	char a = 'a';
	std::cout << "Char: ";
	Printer::print(a);

	int b = 10;
	std::cout << "Int: ";
	Printer::print(b);

	std::string c = "Hello";
	std::cout << "String: ";
	Printer::print(c);

	double d = 3.14;
	std::cout << "Double: ";
	Printer::print(d);

	float e = 3.14f;
	std::cout << "Float: ";
	Printer::print(e);

	bool f = true;
	std::cout << "Bool: ";
	Printer::print(f);

	std::cout << std::endl;

	std::cout << "All in one function call:\n";

	Printer::all(my_vector, my_list, my_fwd_list, my_set, my_map, my_deque, my_stack, my_queue, a, b, c, d, e, f);

	std::cout << std::endl;

	std::cout << "Nested container:\n\n";
	std::vector<std::vector<int>> vectorVectorInt;
	vectorVectorInt.push_back(my_vector);
	std::vector<int> aa = {5, 9, 5, 9};
	vectorVectorInt.push_back(aa);
	std::vector<int> bb = {9, 9, 9, 9};
	vectorVectorInt.push_back(bb);
	std::cout << "all vectorVectorInt:\n";
	Printer::all(vectorVectorInt);

	std::cout << "print vectorVectorInt:\n";
	Printer::print(vectorVectorInt);
	std::cout << std::endl;

	std::pair<std::string, std::vector<int>> p1("vector1", aa);
	std::pair<std::string, std::vector<int>> p2("vector2", bb);
	std::map<std::string, std::vector<int>> my_map2;
	my_map2.insert(p1);
	my_map2.insert(p2);
	Printer::all("all map <string vector>:", my_map2);


	int arr[4] = {1, 2, 3, 4};
	// Printer::all(arr);
	std::cout << arr << std::endl;

	return 0;
}
