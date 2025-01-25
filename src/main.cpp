#include "Logger.h"
#include <thread>
#include <iostream>

void logWorker(Logger& logger, const std::string& message, LogLevel level) {
	logger.logMessage(message, level);
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <log_file> <default_log_level>\n";
		return 1;
	}

	std::string logFile = argv[1]; //принимает при запуске программы название файла
	LogLevel defaultLevel;

	std::string levelStr = argv[2]; //принимает название уровня важности сообщения, которое будет допустимым и по умолчанию
	if (levelStr == "INFO") {
		defaultLevel = LogLevel::INFO;
	} else if (levelStr == "WARNING") {
		defaultLevel = LogLevel::WARNING;
	} else if (levelStr == "ERROR") {
		defaultLevel = LogLevel::ERROR;
	} else {
		std::cerr << "Invalid log level. Use INFO, WARNING, or ERROR.\n";
		return 1;
	}

	try {
		//создаем объект
		Logger logger(logFile, defaultLevel);

		//вечно получаем сообщения, пока не получит сообщение "END", которое завершает выполнение программы
		while (true) {
			std::string message;
			std::string inputLevel;

			std::cout << "Enter message: ";
			std::getline(std::cin, message);

			if (message == "END")
				break;

			std::cout << "Enter log level (INFO, WARNING, ERROR): ";
			std::getline(std::cin, inputLevel);

			LogLevel level = defaultLevel;
			if (inputLevel == "INFO") {
				level = LogLevel::INFO;
			} else if (inputLevel == "WARNING") {
				level = LogLevel::WARNING;
			} else if (inputLevel == "ERROR") {
				level = LogLevel::ERROR;
			}

			std::thread t(logWorker, std::ref(logger), message, level);
			t.detach();
		}
	} catch (const std::invalid_argument& e) {
		std::cerr << "Invalid input! Please enter a valid number." << std::endl;
	} catch (const std::out_of_range& e) {
		std::cerr << "The number is out of range for an int." << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

