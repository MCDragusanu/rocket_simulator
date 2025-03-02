#include "Entity.h"

namespace Core::Gfx::EntitySystem {


    const Transform& Core::Gfx::EntitySystem::Entity::getTransform()
    {
        return this->modelTransform;
    }

    void Core::Gfx::EntitySystem::Entity::setTransform(const Transform& transform)
    {
        this->modelTransform = transform;
    }

    const Core::Gfx::Mesh::Mesh* Core::Gfx::EntitySystem::Entity::getEntityMesh() const noexcept
    {
        return &mMeshObj;
    }
}