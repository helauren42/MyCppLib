#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <iostream>
#include <variant>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <variant>

using std::cerr;
using std::cout;
using std::endl;

// using std::string;
// using std::variant;

// 	using std::deque;
// 	using std::forward_list;
// 	using std::list;
// 	using std::map;
// 	using std::queue;
// 	using std::set;
// 	using std::stack;
// 	using std::vector;

class Printer
{
	public:
		/**
		 * @brief Prints the contents of a std::vector.
		 *
		 * @param vec The vector to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != : uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(const std::vector<T> &vec, int mode = 0);

		/**
		 * @brief Prints the contents of a std::list.
		 *
		 * @param my_list The list to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != : uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(const std::list<T> &my_list, int mode = 0);

		/**
		 * @brief Prints the contents of a std::forward_list.
		 *
		 * @param my_list The forward_list to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != : uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(const std::forward_list<T> &my_list, int mode = 0);

		/**
		 * @brief Prints the contents of a std::deque.
		 *
		 * @param my_deque The deque to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(const std::deque<T> &my_deque, int mode = 0);

		/**
		 * @brief Prints the contents of a std::stack, first element is the top
		 *
		 * @param my_stack The stack to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(std::stack<T> my_stack, int mode = 0);

		/**
		 * @brief Prints the contents of a std::queue, first element is the front.
		 *
		 * @param my_queue The queue to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(std::queue<T> my_queue, int mode = 0);

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
		template <typename K, typename V>
		void printContainer(const std::map<K, V> &my_map, int mode = 0);

		/**
		 * @brief Prints the contents of a std::set.
		 *
		 * @param my_set The set to print.
		 * @param mode Determines the print format:
		 *             - mode = 0: uses ", " as separator between elements.
		 *             - mode != 0: uses "\n" as separator between elements.
		 */
		template <typename T>
		void printContainer(const std::set<T> &my_set, int mode = 0);
};

#endif