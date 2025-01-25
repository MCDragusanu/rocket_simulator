#pragma once
#include "Resource.h"
#include <string>
class Shader  : public OpenGLResource
{
public:
	Shader(const char* src, const char* shaderName, ResourceType type , bool srcIsPath = true);
	const char* get_shader_source_code()const noexcept;
	const char* get_shader_path() const noexcept;
	const char* get_shader_name() const noexcept;

protected:
	std::string    mShaderSrcCode;
	std::string	   mShaderPath;
	std::string	   mShaderName;
};

