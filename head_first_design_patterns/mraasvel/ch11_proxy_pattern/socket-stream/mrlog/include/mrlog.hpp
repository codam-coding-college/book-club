#ifndef MRLOG_HPP
#define MRLOG_HPP

#include <iostream>
#include <fstream>

namespace mrlog {

enum class LogLevel : uint16_t {
	OFF,
	FATAL,
	ERROR,
	WARN,
	INFO,
	DEBUG
};

namespace Detail {
	const char* parseFormat(const char* format);

	template <typename OutStream>
	void processFormat(OutStream& out, const char* format) {
		out << format;
	}

	template<typename OutStream, typename T, typename... Args>
	void processFormat(OutStream& out, const char* format, const T& value, Args&&...args) {
		while (*format != '\0') {
			if (*format == '{') {
				format = parseFormat(format);
				out << value;
				processFormat(out, format + 1, std::forward<Args>(args)...);
				return;
			} else {
				out << *format++;
			}
		}
	}
}

template <typename...Args>
void cout(const char* format, Args&&...args) {
	Detail::processFormat(std::cout, format, std::forward<Args>(args)...);
}

template <typename...Args>
void cerr(const char* format, Args&&...args) {
	Detail::processFormat(std::cerr, format, std::forward<Args>(args)...);
}

namespace Detail {
	extern std::string logfile;
	template <typename OutStream>
	void printLevel(OutStream& out, LogLevel level) {
		static const std::string levels[] = {
			"OFF",
			"fatal",
			"error",
			"warn",
			"info",
			"debug"
		};

		if (level != LogLevel::OFF) {
			out << "[" << levels[static_cast<uint16_t>(level)] << "] ";
		}
	}

	template <typename... Args>
	void log(LogLevel level, const char* format, Args&&...args) {
		printLevel(std::clog, level);
		processFormat(std::clog, format, std::forward<Args>(args)...);
		std::clog << '\n';
	}
}

void clearLog();
void setLogFile(std::string&& file);
void resetLogFile();

template <typename... Args>
void log(const char* format, Args&&...args) {
	Detail::log(LogLevel::OFF, format, std::forward<Args>(args)...);
}

template <typename... Args>
void fatal(const char* format, Args&&...args) {
	Detail::log(LogLevel::FATAL, format, std::forward<Args>(args)...);
}

template <typename... Args>
void error(const char* format, Args&&...args) {
	Detail::log(LogLevel::ERROR, format, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const char* format, Args&&...args) {
	Detail::log(LogLevel::WARN, format, std::forward<Args>(args)...);
}

template <typename... Args>
void info(const char* format, Args&&...args) {
	Detail::log(LogLevel::INFO, format, std::forward<Args>(args)...);
}

template <typename... Args>
void debug(const char* format, Args&&...args) {
	Detail::log(LogLevel::DEBUG, format, std::forward<Args>(args)...);
}

};

#endif /* MRLOG_HPP */
