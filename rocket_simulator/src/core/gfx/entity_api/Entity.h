#pragma once
#include "../../math/Math.h"
#include "../mesh_api/Mesh.h"
namespace Core::Gfx::EntitySystem {
	
	struct Transform {
		const Core::Math::Matrix4f* modelTransform;
	};

	class Entity {
	public:
		Entity(Core::Gfx::MeshSystem::Mesh&& meshObj, Core::Math::Matrix4f& modelTransform);
		virtual const Transform& getTransform();
		virtual void setTransform(const Transform& transform);
		virtual const Core::Gfx::MeshSystem::Mesh* getEntityMesh() const noexcept;
	protected:
		Transform modelTransform;
		MeshSystem::Mesh mMeshObj;
	};
}