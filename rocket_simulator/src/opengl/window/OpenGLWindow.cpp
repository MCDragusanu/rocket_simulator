#include <iostream>
#include <sstream>
#include <assert.h>
#include "OpenGLWindow.h"
#include "../../include/glad/glad.h"
#include "../../include/glfw/glfw3.h"
#include "../../core/events/EventHandler.h"
#include "../input/OpenGLKeyboardMapper.h"
#include "../input/OpenGLMouseCodeMapper.h"
namespace OpenGL::Window {


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

        this->pContext = std::make_shared< OpenGL::Gfx::RenderingSystem::OpenGLContext>(pWindow);
        pContext->init();
       

        glfwSetWindowUserPointer(pWindow, &mData);

        glfwSetWindowSizeCallback(pWindow, [](GLFWwindow* window, int width, int height) {
             
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.attributes.width = width;
            data.attributes.height = height;

            auto event = Core::Events::create_window_event(width, height, (uint8_t)Core::Events::EventType::WindowResized);
            auto callback = (Core::Events::EventCallback*)(data.pHandler);
            if (callback != nullptr) {
                callback->on_window_event(event);
            }

            });

        glfwSetWindowCloseCallback(pWindow, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            auto event = Core::Events::create_window_event(data.attributes.width, data.attributes.height, (uint8_t)Core::Events::EventType::WindowClosed);
            auto callback = (Core::Events::EventCallback*)(data.pHandler);
            if (callback != nullptr) {
                callback->on_window_event(event);
            }
            });

        glfwSetKeyCallback(pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            auto callback = (Core::Events::EventCallback*)(data.pHandler);
            switch (action)
            {
            case GLFW_PRESS:
            {
                auto event = Core::Events::create_keyboard_event(OpenGL::Input::OpenGLKeyCodeMapper::getInstance().translateCode(key), (uint8_t)Core::Events::EventType::KeyboardPressed);
                if (callback) {
                    callback->on_keyboard_event(event);
                }
                break;
            }

            case GLFW_REPEAT: {
                auto event = Core::Events::create_keyboard_event(OpenGL::Input::OpenGLKeyCodeMapper::getInstance().translateCode(key), (uint8_t)Core::Events::EventType::KeyboardRepeated);
                if (callback) {
                    callback->on_keyboard_event(event);
                }
                break;
            }

            case GLFW_RELEASE: {
                auto event = Core::Events::create_keyboard_event(OpenGL::Input::OpenGLKeyCodeMapper::getInstance().translateCode(key), (uint8_t)Core::Events::EventType::KeyboardReleased);
                if (callback) {
                    callback->on_keyboard_event(event);
                }
                break;
            }

            default:
                break;
            }
            });

        glfwSetMouseButtonCallback(pWindow, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            auto callback = (Core::Events::EventCallback*)(data.pHandler);
            switch (action)
            {
            case GLFW_PRESS:
            {
                auto event = Core::Events::create_mouse_event(data.prevMouseX, data.prevMouseY, OpenGL::Input::OpenGLMouseButtonMapper::getInstance().translateCode(button), (uint8_t)Core::Events::EventType::MousePressed);
                if (callback) {
                    callback->on_mouse_event(event);
                }
                break;
            }

            case GLFW_RELEASE: {
                auto event = Core::Events::create_mouse_event(data.prevMouseX, data.prevMouseY, OpenGL::Input::OpenGLMouseButtonMapper::getInstance().translateCode(button), (uint8_t)Core::Events::EventType::KeyboardReleased);
                if (callback) {
                    callback->on_mouse_event(event);
                }
                break;
            }

            default:
                break;
            }
            });

        glfwSetCursorPosCallback(pWindow, [](GLFWwindow* window, double positionX, double positionY) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.prevMouseX = positionX;
            data.prevMouseY = positionY;
            auto event = Core::Events::create_mouse_event(positionX, positionY, OpenGL::Input::OpenGLMouseButtonMapper::getInstance().translateCode(-1), (uint8_t)Core::Events::EventType::MouseMoved);
            auto callback = (Core::Events::EventCallback*)(data.pHandler);
            if (callback) {
                callback->on_mouse_event(event);
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