#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "utils.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <variant>
#include <type_traits>

class Printer
{
public:

	template <typename T, typename... Args>
	static void	all(T first, Args... args)
	{
		Printer::print(first);
		if constexpr (sizeof...(args) > 0) {
			all(args...);
		}
	}

	static void print(const std::string &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const char &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const char *s)
	{
		std::cout << s << std::endl;
	}
	static void print(const int &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const double &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const bool &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const float &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const long &a)
	{
		std::cout << a << std::endl;
	}
	static void print(const long long &a)
	{
		std::cout << a << std::endl;
	}

	static void print(const short &a)
	{
		std::cout << a << std::endl;
	}

	static void print(const unsigned int &a)
	{
		std::cout << a << std::endl;
	}

	static void print(const unsigned long &a)
	{
		std::cout << a << std::endl;
	}

	/**
	 * @brief Prints the contents of a std::vector.
	 *
	 * @param vec The vector to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != : uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(const std::vector<T> &vec, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		for (const auto &value : vec)
		{
			std::cout << value;
			if (&value != &vec.back())
				std::cout << sep;
		}
		std::cout << std::endl;
	}
	/**
	 * @brief Prints the contents of a std::list.
	 *
	 * @param my_list The list to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != : uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(const std::list<T> &my_list, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		for (const auto &value : my_list)
		{
			std::cout << value;
			if (&value != &my_list.back())
				std::cout << sep;
		}
		std::cout << std::endl;
	}

	/**
	 * @brief Prints the contents of a std::forward_list.
	 *
	 * @param my_list The forward_list to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != : uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(const std::forward_list<T> &my_list, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		const auto end = my_list.end();

		for (auto it = my_list.begin(); it != my_list.end(); it++)
		{
			std::cout << *it;
			if (std::next(it) != end)
				std::cout << sep;
		}
		std::cout << std::endl;
	}
	/**
	 * @brief Prints the contents of a std::deque.
	 *
	 * @param my_deque The deque to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != 0: uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(const std::deque<T> &my_deque, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		auto end = my_deque.end();
		for (auto it = my_deque.begin(); it != end; ++it)
		{
			std::cout << *it;
			if (std::next(it) != end)
				std::cout << sep;
		}
		std::cout << std::endl;
	}

	/**
	 * @brief Prints the contents of a std::stack, first element is the top
	 *
	 * @param my_stack The stack to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != 0: uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(std::stack<T> my_stack, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		while (!my_stack.empty())
		{
			std::cout << my_stack.top();
			my_stack.pop();
			if (!my_stack.empty())
				std::cout << sep;
		}
		std::cout << std::endl;
	}

	/**
	 * @brief Prints the contents of a std::queue, first element is the front.
	 *
	 * @param my_queue The queue to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != 0: uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(std::queue<T> my_queue, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		while (!my_queue.empty())
		{
			std::cout << my_queue.front();
			my_queue.pop();
			if (!my_queue.empty())
				std::cout << sep;
		}
		std::cout << std::endl;
	}

	/**
	 * @brief Prints the contents of a std::map in different formats based on mode.
	 *
	 * @tparam k Type of the map's keys.
	 * @tparam v Type of the map's values.
	 * @param my_map The map to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: Prints in "key: value" format with descriptions ("key" and "value" labels).
	 *             - mode = 1: Prints in "key: value" format without labels, for a cleaner, compact look.
	 */
	template <class K, class V>
	static void print(const std::map<K, V> &my_map, int mode = 0)
	{
		if (mode == 0)
		{
			for (const auto &pair : my_map)
			{
				std::cout << "key: " << pair.first << ", value: " << pair.second << std::endl;
			}
		}
		else
		{
			for (const auto &pair : my_map)
			{
				std::cout << pair.first << ": " << pair.second << std::endl;
			}
		}
	}

	/**
	 * @brief Prints the contents of a std::set.
	 *
	 * @param my_set The set to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != 0: uses "\n" as separator between elements.
	 */
	template <class T>
	static void print(const std::set<T> &my_set, int mode = 0)
	{
		std::string sep = (mode == 0) ? ", " : "\n";
		const auto end = my_set.end();
		for (auto it = my_set.begin(); it != my_set.end(); it++)
		{
			std::cout << *it;
			if (std::next(it) != end)
				std::cout << sep;
		}
	}
};

#endif