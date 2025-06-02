#include "logger.h"
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <filesystem>
#include <iostream>

using namespace std::filesystem;

Logger::Logger() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    std::strftime(buf, sizeof(buf), "log/app_%Y%m%d_%H%M%S.log", &tm);
    logFile.open(buf, std::ios::out);
    if (logFile.is_open()) {
        log(LogLevel::Info, "Старт сессии приложения");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        log(LogLevel::Info, "Завершение сессии приложения");
        logFile.close();
    }
}

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!logFile.is_open()) return;
    logFile << "[" << getCurrentTime() << "] [" << levelToString(level) << "] " << message << std::endl;
}

void Logger::info(const std::string& message) {
    log(LogLevel::Info, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::Warning, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::Error, message);
}

std::string Logger::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return buf;
}

std::string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        default: return "UNKNOWN";
    }
} 