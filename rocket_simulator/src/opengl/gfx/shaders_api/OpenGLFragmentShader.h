#pragma once
#include <filesystem>
#include "../../../core/Gfx/shaders_api/Shader.h"

namespace OpenGL::ShadersApi {

	class OpenGLFragmentShader : public Core::Gfx::ShaderSystem::FragmentShader {
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

