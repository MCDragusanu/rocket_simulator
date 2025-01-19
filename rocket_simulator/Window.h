#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <vector>
#include <iostream>

// Observer interface
struct WINDOW_OBSERVER {
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
class WINDOW {
public:
    WINDOW(HINSTANCE instance, UINT width, UINT height, const wchar_t* windowTitle);
    ~WINDOW();
    bool is_running() const noexcept;
    void process_message();
    HWND get_handle() const noexcept;
    int get_window_width() const noexcept;
    int get_window_height() const noexcept;
    void add_listener(WINDOW_OBSERVER* observer);
    void drop_listener(WINDOW_OBSERVER* observer);

protected:
    void setHandle(HWND hwnd);
    static LRESULT CALLBACK static_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void handle_events(UINT uMsg, WPARAM wp, LPARAM lp);
    std::vector<WINDOW_OBSERVER*> m_observers;

private:
    bool running_state;
    bool window_is_resizing = false;
    HWND hwnd;
    HINSTANCE h_inst;
    UINT width, height;
};