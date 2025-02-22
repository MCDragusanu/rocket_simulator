#pragma once
#include <assert.h>


namespace Core::Gfx::RenderingSystem {
	enum class RenderingAPI {
		OpenGL,
		DirectX,
		None
	};
	class RenderContext
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
		static RenderContext* instance;
		virtual RenderingAPI getRenderingAPIUsed()const noexcept = 0;
	};
};



