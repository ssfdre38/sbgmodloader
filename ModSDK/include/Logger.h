#pragma once
#include <string>
#include <fstream>
#include <ctime>

namespace ModSDK {

/// Simple logger for mod development
class Logger {
public:
    static void Info(const char* format, ...);
    static void Warn(const char* format, ...);
    static void Error(const char* format, ...);
    static void Debug(const char* format, ...);
    
private:
    static const char* LogFile();
    static std::string GetTimestamp();
};

#define LOG_INFO(fmt, ...) Logger::Info(fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...) Logger::Warn(fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) Logger::Error(fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) Logger::Debug(fmt, __VA_ARGS__)

}  // namespace ModSDK
