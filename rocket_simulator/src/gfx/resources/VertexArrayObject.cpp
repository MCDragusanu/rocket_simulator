#include "Resource.h"

using namespace Resources;
Resources::VertexArrayObject::VertexArrayObject(size_t offset ,size_t vertexCount, size_t vertex_stride, int vertexType) :
	OpenGLResource(-1 , ResourceType::ARRAY_VERTEX_OBJECT),
	mVertexCount(vertexCount),
	mVertexStride(vertex_stride),
	mVertexOffset(offset),
	mVertexType(vertexType)
{

}

size_t Resources::VertexArrayObject::get_vertex_count() const noexcept
{
	return this->mVertexCount;
}

size_t Resources::VertexArrayObject::get_vertex_stride() const noexcept
{
	return this->mVertexStride;
}

size_t Resources::VertexArrayObject::get_vertex_offset() const noexcept
{
	return this->mVertexOffset;
}

int Resources::VertexArrayObject::get_vertex_type() const noexcept
{
	return this->mVertexType;
}

void Resources::VertexArrayObject::release()
{
	mVertexCount = -1;
	mVertexStride = -1;
	mVertexOffset = -1;
	mVertexType = -1;
}
