#include "OpenGLBuffer.h"
#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"
#include "../../utils/error_handlers/OpenGLErrorHandler.h"
namespace OpenGL :: gfx {
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, size_t byteSize)
	{
		GL_CALL(glGenBuffers(1, &this->resourceUid));
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->resourceUid));
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GL_CALL(glDeleteBuffers(1, &resourceUid));
	}

	void OpenGLVertexBuffer::bind()
	{
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->resourceUid));
	}

	void OpenGLVertexBuffer::unBind()
	{
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}


	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* data, size_t indexCount)
	{
		this->mIndicesCount = indexCount;
		GL_CALL(glGenBuffers(1, &this->resourceUid));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->resourceUid));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GL_CALL(glDeleteBuffers(1, &resourceUid));
	}

	void OpenGLIndexBuffer::bind()
	{
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->resourceUid));
	}

	void OpenGLIndexBuffer::unBind()
	{
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
	size_t OpenGLIndexBuffer::getCount() const noexcept
	{
		return this->mIndicesCount;
	}
}
