#include "Buffer.h"
#include "../../opengl/gfx/OpenGLBuffer.h"
namespace Core::gfx {
	VertexBuffer* Core::gfx::VertexBuffer::create(float* data, size_t byteSize) {


		switch (GraphicsContext::getAPI()) {

		case RenderingAPI::DirectX:
		case RenderingAPI::None:
			assert(false);
			return nullptr;
		case RenderingAPI::OpenGL: return new OpenGL::gfx::OpenGLVertexBuffer(data, byteSize);

		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(unsigned int* data, size_t indexCount) {

		switch (GraphicsContext::getAPI()) {

		case RenderingAPI::DirectX:
		case RenderingAPI::None:
			assert(false);
			return nullptr;
		case RenderingAPI::OpenGL: return new OpenGL::gfx::OpenGLIndexBuffer(data, indexCount);

		}
		return nullptr;
	}

}