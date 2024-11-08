#include "./printer.hpp"

template<class T>
void	printContainer(const std::vector<T>& vec, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n" ;
	for (const auto& value: vec) {
		std::cout << value;
		if(&value != &vec.back())
			std::cout << sep;
	}
	std::cout << std::endl;
}

template<class T>
void	printContainer(const std::list<T>& my_list, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n" ;
	for (const auto& value: my_list) {
		std::cout << value;
		if(&value != &my_list.back())
			std::cout << sep;
	}
	std::cout << std::endl;
}

template<class T>
void	printContainer(const std::forward_list<T>& my_list, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n" ;
	const auto end = my_list.end();

	for (auto it = my_list.begin(); it != my_list.end(); it++) {
		std::cout << *it;
		if(std::next(it) != end)
			std::cout << sep;
	}
	std::cout << std::endl;
}

template<class T>
void	printContainer(const std::deque<T>& my_deque, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n";
	auto end = my_deque.end();
	for (auto it = my_deque.begin(); it != end; ++it) {
		std::cout << *it;
		if (std::next(it) != end)
			std::cout << sep;
	}
	std::cout << std::endl;
}

template<class T>
void	printContainer(std::stack<T> my_stack, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n";
	while (!my_stack.empty()) {
		std::cout << my_stack.top();
		my_stack.pop();
		if (!my_stack.empty())
			std::cout << sep;
	}
	std::cout << std::endl;
}

template<class T>
void	printContainer(std::queue<T> my_queue, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n";
	while (!my_queue.empty()) {
		std::cout << my_queue.front();
		my_queue.pop();
		if (!my_queue.empty())
			std::cout << sep;
	}
	std::cout << std::endl;
}

template<class K, class V>
void	printContainer(const std::map<K, V>& my_map, int mode = 0) {
	if(mode == 0) {
		for(const auto& pair : my_map) {
			std::cout << "key: " << pair.first << ", value: " << pair.second << std::endl;
		}
	}
	else {
		for(const auto& pair : my_map) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
}

template<class T>
void	printContainer(const std::set<T>& my_set, int mode = 0) {
	std::string sep = (mode == 0) ? ", " : "\n";
	const auto end = my_set.end();
	for (auto it = my_set.begin(); it != my_set.end(); it++) {
		std::cout << *it;
		if(std::next(it) != end)
			std::cout << sep;
	}
}

/**
 * Printing Containers
 */

int	main() {
	// Vector 
	std::vector<int> my_vector = {1, 2, 3, 4, 5};
	std::cout << "Vector: ";
	printContainer(my_vector, 1);

	// List 
	std::list<int> my_list = {10, 20, 30, 40, 50};
	std::cout << "List: ";
	printContainer(my_list);

	// Forward List 
	std::forward_list<int> my_fwd_list = {100, 200, 300};
	std::cout << "Forward List: ";
	printContainer(my_fwd_list);

	// Set 
	std::set<int> my_set = {5, 1, 3, 2, 4};
	std::cout << "Set: ";
	printContainer(my_set);

	// Map 
	std::map<int, std::string> my_map = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
	std::cout << "Map: ";
	printContainer(my_map, 1);

	// Deque 
	std::deque<int> my_deque = {7, 8, 9, 10};
	std::cout << "Deque: ";
	printContainer(my_deque);

	// Stack 
	std::stack<int> my_stack;
	my_stack.push(1);
	my_stack.push(2);
	my_stack.push(3);
	std::cout << "Stack: ";
	printContainer(my_stack);

	// Queue 
	std::queue<int> my_queue;
	my_queue.push(10);
	my_queue.push(20);
	my_queue.push(30);
	std::cout << "Queue: ";
	printContainer(my_queue);

	return 0;
}
