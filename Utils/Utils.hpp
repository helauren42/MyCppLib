#ifndef UTILS_HPP
# define UTILS_HPP

#include <type_traits>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <queue>
#include <string>

#include <iostream>

class TypeChecker
{
public:
	template <typename T>
	static constexpr bool isHandledContainer([[maybe_unused]]const T &value)
	{
		return is_specialization<T, std::vector>::value || is_specialization<T, std::list>::value || is_specialization<T, std::forward_list>::value || is_specialization<T, std::set>::value || is_specialization<T, std::map>::value || is_specialization<T, std::deque>::value || is_specialization<T, std::stack>::value || is_specialization<T, std::queue>::value;
	}

private:
	template <typename T, template <typename...> class Template>
	struct is_specialization : std::false_type
	{
	};

	template <template <typename...> class Template, typename... Args>
	struct is_specialization<Template<Args...>, Template> : std::true_type
	{
	};
};

static inline std::string executeCommand(const std::string& command) {
	std::string result;
	int status = system(command.c_str());
	if (WIFEXITED(status)) {
		result = std::to_string(WEXITSTATUS(status));
	}
	return result;
}

template<typename T>
static inline std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
	T value;
	std::cin >> value;
	vec.push_back(value);

    return is;
}

#endif