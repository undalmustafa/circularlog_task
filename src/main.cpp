#include "Logger.h"

int main() {
    try {
        json config = json::parse(std::ifstream("C:\\Users\\undal\\CLionProjects\\CircularLogTask\\src\\config.json"));

        Logger::LoggingType loggingType;
        if (config["logging_type"] == "DAILY") loggingType = Logger::DAILY;
        if (config["logging_type"] == "HOURLY") loggingType = Logger::HOURLY;
        if (config["logging_type"] == "MINUTELY") loggingType = Logger::MINUTELY;
        if (config["logging_type"] == "SECONDLY") loggingType = Logger::SECONDLY;

        Logger logger(loggingType, config["frequency"], config["max_files"]);
        logger.log("This is a log message.");
        logger.log("This is another log message to trigger rotation.");
    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing config.json: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
