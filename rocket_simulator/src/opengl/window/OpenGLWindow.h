#pragma once
#include "../../core/window/MainWindow.h"

#include "../Gfx/renderer_api/OpenGLContext.h"


namespace OpenGL::Window {
   


	class OpenGLWindow : public Core::Window::MainWindow
	{
	public:
		 void initWindow(Core::Window::WindowAttributes& data) override;
		 void shutDown() override;
		 void onUpdate() override;
		 void setVsync(bool is_enabled) override;
		 void* getWindowPtr() const override {
			return pWindow;
		}
	private:
		GLFWwindow* pWindow = { nullptr };
		std::shared_ptr<OpenGL::Gfx::RenderingSystem::OpenGLContext> pContext;
	};
}

