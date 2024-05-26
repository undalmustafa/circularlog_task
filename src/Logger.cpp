#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

Logger::Logger(LoggingType type, int freq, int maxFiles)
        : loggingType(type), frequency(freq), maxFiles(maxFiles), logDirectory("./logs/")
{
    if (!std::filesystem::exists(logDirectory)) {
        std::filesystem::create_directory(logDirectory);
    }
    currentLogFilePath = generateLogFileName();
}

void Logger::log(const std::string& message) {
    std::cout << "Attempting to log to: " << currentLogFilePath << std::endl;

    std::ofstream logFile(currentLogFilePath, std::ios_base::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file: " << currentLogFilePath << std::endl;
        return;
    }

    logFile << getCurrentTimestamp() << " - " << message << std::endl;
    logFile.close();

    std::cout << "Log rotation check: " << std::endl;
    rotateLogFiles();
}


std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Logger::generateLogFileName() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* timeinfo = std::gmtime(&in_time_t); // Use UTC time

    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    switch (loggingType) {
        case DAILY:   oss << ".log"; break;
        case HOURLY:  oss << "_" << std::put_time(timeinfo, "%H") << ".log"; break;
        case MINUTELY:oss << "_" << std::put_time(timeinfo, "%H-%M") << ".log"; break;
        case SECONDLY:oss << "_" << std::put_time(timeinfo, "%H-%M-%S") << ".log"; break;
    }
    return logDirectory + oss.str();
}

void Logger::rotateLogFiles() {
    std::vector<std::filesystem::path> logFiles;
    for (const auto& entry : std::filesystem::directory_iterator(logDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".log") {
            logFiles.push_back(entry.path());
        }
    }

    std::sort(logFiles.begin(), logFiles.end(),
              [](const auto& a, const auto& b) {
                  return std::filesystem::last_write_time(a) < std::filesystem::last_write_time(b);
              });

    while (logFiles.size() > maxFiles) {
        std::filesystem::remove(logFiles.front());
        logFiles.erase(logFiles.begin());
    }
}
