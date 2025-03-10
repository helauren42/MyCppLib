#ifndef WPRINTER_HPP
#define WPRINTER_HPP

#include "../Utils/Utils.hpp"
#include "../Strings/Strings.hpp"

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

#include <cwchar>
#include <locale>
#include <codecvt>

#include <unistd.h>
#include <fcntl.h>
#include <cstring>

class WBasePrinter
{

public:
	WBasePrinter()
	{
	}
	~WBasePrinter()
	{
	}

	enum OutputDest
	{
		STDOUT,
		STDERR,
		FOUT
	};

	static void flushBuffer()
	{
		wbuffer << std::endl;
		const std::wstring content = wbuffer.str();
		switch (dest)
		{
		case STDOUT:
			// std::cout << "ready to out:" << std::endl;
			std::wcout << wbuffer.str();
			break;
		case STDERR:
			std::wcerr << wbuffer.str();
			break;
		case FOUT:
			wprintToFile();
			break;
		default:
			break;
		}
		wbuffer = std::wstringstream();
	}

	static void setOutputDest(OutputDest _dest)
	{
		dest = _dest;
	}

	/**
	 * @brief Sets the file descriptor to redirect the `Fout` stream to the specified file.
	 * @param _file The name of the file to open. Creates the file if it does not exist and opens it.
	 * @param _trunc Defines the open mode truncate if true, append in false, it defaults to true.
	 * @throws std::runtime_error if the file could not be opened.
	 */
	static void setFile(const std::string &_file, const bool _trunc = true)
	{
		file = _file.c_str();
		if (_trunc)
		{
			std::wofstream wof(file, std::ios::out | std::ios::trunc);
			wof.close();
		}
	}
	
	static bool fileSet()
	{
		return file.empty() == false;
	}
	/**
	 * @brief Prints multiple elements to the output stream.
	 * @param first The first element to print.
	 * @param args The remaining elements to print.
	 */
	template <typename T, typename... Args>
	static void printAll(const T &first, const Args &...args)
	{
		WBasePrinter::print(first);
		if constexpr (sizeof...(args) > 0)
		{
			// Recursively call printAll with the remaining arguments.
			// This will print each element.
			printAll(args...);
		}
	}

private:
	static inline std::wstringstream wbuffer;
	static inline OutputDest dest;
	static inline std::string file;

	/**
	 * @brief Prints the given separator string to the output stream.
	 * @param sep The separator string to print.
	 */
	static void printSep(const std::wstring &sep)
	{
		wbuffer << sep;
	}

	/**
	 * @brief Prints the given container to the output stream with the given separator string.
	 * @param container The container to print.
	 * @param sep The separator string to print between elements.
	 */
	template <typename T>
	static void printBeginEnd(const T &container, const std::wstring &sep)
	{
		const auto end = container.end();

		std::wstring new_sep = sep;

		for (auto it = container.begin(); it != container.end(); it++)
		{
			if (std::next(it) == end && !TypeChecker::isHandledContainer(*it))
			{
				WBasePrinter::print(*it, L"");
			}
			else
			{
				WBasePrinter::print(*it, sep);
			}

			// to output the separator in case of nested containers
			if (TypeChecker::isHandledContainer(*it) && std::next(it) != end)
			{
				wbuffer << ", ";
			}
		}
	}

	/**
	 * @brief Prints the opening or closing delimiter of a container.
	 * @param type The type of container to print the delimiter for.
	 * @param side Whether to print the opening (0) or closing (1) delimiter.
	 */
	static void printContainerDelimiters(const int &type, const bool side)
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
			wbuffer << delimiter[0];
		}
		else
		{
			wbuffer << delimiter[1];
		}
	}

	/**
	 * @brief Prints a wide-character string (wchar_t*) to the output stream.
	 * @param a The wide-character string to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const wchar_t *a, const std::wstring &sep = L"")
	{
		wbuffer << a;
		wbuffer << sep;
	}

	/**
	 * @brief Prints a single wide character (wchar_t) to the output stream.
	 * @param a The wide character to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const wchar_t a, const std::wstring &sep = L"")
	{
		wbuffer << a;
		wbuffer << sep;
	}

	/**
	 * @brief Prints a string to the output stream.
	 * @param a The string to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const std::wstring &a, const std::wstring &sep = L"")
	{
		wbuffer << a.c_str();
		wbuffer << sep;
	}

	/**
	 * @brief Prints a string to the output stream.
	 * @param a The string to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const std::wstringstream &a, const std::wstring &sep = L"")
	{
		wbuffer << a.str().c_str();
		wbuffer << sep;
	}
	/**
	 * @brief Prints a string to the output stream.
	 * @param a The string to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const std::wostringstream &a, const std::wstring &sep = L"")
	{
		wbuffer << a.rdbuf();
		wbuffer << sep;
	}
	/**
	 * @brief Prints a single character to the output stream.
	 * @param a The character to print.
	 * @param sep The separator string to print after the character.
	 */
	static void print(const char a, const std::wstring &sep = L"")
	{
		wbuffer << a;
		wbuffer << sep;
	}

	/**
	 * @brief Prints a c-string to the output stream.
	 * @param s The string to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const char *s, const std::wstring &sep = L"")
	{
		wbuffer << s;
		wbuffer << sep;
	}

	/**
	 * @brief Prints a string to the output stream.
	 * @param a The string to print.
	 * @param sep The separator string to print after the string.
	 */
	static void print(const std::string &a, const std::wstring &sep = L"")
	{
		wbuffer << a.c_str();
		wbuffer << sep;
	}

	/**
	 * @brief Prints an integer to the output stream.
	 * @param a The integer to print.
	 * @param sep The separator string to print after the integer.
	 */
	static void print(const int &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}
	/**
	 * @brief Prints a double to the output stream.
	 * @param a The double to print.
	 * @param sep The separator string to print after the double.
	 */
	static void print(const double &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}
	/**
	 * @brief Prints a boolean value to the output stream.
	 * @param a The boolean value to print.
	 * @param sep The separator string to print after the boolean value.
	 */
	static void print(const bool &a, const std::wstring &sep = L"")
	{
		if (a == true)
			wbuffer << "true";
		else
			wbuffer << "false";
		wbuffer << sep;
	}

	/**
	 * @brief Prints a float to the output stream.
	 * @param a The float to print.
	 * @param sep The separator string to print after the float.
	 */
	static void print(const float &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}
	/**
	 * @brief Prints a long integer to the output stream.
	 * @param a The long integer to print.
	 * @param sep The separator string to print after the long integer.
	 */
	static void print(const long &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}
	/**
	 * @brief Prints a long long integer to the output stream.
	 * @param a The long long integer to print.
	 * @param sep The separator string to print after the long long integer.
	 */
	static void print(const long long &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}

	/**
	 * @brief Prints a short integer to the output stream.
	 * @param a The unsigned short integer to print.
	 * @param sep The separator string to print after the unsigned short integer.
	 */
	static void print(const short &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}

	/**
	 * @brief Prints an unsigned integer to the output stream.
	 * @param a The unsigned integer to print.
	 * @param sep The separator string to print after the unsigned integer.
	 */
	static void print(const unsigned int &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}

	/**
	 * @brief Prints an unsigned long integer to the output stream.
	 * @param a The unsigned long integer to print.
	 * @param sep The separator string to print after the unsigned long integer.
	 */
	static void print(const unsigned long &a, const std::wstring &sep = L"")
	{
		std::wstringstream wss;
		wss << a;
		std::wstring s = wss.str();
		wbuffer << s;
		wbuffer << sep;
	}

	/**
	 * @brief Prints the contents of a std::vector.
	 *
	 * @param vec The vector to print.
	 * @param sep The separator to use between elements (default is ", ").
	 */
	template <class T>
	static void print(const std::vector<T> &vec, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(VECTOR, 0);
		WBasePrinter::printBeginEnd(vec, sep);
		WBasePrinter::printContainerDelimiters(VECTOR, 1);
	}
	/**
	 * @brief Prints the contents of a std::list.
	 *
	 * @param my_list The list to print.
	 * @param sep The separator to use between elements (default is ", ").
	 */
	template <class T>
	static void print(const std::list<T> &my_list, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(LIST, 0);
		WBasePrinter::printBeginEnd(my_list, sep);
		WBasePrinter::printContainerDelimiters(LIST, 1);
	}

	/**
	 * @brief Prints the contents of a std::forward_list.
	 *
	 * @param my_list The forward_list to print.
	 * @param sep The separator to use between elements (default is ", ").
	 */
	template <class T>
	static void print(const std::forward_list<T> &my_list, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(FORWARD_LIST, 0);
		WBasePrinter::printBeginEnd(my_list, sep);
		WBasePrinter::printContainerDelimiters(FORWARD_LIST, 1);
	}
	/**
	 * @brief Prints the contents of a std::deque.
	 *
	 * @param my_deque The deque to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 */
	template <class T>
	static void print(const std::deque<T> &my_deque, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(DEQUE, 0);
		WBasePrinter::printBeginEnd(my_deque, sep);
		WBasePrinter::printContainerDelimiters(DEQUE, 1);
	}

	/**
	 * @brief Prints the contents of a std::stack, first element is the top
	 *
	 * @param my_stack The stack to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 */
	template <class T>
	static void print(std::stack<T> my_stack, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(STACK, 0);
		while (!my_stack.empty())
		{
			auto elem = my_stack.top();
			if (TypeChecker::isHandledContainer(elem))
				WBasePrinter::print(elem, sep);
			else
				WBasePrinter::print(elem, "");
			my_stack.pop();
			if (!my_stack.empty())
				WBasePrinter::printSep(sep);
		}
		WBasePrinter::printContainerDelimiters(STACK, 1);
	}

	/**
	 * @brief Prints the contents of a std::queue, first element is the front.
	 *
	 * @param my_queue The queue to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 */
	template <class T>
	static void print(std::queue<T> my_queue, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(QUEUE, 0);
		while (!my_queue.empty())
		{
			auto elem = my_queue.front();
			if (TypeChecker::isHandledContainer(elem))
				WBasePrinter::print(elem, sep);
			else
				WBasePrinter::print(elem, "");
			my_queue.pop();
			if (!my_queue.empty())
				WBasePrinter::printSep(sep);
		}
		WBasePrinter::printContainerDelimiters(QUEUE, 1);
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
	static void print(const std::map<K, V> &my_map, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(MAP, 0); // Print opening delimiter

		bool first = true;
		for (const auto &pair : my_map)
		{
			if (!first)
			{
				WBasePrinter::printSep(sep);
			}
			WBasePrinter::print(pair.first, L"");
			WBasePrinter::print(L": ", L"");
			if (TypeChecker::isHandledContainer(pair.second))
			{
				WBasePrinter::print(pair.second, sep);
			}
			else
			{
				WBasePrinter::print(pair.second, L"");
			}
			first = false;
		}

		WBasePrinter::printContainerDelimiters(MAP, 1); // Print closing delimiter
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
	static void print(const std::unordered_map<T, V> &my_map, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(UNORDERED_MAP, 0);

		bool first = true;
		for (const auto &pair : my_map)
		{
			if (!first)
			{
				WBasePrinter::printSep(sep);
			}
			WBasePrinter::print(pair.first, "");
			WBasePrinter::print(L": ", L"");
			if (TypeChecker::isHandledContainer(pair.second))
				WBasePrinter::print(pair.second, sep);
			else
				WBasePrinter::print(pair.second, "");
			first = false;
		}
		WBasePrinter::printContainerDelimiters(UNORDERED_MAP, 1);
	}

	/**
	 * @brief Prints the contents of a std::set.
	 *
	 * @param my_set The set to print.
	 * @param sep Determines the print format:
	 *             - uses ", " as separator between elements by default.
	 */
	template <class T>
	static void print(const std::set<T> &my_set, const std::wstring &sep = L", ")
	{
		WBasePrinter::printContainerDelimiters(SET, 0);
		const auto end = my_set.end();
		for (auto it = my_set.begin(); it != my_set.end(); it++)
		{
			if (TypeChecker::isHandledContainer(*it))
				WBasePrinter::print(*it, sep);
			else
				WBasePrinter::print(*it, "");
			if (std::next(it) != end)
				WBasePrinter::printSep(sep);
		}
		WBasePrinter::printContainerDelimiters(SET, 1);
	}
	/**
	 * @brief Prints the contents of a custom object. Implementation of std::ostream operator<< overload is required.
	 *
	 * @param object The object to print.
	 * @param sep changing this parameter has no effect
	 */
	template <class T>
	static void print(const T &object, const std::wstring &sep = L"",
					  typename std::enable_if<std::is_class<T>::value>::type * = nullptr)
	{
		std::wstringstream ss;
		ss << object;
		std::wstring s = ss.str();
		wbuffer << s;
		if (!sep.empty())
			wbuffer << sep;
	}

	template <class T>
	static void print(const T *object, const std::wstring &sep = L"",
					  typename std::enable_if<std::is_class<T>::value>::type * = nullptr)
	{
		std::wstringstream ss;
		ss << object;
		std::wstring s = ss.str();
		wbuffer << s;
		if (!sep.empty())
			wbuffer << sep;
	}
	static void wprintToFile()
	{
		std::wofstream wof;

		wof.open(file, std::ios::out | std::ios::app);

		if (!wof.is_open())
			throw(std::runtime_error("Could not open file: "));
		wof << wbuffer.str();
		wof.flush();
		wof.close();
	}
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
};

namespace WPrinter
{
	static WBasePrinter base;
	/**
	 * @brief Sets the file in which the Fout function will output.
	 *
	 * @param file The name of the file to open. Creates the file if it does not exist and opens it.
	 * @param trunc Defines the open mode truncate if true, append in false, it defaults to true.
	 * @throws std::runtime_error if the file could not be opened.
	 */
	static inline void setFout(const std::string file, bool trunc = true)
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
	static inline void stdOut(const Args &...args)
	{
		base.setOutputDest(WBasePrinter::STDOUT);
		base.printAll(args...);
		base.flushBuffer();
	}

	/**
	 * @brief Outputs the given scalar type and container arguments to the standard output.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	static inline void stdErr(const Args &...args)
	{
		base.setOutputDest(WBasePrinter::STDERR);
		base.printAll(args...);
		base.flushBuffer();
	}

	/**
	 * @brief Outputs the given arguments to the file descriptor specified by Fout_fd.
	 *
	 * This function sets the file descriptor to Fout_fd and calls the WBasePrinter::printAll
	 * function to output scalar types and container arguments.
	 *
	 * @tparam Args Variadic template parameter pack representing the types of the arguments.
	 * @param args The arguments to be printed.
	 */
	template <typename... Args>
	static inline void Fout(const Args &...args)
	{
		base.setOutputDest(WBasePrinter::FOUT);
		if (!base.fileSet())
			throw std::logic_error("Output file not defined");
		base.printAll(args...);
		base.flushBuffer();
	}
}

#endif
