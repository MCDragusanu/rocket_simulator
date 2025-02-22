#include "VertexArray.h"
#include "../gfx/renderer_api/RenderContext.h"
#include "../../opengl/gfx/OpenGLVertexArray.h"
namespace Core::Gfx {

	VertexArray* Core::Gfx::VertexArray::create()
	{
		switch (Core::Gfx::RenderingSystem::RenderContext::getAPI())
		{
		case Core::Gfx::RenderingSystem::RenderingAPI::OpenGL: return new OpenGL::Gfx::OpenGLVertexArray();
		default:return nullptr;
			
		}
	}
}
