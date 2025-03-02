#pragma once
#include <vector>
#include <assert.h>
#include "Shader.h"
#include "Uniform.h"
/**
 * @namespace Core::Gfx::ShaderSystem
 * @brief Provides functionality for managing shader pipelines, including state management, uniform handling, and shader attachment.
 */
namespace Core::Gfx::ShaderSystem {


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
        virtual void bind() = 0;
        virtual void unBind() = 0;
        virtual void release() = 0;
        virtual const std::vector<const UniformField>& getAvailableUniformFields() = 0;

        
        virtual UniformResult uploadUniform(const Uniform<int>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<float>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<bool>*) = 0;

        virtual UniformResult uploadUniform(const Uniform<Core::Math::Vec2f>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::Vec3f>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::Vec4f>*) = 0;
        
        virtual UniformResult uploadUniform(const Uniform<Core::Math::Matrix2f>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::Matrix3f>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::Matrix4f>*) = 0;

        /*virtual UniformResult uploadUniform(const Uniform<Core::Math::IVec2>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::IVec3>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::IVec4>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::BVec2>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::BVec3>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Math::BVec4>*) = 0;*/

        /*virtual UniformResult uploadUniform(const Uniform<Core::Gfx::Sampler2D>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Gfx::Sampler3D>*) = 0;
        virtual UniformResult uploadUniform(const Uniform<Core::Gfx::SamplerCube>*) = 0;*/
    protected:

        virtual void validateState(const std::initializer_list<PipeLineState>& validStates) const = 0;
        virtual bool ensureShaderCompiled(Shader* shader) = 0;
        virtual void attachStarted() = 0;
        virtual void attachCompleted() = 0;

        PipeLineState mCurrentState = { PipeLineState::Default }; ///< The current state of the shader pipeline.
    };

}
