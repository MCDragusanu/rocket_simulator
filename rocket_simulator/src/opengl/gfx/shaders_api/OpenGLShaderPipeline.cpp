#include "OpenGLShaderPipeline.h"
#include "OpenGLFragmentShader.h"
#include "OpenGLGeometryShader.h"
#include "OpenGLVertexShader.h"
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"
#include "../../../utils/error_handlers/OpenGLErrorHandler.h"

namespace OpenGL::ShadersApi {
    OpenGLShaderPipeline::OpenGLShaderPipeline() :uniformFields(), mProgramId(-1)
    {

    }
    OpenGLShaderPipeline::~OpenGLShaderPipeline()
    {

    }

    void OpenGLShaderPipeline::createPipeline() {
        GL_CALL(mProgramId = glCreateProgram());
        if (mProgramId == 0) {
            throw  Core::Gfx::ShaderSystem::ShaderPipelineException("Failed to create shader program");
        }
        mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Created;
    }

    void OpenGLShaderPipeline::attachShaders(const std::vector<Core::Gfx::ShaderSystem::Shader*>& compiledShaders) {
        validateState({ Core::Gfx::ShaderSystem::PipeLineState::Created,
                      Core::Gfx::ShaderSystem::PipeLineState::Linked });

        std::cerr << "Vaidation State Passed" << "\n";
        std::cerr << "programUid : " << mProgramId << "\n";
        std::vector<unsigned int> attachedShaders;
        try {
            attachStarted();

            for (auto* shaderPtr : compiledShaders) {
                if (!shaderPtr || !ensureShaderCompiled(shaderPtr)) {
                    throw Core::Gfx::ShaderSystem::ShaderPipelineException("Invalid or uncompilable shader");
                }

                unsigned int shaderUid = extractShaderUid(shaderPtr);
                std::cerr << "ShaderUid = " << shaderUid << "\n";
                if (shaderUid == 0) {
                    throw Core::Gfx::ShaderSystem::ShaderPipelineException("Invalid shader type");
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
                throw Core::Gfx::ShaderSystem::ShaderPipelineException("Link failed: " + infoLog);
            }
            else {
                std::cerr << "Shader Linked!" << "\n";
            }

            attachCompleted();
            std::cerr << "Linking finished!" << "\n";
            mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Linked;
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
            throw Core::Gfx::ShaderSystem::ShaderPipelineException("Link failed: " + infoLog);
        }

        // Clean up individual ShaderSystem after successful linking
        for (auto uid : shaderIds) {
            GL_CALL(glDeleteShader(uid));
        }

        mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Linked;
        std::cerr << "Linking Completed!" << "\n";*/
    }


    void OpenGLShaderPipeline::bind() {
        validateState({ Core::Gfx::ShaderSystem::PipeLineState::Linked });
        GL_CALL(glUseProgram(mProgramId));
        mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Binded;
    }

    void OpenGLShaderPipeline::unBind() {
        GL_CALL(glUseProgram(0));
        mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Unbinded;
    }

    void OpenGLShaderPipeline::release() {
        if (mProgramId != 0) {
            GL_CALL(glDeleteProgram(mProgramId));
            mProgramId = 0;
            mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Deleted;
        }
    }

    const std::vector<Core::Gfx::ShaderSystem::UniformDescriptor>& OpenGLShaderPipeline::getAvailableUniformFields()
    {
        GLint uniformCount;
        glGetProgramiv(mProgramId, GL_ACTIVE_UNIFORMS, &uniformCount);

        auto result = std::vector<Core::Gfx::ShaderSystem::UniformDescriptor>();
        uniformFields.clear();
        for (int i = 0; i < uniformCount; i++) {
            char name[256];  // Buffer for uniform name
            GLsizei length;
            GLint size;
            GLenum type;

            glGetActiveUniform(mProgramId, i, sizeof(name), &length, &size, &type, name);

            GLint location = glGetUniformLocation(mProgramId, name);
            Core::Gfx::ShaderSystem::UniformDescriptor desc{};
            desc.buffer = nullptr;
            desc.type = translateDataType(type);
            desc.uniformName = name;
            desc.uniformLocation = location;
            desc.uniformSize = size;
            result.push_back(desc);
        }
        this->uniformFields = result;
        return result;
    }

    Core::Gfx::ShaderSystem::UniformResult OpenGLShaderPipeline::uploadUniform(const Core::Gfx::ShaderSystem::UniformDescriptor& desc)
    {
        using namespace  Core::Gfx::ShaderSystem;



    }

    Core::Gfx::ShaderSystem::UniformDataType OpenGLShaderPipeline::translateDataType(unsigned int type) noexcept
    {
        using namespace  Core::Gfx::ShaderSystem;
        switch (type)
        {
            // Scalar types
        case GL_FLOAT:  return UniformDataType::Float;
        case GL_INT:    return UniformDataType::Int;
        case GL_BOOL:   return UniformDataType::Bool;

            // Vector types
        case GL_FLOAT_VEC2: return UniformDataType::Vec2;
        case GL_FLOAT_VEC3: return UniformDataType::Vec3;
        case GL_FLOAT_VEC4: return UniformDataType::Vec4;
        case GL_INT_VEC2:   return UniformDataType::IVec2;
        case GL_INT_VEC3:   return UniformDataType::IVec3;
        case GL_INT_VEC4:   return UniformDataType::IVec4;
        case GL_BOOL_VEC2:  return UniformDataType::BVec2;
        case GL_BOOL_VEC3:  return UniformDataType::BVec3;
        case GL_BOOL_VEC4:  return UniformDataType::BVec4;

            // Matrix types
        case GL_FLOAT_MAT2: return UniformDataType::Mat2;
        case GL_FLOAT_MAT3: return UniformDataType::Mat3;
        case GL_FLOAT_MAT4: return UniformDataType::Mat4;

            // Samplers
        case GL_SAMPLER_2D: return UniformDataType::Sampler2D;
        case GL_SAMPLER_3D: return UniformDataType::Sampler3D;
        case GL_SAMPLER_CUBE: return UniformDataType::SamplerCube;

        default: return UniformDataType::Unknown;
        }
    }


    void OpenGLShaderPipeline::uploadMat4(const void* mat, unsigned int location)
    {
    }

    unsigned int OpenGLShaderPipeline::extractShaderUid(Core::Gfx::ShaderSystem::Shader* shader) const {
        if (!shader) return 0;

        switch (shader->getShaderType()) {
        case Core::Gfx::ShaderSystem::ShaderType::FragmentShader:
            return static_cast<OpenGLFragmentShader*>(shader)->mShaderUid;
        case Core::Gfx::ShaderSystem::ShaderType::VertexShader:
            return static_cast<OpenGLVertexShader*>(shader)->mShaderUid;
        case Core::Gfx::ShaderSystem::ShaderType::GeometryShader:
            return static_cast<OpenGLGeometryShader*>(shader)->mShaderUid;
        default:
            return 0;
        }
    }


    void OpenGLShaderPipeline::validateState(const std::initializer_list<Core::Gfx::ShaderSystem::PipeLineState>& validStates) const {
        if (std::find(validStates.begin(), validStates.end(), mCurrentState) == validStates.end()) {
            std::stringstream ss;
            ss << "Invalid pipeline state. Current state: " << static_cast<int>(mCurrentState);
            throw  Core::Gfx::ShaderSystem::ShaderPipelineException(ss.str());
        }
    }

    bool OpenGLShaderPipeline::ensureShaderCompiled(Core::Gfx::ShaderSystem::Shader* shader) {
        if (!shader->isCompiled()) {
            return shader->compile(std::cerr);
        }
        return true;
    }

    Core::Gfx::ShaderSystem::UniformResult OpenGLShaderPipeline::validateDesc(const Core::Gfx::ShaderSystem::UniformDescriptor& desc) {
        using namespace  Core::Gfx::ShaderSystem;
        if (desc.buffer == nullptr) {
            return UniformResult::NotFound;
        }
        if (uniformFields.size() == 0) {
            uniformFields = getAvailableUniformFields();
        }
        //checking if a valid location is provided
        bool isFound = false;
        bool invalidType = false;
        bool invalidSize = false;
        bool invalidLocation = false;
        bool invalidName = false;
        for (const auto& field : uniformFields) {

            invalidType = !(field.type == desc.type);
            invalidSize = !(field.uniformSize == desc.uniformSize);
            invalidLocation = !(field.uniformLocation == desc.uniformLocation);
            invalidName = !(field.uniformName == desc.uniformName);
            isFound = !(invalidLocation && invalidType && invalidSize && invalidName);
            if (isFound) break;
        }

        //remains to translate the propper error
        if (!isFound) {
            return  UniformResult::NotFound;
        }
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

    void OpenGLShaderPipeline::uploadFloat(float value, unsigned int location)
    {
        glUniform1f(location, value);
    }

    void OpenGLShaderPipeline::uploadInt(int value, unsigned int location)
    {
    }

    void OpenGLShaderPipeline::uploadBool(bool value, unsigned int location)
    {
    }

    void OpenGLShaderPipeline::uploadVec4(const void* vec, unsigned int location)
    {

    }

    void OpenGLShaderPipeline::uploadVec3(const void* vec, unsigned int location)
    {
    }

    void OpenGLShaderPipeline::uploadVec2(const void* vec, unsigned int location)
    {
    }

    void OpenGLShaderPipeline::uploadMat2(const void* mat, unsigned int location)
    {
    }

    void OpenGLShaderPipeline::uploadMat3(const void* mat, unsigned int location)
    {
    }

    void OpenGLShaderPipeline::attachStarted() {
        mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Attaching;
    }

    void OpenGLShaderPipeline::attachCompleted() {
        mCurrentState = Core::Gfx::ShaderSystem::PipeLineState::Attached;
    }
}