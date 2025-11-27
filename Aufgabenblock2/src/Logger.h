/*
 * Logger.hpp
 *  Created on: 23 Oct 2025
 *      Author: sulta
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>

namespace Logger {

enum class Level {
	INFO, WARN, ERROR
};

//  interne Hilfsfunktionen
inline std::string getTimestamp() {
	auto now = std::chrono::system_clock::now();
	std::time_t t_c = std::chrono::system_clock::to_time_t(now);
	std::tm tm_buf;
#if defined(_WIN32)
	localtime_s(&tm_buf, &t_c);
#else
		localtime_r(&t_c, &tm_buf);
	#endif
	std::ostringstream oss;
	oss << std::put_time(&tm_buf, "%d:%m:%y %H:%M");
	return oss.str();
}

inline std::string levelToString(Level lvl) {
	switch (lvl) {
		case Level::INFO:
			return "INFO";
		case Level::WARN:
			return "WARN";
		case Level::ERROR:
			return "ERROR";
		default:
			return "UNKNOWN";
	}
}

inline std::string levelColor(Level lvl) {
	switch (lvl) {
		case Level::INFO:
			return "\033[0m";   // normal
		case Level::WARN:
			return "\033[33m";  // yellow
		case Level::ERROR:
			return "\033[31m";  // red
		default:
			return "\033[0m";
	}
}

//  zentrale Logfunktion
inline void log(Level lvl, const std::string &tag, const std::string &msg) {
	std::cout << levelColor(lvl) << "[" << getTimestamp() << "] " << "["
			<< levelToString(lvl) << "] " << "[" << tag << "]: " << msg
			<< "\033[0m" << std::endl;
}

inline void info(const std::string &tag, const std::string &msg) {
	log(Level::INFO, tag, msg);
}
inline void warn(const std::string &tag, const std::string &msg) {
	log(Level::WARN, tag, msg);
}
inline void error(const std::string &tag, const std::string &msg) {
	log(Level::ERROR, tag, msg);
}

//  hübscher Banner-Logger
inline void banner(const std::string &tag, const std::string &title, int width =
		60, char fill = '=') {
	std::ostringstream oss;

	int textLen = static_cast<int>(title.size()) + 2; // extra spaces
	if (textLen >= width) {
		oss << " " << title << " ";
	} else {
		int totalPadding = width - textLen;
		int leftPadding = totalPadding / 2;
		int rightPadding = totalPadding - leftPadding;

		oss << std::setfill(fill) << std::setw(leftPadding) << "" << " "
				<< title << " " << std::setfill(fill) << std::setw(rightPadding)
				<< "";
	}

	log(Level::INFO, tag, "\n" + oss.str() + "\n");
}

} // namespace Logger

#endif /* LOGGER_H_ */
