#include "printer.hpp"

template<typename T1, typename T2>
auto add(const T1& x, const T2& y) -> decltype (x+y){
	// return x + y;
	return x+y;
}

int main() {
	std::cout << add(1, 2.5) << std::endl;
	std::cout << add(1.5, 2) << std::endl;

	return 0;
}