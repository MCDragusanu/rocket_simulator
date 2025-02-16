#pragma once
#include "../../core/gfx/Buffer.h"

namespace OpenGL::gfx {
	
	
	class OpenGLVertexBuffer : public Core :: gfx :: VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, size_t byteSize);
		~OpenGLVertexBuffer();
		void bind() override;
		void unBind()override;
	protected:
		unsigned int resourceUid;
	};

	class OpenGLIndexBuffer : public Core::gfx::IndexBuffer {
	public:
		
		OpenGLIndexBuffer(unsigned int * data, size_t indexCount);
		~OpenGLIndexBuffer();

		void bind() override;
		void unBind()override;
		size_t getCount() const noexcept override;
	protected:
		unsigned int resourceUid;
		size_t mIndicesCount;

	};
}


