#include "Resource.h"

GLuint OpenGLResource::index = -1;

OpenGLResource::OpenGLResource(ResourceType resourceType) : mUid(issue_next_uid()) , mResourceType(resourceType)
{}

OpenGLResource::OpenGLResource(GLuint uid, ResourceType type) : mUid(-1) , mResourceType(type)
{
}

GLuint OpenGLResource::get_resource_id() const noexcept
{
	return this->mUid;
}

void OpenGLResource::set_resouce_id(GLuint uid)
{
	this->mUid = uid;
	if (index < uid) {
		//to try and avoid uid collisions
		index = uid + 1;
	}
}

ResourceType OpenGLResource::get_resource_type() const noexcept
{
	return this->mResourceType;
}

GLuint OpenGLResource::issue_next_uid()
{
	return ++index;
}
