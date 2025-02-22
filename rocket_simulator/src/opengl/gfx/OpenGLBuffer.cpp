#include "OpenGLBuffer.h"
#include "../../utils/error_handlers/OpenGLErrorHandler.h"
namespace OpenGL :: Gfx {
	
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

	void OpenGLVertexBuffer::setLayout(const Core::Gfx::BufferLayout& layout)
	{
		this->layout = layout;
	}

	const Core::Gfx::BufferLayout& OpenGLVertexBuffer::getLayout() const noexcept
	{
		return this->layout;
	}

	 GLenum OpenGLVertexBuffer::dataTypeConverter(Core::Gfx::DataType type) 
	{
		switch (type)
		{
		case Core::Gfx::DataType::Float:    return GL_FLOAT;
		case Core::Gfx::DataType::Float2:   return GL_FLOAT;
		case Core::Gfx::DataType::Float3:   return GL_FLOAT;
		case Core::Gfx::DataType::Float4:   return GL_FLOAT;
		case Core::Gfx::DataType::Mat2:     return GL_FLOAT;
		case Core::Gfx::DataType::Mat3:     return GL_FLOAT;
		case Core::Gfx::DataType::Mat4:     return GL_FLOAT;
		case Core::Gfx::DataType::Int:      return GL_INT;
		case Core::Gfx::DataType::Int2:     return GL_INT;
		case Core::Gfx::DataType::Int3:     return GL_INT;
		case Core::Gfx::DataType::Int4:     return GL_INT;
		case Core::Gfx::DataType::None:
		default:return 0;

		}
		
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
