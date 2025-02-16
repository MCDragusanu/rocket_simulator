#include "Application.h"
#include "../../rocket_simulator/src/opengl/gfx/OpenGLBuffer.h"
#include "../../rocket_simulator/src/opengl/window/OpenGLWindow.h"
#include "../../rocket_simulator/src/opengl/gfx/shaders_api/OpenGLVertexShader.h"
#include "../../rocket_simulator/src/opengl/gfx/shaders_api/OpenGLFragmentShader.h"
#include "../../rocket_simulator/src/opengl/gfx/shaders_api/OpenGLShaderPipeline.h"

void Application::init()
{
	Core::Window::WindowAttributes attr{};
	this->mMainWindow =new OpenGL::Window::OpenGLWindow();
	mMainWindow->initWindow(attr);
	mMainWindow->setEventHandler(this);	
	mIsRunning = true;
}

void Application::update()
{
	mMainWindow->onUpdate();
}

void Application::release()
{
}

bool Application::isRunning()
{
	return mIsRunning;
}

void Application::prepareShutDown()
{
	mIsRunning = false;
}

void Application::on_window_event(const std::unique_ptr<Core::Events::Event>& event)
{
	switch (event->bytes[9]) {
		case (uint8_t)Core::Events::EventType::WindowClosed:
		{
			std::cout << "Window will be closed\n";
			mIsRunning = false;
			prepareShutDown();
			break;
		}
		case (uint8_t)Core::Events::EventType::WindowFocused:
		{
			std::cout << "Window Focussed Event\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::WindowResized:
		{
			std::cout << "Window Resized Event " << event->windowSize[0] << " " << event->windowSize[1] << "\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::WindowMinimised: 
		{
			std::cout << "Window Minimised Event" << "\n";
		}
	}
}

void Application::on_keyboard_event(const std::unique_ptr<Core::Events::Event>& event)
{
	switch (event->bytes[9]) {
		case (uint8_t)Core::Events::EventType::KeyboardPressed:
		{
			std::cout << "Keyboard Pressed Detected " << event->key_code<<"\n";
		
		
			break;
		}
		case (uint8_t)Core::Events::EventType::KeyboardReleased:
		{
			std::cout << "Keyboard Released Detected " << event->key_code << "\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::KeyboardRepeated:
		{
			std::cout << "Keyboard Repeated Detected " << event->key_code << "\n";
			break;
		}
	}
}

void Application::on_mouse_event(const std::unique_ptr<Core::Events::Event>& event)
{
	switch (event->bytes[9]) {
		case (uint8_t)Core::Events::EventType::MouseMoved:
		{
			std::cout << "Mouse Moved Detected " << event->mouseCoordinates[0] << " " << event->mouseCoordinates[1] << "\n";

			break;
		}
		case (uint8_t)Core::Events::EventType::MousePressed:
		{
			std::cout << "Mouse Pressed Detected " << event->bytes[8] << "\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::MouseReleased:
		{
			std::cout << "Mouse Released Detected " << event->bytes[9] << "\n";
			break;
		}
	}
}
