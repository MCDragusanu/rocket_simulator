#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <vector>
#include <iostream>

// Observer interface
struct WindowObserver {
    virtual void on_window_resize(UINT new_width, UINT new_height) = 0;
    virtual void on_window_minimized() = 0;
    virtual void on_window_destroyed() = 0;
    virtual void on_window_input_received(WPARAM wp, LPARAM lp) = 0;
    virtual void on_window_input_released(WPARAM wp, LPARAM lp) = 0;
    virtual void on_window_mouse_moved(int x, int y) {
    };
    virtual const size_t get_uid() const noexcept = 0;
};

// Window class
class Window {
public:
    Window(HINSTANCE instance, UINT width, UINT height, const wchar_t* windowTitle);
    ~Window();
    bool is_running() const noexcept;
    void process_message();
    HWND get_handle() const noexcept;
    int get_window_width() const noexcept;
    int get_window_height() const noexcept;
    void add_listener(WindowObserver* observer);
    void drop_listener(WindowObserver* observer);

protected:
    void set_handle(HWND hwnd);
    static LRESULT CALLBACK static_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void handle_events(UINT uMsg, WPARAM wp, LPARAM lp);
    std::vector<WindowObserver*> m_observers;

private:
    bool mRunning;
    bool mWindowIsResizing = false;
    HWND mHwnd;
    HINSTANCE mHinst;
    UINT mWidth, mHeight;
};