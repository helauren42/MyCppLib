#ifndef OUT_HPP
#define OUT_HPP

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <exception>

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

namespace {

	class Printer
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
			bool newLine = false;

			for (auto it = container.begin(); it != container.end(); it++)
			{
				if (std::next(it) == end && !TypeChecker::isHandledContainer(*it))
				{
					Printer::print(*it, "");
				}
				else
				{
					Printer::print(*it, sep);
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
			Printer::printContainerDelimiters(VECTOR, 0);
			Printer::printBeginEnd(vec, sep);
			Printer::printContainerDelimiters(VECTOR, 1);
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
			Printer::printContainerDelimiters(LIST, 0);
			Printer::printBeginEnd(my_list, sep);
			Printer::printContainerDelimiters(LIST, 1);
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
			Printer::printContainerDelimiters(FORWARD_LIST, 0);
			Printer::printBeginEnd(my_list, sep);
			Printer::printContainerDelimiters(FORWARD_LIST, 1);
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
			Printer::printContainerDelimiters(DEQUE, 0);
			Printer::printBeginEnd(my_deque, sep);
			Printer::printContainerDelimiters(DEQUE, 1);
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
			Printer::printContainerDelimiters(STACK, 0);
			while (!my_stack.empty())
			{
				auto elem = my_stack.top();
				if (TypeChecker::isHandledContainer(elem))
					Printer::print(elem, sep);
				else
					Printer::print(elem, "");
				my_stack.pop();
				if (!my_stack.empty())
					Printer::printSep(sep);
			}
			Printer::printContainerDelimiters(STACK, 1);
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
			Printer::printContainerDelimiters(QUEUE, 0);
			while (!my_queue.empty())
			{
				auto elem = my_queue.front();
				if (TypeChecker::isHandledContainer(elem))
					Printer::print(elem, sep);
				else
					Printer::print(elem, "");
				my_queue.pop();
				if (!my_queue.empty())
					Printer::printSep(sep);
			}
			Printer::printContainerDelimiters(QUEUE, 1);
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
			Printer::printContainerDelimiters(MAP, 0); // Print opening delimiter

			bool first = true;
			for (const auto &pair : my_map)
			{
				if (!first)
				{
					Printer::printSep(sep);
				}
				Printer::print(pair.first, "");
				Printer::print(": ", "");
				if (TypeChecker::isHandledContainer(pair.second))
				{
					Printer::print(pair.second, sep);
				}
				else
				{
					Printer::print(pair.second, "");
				}
				first = false;
			}

			Printer::printContainerDelimiters(MAP, 1); // Print closing delimiter
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
			Printer::printContainerDelimiters(UNORDERED_MAP, 0);

			bool first = true;
			for (const auto &pair : my_map)
			{
				if (!first)
				{
					Printer::printSep(sep);
				}
				Printer::print(pair.first, "");
				Printer::print(": ", "");
				if (TypeChecker::isHandledContainer(pair.second))
					Printer::print(pair.second, sep);
				else
					Printer::print(pair.second, "");
				first = false;
			}
			Printer::printContainerDelimiters(UNORDERED_MAP, 1);
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
			Printer::printContainerDelimiters(SET, 0);
			const auto end = my_set.end();
			for (auto it = my_set.begin(); it != my_set.end(); it++)
			{
				if (TypeChecker::isHandledContainer(*it))
					Printer::print(*it, sep);
				else
					Printer::print(*it, "");
				if (std::next(it) != end)
					Printer::printSep(sep);
			}
			Printer::printContainerDelimiters(SET, 1);
		}
		/**
		 * @brief Prints the contents of a custom object. Implementation of std::ostream operator<< overload is required as cout is called to output the object.
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
				std::cout << sep;
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
				std::cout << sep;
		}

		std::stringstream buffer;

	public:
		std::ofstream of;
		std::string getBufferStr() const
		{
			return buffer.str();
		}
		void emptyBuffer()
		{
			buffer.str("");
		}

		/**
		 * @brief Sets the file descriptor to redirect the `fout` stream to the specified file.
		 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
		 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
		 * @throws std::runtime_error if the file could not be opened.
		 */
		void setFile(const std::string &file, bool trunc = true)
		{
			if (trunc)
				of.open(file);
			else
				of.open(file, std::ios::app);

			if (!of.is_open())
			{
				throw(std::runtime_error("could not open file: " + file));
			}
		}

		bool fileSet() {
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
			Printer::print(first);
			if constexpr (sizeof...(args) > 0)
			{
				// Recursively call printAll with the remaining arguments.
				// This will print each element.
				printAll(args...);
			}
		}
	};
};


namespace Out {

	static Printer printer;
	
	/**
	 * @brief Sets the file in which the fout function will output.
	 * 
	 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
	 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
	 * @throws std::runtime_error if the file could not be opened.
	 */
	void setFoutFile(const std::string &file, bool trunc = true)
	{
		printer.setFile(file, trunc);
	}

	/**
	 * @brief Sets the file in which the fout function will output.
	 * 
	 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
	 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
	 * @throws std::runtime_error if the file could not be opened.
	 */
	void setFoutFile(const char *file, bool trunc = true)
	{
		printer.setFile(file, trunc);
	}

	/**
	 * @brief Outputs the given arguments to the standard output.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	void stdOut(const Args &...args)
	{
		printer.printAll(args...);
		std::cout << printer.getBufferStr() << std::endl;
		printer.emptyBuffer();
	}

	/**
	 * @brief Outputs the given arguments to standard error.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	void stdCerr(const Args &...args)
	{
		printer.printAll(args...);
		std::cerr << printer.getBufferStr() << std::endl;
		printer.emptyBuffer();
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
		printer.printAll(args...);
		if (!printer.fileSet())
			throw std::logic_error("Output file not defined");
		printer.of << printer.getBufferStr() << std::endl;
		printer.emptyBuffer();
	}
}

class Logger {
	private:
		enum logType {
			DEBUG,
        	INFO,
        	WARNING,
        	ERROR,
        	FATAL
		};
		static Printer printer;
		static std::ofstream of;
		static logType type;

		template<typename... Args>
		static void log(const Args &...args) {
			if(!of.is_open())
				throw std::logic_error("Output file not defined");
			of << "[" << type << "] ";;
			printer.printAll(args...);
			of << printer.getBufferStr() << std::endl;
		}

	public :
		static void setLoggerFile(const std::string file, const bool trunc) {
			if(trunc)
				of.open(file);
			else
				of.open(file, std::ios::app);
		};
		
		template<typename... Args>
		static void debug(const Args &...args) {
			type = DEBUG;
			log(args...);
		}
		template<typename... Args>
		static void info(const Args &...args) {
			type = INFO;
			log(args...);
		}
		template<typename... Args>
		static void warning(const Args &...args) {
			type = WARNING;
			log(args...);
		}
		template<typename... Args>
		static void error(const Args &...args) {
			type = ERROR;
			log(args...);
		}
		template<typename... Args>
		static void fatal(const Args &...args) {
			type = FATAL;
			log(args...);
		}
};

#endif
