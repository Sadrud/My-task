#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "Logger.h"
#include <iostream>
#include <iomanip>

/* конструктор: открывает файл и выбрасывает исключение в случае неуспешного открытия */
Logger::Logger(const std::string& filename, LogLevel defaultLevel) : defaultLevel(defaultLevel) {
		logFile.open(filename, std::ios::app);
		if (!logFile) {
			throw std::runtime_error("Failed to open log file");
		}
	}

/* деструктор: закрывает файл, открывыемый в конструкторе */
Logger::~Logger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}

/* записывает сообщение в файл */
void Logger::logMessage(const std::string& message, LogLevel level) {
	std::lock_guard<std::mutex> lock(mtx); //потокобезопасность через mutex
	if (level >= defaultLevel) { //записывает только сообщения, чей уровень важности выше допустимого уровня (в Makefile можно поменять допустимый уровень)
		logFile << getCurrentTime() << " [" << levelToString(level) << "] " << message << std::endl;
	}
}

/* позволяет установить уровень важности сообщения по умолчанию */
void Logger::setDefaultLevel(LogLevel level) {
	std::lock_guard<std::mutex> lock(mtx); //обеспечиваем потокобезопасность через mutex
	defaultLevel = level;
}

/* позволяет установить текущее время дату */
std::string Logger::getCurrentTime() {
	auto now = std::time(nullptr); //получаем время
	std::tm tm;
	localtime_r(&now, &tm); //преобразуем в локальное
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); //преобразуем в строку
	return oss.str();
}

/* преобразует уровень сообщения в строку */
std::string Logger::levelToString(LogLevel level) {
	switch (level) {
		case LogLevel::INFO: return "INFO";
		case LogLevel::WARNING: return "WARNING";
		case LogLevel::ERROR: return "ERROR";
		default: return "UNKNOWN";
	}
}

#endif
