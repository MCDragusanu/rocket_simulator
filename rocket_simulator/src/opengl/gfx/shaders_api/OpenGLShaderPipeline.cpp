#include "OpenGLShaderPipeline.h"
#include "OpenGLFragmentShader.h"
#include "OpenGLGeometryShader.h"
#include "OpenGLVertexShader.h"
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"
#include "../../../utils/error_handlers/OpenGLErrorHandler.h"

namespace OpenGL::ShadersApi {
    OpenGLShaderPipeline::OpenGLShaderPipeline()
    {
      
    }
    OpenGLShaderPipeline::~OpenGLShaderPipeline()
    {

    }

    void OpenGLShaderPipeline::createPipeline() {
        GL_CALL(mProgramId = glCreateProgram());
        if (mProgramId == 0) {
            throw  Core::gfx::ShadersApi::ShaderPipelineException("Failed to create shader program");
        }
        mCurrentState = Core::gfx::ShadersApi::PipeLineState::Created;
    }

    void OpenGLShaderPipeline::attachShaders(const std::vector<Core::gfx::ShadersApi::Shader*>& compiledShaders) {
        validateState({ Core::gfx::ShadersApi::PipeLineState::Created,
                      Core::gfx::ShadersApi::PipeLineState::Linked });

        std::vector<unsigned int> attachedShaders;
        try {
            attachStarted();

            for (auto* shaderPtr : compiledShaders) {
                if (!shaderPtr || !ensureShaderCompiled(shaderPtr)) {
                    throw Core::gfx::ShadersApi::ShaderPipelineException("Invalid or uncompilable shader");
                }

                unsigned int shaderUid = extractShaderUid(shaderPtr);
                if (shaderUid == -1) {
                    throw Core::gfx::ShadersApi::ShaderPipelineException("Invalid shader type");
                }

                GL_CALL(glAttachShader(mProgramId, shaderUid));
                attachedShaders.push_back(shaderUid);
            }

            attachCompleted();
            linkPrograms(attachedShaders);

        }
        catch (...) {
            // Clean up on failure
            for (auto shaderId : attachedShaders) {
                GL_CALL(glDetachShader(mProgramId, shaderId));
            }
            throw;
        }
    }

    void OpenGLShaderPipeline::linkPrograms(const std::vector<unsigned int>& shaderIds) {
        GL_CALL(glLinkProgram(mProgramId));

        int success;
        glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);

        if (!success) {
            std::string infoLog = getProgramInfoLog();
            throw Core::gfx::ShadersApi::ShaderPipelineException("Link failed: " + infoLog);
        }

        // Clean up individual shaders after successful linking
        for (auto uid : shaderIds) {
            GL_CALL(glDeleteShader(uid));
        }

        mCurrentState = Core::gfx::ShadersApi::PipeLineState::Linked;
    }

    void OpenGLShaderPipeline::bind() {
        validateState({ Core::gfx::ShadersApi::PipeLineState::Linked });
        GL_CALL(glUseProgram(mProgramId));
        mCurrentState = Core::gfx::ShadersApi::PipeLineState::Binded;
    }

    void OpenGLShaderPipeline::unBind() {
        GL_CALL(glUseProgram(0));
        mCurrentState = Core::gfx::ShadersApi::PipeLineState::Unbinded;
    }

    void OpenGLShaderPipeline::release() {
        if (mProgramId != 0) {
            GL_CALL(glDeleteProgram(mProgramId));
            mProgramId = 0;
            mCurrentState = Core::gfx::ShadersApi::PipeLineState::Deleted;
        }
    }

    unsigned int OpenGLShaderPipeline::extractShaderUid(Core::gfx::ShadersApi::Shader* shader) const {
        if (!shader) return -1;

        switch (shader->getShaderType()) {
        case Core::gfx::ShadersApi::ShaderType::FragmentShader:
            return static_cast<OpenGLFragmentShader*>(shader)->mShaderUid;
        case Core::gfx::ShadersApi::ShaderType::VertexShader:
            return static_cast<OpenGLVertexShader*>(shader)->mShaderUid;
        case Core::gfx::ShadersApi::ShaderType::GeometryShader:
            return static_cast<OpenGLGeometryShader*>(shader)->mShaderUid;
        default:
            return -1;
        }
    }


    void OpenGLShaderPipeline::validateState(const std::initializer_list<Core::gfx::ShadersApi::PipeLineState>& validStates) const {
        if (std::find(validStates.begin(), validStates.end(), mCurrentState) == validStates.end()) {
            std::stringstream ss;
            ss << "Invalid pipeline state. Current state: " << static_cast<int>(mCurrentState);
            throw  Core::gfx::ShadersApi:: ShaderPipelineException(ss.str());
        }
    }

    bool OpenGLShaderPipeline::ensureShaderCompiled(Core::gfx::ShadersApi::Shader* shader) {
        if (!shader->isCompiled()) {
            return shader->compile(std::cerr);
        }
        return true;
    }

    std::string OpenGLShaderPipeline::getProgramInfoLog() const {
        int logLength;
        glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            std::vector<char> log(logLength);
            glGetProgramInfoLog(mProgramId, logLength, nullptr, log.data());
            return std::string(log.data());
        }
        return "No program info log available";
    }

    void OpenGLShaderPipeline::attachStarted() {
        mCurrentState = Core::gfx::ShadersApi::PipeLineState::Attaching;
    }

    void OpenGLShaderPipeline::attachCompleted() {
        mCurrentState = Core::gfx::ShadersApi::PipeLineState::Attached;
    }
}