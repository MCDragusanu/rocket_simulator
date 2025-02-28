#pragma once
#include <string>
#include <vector>


/**
 * @namespace Core::Gfx::Mesh
 * @brief Defines types and classes for mesh data, including buffers and layout.
 */
namespace Core::Gfx::Mesh {

    /**
     * @enum DataType
     * @brief Enumerates the different types of data used in buffers.
     * @details These types define how the vertex attributes and indices are stored in the GPU buffer.
     */
    enum class DataType {
        None = 0, ///< No data type.
        Float,    ///< Single-precision floating point value (float).
        Float2,   ///< 2D vector of floats (e.g., vec2).
        Float3,   ///< 3D vector of floats (e.g., vec3).
        Float4,   ///< 4D vector of floats (e.g., vec4).
        Mat2,     ///< 2x2 matrix of floats (e.g., mat2).
        Mat3,     ///< 3x3 matrix of floats (e.g., mat3).
        Mat4,     ///< 4x4 matrix of floats (e.g., mat4).
        Int,      ///< Integer value (int).
        Int2,     ///< 2D vector of integers (e.g., ivec2).
        Int3,     ///< 3D vector of integers (e.g., ivec3).
        Int4      ///< 4D vector of integers (e.g., ivec4).
    };

    /**
     * @struct BufferLayoutElement
     * @brief Represents an element of the buffer layout (such as a vertex attribute).
     * @details This struct defines the data type, size, and memory offset of a single element in a buffer layout.
     */
    struct BufferLayoutElement {
        std::string tag;        ///< The tag name of the element (e.g., "position", "color").
        DataType type;          ///< The data type of the element.
        size_t byteSize;        ///< The byte size of the element in the buffer.
        size_t offset;          ///< The memory offset of the element in the buffer.
        bool normalised;        ///< Flag indicating if the element is normalized.

        /**
         * @brief Calculates the byte size for a given data type.
         * @param type The data type of the element.
         * @return The byte size of the data type.
         */
        static size_t getDataTypeByteSize(DataType type);

        /**
         * @brief Constructs a BufferLayoutElement with a tag and data type.
         * @param tag The tag of the element (e.g., "position").
         * @param type The data type of the element (e.g., `DataType::Float3`).
         */
        BufferLayoutElement(const std::string& tag, DataType type);

        /**
         * @brief Returns the number of elements based on the data type.
         * @details For example, `DataType::Float3` returns 3.
         * @return The number of elements for the given data type.
         */
        size_t getElementCount() const noexcept;
    };

    /**
     * @class BufferLayout
     * @brief Represents the layout of a buffer (e.g., vertex buffer or index buffer).
     * @details Contains multiple `BufferLayoutElement` objects, each representing a single attribute or piece of data in the buffer.
     */
    class BufferLayout {
    public:
        /**
         * @brief Default constructor for an empty buffer layout.
         */
        BufferLayout();

        /**
         * @brief Constructs a BufferLayout with a list of elements.
         * @param elements A vector of BufferLayoutElement objects.
         */
        BufferLayout(const std::vector<BufferLayoutElement>& elements);

        /**
         * @brief Constructs a BufferLayout with a list of elements using move semantics.
         * @param elements A vector of BufferLayoutElement objects (moved).
         */
        BufferLayout(std::vector<BufferLayoutElement>&& elements);

        /**
         * @brief Gets the elements of the buffer layout.
         * @return A constant reference to a vector of `BufferLayoutElement` objects.
         */
        inline const std::vector<BufferLayoutElement>& getElements() const noexcept {
            return this->mElements;
        }

        /**
         * @brief Gets the stride of the buffer layout.
         * @details The stride is the total byte size of one vertex or element, including all attributes.
         * @return The stride of the buffer layout in bytes.
         */
        inline size_t getStride() {
            return this->mStride;
        }

        /**
         * @brief Gets an iterator to the beginning of the elements.
         * @return An iterator to the first `BufferLayoutElement`.
         */
        std::vector<BufferLayoutElement>::iterator begin();

        /**
         * @brief Gets an iterator to the end of the elements.
         * @return An iterator to the position after the last `BufferLayoutElement`.
         */
        std::vector<BufferLayoutElement>::iterator end();

        /**
         * @brief Gets a constant iterator to the beginning of the elements.
         * @return A constant iterator to the first `BufferLayoutElement`.
         */
        std::vector<BufferLayoutElement>::const_iterator cbegin() const;

        /**
         * @brief Gets a constant iterator to the end of the elements.
         * @return A constant iterator to the position after the last `BufferLayoutElement`.
         */
        std::vector<BufferLayoutElement>::const_iterator cend() const;

    private:
        /**
         * @brief Calculates the memory offset and stride for the buffer layout.
         * @details This function is used to calculate where each element is located in memory and the overall stride.
         */
        void calculateOffsetAndStride();

        std::vector<BufferLayoutElement> mElements; ///< The list of buffer layout elements.
        size_t mStride = { 0 }; ///< The stride of the layout in bytes.
    };

    /**
     * @struct VertexBuffer
     * @brief Represents a vertex buffer used to store vertex data.
     * @details The vertex buffer stores data like positions, colors, normals, etc., and binds it to the GPU.
     */
    struct VertexBuffer {
        /**
         * @brief Creates a VertexBuffer from the given data.
         * @param data Pointer to the data buffer.
         * @param byteSize Size of the data buffer in bytes.
         * @return A pointer to the created VertexBuffer.
         */
        static VertexBuffer* create(float* data, size_t byteSize);

        virtual ~VertexBuffer() {}; ///< Virtual destructor for cleanup.

        /**
         * @brief Binds the vertex buffer to the GPU.
         */
        virtual void bind() = 0;

        /**
         * @brief Unbinds the vertex buffer from the GPU.
         */
        virtual void unBind() = 0;

        /**
         * @brief Sets the layout of the vertex buffer.
         * @param layout The buffer layout that defines how vertex attributes are organized.
         */
        virtual void setLayout(const BufferLayout& layout) = 0;

        /**
         * @brief Gets the layout of the vertex buffer.
         * @return A constant reference to the buffer layout.
         */
        virtual const BufferLayout& getLayout() const noexcept = 0;
    };

    /**
     * @struct IndexBuffer
     * @brief Represents an index buffer used to store element indices for drawing primitives.
     * @details The index buffer contains indices that refer to vertex data in the vertex buffer.
     */
    struct IndexBuffer {
        /**
         * @brief Creates an IndexBuffer from the given data.
         * @param data Pointer to the index data.
         * @param indexCount The number of indices in the data.
         * @return A pointer to the created IndexBuffer.
         */
        static IndexBuffer* create(unsigned int* data, size_t indexCount);

        virtual ~IndexBuffer() {}; ///< Virtual destructor for cleanup.

        /**
         * @brief Binds the index buffer to the GPU.
         */
        virtual void bind() = 0;

        /**
         * @brief Unbinds the index buffer from the GPU.
         */
        virtual void unBind() = 0;

        /**
         * @brief Gets the number of indices in the buffer.
         * @return The number of indices.
         */
        virtual size_t getCount() const noexcept = 0;
    };
}
