#include "OpenGLGeometryShader.h"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"
#include "../../../utils/error_handlers/OpenGLErrorHandler.h"

namespace OpenGL::ShadersApi {


	OpenGLGeometryShader::OpenGLGeometryShader(const std::string& sourceCode)
	{
		this->mSourceCode = sourceCode;
	}

	OpenGLGeometryShader::OpenGLGeometryShader(const std::filesystem::path& filePath)
	{
		std::stringstream buffer;
		auto stream = std::ifstream(filePath);
		if (not stream) {
			throw std::invalid_argument("Failed to open file : " + filePath.string());
		}
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		stream.open(filePath);
		buffer << stream.rdbuf();
		stream.close();
		this->mSourceCode = buffer.str();
	}

	OpenGLGeometryShader::~OpenGLGeometryShader()
	{
	}

	bool OpenGLGeometryShader::compile(std::ostream& outputLog)
	{
		unsigned int shaderType = GL_GEOMETRY_SHADER;
		auto sourceCode = mSourceCode.c_str();
		GL_CALL(this->mShaderUid = glCreateShader(shaderType));
		GL_CALL(glShaderSource(mShaderUid, 1, &sourceCode, nullptr));
		GL_CALL(glCompileShader(mShaderUid));

		int success;
		char infoLog[512];
		glGetShaderiv(mShaderUid, GL_COMPILE_STATUS, &success);
		mIsCompiled = success == 1;
		if (!success) {
			glGetShaderInfoLog(mShaderUid, 512, nullptr, infoLog);
			outputLog << "Error: Shader Compilation Failed!\n";
			outputLog << "Info: " << infoLog << "\n";
			outputLog << "Shader Name: " << "Vertex Shader" << "\n";
			glDeleteShader(mShaderUid);
			return false;
		}
		return true;

	}

	bool OpenGLGeometryShader::isCompiled()
	{
		return mIsCompiled;
	}

	void* OpenGLGeometryShader::getRawImpl()
	{
		return (this);
	}
}