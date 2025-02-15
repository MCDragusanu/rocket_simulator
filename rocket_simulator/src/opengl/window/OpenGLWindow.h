#pragma once
#include "../../core/window/MainWindow.h"

#include "../gfx/OpenGLContext.h"


namespace OPEN_GL::Window {
	
	class OpenGLWindow : public Core::Window::MainWindow
	{
	public:
		virtual void initWindow(Core::Window::WindowAttributes& data) override;
		virtual void shutDown() override;
		virtual void onUpdate() override;
		virtual void setVsync(bool is_enabled) override;
		virtual void* getWindowPtr() const override {
			return pWindow;
		}
	private:
		GLFWwindow* pWindow;
		std::shared_ptr<OPEN_GL::GFX::OpenGLContext> pContext;
	};
}


