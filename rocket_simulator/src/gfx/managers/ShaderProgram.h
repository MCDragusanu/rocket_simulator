#pragma once

#include "../resources/Shader.h"

#include <iostream>
class ShaderProgram : public OpenGLResource
{
public:
	ShaderProgram();
	
	bool compile_shader(Shader& shader, std :: ostream& outputLog = std :: cout) const;

	void run_program();
protected:
	GLuint issue_handle(const Shader& shader , std::ostream& outputLog)const;
};

