#include "printer.hpp"



	template <typename T, typename... Args>
	void	all(T first, Args... args)
	{
		Printer::print(first);
		if constexpr (sizeof...(args) > 0) {
			all(args...);
		}
	}



/**
 * Printing Containers
 */

int	main() {
	// Vector 
	std::vector<int> my_vector = {1, 2, 3, 4, 5};
	std::cout << "Vector: ";
	Printer::print(my_vector, 1);

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
	Printer::print(my_map, 1);

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

	// all(c);
	all(my_vector, my_list, my_fwd_list, my_set, my_map, my_deque, my_stack, my_queue);

	return 0;
}
