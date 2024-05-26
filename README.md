# Circular Logger for C++

A robust and customizable circular logging library for C++. This logger writes log messages to separate files for each day (or other time intervals), keeping a limited number of log files and automatically deleting the oldest ones when the limit is reached.

## Installation

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/undalmustafa/circular_logger
    ```

2.  **Include Header:**
    Copy `logger.h` to your project's directory and include it in your source files:

    ```c++
    #include "logger.h"
    ```


## Usage

1.  **Create a Logger:**
    Create a `Logger` object with the desired settings:

    ```c++
    Logger logger; // Use default settings: daily logging, 1 file per day, 7 days max, ./logs/ directory
    
    // or customize the settings:
    std::string logDir = "/path/to/your/logs/";  // Custom directory
    ```

You can easily customize the behavior of the Circular Logger by modifying the `config.json` file:


```json
{
        "logging_type": "DAILY",  // Options: "DAILY", "HOURLY", "MINUTELY", "SECONDLY"
        "frequency": 1,           // Number of days/hours/minutes/seconds between log file creation
        "max_files": 7,           // Maximum number of log files to keep
}
```

2.  **Log Messages:**
    Use the `log()` function to write messages to the log file:

    ```c++
    logger.log("This is a log message.");
    ```

