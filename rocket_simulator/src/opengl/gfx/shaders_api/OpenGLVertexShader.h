#pragma once
#include <filesystem>
#include "../../../core/gfx/shaders_api/Shader.h"
namespace OpenGL::ShadersApi {
	
	class OpenGLVertexShader  : public Core::gfx::ShadersApi::VertexShader{
		friend class OpenGLShaderPipeline;
	public:
		OpenGLVertexShader(const std::string& sourceCode);
		OpenGLVertexShader(const std::filesystem::path& filePath);
		~OpenGLVertexShader();

		bool compile(std::ostream& outputLog) override;
		bool isCompiled()override;
		void* getRawImpl()override;
	protected:
		
	private:
		unsigned int mShaderUid = {0 };
		bool mIsCompiled = { false };
		std::string mSourceCode = { "" };
	};

}


