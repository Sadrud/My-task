#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>
#include <ctime>

/* названия уровненей важности сообщения (предпологалось, что программа будет использована для записи состояний в ходе выполнения процесса) */
enum class LogLevel {
	INFO, //полезная информация
	WARNING, //предупреждение
	ERROR //ошибка
};

/* класс для работы с файлом */
class Logger {
	private:
		std::ofstream logFile;
		LogLevel defaultLevel;
		std::mutex mtx;

		/* дает текущее время */
		std::string getCurrentTime();
		/* преобразует уровень сообщения в строку */ 
		std::string levelToString(LogLevel level);

	public:
		Logger(const std::string& filename, LogLevel defaultLevel);
		~Logger();

		/* запись сообщения в файл  */
		void logMessage(const std::string& message, LogLevel level);
		/* устанавливает уровень важности сообщенияч по умолчанию  */
		void setDefaultLevel(LogLevel level);

};


#endif
