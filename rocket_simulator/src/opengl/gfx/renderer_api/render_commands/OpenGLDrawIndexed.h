#pragma once
#include "../OpenGLRenderer.h"
#include "../../../../core/gfx/mesh_api/mesh.h"
namespace OpenGL::Gfx::RenderSystem::Commands {
	class OpenGLDrawIndexed : public Core::Gfx::RenderingSystem::RenderCommand
	{
	public:
		OpenGLDrawIndexed(const std::shared_ptr<Core::Gfx::MeshSystem::VertexArray>& vertexArray);
		virtual Core::Gfx::RenderingSystem::CommandType getType()override;
		virtual void execute() override;
	private:
		std::shared_ptr<Core::Gfx::MeshSystem::VertexArray> vertexArray;
	};
}


