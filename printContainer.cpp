#include "./printContainer.hpp"

template<typename T>
void	printContainer(const vector<T>& vec, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n" ;
	for (const auto& value: vec) {
		cout << value;
		if(&value != &vec.back())
			cout << sep;
	}
	cout << endl;
}

template<typename T>
void	printContainer(const list<T>& my_list, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n" ;
	for (const auto& value: my_list) {
		cout << value;
		if(&value != &my_list.back())
			cout << sep;
	}
	cout << endl;
}

template<typename T>
void	printContainer(const forward_list<T>& my_list, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n" ;
	const auto end = my_list.end();

	for (auto it = my_list.begin(); it != my_list.end(); it++) {
		cout << *it;
		if(std::next(it) != end)
			cout << sep;
	}
	cout << endl;
}

template<typename T>
void	printContainer(const deque<T>& my_deque, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n";
	auto end = my_deque.end();
	for (auto it = my_deque.begin(); it != end; ++it) {
		cout << *it;
		if (std::next(it) != end)
			cout << sep;
	}
	cout << endl;
}

template<typename T>
void	printContainer(stack<T> my_stack, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n";
	while (!my_stack.empty()) {
		cout << my_stack.top();
		my_stack.pop();
		if (!my_stack.empty())
			cout << sep;
	}
	cout << endl;
}

template<typename T>
void	printContainer(queue<T> my_queue, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n";
	while (!my_queue.empty()) {
		cout << my_queue.front();
		my_queue.pop();
		if (!my_queue.empty())
			cout << sep;
	}
	cout << endl;
}

template<typename K, typename V>
void	printContainer(const map<K, V>& my_map, int mode = 0) {
	if(mode == 0) {
		for(const auto& pair : my_map) {
			cout << "key: " << pair.first << ", value: " << pair.second << endl;
		}
	}
	else {
		for(const auto& pair : my_map) {
			cout << pair.first << ": " << pair.second << endl;
		}
	}
}

template<typename T>
void	printContainer(const set<T>& my_set, int mode = 0) {
	string sep = (mode == 0) ? ", " : "\n";
	const auto end = my_set.end();
	for (auto it = my_set.begin(); it != my_set.end(); it++) {
		cout << *it;
		if(std::next(it) != end)
			cout << sep;
	}
}

int	main() {
	// Vector 
	vector<int> my_vector = {1, 2, 3, 4, 5};
	cout << "Vector: ";
	printContainer(my_vector, 1);

	// List 
	list<int> my_list = {10, 20, 30, 40, 50};
	cout << "List: ";
	printContainer(my_list);

	// Forward List 
	forward_list<int> my_fwd_list = {100, 200, 300};
	cout << "Forward List: ";
	printContainer(my_fwd_list);

	// Set 
	set<int> my_set = {5, 1, 3, 2, 4};
	cout << "Set: ";
	printContainer(my_set);

	// Map 
	map<int, string> my_map = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
	cout << "Map: ";
	printContainer(my_map, 1);

	// Deque 
	deque<int> my_deque = {7, 8, 9, 10};
	cout << "Deque: ";
	printContainer(my_deque);

	// Stack 
	stack<int> my_stack;
	my_stack.push(1);
	my_stack.push(2);
	my_stack.push(3);
	cout << "Stack: ";
	printContainer(my_stack);

	// Queue 
	queue<int> my_queue;
	my_queue.push(10);
	my_queue.push(20);
	my_queue.push(30);
	cout << "Queue: ";
	printContainer(my_queue);

	return 0;
}
