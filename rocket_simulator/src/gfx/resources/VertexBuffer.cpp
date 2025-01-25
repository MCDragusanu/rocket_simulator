#include "VertexBuffer.h"
#include <assert.h>
#include "../../../include/glfw/glfw3.h"
#include <stdexcept>
#include <iostream>

VertexBuffer::VertexBuffer(std::unique_ptr<float[]>&& buffer, size_t vertexCount, size_t vertexStride, int normalization) :
    OpenGLResource(-1,ResourceType::BUFFER_VERTEX),
    pBuffer(std::move(buffer)),
    mVertexStride(vertexStride), 
    mVertexCount(vertexCount) ,
    mFloatCount(vertexCount * (vertexStride / sizeof(float))),
    mByteSize(vertexCount * vertexStride),
    mWithNormalisation(normalization ? GL_TRUE : GL_FALSE )
{
    assert(this->mVertexCount > 0);
    assert(this->mVertexStride > 0);
    assert(this->pBuffer.get() != nullptr);
#ifdef _DEBUG
    print_buffer_content();
#endif // _DEBUG
}

VertexBuffer::VertexBuffer(size_t vertexCount, size_t vertexStride, int normalization) :
    OpenGLResource(ResourceType::BUFFER_VERTEX),
    mVertexStride(vertexStride),
    mVertexCount(vertexCount),
    mByteSize(vertexCount* vertexStride),
    mFloatCount(vertexCount* (vertexStride / sizeof(float))),
    mWithNormalisation(normalization ? GL_TRUE : GL_FALSE)
{
   
    //allocating the memory for the buffer
    pBuffer = std::make_unique<float[]>(mFloatCount);
    assert(this->mVertexCount > 0);
    assert(this->mVertexStride > 0);
    assert(this->pBuffer.get() != nullptr);
#ifdef _DEBUG
    print_buffer_content();
#endif // _DEBUG

}



const float* VertexBuffer::get_buffer() const noexcept
{
    return pBuffer.get();
}

float VertexBuffer::at(size_t index) const
{
#ifndef _DEBUG
    assert(index < mFloatCount);
#endif
    if (index >= mFloatCount) {
        throw std::out_of_range("Index out of range");
    }
    return pBuffer[index];
}

float& VertexBuffer::at(size_t index)
{
#ifndef _DEBUG
    assert(index < mFloatCount);
#endif
    if (index >= mFloatCount) {
        throw std::out_of_range("Index out of range");
    }
    return pBuffer[index];
}

float VertexBuffer::operator[](size_t index) const
{
    return at(index);
}

float& VertexBuffer::operator[](size_t index)
{
    return at(index);
}

size_t VertexBuffer::get_float_count() const noexcept
{
    return this->mFloatCount;
}

size_t VertexBuffer::get_vertex_stride() const noexcept
{
    return this->mVertexStride;
}

size_t VertexBuffer::get_vertex_count() const noexcept
{
    return this->mVertexCount;
}

size_t VertexBuffer::get_byte_size() const noexcept
{
    return this->mFloatCount * sizeof(float);
}

void VertexBuffer::print_buffer_content()const noexcept
{
    std::cout << "\n[";
    for (int i = 0; i < mFloatCount; i++) {
        std::cout << pBuffer[i] << " ";
    }
    std::cout << "]\n";
}
