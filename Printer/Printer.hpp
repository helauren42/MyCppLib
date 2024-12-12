#ifndef OUT_HPP
#define OUT_HPP

#include <sstream>
#include <exception>

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <variant>

#include <unistd.h>
#include <fcntl.h>
#include <cstring>

#ifndef UTILS_HPP
#define UTILS_HPP
class TypeChecker
{
public:
	template <typename T>
	static constexpr bool isHandledContainer(const T &value)
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

#endif

enum ContainerType
{
	VECTOR,
	LIST,
	FORWARD_LIST,
	DEQUE,
	STACK,
	QUEUE,
	MAP,
	UNORDERED_MAP,
	UNORDERED_SET,
	SET,
	CUSTOM
};

template <typename... Args>
void out(const Args &...args);

template <typename... Args>
void fout(const Args &...args);

class Printer
{

private:

	/**
	 * @brief Prints the given separator string to the output stream.
	 * @param sep The separator string to print.
	 */
	static void printSep(const std::string &sep)
	{
		buffer << sep;
	}

	/**
	 * @brief Prints the given container to the output stream with the given separator string.
	 * @param container The container to print.
	 * @param sep The separator string to print between elements.
	 */
	template <typename T>
	static void printBeginEnd(const T &container, const std::string &sep)
	{
		const auto end = container.end();

		std::string new_sep = sep;
		bool newLine = false;

		for (auto it = container.begin(); it != container.end(); it++)
		{
			if (std::next(it) == end && !TypeChecker::isHandledContainer(*it))
			{
				Printer::print(*it, "", newLine);
			}
			else
			{
				Printer::print(*it, sep, newLine);
			}

			// to output the separator in case of nested containers
			if (TypeChecker::isHandledContainer(*it) && std::next(it) != end)
			{
				buffer << ", ";
			}
		}
	}

	/**
	 * @brief Prints the opening or closing delimiter of a container.
	 * @param type The type of container to print the delimiter for.
	 * @param side Whether to print the opening (0) or closing (1) delimiter.
	 * @param newLine Whether to print a newline after the closing delimiter.
	 */
	static void printContainerDelimiters(const int &type, const bool side, const bool &newLine)
	{
		char delimiter[2];
		switch (type)
		{
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
		case UNORDERED_MAP:
		case UNORDERED_SET:
		case SET:
			delimiter[0] = '{';
			delimiter[1] = '}';
			break;
		default:
			delimiter[0] = '(';
			delimiter[1] = ')';
			break;
		}

		if (side == 0)
		{
			buffer << delimiter[0];
		}
		else
		{
			buffer << &delimiter[1];
			if (newLine)
				buffer << "\n";
		}
	}

public:

	static std::stringstream buffer;
	// static void freeBuffer() {
	// 	std::cout << buffer << std::endl;
	// }

	/**
	 * @brief Prints multiple elements to the output stream with the given separator and newline control.
	 * @param first The first element to print.
	 * @param args The remaining elements to print.
	 */
	template <typename T, typename... Args>
	static void printAll(const T &first, const Args &...args)
	{
		Printer::print(first);
		if constexpr (sizeof...(args) > 0)
		{
			// Recursively call printAll with the remaining arguments.
			// This will print each element with the given separator and newline control.
			printAll(args...);
		}
	}

	/**
	 * @brief Prints a string to the output stream.
	 * @param a The string to print.
	 * @param sep The separator string to print after the string.
	 * @param newLine Whether to print a newline after the string.
	 */
	static void print(const std::string &a, const std::string &sep = "", const bool &newLine = true)
	{
		buffer << "\"";
		buffer << a;
		buffer << "\"";
		buffer << sep;
		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints a single character to the output stream.
	 * @param a The character to print.
	 * @param sep The separator string to print after the character.
	 * @param newLine Whether to print a newline after the character.
	 */
	static void print(const char &a, const std::string &sep = "", const bool &newLine = true)
	{
		buffer << &a;
		buffer << sep;
		if (newLine == true)
			buffer << "\n";;
	}

	/**
	 * @brief Prints a c-string to the output stream.
	 * @param s The string to print.
	 * @param sep The separator string to print after the string.
	 * @param newLine Whether to print a newline after the string.
	 */
	static void print(const char *s, const std::string &sep = "", const bool &newLine = false)
	{
		// strings are enclosed in double quotes
		buffer << s;
		buffer << sep;
		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints an integer to the output stream.
	 * @param a The integer to print.
	 * @param sep The separator string to print after the integer.
	 * @param newLine Whether to print a newline after the integer.
	 */
	static void print(const int &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the integer to a string
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		buffer << s;
		buffer << sep;
		if (newLine == true)
			buffer << "\n";
	}
	/**
	 * @brief Prints a double to the output stream.
	 * @param a The double to print.
	 * @param sep The separator string to print after the double.
	 * @param newLine Whether to print a newline after the double.
	 */
	static void print(const double &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the double to a string
		// using a stringstream
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		buffer << s;

		if (!sep.empty())
			buffer << sep;

		buffer << sep;
		if (newLine == true)
			buffer << "\n";
	}
	/**
	 * @brief Prints a boolean value to the output stream.
	 * @param a The boolean value to print.
	 * @param sep The separator string to print after the boolean value.
	 * @param newLine Whether to print a newline after the boolean value.
	 */
	static void print(const bool &a, const std::string &sep = "", const bool &newLine = true)
	{
		if (a == true)
			buffer << "true";
		else
			buffer << "false";
		buffer << sep;
		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints a float to the output stream.
	 * @param a The float to print.
	 * @param sep The separator string to print after the float.
	 * @param newLine Whether to print a newline after the float.
	 */
	static void print(const float &a, const std::string &sep = "", const bool &newLine = true)
	{
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();
		buffer << s;
		buffer << sep;
		if (newLine == true)
			buffer << "\n";
	}
	/**
	 * @brief Prints a long integer to the output stream.
	 * @param a The long integer to print.
	 * @param sep The separator string to print after the long integer.
	 * @param newLine Whether to print a newline after the long integer.
	 */
	static void print(const long &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the long integer to a string using a stringstream
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		buffer << s;
		buffer << sep;

		if (newLine == true)
			buffer << "\n";
	}
	/**
	 * @brief Prints a long long integer to the output stream.
	 * @param a The long long integer to print.
	 * @param sep The separator string to print after the long long integer.
	 * @param newLine Whether to print a newline after the long long integer.
	 */
	static void print(const long long &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the long long integer to a string using a stringstream
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		buffer << s;
		buffer << sep;

		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints a short integer to the output stream.
	 * @param a The unsigned short integer to print.
	 * @param sep The separator string to print after the unsigned short integer.
	 * @param newLine Whether to print a newline after the unsigned short integer.
	 */
	static void print(const short &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the unsigned short integer to a string using a stringstream
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		buffer << sep;
		buffer << s;
		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints an unsigned integer to the output stream.
	 * @param a The unsigned integer to print.
	 * @param sep The separator string to print after the unsigned integer.
	 * @param newLine Whether to print a newline after the unsigned integer.
	 */
	static void print(const unsigned int &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the unsigned integer to a string using a stringstream
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		// Write the separator string, the unsigned integer, and a newline to the output stream
		buffer << sep;
		buffer << s;
		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints an unsigned long integer to the output stream.
	 * @param a The unsigned long integer to print.
	 * @param sep The separator string to print after the unsigned long integer.
	 * @param newLine Whether to print a newline after the unsigned long integer.
	 */
	static void print(const unsigned long &a, const std::string &sep = "", const bool &newLine = true)
	{
		// Convert the unsigned long integer to a string using a stringstream
		std::stringstream ss;
		ss << a;
		std::string s = ss.str();

		buffer << s;
		buffer << sep;

		if (newLine == true)
			buffer << "\n";
	}

	/**
	 * @brief Prints the contents of a std::vector.
	 *
	 * @param vec The vector to print.
	 * @param sep The separator to use between elements (default is ", ").
	 * @param newLine Determines if a newline should be added after the output (default is true).
	 */
	template <class T>
	static void print(const std::vector<T> &vec, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(VECTOR, 0, newLine);
		Printer::printBeginEnd(vec, sep);
		Printer::printContainerDelimiters(VECTOR, 1, newLine);
	}
	/**
	 * @brief Prints the contents of a std::list.
	 *
	 * @param my_list The list to print.
	 * @param sep The separator to use between elements (default is ", ").
	 * @param newLine Determines if a newline should be added after the output (default is true).
	 */
	template <class T>
	static void print(const std::list<T> &my_list, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(LIST, 0, newLine);
		Printer::printBeginEnd(my_list, sep);
		Printer::printContainerDelimiters(LIST, 1, newLine);
	}

	/**
	 * @brief Prints the contents of a std::forward_list.
	 *
	 * @param my_list The forward_list to print.
	 * @param sep The separator to use between elements (default is ", ").
	 * @param newLine Determines if a newline should be added after the output (default is true).
	 */
	template <class T>
	static void print(const std::forward_list<T> &my_list, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(FORWARD_LIST, 0, newLine);
		Printer::printBeginEnd(my_list, sep);
		Printer::printContainerDelimiters(FORWARD_LIST, 1, newLine);
	}
	/**
	 * @brief Prints the contents of a std::deque.
	 *
	 * @param my_deque The deque to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 * @param newline Determines whether to print a new line at the end:
	 *             - set to true as default.
	 */
	template <class T>
	static void print(const std::deque<T> &my_deque, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(DEQUE, 0, newLine);
		Printer::printBeginEnd(my_deque, sep);
		Printer::printContainerDelimiters(DEQUE, 1, newLine);
	}

	/**
	 * @brief Prints the contents of a std::stack, first element is the top
	 *
	 * @param my_stack The stack to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 * @param newline Determines whether to print a new line at the end:
	 *             - set to true as default.
	 */
	template <class T>
	static void print(std::stack<T> my_stack, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(STACK, 0, newLine);
		while (!my_stack.empty())
		{
			auto elem = my_stack.top();
			if (TypeChecker::isHandledContainer(elem))
				Printer::print(elem, sep, false);
			else
				Printer::print(elem, "", false);
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
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 * @param newline Determines whether to print a new line at the end:
	 *             - set to true as default.
	 */
	template <class T>
	static void print(std::queue<T> my_queue, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(QUEUE, 0, newLine);
		while (!my_queue.empty())
		{
			auto elem = my_queue.front();
			if (TypeChecker::isHandledContainer(elem))
				Printer::print(elem, sep, false);
			else
				Printer::print(elem, "", false);
			my_queue.pop();
			if (!my_queue.empty())
				Printer::printSep(sep);
		}
		Printer::printContainerDelimiters(QUEUE, 1, newLine);
	}

	/**
	 * @brief Prints the contents of a std::map in different formats based on optional params.
	 *
	 * @tparam k Type of the map's keys.
	 * @tparam v Type of the map's values.
	 * @param my_map The map to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 * @param newline Determines whether to print a new line at the end:
	 *             - set to true as default.
	 */
	template <class K, class V>
	static void print(const std::map<K, V> &my_map, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(MAP, 0, newLine); // Print opening delimiter

		bool first = true;
		for (const auto &pair : my_map)
		{
			if (!first)
			{
				Printer::printSep(sep);
			}
			Printer::print(pair.first, "", false);
			Printer::print(": ", "", false);
			if (TypeChecker::isHandledContainer(pair.second))
			{
				Printer::print(pair.second, sep, false);
			}
			else
			{
				Printer::print(pair.second, "", false);
			}
			first = false;
		}

		Printer::printContainerDelimiters(MAP, 1, newLine); // Print closing delimiter
	}

	/**
	 * @brief Prints the contents of a std::unordered_map in different formats based on optional params.
	 *
	 * @tparam k Type of the map's keys.
	 * @tparam v Type of the map's values.
	 * @param my_map The map to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 * @param newline Determines whether to print a new line at the end:
	 *             - set to true as default.
	 */
	template <class T, class V>
	static void print(const std::unordered_map<T, V> &my_map, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(UNORDERED_MAP, 0, newLine);

		bool first = true;
		for (const auto &pair : my_map)
		{
			if (!first)
			{
				Printer::printSep(sep);
			}
			Printer::print(pair.first, "", false);
			Printer::print(": ", "", false);
			if (TypeChecker::isHandledContainer(pair.second))
				Printer::print(pair.second, sep, false);
			else
				Printer::print(pair.second, "", false);
			first = false;
		}
		Printer::printContainerDelimiters(UNORDERED_MAP, 1, newLine);
	}

	/**
	 * @brief Prints the contents of a std::set.
	 *
	 * @param my_set The set to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 * @param newline Determines whether to print a new line at the end:
	 *             - set to true as default.
	 */
	template <class T>
	static void print(const std::set<T> &my_set, const std::string &sep = ", ", const bool &newLine = true)
	{
		Printer::printContainerDelimiters(SET, 0, newLine);
		const auto end = my_set.end();
		for (auto it = my_set.begin(); it != my_set.end(); it++)
		{
			if (TypeChecker::isHandledContainer(*it))
				Printer::print(*it, sep, false);
			else
				Printer::print(*it, "", false);
			if (std::next(it) != end)
				Printer::printSep(sep);
		}
		Printer::printContainerDelimiters(SET, 1, newLine);
	}
	/**
	 * @brief Prints the contents of a custom object. Implementation of std::ostream operator<< overload is required as cout is called to output the object.
	 *
	 * @param object The object to print.
	 * @param sep changing this parameter has no effect
	 * @param newLine changing this parameter has no effect
	 */
	template <class T>
	static void print(const T &object, const std::string &sep = "", const bool &newLine = false,
					  typename std::enable_if<std::is_class<T>::value>::type * = nullptr)
	{
		std::stringstream ss;
		ss << object;
		std::string s(ss.str());
		buffer << s;
		if (!sep.empty())
			std::cout << sep;
		if (newLine)
			std::cout << std::endl;
	}

	template <class T>
	static void print(const T *object, const std::string &sep = "", const bool &newLine = false,
					  typename std::enable_if<std::is_class<T>::value>::type * = nullptr)
	{
		std::stringstream ss;
		ss << object;
		std::string s(ss.str());
		buffer << s;
		if (!sep.empty())
			std::cout << sep;
		if (newLine)
			std::cout << std::endl;
	}
};

/**
 * @brief Sets the file descriptor to redirect the `fout` stream to the specified file.
 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
 * @throws std::runtime_error if the file could not be opened.
 */
static int setFout(const char *file, bool trunc=true)
{
	int fd;
	if(trunc)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		std::string s("could not open file: ");
		s += file;
		throw(std::runtime_error(s));
	}
	// xxfileDes.setFout(fd);
	return (fd);
}

/**
 * @brief Sets the file descriptor to redirect the `fout` stream to the specified file.
 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
 * @throws std::runtime_error if the file could not be opened.
 */
static int setFout(const std::string &file, bool trunc=true)
{
	int fd;
	if(trunc)
		fd = open(file.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file.c_str(), O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		std::string s("could not open file: " + file);
		throw(std::runtime_error(s));
	}
	return (fd);
}

std::stringstream Printer::buffer("");

/**
 * @brief Outputs the given arguments to the standard output.
 *
 * This function sets the file descriptor to standard output (stdout)
 * and calls the Printer::printAll function to output the provided arguments.
 *
 * @tparam Args Variadic template parameter pack representing the types of the arguments.
 * @param args The arguments to be printed.
 */
template <typename... Args>
void out(const Args &...args)
{
	Printer::printAll(args...);
	std::cout << Printer::buffer.str() << std::endl;
	Printer::buffer.str("");
}

/**
 * @brief Outputs the given arguments to the file descriptor specified by fout_fd.
 *
 * This function sets the file descriptor to fout_fd and calls the Printer::printAll
 * function to output the provided arguments.
 *
 * @tparam Args Variadic template parameter pack representing the types of the arguments.
 * @param args The arguments to be printed.
 */
template <typename... Args>
void fout(const Args &...args)
{
	Printer::printAll(args...);
	std::ofstream of;
	std::cout << Printer::buffer.str() << std::endl;
}



#endif
