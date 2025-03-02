#pragma once
#include "../../../core/Gfx/renderer_api/Renderer.h"
#include "OpenGLContext.h"

#include <mutex>
#include <queue>
namespace OpenGL::Gfx::RenderingSystem {

	class OpenGLRenderer : public Core::Gfx::RenderingSystem::Renderer {
		
	public:

		OpenGLRenderer(std :: shared_ptr<OpenGLContext>& context);
		virtual void beginDraw() override;
		virtual void endDraw() override;
		virtual void addCommand(const Core::Gfx::RenderingSystem::RenderCommand* command) override;
		virtual void addCommand(Core::Gfx::RenderingSystem::RenderCommand* command) override;
	protected:
		

		// Inherited via Renderer
		virtual void setClearColor(float r, float g, float b) override;
		virtual void clear() override;
	
	private:
		std::mutex queueMutex;
		std :: shared_ptr<OpenGL::Gfx::RenderingSystem::OpenGLContext> mContext;
		std :: queue<Core::Gfx::RenderingSystem::RenderCommand*> mFrontBuffer;
		std :: queue<Core::Gfx::RenderingSystem::RenderCommand*> mBackBuffer;
	};
}