#include "printer.hpp"

/**
 * Printing Containers
 */

int	main() {
	// Vector 
	std::vector<int> my_vector = {1, 2, 3, 4, 5};
	std::cout << "Vector: ";
	Printer::printContainer(my_vector, 1);

	// List 
	std::list<int> my_list = {10, 20, 30, 40, 50};
	std::cout << "List: ";
	Printer::printContainer(my_list);

	// Forward List 
	std::forward_list<int> my_fwd_list = {100, 200, 300};
	std::cout << "Forward List: ";
	Printer::printContainer(my_fwd_list);

	// Set 
	std::set<int> my_set = {5, 1, 3, 2, 4};
	std::cout << "Set: ";
	Printer::printContainer(my_set);

	// Map 
	std::map<int, std::string> my_map = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
	std::cout << "Map: ";
	Printer::printContainer(my_map, 1);

	// Deque
	std::deque<int> my_deque = {7, 8, 9, 10};
	std::cout << "Deque: ";
	Printer::printContainer(my_deque);

	// Stack 
	std::stack<int> my_stack;
	my_stack.push(1);
	my_stack.push(2);
	my_stack.push(3);
	std::cout << "Stack: ";
	Printer::printContainer(my_stack);

	// Queue
	std::queue<int> my_queue;
	my_queue.push(10);
	my_queue.push(20);
	my_queue.push(30);
	std::cout << "Queue: ";
	Printer::printContainer(my_queue);

	// //unordered map
	// std::unordered_map<int, std::string> my_unordered_map = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
	// std::cout << "Unordered Map: ";
	// Printer::printContainer(my_unordered_map);
	return 0;
}
