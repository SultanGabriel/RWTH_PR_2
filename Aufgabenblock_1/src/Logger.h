/*
 * Logger.hpp
 *
 *  Created on: 23 Oct 2025
 *      Author: sulta
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>

class Logger {
public:
	enum class Level {
		INFO, WARN, ERROR
	};

private:
	static std::string getTimestamp() {
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

	static std::string levelToString(Level lvl) {
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

	static std::string levelColor(Level lvl) {
		switch (lvl) {
		case Level::INFO:
			return "\033[0m";      // normal
		case Level::WARN:
			return "\033[33m";     // yellow
		case Level::ERROR:
			return "\033[31m";     // red
		default:
			return "\033[0m";
		}
	}

public:
	static void log(Level lvl, const std::string &tag, const std::string &msg) {
		std::cout << levelColor(lvl) << "[" << getTimestamp() << "] " << "["
				<< levelToString(lvl) << "] " << "[" << tag << "]: " << msg
				<< "\033[0m" // reset color
				<< std::endl;
	}

	static void info(const std::string &tag, const std::string &msg) {
		log(Level::INFO, tag, msg);
	}

	static void warn(const std::string &tag, const std::string &msg) {
		log(Level::WARN, tag, msg);
	}

	static void error(const std::string &tag, const std::string &msg) {
		log(Level::ERROR, tag, msg);
	}

//	static void logExerciseTitle(const std::string &title,
//			int width = 60, char fill = ' ') {
//		std::ostringstream oss;
//
//		// Compute padding
//		int textLen = static_cast<int>(title.size()) + 2; // extra spaces around text
//		if (textLen >= width) {
//			oss << " " << title << " ";
//		} else {
//			int totalPadding = width - textLen;
//			int leftPadding = totalPadding / 2;
//			int rightPadding = totalPadding - leftPadding;
//
//			oss << std::setfill(fill) << std::setw(leftPadding) << "" << " "
//					<< title << " " << std::setfill(fill)
//					<< std::setw(rightPadding) << "";
//		}
//
//		// log
//		log(Level::INFO, tag, oss.str());
//	}
};

#endif /* LOGGER_H_ */
