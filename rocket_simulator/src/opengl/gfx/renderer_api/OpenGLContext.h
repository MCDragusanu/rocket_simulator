#pragma once
#include "../../../core/Gfx/renderer_api/RenderContext.h"


struct GLFWwindow;
namespace OpenGL::Gfx::RenderingSystem {

	class OpenGLContext : public Core::Gfx::RenderingSystem::RenderContext{

	public:
		OpenGLContext(GLFWwindow* window);
		virtual void init() override;
		virtual void swap_buffers() override;
		virtual void release() override;
		virtual Core::Gfx::RenderingSystem::RenderingAPI getRenderingAPIUsed() const noexcept override { return Core::Gfx::RenderingSystem::RenderingAPI::OpenGL; };
	private:
		GLFWwindow* mWindowHandle;
	};
}


