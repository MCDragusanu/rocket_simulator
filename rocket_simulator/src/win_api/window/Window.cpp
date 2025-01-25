#include "Window.h"

Window::Window(HINSTANCE instance, UINT width, UINT height, const wchar_t* windowTitle)
    : mHinst(instance), mRunning(true), mWidth(width), mHeight(height) {

    // Window class setup
    WNDCLASSEX classDesc = {};
    classDesc.cbSize = sizeof(WNDCLASSEX);
    classDesc.lpfnWndProc = static_wnd_proc; // Register static window procedure
    classDesc.lpszClassName = L"ProjectRex";
    classDesc.hInstance = this->mHinst;
    classDesc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    classDesc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassEx(&classDesc)) {
        throw std::exception("Window class registration failed!");
    }

    // Create window
    mHwnd = CreateWindowEx(
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

    if (mHwnd == nullptr) {
        throw std::exception("Window creation failed!");
    }

    ShowWindow(mHwnd, SW_SHOW);
    UpdateWindow(mHwnd);
}

Window::~Window()
{
    bool result = ~DestroyWindow(get_handle());
    if (result) {
        for (auto* obs : m_observers) {
            obs->on_window_destroyed();
        }
    }
}

bool Window::is_running() const noexcept {
    return this->mRunning;
}

void Window::process_message() {

    MSG msg;
    while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
       
    }

}

HWND Window::get_handle() const noexcept {
    return mHwnd;
}

int Window::get_window_width() const noexcept {
    return this->mWidth;
}

int Window::get_window_height() const noexcept {
    return this->mHeight;
}

void Window::add_listener(WindowObserver* observer) {
    m_observers.push_back(observer);
}

void Window::drop_listener(WindowObserver* observer) {
    m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(),
        [observer](const WindowObserver* item) {
            return observer->get_uid() == item->get_uid();
        }), m_observers.end());
}

void Window::set_handle(HWND hwnd) {
    this->mHwnd = hwnd;
}

LRESULT CALLBACK Window::static_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_NCCREATE) {
        // Store the this pointer in the window's user data
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(lpcs->lpCreateParams));
    }

    // Retrieve the this pointer from the window's user data
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

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

void Window::handle_events(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    
    switch (uMsg) {
    case WM_WINDOWPOSCHANGED: {
        WINDOWPOS* wp = reinterpret_cast<WINDOWPOS*>(lParam);
        UINT new_width = wp->cx;
        UINT new_height = wp->cy;

        for (auto observer : m_observers) {
            observer->on_window_resize(new_width, new_height);
        }
        this->mWidth = new_width;
        this->mHeight = new_height;
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