#pragma once
#include "../../core/gfx/Buffer.h"
#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"
namespace OpenGL::Gfx {
	
	
	class OpenGLVertexBuffer : public Core :: Gfx :: VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, size_t byteSize);
		~OpenGLVertexBuffer();
		void bind() override;
		void unBind()override;
		void setLayout(const Core::Gfx::BufferLayout& layout) override;
		const Core::Gfx::BufferLayout& getLayout()const noexcept override;
		static  GLenum dataTypeConverter(Core::Gfx::DataType type);
	protected:
		unsigned int resourceUid;	
		Core::Gfx::BufferLayout layout;
	};

	class OpenGLIndexBuffer : public Core::Gfx::IndexBuffer {
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


