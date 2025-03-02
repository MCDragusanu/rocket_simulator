#pragma once
#include "../Entity.h"
namespace Core::Gfx::EntitySystem :: Primitives {
	class Cube : public Entity
	{
	public:
		Cube(Core::Gfx::MeshSystem::Mesh&& mesh, Core::Math::Matrix4f& transform);
	};

	static Cube createUnitCube();
}

