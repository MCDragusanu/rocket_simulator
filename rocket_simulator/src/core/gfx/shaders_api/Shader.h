#pragma once
#include <iostream>
namespace Core::gfx::shaders {
	enum class ShaderType {
		VertexShader,
		FragmentShader,
		GeometryShader
	};

	class Shader {
	public:
		virtual bool compile(std::ostream& outputLog = std :: cerr) = 0;
		virtual bool isCompiled() = 0;
		virtual void* getRawImpl() = 0;
		virtual ShaderType getShaderType() const noexcept = 0;
	protected:
		
		std::string mSourceCode;
		bool mIsCompiled;
	};

	class VertexShader : public Shader {
	protected:
		ShaderType getShaderType()  const noexcept override{
			return ShaderType::VertexShader;
		}
	};

	class FragmentShader : public Shader {
	protected:
		ShaderType getShaderType()  const noexcept override {
			return ShaderType::FragmentShader;
		}
	};

	class GeometryShader : public Shader {
	protected:
		ShaderType getShaderType() const noexcept override {
			return ShaderType::GeometryShader;
		}
	};

}