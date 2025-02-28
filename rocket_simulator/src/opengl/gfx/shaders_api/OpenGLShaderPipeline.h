#pragma once

#include "../../../core/Gfx/shaders_api/ShaderPipeline.h"

namespace OpenGL::ShadersApi {
	class OpenGLShaderPipeline : public Core::Gfx::ShaderSystem::ShaderPipeline
	{
	public:
		OpenGLShaderPipeline();
		~OpenGLShaderPipeline();
		void createPipeline()override;
		void attachShaders(const std::vector<Core::Gfx::ShaderSystem::Shader*>& compiledShaders)override;
		
		void bind()override;
		void unBind() override;
		void release()override;


	protected:
		void linkPrograms(const std::vector<unsigned int>& shaderIds);
		void attachStarted()override;
		void attachCompleted() override;
		unsigned int mProgramId;
	private:
		unsigned int extractShaderUid(Core::Gfx::ShaderSystem::Shader* shader)const;
		void validateState(const std::initializer_list<Core::Gfx::ShaderSystem::PipeLineState>& validStates) const override;
		bool ensureShaderCompiled(Core::Gfx::ShaderSystem::Shader* shader) override;
		std::string getProgramInfoLog() const;
	};
}

