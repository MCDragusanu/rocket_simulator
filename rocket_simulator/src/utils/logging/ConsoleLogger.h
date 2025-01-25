#pragma once
#pragma once
#include <Windows.h>
#include <string>
#include <unordered_map>
#include <mutex>

// Singleton logger class with multiple channels
class Logger {
public:
    // Get the singleton instance
    static Logger& get_instance();

    // Add a new channel with a unique console window
    void add_channel(const std::string& channel_name);

    // Log an error message
    void logError(const std::string& message);

    // Log a warning message
    void logWarning(const std::string& message);

    // Log a debug message
    void logDebug(const std::string& message);

    // Log a custom message to a specified channel
    void logCustom(const std::string& channel_name, const std::string& message);

private:
    // Private constructor for singleton
    Logger();

    // Disable copy and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* _instance;
    // Log a message to a specific channel
    void log(const std::string& channel_name, const std::string& message);

    std::unordered_map<std::string, HWND> channels; // Map of channels to console handles
    std::mutex mutex_; // Thread safety
};
