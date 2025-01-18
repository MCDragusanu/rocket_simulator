#pragma once

#include <Windows.h>
#include <exception>
#include <iostream>
#include <functional>
class WINDOW {
public:

	WINDOW(HINSTANCE instance, int width, int height, const char* windowTitle);
	bool is_running() const noexcept;
	void process_message();
	HWND get_handle() const noexcept;
    int get_window_width() const noexcept {
        return this->width;
    }
    int get_window_height() const noexcept {
        return this->height;
    }
protected :
	virtual LRESULT wnd_proc(MSG& msg, WPARAM wp, LPARAM lp) = 0;
	virtual void destroy() = 0;
    void setHandle(HWND hwnd) {
        this->hwnd = hwnd;
    }
    static LRESULT CALLBACK static_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private :
	bool running_state;
	HWND hwnd;
	HINSTANCE h_inst;
    int width, height;
};


class MainWindow : public WINDOW {
public:
    MainWindow(HINSTANCE hInstance, int width, int height, const char* title)
        : WINDOW(hInstance, width, height, title) {
       

            // Ensure WNDCLASSEX is properly initialized
        WNDCLASSEX classDesc = {};
        classDesc.cbSize = sizeof(WNDCLASSEX);  // Set the size of the structure
        classDesc.lpfnWndProc = static_wnd_proc;  // Set the static window proc function
        classDesc.lpszClassName = "ProjectRex";  // Set a unique window class name
        classDesc.hInstance = hInstance;
        classDesc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        classDesc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Set background color

        // Register the window class
        if (!RegisterClassEx(&classDesc)) {
            throw std::exception("Window class registration failed!");
        }

        // Create the window
        HWND hwnd = CreateWindowEx(
            0,
            classDesc.lpszClassName,
            title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
           width , height,
            nullptr, nullptr,
            classDesc.hInstance,
            nullptr);

        if (hwnd == nullptr) {
            throw std::exception("Window creation failed!");
        }
        setHandle(hwnd);
        ShowWindow(hwnd, SW_SHOW);  // Display the window
        UpdateWindow(hwnd);  // Refresh the window

    }

protected:
    LRESULT wnd_proc(MSG& msg, WPARAM wp, LPARAM lp) override {
        switch (msg.message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            // Handle key press
            return 0;
        default:
            return DefWindowProc(msg.hwnd, msg.message, wp, lp);
        }
    }
    void destroy() override {
        BOOL result = DestroyWindow(this->get_handle());
        if (result) {
            std::cout << "Window has been destroyed";
        }
    }

    
private:
    WNDCLASSEX m_classDesc = {};  // Configure the window class

   
        
};