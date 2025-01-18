#include "Window.h"


// WinMain: Entry point for a Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    try {
        // Create and initialize the MyWindow object
        MainWindow win(hInstance, 800, 600, "My DirectX 12 Window");

        // Message loop
        while (win.is_running()) {
            win.process_message();
        }
    }
    catch (const std::exception& e) {
        MessageBox(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
}