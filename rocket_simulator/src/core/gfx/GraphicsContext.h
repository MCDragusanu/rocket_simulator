#pragma once
#include <assert.h>
#include "../window/MainWindow.h"


namespace Core::gfx {
	enum class RenderingAPI {
		OpenGL,
		DirectX,
		None
	};
	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swap_buffers() = 0;
		virtual void release() = 0;
		static RenderingAPI getAPI() {
			assert(instance != nullptr);
			return instance->getRenderingAPIUsed();
		}
	protected:
		static GraphicsContext* instance;
		virtual RenderingAPI getRenderingAPIUsed()const noexcept = 0;
	};
};

Core::gfx::GraphicsContext* Core::gfx::GraphicsContext::instance = nullptr;


