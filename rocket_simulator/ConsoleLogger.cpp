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
        _instance->add_channel(L"debug");
        _instance->add_channel(L"error");
        _instance->add_channel(L"warning");
    }
    return *_instance;
}

Logger::Logger() = default;

void Logger::add_channel(const std::wstring& channel_name) {
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

    SetConsoleTitle(channel_name.c_str());
    channels[channel_name] = console_window;

    std::wcout << L"[" << channel_name << L"] Console initialized." << std::endl;
}

void Logger::logError(const std::wstring& message) {
    this->log(L"error", message);
}

void Logger::logWarning(const std::wstring& message) {
    log(L"warning", message);
}

void Logger::logDebug(const std::wstring& message) {
    log(L"debug", message);
}

void Logger::logCustom(const std::wstring& channel_name, const std::wstring& message) {
    if (channels.find(channel_name) == channels.end()) {
        add_channel(channel_name);
    }
    log(channel_name, message);
}

void Logger::log(const std::wstring& channel_name, const std::wstring& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = channels.find(channel_name);
    if (it == channels.end()) {
        throw std::exception("Channel not found! ");
    }

    SetForegroundWindow(it->second);

    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);

    std::wcout << L"[" << channel_name << L"] " << message << std::endl;
}
