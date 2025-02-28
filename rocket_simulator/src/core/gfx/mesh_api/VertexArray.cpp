#include "VertexArray.h"
#include "../../Gfx/renderer_api/RenderContext.h"
#include "../../../opengl/Gfx/OpenGLVertexArray.h"
namespace Core::Gfx::Mesh {

	VertexArray* Core::Gfx::Mesh::VertexArray::create()
	{
		switch (Core::Gfx::RenderingSystem::RenderContext::getAPI())
		{
		case Core::Gfx::RenderingSystem::RenderingAPI::OpenGL: return new OpenGL::Gfx::OpenGLVertexArray();
		default:return nullptr;
			
		}
	}
}
