#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../Printer/Printer.hpp"
#include "../WPrinter/WPrinter.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

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
	static inline bool stdout;

	template <typename... Args>
	static inline void log(const Args &...args)
	{
		if (method_level < level)
		{
			return;
		}
		std::string bar = outputTime() + outputType(method_level);
		if(stdout) {
			Printer::stdOut(bar);
			Printer::stdOut(args...);
		}
		Printer::Fout(bar);
		Printer::Fout(args...);
		if(extraSpacing)
			Printer::Fout("");
	}
    template <typename... Args>
	static inline void wlog(const Args &...args)
	{
		if (method_level < level)
		{
			return;
		}
		std::string bar = outputTime() + outputType(method_level);
        // Printer::stdOut("stdout: ", stdout);
		if(stdout) {
			WPrinter::stdOut(bar);
			WPrinter::stdOut(args...);
		}
		WPrinter::Fout(bar);
		WPrinter::Fout(args...);
		if(extraSpacing)
			WPrinter::Fout("");
	}
	static inline void setLoggerFile(const std::string file, const bool trunc)
	{
		if (trunc) {
			Printer::setFout(file, true);
			WPrinter::setFout(file, true);
        }
		else {
			Printer::setFout(file, false);
			WPrinter::setFout(file, false);
        }
	}
};

namespace Logger
{
    constexpr int DEBUG = logLevel::_DEBUG;
    constexpr int INFO = logLevel::_INFO;
    constexpr int WARNING = logLevel::_WARNING;
    constexpr int ERROR = logLevel::_ERROR;
    constexpr int FATAL = logLevel::_FATAL;

    /**
     * @brief Sets whether extra spacing should be added between log messages.
     * @param _value A boolean value (`true` to enable extra spacing, `false` to disable it).
     */
    inline void setExtraSpacing(const bool _value)
    {
        BaseLogger::extraSpacing = _value;
    }

    /**
     * @brief Configures the logger with the output file, log level, file truncation mode, and stdout redirection.
     * @param file The name of the file to which logs will be written.
     * @param intlevel The log level (e.g., `DEBUG`, `INFO`, `WARNING`, etc.). Defaults to `DEBUG`.
     * @param trunc A boolean value (`true` to truncate the file, `false` to append to it). Defaults to `true`.
     * @param _stdout A boolean value (`true` to enable stdout redirection, `false` to disable it). Defaults to `false`.
     */
    inline void setLogger(const std::string file, const int &intlevel = DEBUG, const bool trunc = true, const bool _stdout = false)
    {
        BaseLogger::method_level = _DEBUG;
        BaseLogger::level = _DEBUG;
        BaseLogger::extraSpacing = false;
        BaseLogger::stdout = false;

        BaseLogger::setLoggerFile(file, trunc);
        logLevel _level;
        switch (intlevel)
        {
        case DEBUG:
            _level = _DEBUG;
            break;
        case INFO:
            _level = _INFO;
            break;
        case WARNING:
            _level = _WARNING;
            break;
        case ERROR:
            _level = _ERROR;
            break;
        case FATAL:
            _level = _FATAL;
            break;
        default:
            break;
        }
        BaseLogger::level = _level;
        BaseLogger::stdout = _stdout;
    }

    /**
     * @brief Logs a message at the DEBUG level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void debug(const Args &...args)
    {
        BaseLogger::method_level = _DEBUG;
        BaseLogger::log(args...);
    }

    /**
     * @brief Logs a message at the INFO level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void info(const Args &...args)
    {
        BaseLogger::method_level = _INFO;
        BaseLogger::log(args...);
    }

    /**
     * @brief Logs a message at the WARNING level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void warning(const Args &...args)
    {
        BaseLogger::method_level = _WARNING;
        BaseLogger::log(args...);
    }

    /**
     * @brief Logs a message at the ERROR level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void error(const Args &...args)
    {
        BaseLogger::method_level = _ERROR;
        BaseLogger::log(args...);
    }

    /**
     * @brief Logs a message at the FATAL level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void fatal(const Args &...args)
    {
        BaseLogger::method_level = _FATAL;
        BaseLogger::log(args...);
    }
    
    /**
     * @brief Logs a message at the DEBUG level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void wdebug(const Args &...args)
    {
        BaseLogger::method_level = _DEBUG;
        BaseLogger::wlog(args...);
    }

    /**
     * @brief Logs a message at the INFO level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void winfo(const Args &...args)
    {
        BaseLogger::method_level = _INFO;
        BaseLogger::wlog(args...);
    }

    /**
     * @brief Logs a message at the WARNING level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void wwarning(const Args &...args)
    {
        BaseLogger::method_level = _WARNING;
        BaseLogger::wlog(args...);
    }

    /**
     * @brief Logs a message at the ERROR level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void werror(const Args &...args)
    {
        BaseLogger::method_level = _ERROR;
        BaseLogger::wlog(args...);
    }

    /**
     * @brief Logs a message at the FATAL level.
     * @param args... Variadic arguments representing the message to log.
     */
    template <typename... Args>
    inline void wfatal(const Args &...args)
    {
        BaseLogger::method_level = _FATAL;
        BaseLogger::wlog(args...);
    }
}
#endif
