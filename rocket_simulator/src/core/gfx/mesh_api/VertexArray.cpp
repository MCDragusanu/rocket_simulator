#include "VertexArray.h"
#include "../../Gfx/renderer_api/RenderContext.h"
#include "../../../opengl/Gfx/mesh_api/OpenGLVertexArray.h"
namespace Core::Gfx::MeshSystem {

	VertexArray* Core::Gfx::MeshSystem::VertexArray::create()
	{
		switch (Core::Gfx::RenderingSystem::RenderContext::getAPI())
		{
		case Core::Gfx::RenderingSystem::RenderingAPI::OpenGL: return new OpenGL::Gfx::OpenGLVertexArray();
		default:return nullptr;
			
		}
	}
}
