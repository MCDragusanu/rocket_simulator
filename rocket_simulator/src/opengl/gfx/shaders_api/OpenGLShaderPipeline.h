#pragma once

#include "../../../core/gfx/shaders_api/ShaderPipeline.h"

namespace OpenGL::ShadersApi {
	class OpenGLShaderPipeline : public Core::gfx::ShadersApi::ShaderPipeline
	{
	public:
		OpenGLShaderPipeline();
		~OpenGLShaderPipeline();
		void createPipeline()override;
		void attachShaders(const std::vector<Core::gfx::ShadersApi::Shader*>& compiledShaders)override;
		
		void bind()override;
		void unBind() override;
		void release()override;


	protected:
		void linkPrograms(const std::vector<unsigned int>& shaderIds);
		void attachStarted()override;
		void attachCompleted() override;
		unsigned int mProgramId;
	private:
		unsigned int extractShaderUid(Core::gfx::ShadersApi::Shader* shader)const;
		void validateState(const std::initializer_list<Core::gfx::ShadersApi::PipeLineState>& validStates) const override;
		bool ensureShaderCompiled(Core::gfx::ShadersApi::Shader* shader) override;
		std::string getProgramInfoLog() const;
	};
}

