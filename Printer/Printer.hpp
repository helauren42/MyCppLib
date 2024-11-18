#ifndef Out_HPP
#define Out_HPP

#include <sstream>
#include <exception>

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

#include <unistd.h>
#include <fcntl.h>
#include <cstring>

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

class TypeChecker {
public:
    template <typename T>
    static constexpr bool isHandledContainer(const T& value) {
        return is_specialization<T, std::vector>::value
				|| is_specialization<T, std::list>::value
				|| is_specialization<T, std::forward_list>::value
				|| is_specialization<T, std::set>::value
				|| is_specialization<T, std::map>::value
				|| is_specialization<T, std::deque>::value
				|| is_specialization<T, std::stack>::value
				|| is_specialization<T, std::queue>::value;
    }

private:
    template <typename T, template <typename...> class Template>
    struct is_specialization : std::false_type {};

    template <template <typename...> class Template, typename... Args>
    struct is_specialization<Template<Args...>, Template> : std::true_type {};
};

int fout_fd = 1;

class Out {

	private:
	
		static void	printSep(const std::string& sep) {
			write(Out::fd, sep.c_str(), sep.length());
		}

		template<typename T>
		static void	printBeginEnd(const T& container, const std::string& sep) {
			const auto end = container.end();

			std::string new_sep = sep;
			bool newLine = false;

			for (auto it = container.begin(); it != container.end(); it++)
			{
				if (std::next(it) == end && !TypeChecker::isHandledContainer(*it))
					Out::print(*it, "", newLine);
				else
					Out::print(*it, sep, newLine);

				// to output the separator in case of nested containers
				if(TypeChecker::isHandledContainer(*it) && std::next(it) != end) {
					write(Out::fd, ", ", 1);
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
				write(Out::fd, &delimiter[0], 1);
			} else {
				write(Out::fd, &delimiter[1], 1);
				if(newLine)
					write(Out::fd, "\n", 1);
			}
		}

	public:

		static int fd;

		static void	setFoutFd(const int file_descriptor) {
			fout_fd = file_descriptor;
		}

		static void	setFoutFd(const char* file) {
			fout_fd = open(file, O_CREAT | O_WRONLY, 0644);
			if(fout_fd < 0) {
				std::string s("could not open file: ");
				s += file;
				throw (std::runtime_error(s));
			}
		}

		static void	setFoutFd(const std::string& file) {
			fout_fd = open(file.c_str(), O_CREAT, O_WRONLY, 0644);
			if(fout_fd < 0) {
				std::string s("could not open file: " + file);
				throw (std::runtime_error(s));
			}
		}
	
		template <typename T, typename... Args>
		static void	printAll(T first, Args... args)
		{
			Out::print(first);
			if constexpr (sizeof...(args) > 0) {
				printAll(args...);
			}
		}

		static void print(const std::string &a, const std::string& sep = "", const bool& newLine = true)
		{
			write(Out::fd, "\"", 1);
			write(Out::fd, a.c_str(), a.length());
			write(Out::fd, "\"", 1);
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const char &a, const std::string& sep = "", const bool& newLine = true)
		{
			write(Out::fd, &a, 1);
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const char *s, const std::string& sep = "", const bool& newLine = false)
		{
			write(Out::fd, s, strlen(s));
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}

		static void print(const int &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, s.c_str(), s.length());
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const double &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, s.c_str(), s.length());
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const bool &a, const std::string& sep = "", const bool& newLine = true)
		{
			if(a == true)
				write(Out::fd, "true", 4);
			else
				write(Out::fd, "false", 5);
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const float &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const long &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}
		static void print(const long long &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}

		static void print(const short &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}

		static void print(const unsigned int &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
		}

		static void print(const unsigned long &a, const std::string& sep = "", const bool& newLine = true)
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			write(Out::fd, sep.c_str(), sep.length());
			if(newLine == true)
				write(Out::fd, "\n", 1);
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
			Out::printContainerDelimiters(VECTOR, 0, newLine);
			Out::printBeginEnd(vec, sep);
			Out::printContainerDelimiters(VECTOR, 1, newLine);
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
			Out::printContainerDelimiters(LIST, 0, newLine);
			Out::printBeginEnd(my_list, sep);
			Out::printContainerDelimiters(LIST, 1, newLine);
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
			Out::printContainerDelimiters(FORWARD_LIST, 0, newLine);
			Out::printBeginEnd(my_list, sep);
			Out::printContainerDelimiters(FORWARD_LIST, 1, newLine);
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
			Out::printContainerDelimiters(DEQUE, 0, newLine);
			Out::printBeginEnd(my_deque, sep);
			Out::printContainerDelimiters(DEQUE, 1, newLine);
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
			Out::printContainerDelimiters(STACK, 0, newLine);
			while (!my_stack.empty())
			{
				auto elem = my_stack.top();
				if(TypeChecker::isHandledContainer(elem))
					Out::print(elem, sep, false);
				else
					Out::print(elem, "", false);
				my_stack.pop();
				if (!my_stack.empty())
					Out::printSep(sep);
			}
			Out::printContainerDelimiters(STACK, 1, newLine);
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
			Out::printContainerDelimiters(QUEUE, 0, newLine);
			while (!my_queue.empty())
			{
				auto elem = my_queue.front();
				if(TypeChecker::isHandledContainer(elem))
					Out::print(elem, sep, false);
				else
					Out::print(elem, "", false);
				my_queue.pop();
				if (!my_queue.empty())
					Out::printSep(sep);
			}
			Out::printContainerDelimiters(QUEUE, 1, newLine);
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
        
		Out::printContainerDelimiters(MAP, 0, newLine);  // Print opening delimiter

        bool first = true;
        for (const auto &pair : my_map) {
            if (!first) {
				Out::printSep(sep);
            }
			Out::print(pair.first, "", false);
			Out::print(": ", "", false);
			if(TypeChecker::isHandledContainer(pair.second))
				Out::print(pair.second, sep, false);
			else
				Out::print(pair.second, "", false);
            first = false;
        }

        Out::printContainerDelimiters(MAP, 1, newLine);  // Print closing delimiter
    }

	/**
	 * @brief Prints the contents of a std::set.
	 *
	 * @param my_set The set to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 */
	template <class T>
	static void print(const std::set<T> &my_set, const std::string& sep = ", ", const bool& newLine = true)
	{
		Out::printContainerDelimiters(SET, 0, newLine);
		const auto end = my_set.end();
		for (auto it = my_set.begin(); it != my_set.end(); it++)
		{
			if(TypeChecker::isHandledContainer(*it))
				Out::print(*it, sep, false);
			else
				Out::print(*it, "", false);
			if (std::next(it) != end)
				Out::printSep(sep);
		}
		Out::printContainerDelimiters(SET, 1, newLine);
	}

};

int Out::fd = 1;

template<typename... Args>
void	out(Args... args) {
	Out::fd = 1;
	Out::printAll(args...);
}

template<typename... Args>
void	fout(Args... args) {
	Out::fd = fout_fd;
	// out("fout::fd: ", Out::fd);
	
	Out::printAll(args...);
}

#endif
