#pragma once
#include <memory>
#include "Resource.h"

class VertexBuffer : public OpenGLResource
{
public:
	
	VertexBuffer(std::unique_ptr<float[]>&& buffer, size_t vertexCount, size_t vertexStride, int normalization = 0);
	VertexBuffer(size_t vertexCount, size_t vertexStride, int normalization = 0);
	
	VertexBuffer& operator=(VertexBuffer& other) = delete;
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer operator=(VertexBuffer other) = delete;


	const float*		get_buffer() const noexcept;
	float				at(size_t index) const;
	float&				at(size_t index);

	float				operator[](size_t index) const;
	float&				operator[](size_t index);

	size_t				get_float_count() const noexcept;
	size_t				get_vertex_stride() const noexcept;
	size_t				get_vertex_count() const noexcept;
	size_t				get_byte_size()const noexcept;

	void				print_buffer_content()const noexcept;
protected:
	std::unique_ptr<float[]>		pBuffer;
	size_t							mVertexCount;
	size_t							mVertexStride;
	size_t							mFloatCount;
	size_t							mByteSize;
	int								mWithNormalisation;
};

