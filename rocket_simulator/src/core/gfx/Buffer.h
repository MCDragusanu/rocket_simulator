#pragma once
#include "GraphicsContext.h"



namespace Core::gfx {

	
	struct VertexBuffer {
	

		static VertexBuffer* create(float* data, size_t byteSize); 
		virtual ~VertexBuffer() {};
		virtual void bind() = 0;
		virtual void unBind() = 0;

	};

	struct IndexBuffer {

		static IndexBuffer* create(unsigned int* data, size_t indexCount); 

		virtual ~IndexBuffer() {};
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual size_t getCount()const noexcept = 0;

	};
}