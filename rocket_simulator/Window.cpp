#include "Window.h"

WINDOW::WINDOW(HINSTANCE instance, int width, int height, const char* windowTitle)
    :h_inst(instance),
     width(width),
     height(height),
     running_state(true)
{}

bool WINDOW::is_running() const noexcept
{
    return this->running_state;
}

void WINDOW::process_message()
{
    MSG msg;
    while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            running_state = false;
        }
        else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

HWND WINDOW::get_handle() const noexcept
{
    return hwnd;
}

LRESULT WINDOW::static_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WINDOW* pWindow;
    if (uMsg == WM_NCCREATE) {
        pWindow = reinterpret_cast<WINDOW*>(((CREATESTRUCT*)lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
    }
    else {
        pWindow = reinterpret_cast<WINDOW*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pWindow) {
        return pWindow->wnd_proc(*reinterpret_cast<MSG*>(&lParam), wParam, lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
