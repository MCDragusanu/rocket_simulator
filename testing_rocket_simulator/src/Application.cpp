#include "Application.h"
#include "../../rocket_simulator/src/opengl/gfx/OpenGLBuffer.h"
#include "../../rocket_simulator/src/opengl/window/OpenGLWindow.h"
#include "../../rocket_simulator/src/opengl/gfx/shaders_api/OpenGLVertexShader.h"
#include "../../rocket_simulator/src/opengl/gfx/shaders_api/OpenGLFragmentShader.h"
#include "../../rocket_simulator/src/opengl/gfx/shaders_api/OpenGLShaderPipeline.h"
#include "../../rocket_simulator/src/opengl/gfx/OpenGLVertexArray.h"
void Application::init()
{
	using namespace Core::Window;
	using namespace Core::gfx;
	using namespace Core::gfx::shaders;
	using namespace OpenGL::gfx;
	using namespace OpenGL::Window;
	using namespace OpenGL::ShadersApi;
	WindowAttributes attr{};
	this->mMainWindow = new OpenGLWindow();
	mMainWindow->initWindow(attr);
	mMainWindow->setEventHandler(this);
	mIsRunning = true;

	

	
	float vertexData[] = {
		-1.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	}; 
	unsigned int indices[] = { 0 , 1 , 2 }; 
	pVertexArray.reset(VertexArray::create());  
	pVertexBuffer.reset(VertexBuffer::create(vertexData, sizeof(vertexData)));
	pIndexBuffer.reset(IndexBuffer::create(indices, 3));
	{
		auto elements = std::vector<BufferLayoutElement>{
			{ "aPos",DataType::Float3}
		};
		BufferLayout layout = BufferLayout(elements);	
		pVertexBuffer->setLayout(layout);
	}




	pVertexArray->addVertexBuffer(pVertexBuffer);
	pVertexArray->addIndexBuffer(pIndexBuffer);


	{
		auto pixel_shader_path = std::filesystem::path("resources/shaders/pixel_shader.txt");
		auto vertex_shader_path = std::filesystem::path("resources/shaders/vertex_shader.txt");
		pVertexShader = new OpenGLVertexShader(vertex_shader_path);
		pFragmentShader = new OpenGLFragmentShader(pixel_shader_path);
		pShaderPipeline = new OpenGLShaderPipeline();
	}

	pShaderPipeline->createPipeline();
	bool isCompiled = pVertexShader->compile(std::cerr);
	if (!isCompiled) {
		std::cerr << "Failed to compile vertex shader!\n";
		prepareShutDown();
		return;
	}
	isCompiled = pFragmentShader->compile(std::cerr);
	if (!isCompiled) {
		std::cerr << "Failed to compile fragment shader!\n";
		prepareShutDown();
		return;
	}
	try{
		pShaderPipeline->attachShaders(std::vector<Shader*> { pVertexShader,pFragmentShader});
	}
	catch (const std::exception& e) {
		std::cerr <<"\n" << e.what();
		prepareShutDown();
		return;
	}
	
	pShaderPipeline->bind();
}

void Application::update()
{
	mMainWindow->onUpdate();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	
	pVertexArray->bind();
	glDrawElements(GL_TRIANGLES, pIndexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
	glfwSwapBuffers((GLFWwindow*)mMainWindow->getWindowPtr());
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
			//std::cout << "Window will be closed\n";
			mIsRunning = false;
			prepareShutDown();
			break;
		}
		case (uint8_t)Core::Events::EventType::WindowFocused:
		{
			//std::cout << "Window Focussed Event\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::WindowResized:
		{
			//std::cout << "Window Resized Event " << event->windowSize[0] << " " << event->windowSize[1] << "\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::WindowMinimised: 
		{
			//std::cout << "Window Minimised Event" << "\n";
		}
	}
}

void Application::on_keyboard_event(const std::unique_ptr<Core::Events::Event>& event)
{
	switch (event->bytes[9]) {
		case (uint8_t)Core::Events::EventType::KeyboardPressed:
		{
			//std::cout << "Keyboard Pressed Detected " << event->key_code<<"\n";
		
		
			break;
		}
		case (uint8_t)Core::Events::EventType::KeyboardReleased:
		{
			//std::cout << "Keyboard Released Detected " << event->key_code << "\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::KeyboardRepeated:
		{
			//std::cout << "Keyboard Repeated Detected " << event->key_code << "\n";
			break;
		}
	}
}

void Application::on_mouse_event(const std::unique_ptr<Core::Events::Event>& event)
{
	switch (event->bytes[9]) {
		case (uint8_t)Core::Events::EventType::MouseMoved:
		{
			//std::cout << "Mouse Moved Detected " << event->mouseCoordinates[0] << " " << event->mouseCoordinates[1] << "\n";

			break;
		}
		case (uint8_t)Core::Events::EventType::MousePressed:
		{
			//std::cout << "Mouse Pressed Detected " << event->bytes[8] << event->mouseCoordinates[0] << " " << event->mouseCoordinates[1] << "\n";
			break;
		}
		case (uint8_t)Core::Events::EventType::MouseReleased:
		{
			//std::cout << "Mouse Released Detected " << event->bytes[8] << event->mouseCoordinates[0] << " " << event->mouseCoordinates[1] << "\n";
			break;
		}
	}
}
