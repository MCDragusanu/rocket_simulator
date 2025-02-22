#pragma once
#include <thread>
#include "../VertexArray.h"
#include "../scene_api/Scene.h"
namespace Core::Gfx::RenderingSystem {

	enum class CommandType {
		DrawIndexed
	};

	class RenderCommand {
		friend class Renderer;
		
	public:
		virtual CommandType getType() = 0;
		virtual void execute() = 0;
		static  void setRendererAPI(Renderer* instance);
	protected:
		static Renderer* pRendererAPI;
	};

	class Renderer {
		friend class RenderCommand;
	public:
		virtual void beginScene(const Core::Gfx::SceneSystem::Scene& scene) = 0;
		virtual void endScene() = 0;
		virtual void submit() = 0;
	protected:
		virtual const std::vector<RenderCommand*>& getCommands(const Core::Gfx::SceneSystem::Scene& scene) const = 0;
		virtual void setClearColor(float r, float g, float b) = 0;
		virtual void clear() = 0;
		virtual void setThread(std::thread& renderingThread) = 0;
		virtual void addCommand(RenderCommand* command) = 0;
		virtual void executeCommands() = 0;
		virtual void drawIndexed(const std::shared_ptr<Core::Gfx::VertexArray>& vertexArray) = 0;
		static Renderer* pRendererAPI;
	};
}