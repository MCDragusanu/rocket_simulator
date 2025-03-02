#include "OpenGLVertexArray.h"
#include <glad.h>
#include "OpenGLBuffer.h"
#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"
#include <assert.h>
#include <iostream>
OpenGL::Gfx::OpenGLVertexArray::OpenGLVertexArray() : mVertexBufferList() , mIndexBuffer() , mVertexArrayUid(-1)
{
	glGenVertexArrays(1, &this->mVertexArrayUid);

}

void OpenGL::Gfx::OpenGLVertexArray::bind()
{
	glBindVertexArray(mVertexArrayUid);
}

void OpenGL::Gfx::OpenGLVertexArray::unBind()
{
	glBindVertexArray(0);
}

void OpenGL::Gfx::OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<Core::Gfx::MeshSystem::VertexBuffer>& buffer)
{
	glBindVertexArray(mVertexArrayUid);
	buffer->bind();
	size_t index = 0;
	auto layout = buffer->getLayout();



	for (const auto& element : layout) {
		
		auto elementCount = element.getElementCount();
		auto dataType = OpenGL::Gfx::OpenGLVertexBuffer::dataTypeConverter(element.type);
		auto isNormalised = element.normalised ? GL_TRUE : GL_FALSE;
		auto stride = layout.getStride();
		auto elementOffset = (const void*)element.offset;
		
		std::cerr << "Count :" << elementCount << " DataType : " << (int)dataType << " Stride : " << stride << " offfset :" <<  element.offset<<"\n";
		
		
		glVertexAttribPointer(
			index,
			elementCount,
			dataType,
			isNormalised,
			stride,
			elementOffset
		);
		glEnableVertexAttribArray(index);
		index++;
	}
	mVertexBufferList.push_back(buffer);
}

void OpenGL::Gfx::OpenGLVertexArray::addIndexBuffer(const std::shared_ptr<Core::Gfx::MeshSystem::IndexBuffer>& buffer)
{
	glBindVertexArray(mVertexArrayUid);
	buffer->bind();
	mIndexBuffer = buffer;
}

const Core::Gfx::MeshSystem::IndexBuffer* OpenGL::Gfx::OpenGLVertexArray::getIndexBuffer() const noexcept
{
	return this->mIndexBuffer.get();
}
