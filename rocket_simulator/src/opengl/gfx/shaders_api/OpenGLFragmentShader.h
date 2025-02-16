#pragma once
#include <filesystem>
#include "../../../core/gfx/shaders_api/Shader.h"

namespace OpenGL::ShadersApi {

	class OpenGLFragmentShader : public Core::gfx::shaders::FragmentShader {
		friend class OpenGLShaderPipeline;
	public:
		OpenGLFragmentShader(const std::string& sourceCode);
		OpenGLFragmentShader(const std::filesystem::path& filePath);
		~OpenGLFragmentShader();

		bool compile(std::ostream& outputLog) override;
		bool isCompiled()override;
		void* getRawImpl()override;
		
	protected:
		
	private:
		unsigned int mShaderUid = { 0 };
		
	};
}

