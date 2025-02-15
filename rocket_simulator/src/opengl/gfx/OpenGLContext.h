#pragma once
#include "../../core/gfx/GraphicsContext.h"
#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"


namespace OPEN_GL::GFX {

	class OpenGLContext : public Core::gfx::GraphicsContext{

	public:
		OpenGLContext(GLFWwindow* window);
		virtual void init() override;
		virtual void swap_buffers() override;
		virtual void release() override;
		virtual Core::gfx::RenderingAPI getRenderingAPIUsed() const noexcept override { return Core::gfx::RenderingAPI::OpenGL; };
	private:
		GLFWwindow* mWindowHandle;
	};
}


