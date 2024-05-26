#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <filesystem>
#include "json.hpp"

class Logger {
public:
    enum LoggingType { DAILY, HOURLY, MINUTELY, SECONDLY };

    Logger(LoggingType type, int frequency, int maxFiles);

    void log(const std::string& message);

private:
    LoggingType loggingType;
    int frequency;
    int maxFiles;
    std::string currentLogFilePath;
    std::string logDirectory;

    std::string getCurrentTimestamp();
    std::string generateLogFileName();
    void rotateLogFiles();
};

#endif // LOGGER_H
