#pragma once
#include <filesystem>
#include "../../../core/gfx/shaders_api/Shader.h"

namespace OpenGL::ShadersApi {
	class OpenGLGeometryShader : public Core::gfx::ShadersApi::FragmentShader {
		friend class OpenGLShaderPipeline;
	public:
		OpenGLGeometryShader(const std::string& sourceCode);
		OpenGLGeometryShader(const std::filesystem::path& filePath);
		~OpenGLGeometryShader();

		bool compile(std::ostream& outputLog) override;
		bool isCompiled()override;
		void* getRawImpl()override;
	protected:
		
	private:
		unsigned int mShaderUid = { 0 };
		bool mIsCompiled = { false };
		std::string mSourceCode = { "" };
	};
}


