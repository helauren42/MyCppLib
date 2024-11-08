#include "printer.hpp"

#include <type_traits>
#include <iterator>

// Check if type T has begin() and end() methods
template <typename T>
class is_container {
private:
    // Helper type to detect presence of `begin` and `end`
	template <typename U>
	static auto check(U p) -> decltype(std::begin(p), std::end(p), std::true_type{}) {
		return std::true_type{};
	}

    // Fallback for types that do not have `begin` and `end`
    template <typename>
    static std::false_type check(...);

public:
    static constexpr bool value = decltype(check<T>(nullptr))::value;
};

int main() {
    std::cout << "Is vector a container? " << is_container<std::vector<int>>::value << std::endl;  // true
    std::cout << "Is list a container? " << is_container<std::list<int>>::value << std::endl;    // true
    std::cout << "Is int a container? " << is_container<int>::value << std::endl;                // false
    std::cout << "Is string a container? " << is_container<std::string>::value << std::endl;     // true
    return 0;
}