#pragma once
#include "../../../core/Gfx/renderer_api/Renderer.h"
#include "OpenGLContext.h"
#include <concurrent_queue.h>
namespace OpenGL::Gfx::RenderingSystem {

	class OpenGLRenderer : public Core::Gfx::RenderingSystem::Renderer {
		friend class Core::Gfx::SceneSystem::Scene;
		friend class Core::Gfx::RenderingSystem::RenderCommand;
	public:

		OpenGLRenderer(std :: shared_ptr<OpenGLContext>& context);
		virtual void beginScene(const Core::Gfx::SceneSystem::Scene& scene) override;
		virtual void endScene() override;
		virtual void submit() override;
	protected:
		

		// Inherited via Renderer
		virtual void setClearColor(float r, float g, float b) override;
		virtual void clear() override;
		virtual void setThread(std::thread& renderingThread) override;
		virtual void addCommand(Core::Gfx::RenderingSystem::RenderCommand* command) override;
		virtual void executeCommands() override;
		virtual void drawIndexed(const std::shared_ptr<Core::Gfx::VertexArray>& vertexArray) override;
	private:
		std :: shared_ptr<OpenGL::Gfx::RenderingSystem::OpenGLContext> mContext;
		Concurrency::concurrent_queue<Core::Gfx::RenderingSystem::RenderCommand*> mCommandQueue;
	};
}