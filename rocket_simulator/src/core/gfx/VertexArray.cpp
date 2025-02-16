#include "VertexArray.h"
#include "GraphicsContext.h"
#include "../../opengl/gfx/OpenGLVertexArray.h"
namespace Core::gfx {

	VertexArray* Core::gfx::VertexArray::create()
	{
		switch (Core::gfx::GraphicsContext::getAPI())
		{
		case Core::gfx::RenderingAPI::OpenGL: return new OpenGL::gfx::OpenGLVertexArray();
		default:
			break;
		}
	}
}
