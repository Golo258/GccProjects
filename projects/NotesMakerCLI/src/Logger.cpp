#include "Logger.hpp"
#include <iostream>
#include <cstdarg>
#include <cstdio>

void logMessage(LogLevel level, const char* format, ...) {
    constexpr int BUF_SIZE = 1024;
    char buffer[BUF_SIZE];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUF_SIZE, format, args);
    va_end(args);

    std::string prefix;
    std::string color;

    switch (level) {
        case LogLevel::DEBUG:
            prefix = "[DEBUG]";
            color = "\033[36m"; break; // Cyan
        case LogLevel::INFO:
            prefix = "[INFO]";
            color = "\033[32m"; break; // Green
        case LogLevel::ERROR:
            prefix = "[ERROR]";
            color = "\033[31m"; break; // Red
    }

    std::cout << color << prefix << " " << buffer << "\033[0m" << std::endl;
}

