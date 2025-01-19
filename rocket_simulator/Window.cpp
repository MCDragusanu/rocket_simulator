#include "Window.h"

WINDOW::WINDOW(HINSTANCE instance, UINT width, UINT height, const wchar_t* windowTitle)
    : h_inst(instance), running_state(true), width(width), height(height) {

    // Window class setup
    WNDCLASSEX classDesc = {};
    classDesc.cbSize = sizeof(WNDCLASSEX);
    classDesc.lpfnWndProc = static_wnd_proc; // Register static window procedure
    classDesc.lpszClassName = L"ProjectRex";
    classDesc.hInstance = this->h_inst;
    classDesc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    classDesc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassEx(&classDesc)) {
        throw std::exception("Window class registration failed!");
    }

    // Create window
    hwnd = CreateWindowEx(
        0,
        classDesc.lpszClassName,
        windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        static_cast<int>(width), static_cast<int>(height),
        nullptr, nullptr,
        classDesc.hInstance,
        this
    );

    if (hwnd == nullptr) {
        throw std::exception("Window creation failed!");
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

WINDOW::~WINDOW()
{
    bool result = ~DestroyWindow(get_handle());
    if (result) {
        for (auto* obs : m_observers) {
            obs->on_window_destroyed();
        }
    }
}

bool WINDOW::is_running() const noexcept {
    return this->running_state;
}

void WINDOW::process_message() {

    MSG msg;
    while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
       
    }

}

HWND WINDOW::get_handle() const noexcept {
    return hwnd;
}

int WINDOW::get_window_width() const noexcept {
    return this->width;
}

int WINDOW::get_window_height() const noexcept {
    return this->height;
}

void WINDOW::add_listener(WINDOW_OBSERVER* observer) {
    m_observers.push_back(observer);
}

void WINDOW::drop_listener(WINDOW_OBSERVER* observer) {
    m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(),
        [observer](const WINDOW_OBSERVER* item) {
            return observer->get_uid() == item->get_uid();
        }), m_observers.end());
}

void WINDOW::setHandle(HWND hwnd) {
    this->hwnd = hwnd;
}

LRESULT CALLBACK WINDOW::static_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_NCCREATE) {
        // Store the this pointer in the window's user data
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(lpcs->lpCreateParams));
    }

    // Retrieve the this pointer from the window's user data
    WINDOW* window = reinterpret_cast<WINDOW*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (window) {
        window->handle_events(uMsg, wParam, lParam);
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        
    }
    else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void WINDOW::handle_events(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    
    switch (uMsg) {
    case WM_WINDOWPOSCHANGED: {
        WINDOWPOS* wp = reinterpret_cast<WINDOWPOS*>(lParam);
        UINT new_width = wp->cx;
        UINT new_height = wp->cy;

        for (auto observer : m_observers) {
            observer->on_window_resize(new_width, new_height);
        }
        this->width = new_width;
        this->height = new_height;
        break;
    }

    case WM_SYSCOMMAND:
        if (wParam == SC_MINIMIZE) {
            for (auto observer : m_observers) {
                observer->on_window_minimized();
            }
        }
        break;

    case WM_DESTROY:
        for (auto observer : m_observers) {
            observer->on_window_destroyed();
        }
        break;

    case WM_KEYDOWN:
        for (auto observer : m_observers) {
            observer->on_window_input_received(wParam, lParam);
        }
        break;

    case WM_KEYUP:
        for (auto observer : m_observers) {
            observer->on_window_input_released(wParam, lParam);
        }
        break;

    case WM_MOUSEMOVE:
        for (auto observer : m_observers) {
            observer->on_window_mouse_moved(GET_X_LPARAM(lParam) , GET_Y_LPARAM(lParam));
        }
        break;

    default:
        break;
    }
}