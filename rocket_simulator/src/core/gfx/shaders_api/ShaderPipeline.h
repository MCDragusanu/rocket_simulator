#pragma once
#include <vector>
#include <assert.h>
#include "Shader.h"

namespace Core::gfx::ShadersApi{
	enum class PipeLineState {
		Default,
		Created,
		Attaching,
		Attached,
		Linked,
		Binded,
		Unbinded,
		Deleted
	};

	class ShaderPipelineException : public std::runtime_error {
	public:
		explicit ShaderPipelineException(const std::string& message)
			: std::runtime_error("Shader Pipeline Error: " + message) {}
	};


	class ShaderPipeline {
	public:	
		
		virtual void createPipeline() = 0;
		virtual void attachShaders(const std::vector<Shader*>& compiledShaders) = 0;
		virtual void linkPrograms() {};

		virtual void bind() = 0;
		virtual void unBind() =0;
		virtual void release() = 0;


	protected:
		virtual void validateState(const std::initializer_list<PipeLineState>& validStates) const= 0;
		virtual bool ensureShaderCompiled(Shader* shader) = 0;
		virtual void attachStarted() = 0;
		virtual void attachCompleted()	= 0;
		PipeLineState mCurrentState = { PipeLineState::Default };
	private:
		
	};

}
