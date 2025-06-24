

#pragma once
#include <iostream>
#include <string>


enum class LogLevel { DEBUG, INFO, CREATED, ERROR };
void logMessage(LogLevel level, const char* format, ...);

#define NOTE_DEBUG(...) logMessage(LogLevel::DEBUG, __VA_ARGS__)
#define NOTE_INFO(...)  logMessage(LogLevel::INFO, __VA_ARGS__)
#define NOTE_ERROR(...) logMessage(LogLevel::ERROR, __VA_ARGS__)