#pragma once
#include "../../core/gfx/VertexArray.h"
#include <vector>
#include <memory>
namespace OpenGL::Gfx {

	class OpenGLVertexArray : public Core::Gfx::VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual void bind() override;
		virtual void unBind() override;

		virtual void addVertexBuffer(const std::shared_ptr<Core::Gfx::VertexBuffer>& buffer) override;
		virtual void addIndexBuffer(const std::shared_ptr<Core::Gfx::IndexBuffer>& buffer) override;
		virtual const Core::Gfx::IndexBuffer* getIndexBuffer() const noexcept override;
	private:
		std::vector<std::shared_ptr<Core::Gfx::VertexBuffer>> mVertexBufferList;
		std::shared_ptr<Core::Gfx::IndexBuffer> mIndexBuffer;
		unsigned int mVertexArrayUid;
	};
}

