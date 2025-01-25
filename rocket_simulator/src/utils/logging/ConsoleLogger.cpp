#include "ConsoleLogger.h"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#pragma warning(disable : 4996)

Logger* Logger::_instance = nullptr;


Logger& Logger::get_instance() {
    if (_instance == nullptr) {
        _instance =new Logger();
        _instance->add_channel("debug");
        _instance->add_channel("error");
        _instance->add_channel("warning");
    }
    return *_instance;
}

Logger::Logger() = default;

void Logger::add_channel(const std::string& channel_name) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (channels.find(channel_name) != channels.end()) {
        return; 
    }

    AllocConsole();
    HWND console_window = GetConsoleWindow();
    if (!console_window) {
        throw std::runtime_error("Failed to allocate console for channel! ");
    }

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);


    channels[channel_name] = console_window;

    std::cout << "[" << channel_name << "] Console initialized." << std::endl;
}

void Logger::logError(const std::string& message) {
    this->log("error", message);
}

void Logger::logWarning(const std::string& message) {
    log("warning", message);
}

void Logger::logDebug(const std::string& message) {
    log("debug", message);
}

void Logger::logCustom(const std::string& channel_name, const std::string& message) {
    if (channels.find(channel_name) == channels.end()) {
        add_channel(channel_name);
    }
    log(channel_name, message);
}

void Logger::log(const std::string& channel_name, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = channels.find(channel_name);
    if (it == channels.end()) {
        throw std::exception("Channel not found! ");
    }

    SetForegroundWindow(it->second);

    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);

    std::cout << "[" << channel_name << "] " << message << std::endl;
}
