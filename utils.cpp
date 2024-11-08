#include "printer.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <iterator>

template <typename T>
struct has_c_str {
	private :
		template <typename U>
		static auto check(int) -> decltype(std::declval<U>().c_str(), std::true_type{});
		template <typename U> 
		static auto check(...) -> std::false_type{ return std::false_type{};};
	public :
		static constexpr bool value = decltype(check<T>(0))::value;
};

// Check for containers that have `begin()` and `end()`, excluding strings
template <typename T>
auto isContainer(T* p) -> std::enable_if_t<!has_c_str<T>::value, decltype(std::begin(*p), std::end(*p), std::true_type{})> {
	return std::true_type{};
}

template <typename T>
auto isContainer(T* p) -> decltype(p->pop(), std::true_type{}) {
	return std::true_type{};
}

template <typename T>
auto isContainer(T) -> std::false_type {
	return std::false_type{};
}

int main() {
	std::vector<int> v = {1, 2, 3};
	std::string s = "Hello";

	std::cout << "Is vector a container? " << decltype(isContainer(&v))::value << std::endl;
	std::cout << "Is string a container? " << decltype(isContainer(&s))::value << std::endl;
	return 0;
}

// template <typename T>
// class is_container {
// private:
// 	template <typename U>
// 	static auto check(U *p) -> decltype(std::begin(*p), std::end(*p), std::true_type{}) {
// 		return std::true_type{};
// 	}

//     template <typename U>
//     static auto check(U *p) -> decltype(p->pop(), std::true_type{});

//     template <typename U>
//     static std::false_type check(U) {
// 		return std::false_type{};
// 	};

//     template <typename>
//     static std::false_type check(...) {
// 		return std::false_type{};
// 	};

// public:
//     static constexpr bool value = decltype(check<T>(nullptr))::value;
// };


// int main() {
// 	// auto something = is_container<int>::value;
// 	// cout << "something: " << something << endl;

// 	std::vector<int> v = {1, 2, 3, 4, 5};

//     std::cout << "Is stack a container? " << is_container<std::stack<int>>::value << std::endl;  // true
//     std::cout << "Is queue a container? " << is_container<std::queue<int>>::value << std::endl;  // true
//     std::cout << "Is vector a container? " << is_container<std::vector<int>>::value << std::endl;  // true
//     std::cout << "Is list a container? " << is_container<std::list<int>>::value << std::endl;    // true
//     std::cout << "Is int a container? " << is_container<int>::value << std::endl;                // false
//     std::cout << "Is string a container? " << is_container<std::string>::value << std::endl;     // true
//     return 0;
// }