#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../Printer/Printer.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace Printer;

enum logLevel
{
	_DEBUG,
	_INFO,
	_WARNING,
	_ERROR,
	_FATAL
};

class BaseLogger
{
private:
	static inline std::string outputType(logLevel method_level)
	{
		std::string ret;
		switch (method_level)
		{
		case _DEBUG:
			ret = "[DEBUG]";
			break;
		case _INFO:
			ret = "[INFO]";
			break;
		case _WARNING:
			ret = "[WARNING]";
			break;
		case _ERROR:
			ret = "[ERROR]";
			break;
		case _FATAL:
			ret = "[FATAL]";
			break;
		default:
			break;
		}
		return ret;
	}
	static inline std::string outputTime()
	{
		std::stringstream ss;
		auto now = std::chrono::system_clock::now();
		auto timeNow = std::chrono::system_clock::to_time_t(now);

		std::tm timeStruct = *std::localtime(&timeNow);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

		std::ostringstream time;
		time << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
		ss << "[" << time.str() << "." << std::setw(3) << std::setfill('0') << ms.count() << "]";
		return ss.str();
	}

public:
	static inline logLevel method_level;
	static inline logLevel level;
	static inline bool extraSpacing;

	template <typename... Args>
	static inline void log(const Args &...args)
	{
		if (method_level < level)
		{
			return;
		}
		Fout(outputTime() + outputType(method_level));
		Fout(args...);
		if (extraSpacing)
			Fout("");
	}
	static inline void setLoggerFile(const std::string file, const bool trunc)
	{
		if (trunc)
			setFout(file, true);
		else
			setFout(file, false);
	}
};

namespace Logger
{
	constexpr int DEBUG = logLevel::_DEBUG;
	constexpr int INFO = logLevel::_INFO;
	constexpr int WARNING = logLevel::_WARNING;
	constexpr int ERROR = logLevel::_ERROR;
	constexpr int FATAL = logLevel::_FATAL;

	inline void setExtraSpacing(const bool _value)
	{
		BaseLogger::extraSpacing = _value;
	}
	inline void setLogger(const std::string file, const int &intlevel, const bool trunc)
	{
		BaseLogger::method_level = _DEBUG;
		BaseLogger::level = _DEBUG;
		BaseLogger::extraSpacing = false;

		BaseLogger::setLoggerFile(file, trunc);
		logLevel level;
		switch (intlevel)
		{
		case DEBUG:
			level = _DEBUG;
			break;
		case INFO:
			level = _INFO;
			break;
		case WARNING:
			level = _WARNING;
			break;
		case ERROR:
			level = _ERROR;
			break;
		case FATAL:
			level = _FATAL;
			break;

		default:
			break;
		}
		BaseLogger::level = level;
	}
	template <typename... Args>
	inline void debug(const Args &...args)
	{
		BaseLogger::method_level = _DEBUG;
		BaseLogger::log(args...);
	}
	template <typename... Args>
	inline void info(const Args &...args)
	{
		BaseLogger::method_level = _INFO;
		BaseLogger::log(args...);
	}
	template <typename... Args>
	inline void warning(const Args &...args)
	{
		BaseLogger::method_level = _WARNING;
		BaseLogger::log(args...);
	}
	template <typename... Args>
	inline void error(const Args &...args)
	{
		BaseLogger::method_level = _ERROR;
		BaseLogger::log(args...);
	}
	template <typename... Args>
	inline void fatal(const Args &...args)
	{
		BaseLogger::method_level = _FATAL;
		BaseLogger::log(args...);
	}
}

#endif
