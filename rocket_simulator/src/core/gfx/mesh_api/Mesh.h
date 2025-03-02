#pragma once
#include "Buffer.h"
#include "VertexArray.h"
namespace Core::Gfx::MeshSystem {
	class Mesh {
	public:
		Mesh(Core::Gfx::MeshSystem::VertexArray&& vertexArray);
		virtual const Core::Gfx::MeshSystem::VertexArray* getVertexArray() const noexcept ;
		virtual void setVisibility(bool visible);
	protected:
		std::shared_ptr<VertexArray> mVertexArray;
		bool mIsVisible = { false };
	};

}


