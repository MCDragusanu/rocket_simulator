#pragma once
#include "../../core/gfx/VertexArray.h"
#include <vector>
#include <memory>
namespace OpenGL::gfx {

	class OpenGLVertexArray : public Core::gfx::VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual void bind() override;
		virtual void unBind() override;

		virtual void addVertexBuffer(const std::shared_ptr<Core::gfx::VertexBuffer>& buffer) override;
		virtual void addIndexBuffer(const std::shared_ptr<Core::gfx::IndexBuffer>& buffer) override;

	private:
		std::vector<std::shared_ptr<Core::gfx::VertexBuffer>> mVertexBufferList;
		std::shared_ptr<Core::gfx::IndexBuffer> mIndexBuffer;
		unsigned int mVertexArrayUid;
	};
}

