#pragma once

#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"

enum class ResourceType {
	BUFFER_VERTEX,
	BUFFER_INDEX,

	ARRAY_VERTEX_OBJECT,

	SHADER_MANAGER,
	SHADER_VERTEX,
	SHADER_FRAGMENT,
};

class OpenGLResource {
public:

	OpenGLResource(ResourceType type);
	OpenGLResource( GLuint uid, ResourceType type);
	GLuint get_resource_id() const noexcept;
	void set_resouce_id(GLuint uid);
	ResourceType get_resource_type() const noexcept;
	static const char* resource_type_to_string(int num) {
		switch (num) {
		case 0: return "BUFFER_VERTEX";
		case 1: return "BUFFER_INDEX";
		case 2: return "SHADER_MANAGER";
		case 3: return "SHADER_VERTEX";
		case 4: return "SHADER_PIXEL";
		default: return "Invalid ResourceType"; // Invalid input
		}
	}
protected:
	GLuint mUid;
	ResourceType mResourceType;
private:
	static GLuint index;
	static GLuint issue_next_uid();
};