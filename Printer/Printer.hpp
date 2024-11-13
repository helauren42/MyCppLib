#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "../Checker/Checker.hpp"

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

enum ContainerType {
    VECTOR,
    LIST,
    FORWARD_LIST,
    DEQUE,
    STACK,
    QUEUE,
    MAP,
    SET
};

class Printer {

	private:
	
		static void	printSep(const std::string& sep) {
			if (sep == "\n")
				std::cout << std::endl;
			else
				std::cout << (sep);
		}

		template<typename T>
		static void	printBeginEnd(const T& container, const std::string& sep) {
			const auto end = container.end();

			std::string new_sep = sep;
			bool newLine = false;

			for (auto it = container.begin(); it != container.end(); it++)
			{
				if (std::next(it) == end && !TypeChecker::isContainer(*it))
					Printer::print(*it, "", newLine);
				else
					Printer::print(*it, sep, newLine);

				// to output the separator in case of nested containers
				if(TypeChecker::isContainer(*it) && std::next(it) != end) {
					std::cout << ", ";
				}
			}
		}

		static void printContainerDelimiters(const int& type, const bool side, const bool& newLine) {
			char delimiter[2];
			switch (type) {
				case VECTOR:
				case LIST:
				case FORWARD_LIST:
				case DEQUE:
				case STACK:
				case QUEUE:
					delimiter[0] = '[';
					delimiter[1] = ']';
					break;
				case MAP:
				case SET:
					delimiter[0] = '{';
					delimiter[1] = '}';
					break;
				default:
					delimiter[0] = '(';
					delimiter[1] = ')';
					break;
			}

			if (side == 0) {
				std::cout << delimiter[0];
			} else {
				std::cout << delimiter[1];
				if(newLine)
					std::cout << std::endl;
			}
		}

	public:

		template <typename T, typename... Args>
		static void	printAll(T first, Args... args)
		{
			Printer::print(first);
			if constexpr (sizeof...(args) > 0) {
				printAll(args...);
			}
		}

		static void print(const std::string &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << "\"";
			std::cout << a;
			std::cout << "\"";
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const char &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const char *s, const std::string& sep = "", const bool& newLine = false)
		{
			std::cout << s;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}

		static void print(const int &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const double &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const bool &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const float &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const long &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}
		static void print(const long long &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}

		static void print(const short &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}

		static void print(const unsigned int &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
		}

		static void print(const unsigned long &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::cout << a;
			std::cout << sep;
			if(newLine == true)
				std::cout << std::endl;
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
		static void print(const std::vector<T> &vec, const std::string& sep = ", ", const bool& newLine = true)
		{
			Printer::printContainerDelimiters(VECTOR, 0, newLine);
			Printer::printBeginEnd(vec, sep);
			Printer::printContainerDelimiters(VECTOR, 1, newLine);
		}
		/**
		 * @brief Prints the contents of a std::list.
		 *
		 * @param my_list The list to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != : uses ", " as separator between elements.
		 */
		template <class T>
		static void print(const std::list<T> &my_list, const std::string& sep = ", ", const bool& newLine = true)
		{
			Printer::printContainerDelimiters(LIST, 0, newLine);
			Printer::printBeginEnd(my_list, sep);
			Printer::printContainerDelimiters(LIST, 1, newLine);
		}

		/**
		 * @brief Prints the contents of a std::forward_list.
		 *
		 * @param my_list The forward_list to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != : uses ", " as separator between elements.
		 */
		template <class T>
		static void print(const std::forward_list<T> &my_list, const std::string& sep = ", ", const bool& newLine = true)
		{
			Printer::printContainerDelimiters(FORWARD_LIST, 0, newLine);
			Printer::printBeginEnd(my_list, sep);
			Printer::printContainerDelimiters(FORWARD_LIST, 1, newLine);
		}
		/**
		 * @brief Prints the contents of a std::deque.
		 *
		 * @param my_deque The deque to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses ", " as separator between elements.
		 */
		template <class T>
		static void print(const std::deque<T> &my_deque, const std::string& sep = ", ", const bool& newLine = true)
		{
			Printer::printContainerDelimiters(DEQUE, 0, newLine);
			Printer::printBeginEnd(my_deque, sep);
			Printer::printContainerDelimiters(DEQUE, 1, newLine);
		}

		/**
		 * @brief Prints the contents of a std::stack, first element is the top
		 *
		 * @param my_stack The stack to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses ", " as separator between elements.
		 */
		template <class T>
		static void print(std::stack<T> my_stack, const std::string& sep = ", ", const bool& newLine = true)
		{
			Printer::printContainerDelimiters(STACK, 0, newLine);
			while (!my_stack.empty())
			{
				std::cout << my_stack.top();
				my_stack.pop();
				if (!my_stack.empty())
					Printer::printSep(sep);
			}
			Printer::printContainerDelimiters(STACK, 1, newLine);
		}

		/**
		 * @brief Prints the contents of a std::queue, first element is the front.
		 *
		 * @param my_queue The queue to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses ", " as separator between elements.
		 */
		template <class T>
		static void print(std::queue<T> my_queue, const std::string& sep = ", ", const bool& newLine = true)
		{
			Printer::printContainerDelimiters(QUEUE, 0, newLine);
			while (!my_queue.empty())
			{
				std::cout << my_queue.front();
				my_queue.pop();
				if (!my_queue.empty())
					Printer::printSep(sep);
			}
			Printer::printContainerDelimiters(QUEUE, 1, newLine);
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
    static void print(const std::map<K, V> &my_map, const std::string& sep = ", ", const bool& newLine = true) {
        
		Printer::printContainerDelimiters(MAP, 0, newLine);  // Print opening delimiter

        bool first = true;
        for (const auto &pair : my_map) {
            if (!first) {
				Printer::printSep(sep);
            }
			Printer::print(pair.first, "", false);
			Printer::print(": ", "", false);
			if(TypeChecker::isContainer(pair.second))
				Printer::print(pair.second, sep, false);
			else
				Printer::print(pair.second, "", false);
            first = false;
        }

        Printer::printContainerDelimiters(MAP, 1, newLine);  // Print closing delimiter
    }

	/**
	 * @brief Prints the contents of a std::set.
	 *
	 * @param my_set The set to print.
	 * @param mode Determines the print format:
	 *             - mode = 0: uses ", " as separator between elements.
	 *             - mode != 0: uses ", " as separator between elements.
	 */
	template <class T>
	static void print(const std::set<T> &my_set, const std::string& sep = ", ", const bool& newLine = true)
	{
		Printer::printContainerDelimiters(SET, 0, newLine);
		const auto end = my_set.end();
		for (auto it = my_set.begin(); it != my_set.end(); it++)
		{
			Printer::print(*it, ",", false);
			if (std::next(it) != end)
				Printer::printSep(sep);
		}
		Printer::printContainerDelimiters(SET, 1, newLine);
	}

};

template<typename... Args>
void	out(Args... args) {
	Printer::printAll(args...);
}

#endif