#pragma once
#include "Buffer.h"
#include <memory>
namespace Core::Gfx {

	class VertexArray
	{
	public:
		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;
		virtual const Core::Gfx::IndexBuffer* getIndexBuffer() const noexcept = 0;

		static VertexArray* create();
	};
}

