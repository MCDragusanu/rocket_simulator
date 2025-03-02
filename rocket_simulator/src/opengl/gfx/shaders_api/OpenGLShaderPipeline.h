#pragma once
#include "../../../core/math/Math.h"
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
		virtual const std::vector<Core::Gfx::ShaderSystem::UniformDescriptor>& getAvailableUniformFields()  override;
		virtual Core::Gfx::ShaderSystem::UniformResult uploadUniform(const Core::Gfx::ShaderSystem::UniformDescriptor& desc) override;
		static Core::Gfx::ShaderSystem::UniformDataType translateDataType(unsigned int type)  noexcept;

	protected:
		void linkPrograms(const std::vector<unsigned int>& shaderIds);
		void attachStarted()override;
		void attachCompleted() override;
		unsigned int mProgramId;
	private:
		Core::Gfx::ShaderSystem::UniformResult validateDesc(const Core::Gfx::ShaderSystem::UniformDescriptor& desc);
		void uploadFloat(float value, unsigned int location);
		void uploadInt(int value, unsigned int location);
		void uploadBool(bool value, unsigned int location);
		void uploadVec4(const void* vec, unsigned int location);
		void uploadVec3(const void* vec, unsigned int location);
		void uploadVec2(const void* vec, unsigned int location);
		void uploadMat2(const void* mat, unsigned int location);
		void uploadMat3(const void* mat, unsigned int location);
		void uploadMat4(const void* mat, unsigned int location);
		unsigned int extractShaderUid(Core::Gfx::ShaderSystem::Shader* shader)const;
		void validateState(const std::initializer_list<Core::Gfx::ShaderSystem::PipeLineState>& validStates) const override;
		bool ensureShaderCompiled(Core::Gfx::ShaderSystem::Shader* shader) override;
		std::string getProgramInfoLog() const;
		std::vector<Core::Gfx::ShaderSystem::UniformDescriptor> uniformFields;
	};
}

