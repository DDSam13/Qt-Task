#pragma once
#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    static Logger& instance();
    void log(LogLevel level, const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
private:
    Logger();
    ~Logger();
    std::ofstream logFile;
    std::mutex mtx;
    std::string getCurrentTime() const;
    std::string levelToString(LogLevel level) const;
}; 