#include "../Printer/Printer.hpp"

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

	public:

		static Printer printer;
		static std::ofstream of;
		static logType type;
		template <typename... Args>
		static void log(const Args &...args)
		{
			if (!of.is_open())
				throw std::logic_error("Output file not defined");
			outputType(type);
			printer.printAll(args...);
			of << printer.getBufferStr() << std::endl;
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
	Printer Logging::printer;
	std::ofstream Logging::of;
	logType Logging::type;
}

namespace Logger
{
	Logging logging;
	static void setLoggerFile(const std::string file, const bool trunc) {
		logging.setLoggerFile(file, trunc);
	}
	template <typename... Args>
	static void debug(const Args &...args)
	{
		logging.type = DEBUG;
		logging.log(args...);
	}
	template <typename... Args>
	static void info(const Args &...args)
	{
		logging.type = INFO;
		logging.log(args...);
	}
	template <typename... Args>
	static void warning(const Args &...args)
	{
		logging.type = WARNING;
		logging.log(args...);
	}
	template <typename... Args>
	static void error(const Args &...args)
	{
		logging.type = ERROR;
		logging.log(args...);
	}
	template <typename... Args>
	static void fatal(const Args &...args)
	{
		logging.type = FATAL;
		logging.log(args...);
	}
}
