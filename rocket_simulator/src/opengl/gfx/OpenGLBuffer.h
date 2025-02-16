#pragma once
#include "../../core/gfx/Buffer.h"
#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"
namespace OpenGL::gfx {
	
	
	class OpenGLVertexBuffer : public Core :: gfx :: VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, size_t byteSize);
		~OpenGLVertexBuffer();
		void bind() override;
		void unBind()override;
		void setLayout(const Core::gfx::BufferLayout& layout) override;
		const Core::gfx::BufferLayout& getLayout()const noexcept override;
		static  GLenum dataTypeConverter(Core::gfx::DataType type);
	protected:
		unsigned int resourceUid;	
		Core::gfx::BufferLayout layout;
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


