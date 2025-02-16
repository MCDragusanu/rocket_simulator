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
            throw  Core::gfx::shaders::ShaderPipelineException("Failed to create shader program");
        }
        mCurrentState = Core::gfx::shaders::PipeLineState::Created;
    }

    void OpenGLShaderPipeline::attachShaders(const std::vector<Core::gfx::shaders::Shader*>& compiledShaders) {
        validateState({ Core::gfx::shaders::PipeLineState::Created,
                      Core::gfx::shaders::PipeLineState::Linked });

        std::cerr << "Vaidation State Passed" << "\n";
        std::cerr << "programUid : " << mProgramId << "\n";
        std::vector<unsigned int> attachedShaders;
        try {
            attachStarted();

            for (auto* shaderPtr : compiledShaders) {
                if (!shaderPtr || !ensureShaderCompiled(shaderPtr)) {
                    throw Core::gfx::shaders::ShaderPipelineException("Invalid or uncompilable shader");
                }

                unsigned int shaderUid = extractShaderUid(shaderPtr);
                std::cerr << "ShaderUid = " << shaderUid << "\n";
                if (shaderUid == 0) {
                    throw Core::gfx::shaders::ShaderPipelineException("Invalid shader type");
                }

                GL_CALL(glAttachShader(mProgramId, shaderUid));
                attachedShaders.push_back(shaderUid);
                std::cerr << "Attached a shader!" << "\n";


            }
            std::cerr << "Preparing Linking!" << "\n";
            GL_CALL(glLinkProgram(mProgramId));

            int success;
            glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);

            if (!success) {
                std::cerr << "Failed Linking!" << "\n";
                std::string infoLog = getProgramInfoLog();
                std::cerr << infoLog;
                throw Core::gfx::shaders::ShaderPipelineException("Link failed: " + infoLog);
            }
            else {
                std::cerr << "Shader Linked!" << "\n";
            }

            attachCompleted();
            std::cerr << "Linking finished!" << "\n";
            mCurrentState = Core::gfx::shaders::PipeLineState::Linked;
        }
        catch (...) {
            for (auto shaderId : attachedShaders) {
                GL_CALL(glDetachShader(mProgramId, shaderId));
            }
            throw;
        }
    }

    
    void OpenGLShaderPipeline::linkPrograms(const std::vector<unsigned int>& shaderIds) {
        /*std::cerr << "Preparing Linking!" << "\n";
        GL_CALL(glLinkProgram(mProgramId));

        int success;
        glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);

        if (!success) {
            std::cerr << "Failed Linking!" << "\n";
            std::string infoLog = getProgramInfoLog();
            std::cerr << infoLog;
            throw Core::gfx::shaders::ShaderPipelineException("Link failed: " + infoLog);
        }

        // Clean up individual shaders after successful linking
        for (auto uid : shaderIds) {
            GL_CALL(glDeleteShader(uid));
        }

        mCurrentState = Core::gfx::shaders::PipeLineState::Linked;
        std::cerr << "Linking Completed!" << "\n";*/
    }


    void OpenGLShaderPipeline::bind() {
        validateState({ Core::gfx::shaders::PipeLineState::Linked });
        GL_CALL(glUseProgram(mProgramId));
        mCurrentState = Core::gfx::shaders::PipeLineState::Binded;
    }

    void OpenGLShaderPipeline::unBind() {
        GL_CALL(glUseProgram(0));
        mCurrentState = Core::gfx::shaders::PipeLineState::Unbinded;
    }

    void OpenGLShaderPipeline::release() {
        if (mProgramId != 0) {
            GL_CALL(glDeleteProgram(mProgramId));
            mProgramId = 0;
            mCurrentState = Core::gfx::shaders::PipeLineState::Deleted;
        }
    }

    unsigned int OpenGLShaderPipeline::extractShaderUid(Core::gfx::shaders::Shader* shader) const {
        if (!shader) return 0;

        switch (shader->getShaderType()) {
        case Core::gfx::shaders::ShaderType::FragmentShader:
            return static_cast<OpenGLFragmentShader*>(shader)->mShaderUid;
        case Core::gfx::shaders::ShaderType::VertexShader:
            return static_cast<OpenGLVertexShader*>(shader)->mShaderUid;
        case Core::gfx::shaders::ShaderType::GeometryShader:
            return static_cast<OpenGLGeometryShader*>(shader)->mShaderUid;
        default:
            return 0;
        }
    }


    void OpenGLShaderPipeline::validateState(const std::initializer_list<Core::gfx::shaders::PipeLineState>& validStates) const {
        if (std::find(validStates.begin(), validStates.end(), mCurrentState) == validStates.end()) {
            std::stringstream ss;
            ss << "Invalid pipeline state. Current state: " << static_cast<int>(mCurrentState);
            throw  Core::gfx::shaders:: ShaderPipelineException(ss.str());
        }
    }

    bool OpenGLShaderPipeline::ensureShaderCompiled(Core::gfx::shaders::Shader* shader) {
        if (!shader->isCompiled()) {
            return shader->compile(std::cerr);
        }
        return true;
    }

    std::string OpenGLShaderPipeline::getProgramInfoLog() const {
        int logLength = 512;
        glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            std::vector<char> log(logLength);
            glGetProgramInfoLog(mProgramId, logLength, nullptr, log.data());
            return std::string(log.data());
        }
        return "No program info log available";
    }

    void OpenGLShaderPipeline::attachStarted() {
        mCurrentState = Core::gfx::shaders::PipeLineState::Attaching;
    }

    void OpenGLShaderPipeline::attachCompleted() {
        mCurrentState = Core::gfx::shaders::PipeLineState::Attached;
    }
}