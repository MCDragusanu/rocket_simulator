#include <iostream>
#include <sstream>
#include <assert.h>
#include "OpenGLWindow.h"

namespace OPEN_GL::Window {


    void OpenGLWindow::initWindow(Core::Window::WindowAttributes& data)
    {
        this->mData.attributes = data;


        int glfw_status = glfwInit();
        if (!glfw_status) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(1);
        }
        glfwSetErrorCallback([](int errorCode, const char* description) {
            std::stringstream ss;
            ss << "Error Code : " << errorCode << "\n";
            ss << "Description : " << description;
            });

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        pWindow = glfwCreateWindow(data.width, data.height, data.windowTitle.c_str(), NULL, NULL);

        if (pWindow == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(2);
        }

        this->pContext = std::make_shared< OPEN_GL::GFX::OpenGLContext>(pWindow);
        pContext->init();

        glfwSetWindowUserPointer(pWindow, &mData);

        glfwSetWindowSizeCallback(pWindow, [](GLFWwindow* window, int width, int height) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.attributes.width = width;
            data.attributes.height = height;

            auto event = Core::Events::create_window_event(width, height, (uint8_t)Core::Events::EventType::WindowResized);
            if (data.pHandler != nullptr) {
                data.pHandler->on_window_event(event);
            }

            });

        glfwSetWindowCloseCallback(pWindow, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            auto event = Core::Events::create_window_event(data.attributes.width, data.attributes.height, (uint8_t)Core::Events::EventType::WindowClosed);
            if (data.pHandler != nullptr) {
                data.pHandler->on_window_event(event);
            }
            });

        glfwSetKeyCallback(pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                auto event = Core::Events::create_keyboard_event((uint64_t)key, (uint8_t)Core::Events::EventType::KeyboardPressed);
                if (data.pHandler) {
                    data.pHandler->on_keyboard_event(event);
                }
                break;
            }

            case GLFW_REPEAT: {
                auto event = Core::Events::create_keyboard_event((uint64_t)key, (uint8_t)Core::Events::EventType::KeyboardRepeated);
                if (data.pHandler) {
                    data.pHandler->on_keyboard_event(event);
                }
                break;
            }

            case GLFW_RELEASE: {
                auto event = Core::Events::create_keyboard_event((uint64_t)key, (uint8_t)Core::Events::EventType::KeyboardReleased);
                if (data.pHandler) {
                    data.pHandler->on_keyboard_event(event);
                }
                break;
            }

            default:
                break;
            }
            });

        glfwSetMouseButtonCallback(pWindow, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                auto event = Core::Events::create_mouse_event(0xffff, 0xffff, uint8_t(button), (uint8_t)Core::Events::EventType::MousePressed);
                if (data.pHandler) {
                    data.pHandler->on_mouse_event(event);
                }
                break;
            }

            case GLFW_RELEASE: {
                auto event = Core::Events::create_mouse_event(0xffff, 0xffff, uint8_t(button), (uint8_t)Core::Events::EventType::KeyboardReleased);
                if (data.pHandler) {
                    data.pHandler->on_mouse_event(event);
                }
                break;
            }

            default:
                break;
            }
            });

        glfwSetCursorPosCallback(pWindow, [](GLFWwindow* window, double positionX, double positionY) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            auto event = Core::Events::create_mouse_event(0xffff, 0xffff, 0x0000, (uint8_t)Core::Events::EventType::MouseMoved);

            if (data.pHandler) {
                data.pHandler->on_mouse_event(event);
            }

            });
    }

    void OpenGLWindow::shutDown()
    {
        glfwDestroyWindow(pWindow);
        pContext->release();
        pContext.reset();
    }

    void  OpenGLWindow::onUpdate()
    {
        glfwPollEvents();
    }

    void OpenGLWindow::setVsync(bool is_enabled)
    {
        if (is_enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        mData.attributes.VSyncEnabled = is_enabled;
    }

}