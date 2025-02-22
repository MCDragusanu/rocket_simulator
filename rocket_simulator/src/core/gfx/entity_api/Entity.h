#pragma once


namespace Core::Gfx::EntitySystem {
	
	struct Transform {

	};

	class Entity {
	public:
		virtual const Transform& getTransform() = 0;
		virtual void setTransform(const Transform& transform) = 0;
	};
}