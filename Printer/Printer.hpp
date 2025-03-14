#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "../Utils/Utils.hpp"

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <exception>
#include <mutex>

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

inline std::ofstream of;

#ifndef UTILS_HPP
#define UTILS_HPP

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

namespace
{
	class BasePrinter
	{

	private:
		/**
		 * @brief Prints the given separator string to the output stream.
		 * @param sep The separator string to print.
		 */
		void printSep(const std::string &sep)
		{
			buffer << sep;
		}

		/**
		 * @brief Prints the given container to the output stream with the given separator string.
		 * @param container The container to print.
		 * @param sep The separator string to print between elements.
		 */
		template <typename T>
		void printBeginEnd(const T &container, const std::string &sep)
		{
			const auto end = container.end();

			std::string new_sep = sep;

			for (auto it = container.begin(); it != container.end(); it++)
			{
				if (std::next(it) == end && !TypeChecker::isHandledContainer(*it))
				{
					BasePrinter::print(*it, "");
				}
				else
				{
					BasePrinter::print(*it, sep);
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
		 */
		void printContainerDelimiters(const int &type, const bool side)
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
				buffer << delimiter[1];
			}
		}

		/**
		 * @brief Prints a string to the output stream.
		 * @param a The string to print.
		 * @param sep The separator string to print after the string.
		 */
		void print(const std::string &a, const std::string &sep = "")
		{
			buffer << "\"";
			buffer << a;
			buffer << "\"";
			buffer << sep;
		}

		/**
		 * @brief Prints a single character to the output stream.
		 * @param a The character to print.
		 * @param sep The separator string to print after the character.
		 */
		void print(const char a, const std::string &sep = "")
		{
			buffer << a;
			buffer << sep;
			;
		}

		/**
		 * @brief Prints a c-string to the output stream.
		 * @param s The string to print.
		 * @param sep The separator string to print after the string.
		 */
		void print(const char *s, const std::string &sep = "")
		{
			// strings are enclosed in double quotes
			buffer << s;
			buffer << sep;
		}

		/**
		 * @brief Prints an integer to the output stream.
		 * @param a The integer to print.
		 * @param sep The separator string to print after the integer.
		 */
		void print(const int &a, const std::string &sep = "")
		{
			// Convert the integer to a string
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();

			buffer << s;
			buffer << sep;
		}
		/**
		 * @brief Prints a double to the output stream.
		 * @param a The double to print.
		 * @param sep The separator string to print after the double.
		 */
		void print(const double &a, const std::string &sep = "")
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
		}
		/**
		 * @brief Prints a boolean value to the output stream.
		 * @param a The boolean value to print.
		 * @param sep The separator string to print after the boolean value.
		 */
		void print(const bool &a, const std::string &sep = "")
		{
			if (a == true)
				buffer << "true";
			else
				buffer << "false";
			buffer << sep;
		}

		/**
		 * @brief Prints a float to the output stream.
		 * @param a The float to print.
		 * @param sep The separator string to print after the float.
		 */
		void print(const float &a, const std::string &sep = "")
		{
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();
			buffer << s;
			buffer << sep;
		}
		/**
		 * @brief Prints a long integer to the output stream.
		 * @param a The long integer to print.
		 * @param sep The separator string to print after the long integer.
		 */
		void print(const long &a, const std::string &sep = "")
		{
			// Convert the long integer to a string using a stringstream
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();

			buffer << s;
			buffer << sep;
		}
		/**
		 * @brief Prints a long long integer to the output stream.
		 * @param a The long long integer to print.
		 * @param sep The separator string to print after the long long integer.
		 */
		void print(const long long &a, const std::string &sep = "")
		{
			// Convert the long long integer to a string using a stringstream
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();

			buffer << s;
			buffer << sep;
		}

		/**
		 * @brief Prints a short integer to the output stream.
		 * @param a The unsigned short integer to print.
		 * @param sep The separator string to print after the unsigned short integer.
		 */
		void print(const short &a, const std::string &sep = "")
		{
			// Convert the unsigned short integer to a string using a stringstream
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();

			buffer << sep;
			buffer << s;
		}

		/**
		 * @brief Prints an unsigned integer to the output stream.
		 * @param a The unsigned integer to print.
		 * @param sep The separator string to print after the unsigned integer.
		 */
		void print(const unsigned int &a, const std::string &sep = "")
		{
			// Convert the unsigned integer to a string using a stringstream
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();

			// Write the separator string, the unsigned integer
			buffer << sep;
			buffer << s;
		}

		/**
		 * @brief Prints an unsigned long integer to the output stream.
		 * @param a The unsigned long integer to print.
		 * @param sep The separator string to print after the unsigned long integer.
		 */
		void print(const unsigned long &a, const std::string &sep = "")
		{
			// Convert the unsigned long integer to a string using a stringstream
			std::stringstream ss;
			ss << a;
			std::string s = ss.str();

			buffer << s;
			buffer << sep;
		}

		/**
		 * @brief Prints the contents of a std::vector.
		 *
		 * @param vec The vector to print.
		 * @param sep The separator to use between elements (default is ", ").
		 */
		template <class T>
		void print(const std::vector<T> &vec, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(VECTOR, 0);
			BasePrinter::printBeginEnd(vec, sep);
			BasePrinter::printContainerDelimiters(VECTOR, 1);
		}
		/**
		 * @brief Prints the contents of a std::list.
		 *
		 * @param my_list The list to print.
		 * @param sep The separator to use between elements (default is ", ").
		 */
		template <class T>
		void print(const std::list<T> &my_list, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(LIST, 0);
			BasePrinter::printBeginEnd(my_list, sep);
			BasePrinter::printContainerDelimiters(LIST, 1);
		}

		/**
		 * @brief Prints the contents of a std::forward_list.
		 *
		 * @param my_list The forward_list to print.
		 * @param sep The separator to use between elements (default is ", ").
		 */
		template <class T>
		void print(const std::forward_list<T> &my_list, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(FORWARD_LIST, 0);
			BasePrinter::printBeginEnd(my_list, sep);
			BasePrinter::printContainerDelimiters(FORWARD_LIST, 1);
		}
		/**
		 * @brief Prints the contents of a std::deque.
		 *
		 * @param my_deque The deque to print.
		 * @param sep Determines the print format:
		 *             - uses ", " as separator between elements by default.
		 */
		template <class T>
		void print(const std::deque<T> &my_deque, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(DEQUE, 0);
			BasePrinter::printBeginEnd(my_deque, sep);
			BasePrinter::printContainerDelimiters(DEQUE, 1);
		}

		/**
		 * @brief Prints the contents of a std::stack, first element is the top
		 *
		 * @param my_stack The stack to print.
		 * @param sep Determines the print format:
		 *             - uses ", " as separator between elements by default.
		 */
		template <class T>
		void print(std::stack<T> my_stack, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(STACK, 0);
			while (!my_stack.empty())
			{
				auto elem = my_stack.top();
				if (TypeChecker::isHandledContainer(elem))
					BasePrinter::print(elem, sep);
				else
					BasePrinter::print(elem, "");
				my_stack.pop();
				if (!my_stack.empty())
					BasePrinter::printSep(sep);
			}
			BasePrinter::printContainerDelimiters(STACK, 1);
		}

		/**
		 * @brief Prints the contents of a std::queue, first element is the front.
		 *
		 * @param my_queue The queue to print.
		 * @param sep Determines the print format:
		 *             - uses ", " as separator between elements by default.
		 */
		template <class T>
		void print(std::queue<T> my_queue, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(QUEUE, 0);
			while (!my_queue.empty())
			{
				auto elem = my_queue.front();
				if (TypeChecker::isHandledContainer(elem))
					BasePrinter::print(elem, sep);
				else
					BasePrinter::print(elem, "");
				my_queue.pop();
				if (!my_queue.empty())
					BasePrinter::printSep(sep);
			}
			BasePrinter::printContainerDelimiters(QUEUE, 1);
		}

		/**
		 * @brief Prints the contents of a std::map in different formats based on optional params.
		 *
		 * @tparam k Type of the map's keys.
		 * @tparam v Type of the map's values.
		 * @param my_map The map to print.
		 * @param sep Determines the print format:
		 *             - uses ", " as separator between elements by default.
		 */
		template <class K, class V>
		void print(const std::map<K, V> &my_map, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(MAP, 0); // Print opening delimiter

			bool first = true;
			for (const auto &pair : my_map)
			{
				if (!first)
				{
					BasePrinter::printSep(sep);
				}
				BasePrinter::print(pair.first, "");
				BasePrinter::print(": ", "");
				if (TypeChecker::isHandledContainer(pair.second))
				{
					BasePrinter::print(pair.second, sep);
				}
				else
				{
					BasePrinter::print(pair.second, "");
				}
				first = false;
			}

			BasePrinter::printContainerDelimiters(MAP, 1); // Print closing delimiter
		}

		/**
		 * @brief Prints the contents of a std::unordered_map in different formats based on optional params.
		 *
		 * @tparam k Type of the map's keys.
		 * @tparam v Type of the map's values.
		 * @param my_map The map to print.
		 * @param sep Determines the print format:
		 *             - uses ", " as separator between elements by default.
		 */
		template <class T, class V>
		void print(const std::unordered_map<T, V> &my_map, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(UNORDERED_MAP, 0);

			bool first = true;
			for (const auto &pair : my_map)
			{
				if (!first)
				{
					BasePrinter::printSep(sep);
				}
				BasePrinter::print(pair.first, "");
				BasePrinter::print(": ", "");
				if (TypeChecker::isHandledContainer(pair.second))
					BasePrinter::print(pair.second, sep);
				else
					BasePrinter::print(pair.second, "");
				first = false;
			}
			BasePrinter::printContainerDelimiters(UNORDERED_MAP, 1);
		}

		/**
		 * @brief Prints the contents of a std::set.
		 *
		 * @param my_set The set to print.
		 * @param sep Determines the print format:
		 *             - uses ", " as separator between elements by default.
		 */
		template <class T>
		void print(const std::set<T> &my_set, const std::string &sep = ", ")
		{
			BasePrinter::printContainerDelimiters(SET, 0);
			const auto end = my_set.end();
			for (auto it = my_set.begin(); it != my_set.end(); it++)
			{
				if (TypeChecker::isHandledContainer(*it))
					BasePrinter::print(*it, sep);
				else
					BasePrinter::print(*it, "");
				if (std::next(it) != end)
					BasePrinter::printSep(sep);
			}
			BasePrinter::printContainerDelimiters(SET, 1);
		}
		/**
		 * @brief Prints the contents of a custom object. Implementation of std::ostream operator<< overload is required.
		 *
		 * @param object The object to print.
		 * @param sep changing this parameter has no effect
		 */
		template <class T>
		void print(const T &object, const std::string &sep = "",
				   typename std::enable_if<std::is_class<T>::value>::type * = nullptr)
		{
			std::stringstream ss;
			ss << object;
			std::string s(ss.str());
			buffer << s;
			if (!sep.empty())
				buffer << sep;
		}

		template <class T>
		void print(const T *object, const std::string &sep = "",
				   typename std::enable_if<std::is_class<T>::value>::type * = nullptr)
		{
			std::stringstream ss;
			ss << object;
			std::string s(ss.str());
			buffer << s;
			if (!sep.empty())
				buffer << sep;
		}

		std::stringstream buffer;

	public:
		std::string getBufferStr() const
		{
			return buffer.str();
		}
		void emptyBuffer()
		{
			buffer.str("");
		}

		/**
		 * @brief Sets the file descriptor to redirect the `Fout` stream to the specified file.
		 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
		 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
		 * @throws std::runtime_error if the file could not be opened.
		 */
		void setFile(const std::string &file, bool trunc = true)
		{
			if (trunc == true)
				of.open(file, std::ios::out | std::ios::trunc);
			else
				of.open(file, std::ios::out | std::ios::app);
			if (!of.is_open())
				throw(std::runtime_error("Could not open file: " + file));
		}
		bool fileSet()
		{
			return of.is_open();
		}
		/**
		 * @brief Prints multiple elements to the output stream.
		 * @param first The first element to print.
		 * @param args The remaining elements to print.
		 */
		template <typename T, typename... Args>
		void printAll(const T &first, const Args &...args)
		{
			BasePrinter::print(first);
			if constexpr (sizeof...(args) > 0)
			{
				// Recursively call printAll with the remaining arguments.
				// This will print each element.
				printAll(args...);
			}
		}
	};
};

namespace Printer
{
	static BasePrinter base;
	/**
	 * @brief Sets the file in which the Fout function will output.
	 *
	 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
	 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
	 * @throws std::runtime_error if the file could not be opened.
	 */
	inline void setFout(const std::string file, bool trunc = true)
	{
		base.setFile(file, trunc);
	}

	/**
	 * @brief Outputs the given scalar type and container arguments to the standard output.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	inline void stdOut(const Args &...args)
	{
		base.printAll(args...);
		std::cout << base.getBufferStr() << std::endl;
		base.emptyBuffer();
	}

	/**
	 * @brief Outputs the given scalar type and container arguments to the standard output.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	inline void stdErr(const Args &...args)
	{
		base.printAll(args...);
		std::cerr << base.getBufferStr() << std::endl;
		base.emptyBuffer();
	}

	/**
	 * @brief Outputs the given arguments to the file descriptor specified by Fout_fd.
	 *
	 * This function sets the file descriptor to Fout_fd and calls the BasePrinter::printAll
	 * function to output scalar types and container arguments.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	inline void Fout(const Args &...args)
	{
		base.printAll(args...);
		if (!base.fileSet())
			throw std::logic_error("Output file not defined");
		of << base.getBufferStr() << std::endl;
		base.emptyBuffer();
	}
}

#endif
