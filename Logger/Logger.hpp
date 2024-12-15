#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../Printer/Printer.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>


#ifndef STRINGS_HPP
#define STRINGS_HPP

template<template<typename T> class Container>
Container<std::string> split(const std::string& str, const std::string& delimiter = "\n") {
	Container<std::string> container;

	size_t start = 0;
	size_t end = 0;

	while(true) {
		if((start = str.find_first_not_of(delimiter, start)) == std::string::npos)
			break;
		end = str.find_first_of(delimiter, start);
		if(end == std::string::npos)
			end = str.length();
		container.push_back(str.substr(start, end - start));
		start = end+1;
	}
	return(container);
}

#endif

namespace
{
	enum logType
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL
	};
}

namespace
{
	class Logging
	{
	private:
		static void outputType(logType type)
		{
			switch (type)
			{
			case DEBUG:
				of << "[DEBUG] ";
				break;
			case INFO:
				of << "[INFO] ";
				break;
			case WARNING:
				of << "[WARNING] ";
				break;
			case ERROR:
				of << "[ERROR] ";
				break;
			case FATAL:
				of << "[FATAL] ";
				break;

			default:
				break;
			}
		}
		static void outputTime() {
			auto now = std::chrono::system_clock::now();
			auto timeNow = std::chrono::system_clock::to_time_t(now);

			std::tm timeStruct = *std::localtime(&timeNow);
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

			of << "[" << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S") << "."
				<< std::setw(3) << std::setfill('0') << ms.count() << "]" << "\n";
		}

	public:

		static Printer printer;
		static logType type;
		static bool extraSpacing;

		template <typename... Args>
		static void log(const Args &...args)
		{
			if (!of.is_open())
				throw std::logic_error("Output file not defined");
			outputTime();
			outputType(type);
			printer.printAll(args...);
			of << printer.getBufferStr() << std::endl;
			if(extraSpacing)
				of << std::endl;
			printer.emptyBuffer();
		}

		static void setLoggerFile(const std::string file, const bool trunc)
		{
			if (trunc)
				of.open(file);
			else
				of.open(file, std::ios::app);
		}
	};
}

namespace {
	inline Printer Logging::printer;
	inline logType Logging::type;
	bool Logging::extraSpacing = true;
	inline std::mutex mtx;
}

namespace Logger
{
	inline void setExtraSpacing(const bool _value) {
		Logging::extraSpacing = _value;
	}

	inline void setLoggerFile(const std::string file, const bool trunc) {
		Logging::setLoggerFile(file, trunc);
	}
	template <typename... Args>
	inline void debug(const Args &...args)
	{
		std::unique_lock<std::mutex> lock(mtx);
		Logging::type = DEBUG;
		Logging::log(args...);
	}
	template <typename... Args>
	inline void info(const Args &...args)
	{
		std::unique_lock<std::mutex> lock(mtx);
		Logging::type = INFO;
		Logging::log(args...);
	}
	template <typename... Args>
	inline void warning(const Args &...args)
	{
		std::unique_lock<std::mutex> lock(mtx);
		Logging::type = WARNING;
		Logging::log(args...);
	}
	template <typename... Args>
	inline void error(const Args &...args)
	{
		std::unique_lock<std::mutex> lock(mtx);
		Logging::type = ERROR;
		Logging::log(args...);
	}
	template <typename... Args>
	inline void fatal(const Args &...args)
	{
		std::unique_lock<std::mutex> lock(mtx);
		Logging::type = FATAL;
		Logging::log(args...);
	}
}

#endif