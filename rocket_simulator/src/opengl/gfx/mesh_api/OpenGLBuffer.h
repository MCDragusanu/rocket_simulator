#pragma once
#include "../../../core/Gfx/mesh_api/Buffer.h"
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"
namespace OpenGL::Gfx {
	
	
	class OpenGLVertexBuffer : public Core::Gfx::MeshSystem::VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, size_t byteSize);
		~OpenGLVertexBuffer();
		void bind() override;
		void unBind()override;
		void setLayout(const Core::Gfx::MeshSystem::BufferLayout& layout) override;
		const Core::Gfx::MeshSystem::BufferLayout& getLayout()const noexcept override;
		static  GLenum dataTypeConverter(Core::Gfx::MeshSystem::DataType type);
	protected:
		unsigned int resourceUid;	
		Core::Gfx::MeshSystem::BufferLayout layout;
	};

	class OpenGLIndexBuffer : public Core::Gfx::MeshSystem::IndexBuffer {
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


