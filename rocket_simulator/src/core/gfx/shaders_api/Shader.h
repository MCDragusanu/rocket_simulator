#pragma once
#include <iostream>
/**
 * @namespace Core::Gfx::ShaderSystem
 * @brief Provides functionality for handling shader compilation and management.
 */
namespace Core::Gfx::ShaderSystem {

    /**
     * @enum ShaderType
     * @brief Specifies different types of shaders.
     */
    enum class ShaderType {
        VertexShader,   ///< Vertex shader used for vertex processing.
        FragmentShader, ///< Fragment (pixel) shader for color calculations.
        GeometryShader  ///< Geometry shader for modifying geometry.
    };

    /**
     * @class Shader
     * @brief Abstract base class for shaders.
     * @details Handles shader compilation and management.
     */
    class Shader {
    public:
        /**
         * @brief Compiles the shader source code.
         * @param outputLog Output stream for logging errors and warnings (default: std::cerr).
         * @return True if compilation succeeds, false otherwise.
         */
        virtual bool compile(std::ostream& outputLog = std::cerr) = 0;

        /**
         * @brief Checks if the shader has been successfully compiled.
         * @return True if compiled, false otherwise.
         */
        virtual bool isCompiled() = 0;

        /**
         * @brief Retrieves the raw implementation handle for the shader.
         * @return A pointer to the underlying shader implementation.
         */
        virtual void* getRawImpl() = 0;

        /**
         * @brief Gets the type of the shader.
         * @return The shader type.
         */
        virtual ShaderType getShaderType() const noexcept = 0;

    protected:
        std::string mSourceCode; ///< Shader source code.
        bool mIsCompiled;        ///< Compilation status of the shader.
    };

    /**
     * @class VertexShader
     * @brief Represents a vertex shader.
     */
    class VertexShader : public Shader {
    protected:
        /**
         * @brief Returns the shader type as a vertex shader.
         * @return ShaderType::VertexShader
         */
        ShaderType getShaderType() const noexcept override {
            return ShaderType::VertexShader;
        }
    };

    /**
     * @class FragmentShader
     * @brief Represents a fragment (pixel) shader.
     */
    class FragmentShader : public Shader {
    protected:
        /**
         * @brief Returns the shader type as a fragment shader.
         * @return ShaderType::FragmentShader
         */
        ShaderType getShaderType() const noexcept override {
            return ShaderType::FragmentShader;
        }
    };

    /**
     * @class GeometryShader
     * @brief Represents a geometry shader.
     */
    class GeometryShader : public Shader {
    protected:
        /**
         * @brief Returns the shader type as a geometry shader.
         * @return ShaderType::GeometryShader
         */
        ShaderType getShaderType() const noexcept override {
            return ShaderType::GeometryShader;
        }
    };

}
