#pragma once
#include "../../../core/Gfx/mesh_api/VertexArray.h"
#include <vector>
#include <memory>
namespace OpenGL::Gfx {

	class OpenGLVertexArray : public Core::Gfx::MeshSystem::VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual void bind() override;
		virtual void unBind() override;

		virtual void addVertexBuffer(const std::shared_ptr<Core::Gfx::MeshSystem::VertexBuffer>& buffer) override;
		virtual void addIndexBuffer(const std::shared_ptr<Core::Gfx::MeshSystem::IndexBuffer>& buffer) override;
		virtual const Core::Gfx::MeshSystem::IndexBuffer* getIndexBuffer() const noexcept override;
	private:
		std::vector<std::shared_ptr<Core::Gfx::MeshSystem::VertexBuffer>> mVertexBufferList;
		std::shared_ptr<Core::Gfx::MeshSystem::IndexBuffer> mIndexBuffer;
		unsigned int mVertexArrayUid;
	};
}

