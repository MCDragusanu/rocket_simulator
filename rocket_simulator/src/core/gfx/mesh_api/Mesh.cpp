#include "Mesh.h"

namespace Core::Gfx::MeshSystem {

    Core::Gfx::MeshSystem::Mesh::Mesh(Core::Gfx::MeshSystem::VertexArray&& vertexArray)

    {
        mVertexArray = std::make_shared<Core::Gfx::MeshSystem::VertexArray>(vertexArray);
    }

    const Core::Gfx::MeshSystem::VertexArray* Core::Gfx::MeshSystem::Mesh::getVertexArray() const noexcept
    {
        return mVertexArray.get();
    }

    void Core::Gfx::MeshSystem::Mesh::setVisibility(bool visible)
    {
        mIsVisible = visible;
        if (visible) {
            mVertexArray->bind();
        }
        else {
            mVertexArray->unBind();
        }
    }
}