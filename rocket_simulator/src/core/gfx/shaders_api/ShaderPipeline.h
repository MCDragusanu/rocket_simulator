#pragma once
#include <vector>
#include <assert.h>
#include "Shader.h"

/**
 * @namespace Core::Gfx::ShaderSystem
 * @brief Provides functionality for managing shader pipelines, including state management, uniform handling, and shader attachment.
 */
namespace Core::Gfx::ShaderSystem {

    /**
     * @enum PipeLineState
     * @brief Defines the different states of a shader pipeline.
     */
    enum class PipeLineState {
        Default,   ///< Initial state of the pipeline.
        Created,   ///< Pipeline has been created.
        Attaching, ///< Shaders are being attached.
        Attached,  ///< Shaders have been attached.
        Linked,    ///< Shaders have been linked into a pipeline.
        Binded,    ///< Pipeline is bound.
        Unbinded,  ///< Pipeline is unbound.
        Deleted    ///< Pipeline has been deleted.
    };

    /**
     * @class ShaderPipelineException
     * @brief Exception class for errors occurring during shader pipeline operations.
     * @details This exception is thrown when an error occurs in creating, attaching, or linking shader programs.
     */
    class ShaderPipelineException : public std::runtime_error {
    public:
        /**
         * @brief Constructs a ShaderPipelineException with an error message.
         * @param message The error message.
         */
        explicit ShaderPipelineException(const std::string& message)
            : std::runtime_error("Shader Pipeline Error: " + message) {}
    };

    /**
     * @enum UniformDataType
     * @brief Defines different types of uniform data.
     * @details These types define the kind of data that can be used as a uniform in the shader pipeline.
     */
    enum class UniformDataType : unsigned char {
        Scalar = 0b0010000, ///< Single value (e.g., int, float).
        Vector = 0b0100000, ///< Vector of values (e.g., float3, vec4).
        Matrix = 0b1000000, ///< Matrix (e.g., mat4).
    };

    /**
     * @enum UniformResult
     * @brief Represents the possible results of uniform operations.
     */
    enum class UniformResult {
        Success,        ///< The uniform was successfully uploaded.
        NotFound,       ///< The specified uniform field was not found.
        TypeMismatch,   ///< The uniform type did not match the expected type.
        InvalidState    ///< The uniform operation cannot be performed due to the current pipeline state.
    };

    /**
     * @struct UniformDescriptor
     * @brief Describes a uniform, including its data and metadata.
     * @details This struct is used to upload uniform data to the shader pipeline.
     */
    struct UniformDescriptor {
        uint64_t bufferMetadata;  ///< Reserved space for metadata (e.g., data type, layout).
        void* buffer;             ///< Pointer to the uniform data buffer.
        UniformDataType type;     ///< Type of the uniform (e.g., Scalar, Vector, Matrix).

        /**
         * @brief Sets the size of a matrix uniform.
         * @param width The number of columns in the matrix.
         * @param height The number of rows in the matrix.
         */
        static void setMatrixSize(int width, int height);

        /**
         * @brief Sets the size of a vector uniform.
         * @param itemCount The number of elements in the vector.
         */
        static void setVectorSize(int itemCount);
    };

    /**
     * @class ShaderPipeline
     * @brief Abstract base class for managing a shader pipeline.
     * @details Handles the process of creating, attaching, linking, binding, and uploading uniforms to the shader pipeline.
     */
    class ShaderPipeline {
    public:
        /**
         * @brief Creates a new shader pipeline.
         */
        virtual void createPipeline() = 0;

        /**
         * @brief Attaches compiled shaders to the pipeline.
         * @param compiledShaders A vector of pointers to compiled shader objects.
         */
        virtual void attachShaders(const std::vector<Shader*>& compiledShaders) = 0;

        /**
         * @brief Links the attached shaders into a complete pipeline.
         * @details This function may be empty, depending on implementation.
         */
        virtual void linkPrograms() {}

        /**
         * @brief Binds the shader pipeline to be used for rendering.
         */
        virtual void bind() = 0;

        /**
         * @brief Unbinds the shader pipeline.
         */
        virtual void unBind() = 0;

        /**
         * @brief Releases resources associated with the shader pipeline.
         */
        virtual void release() = 0;

        /**
         * @brief Retrieves the available uniform fields in the shader pipeline.
         * @return A reference to a vector of uniform field names as strings.
         */
        virtual const std::vector<std::string>& getAvailableUniformFields() const = 0;

        /**
         * @brief Uploads a uniform to the shader pipeline.
         * @param fieldName The name of the uniform field.
         * @param desc A descriptor containing the uniform data and type.
         * @return The result of the upload operation.
         */
        virtual UniformResult uploadUniform(const std::string& fieldName, const UniformDescriptor& desc) = 0;

    protected:
        /**
         * @brief Validates that the current pipeline state is valid for the requested operation.
         * @param validStates A list of valid states for the current operation.
         */
        virtual void validateState(const std::initializer_list<PipeLineState>& validStates) const = 0;

        /**
         * @brief Ensures that the shader has been successfully compiled.
         * @param shader A pointer to the shader.
         * @return True if the shader is compiled, false otherwise.
         */
        virtual bool ensureShaderCompiled(Shader* shader) = 0;

        /**
         * @brief Starts the shader attachment process.
         */
        virtual void attachStarted() = 0;

        /**
         * @brief Completes the shader attachment process.
         */
        virtual void attachCompleted() = 0;

        PipeLineState mCurrentState = { PipeLineState::Default }; ///< The current state of the shader pipeline.
    };

}
