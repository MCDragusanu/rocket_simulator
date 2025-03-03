
#include <assert.h>
#include <iostream>
#include <sstream>
#include "OpenGLContext.h"
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"

namespace OpenGL::Gfx::RenderingSystem {
	OpenGLContext::OpenGLContext(GLFWwindow* window) : mWindowHandle(window)
	{
		assert(mWindowHandle != nullptr);
	}

	void OpenGLContext::init()
	{

		if (mWindowHandle == nullptr) {
			std::cerr << "Failed to obtain window handle.The current handle is null!" << " file : " << __FILE__ << " line : " << __LINE__ << "\n";
			exit(0);
		}
		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0) {
			std::cerr << "Failed to Initialise GLAD!" << " file : " << __FILE__ << " line : " << __LINE__ << "\n";
			exit(0);
		}

		Core::Gfx:: RenderingSystem::RenderContext::instance = this;
	}

	void OpenGLContext::swap_buffers()
	{
		glfwSwapBuffers(mWindowHandle);
	}

	void OpenGLContext::release()
	{
		glfwTerminate();
	}
}