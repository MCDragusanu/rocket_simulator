#pragma once
#include <string>
#include <vector>


/**
 * @namespace Core::Gfx::Mesh
 * @brief Defines types and classes for mesh data, including buffers and layout.
 */
namespace Core::Gfx::MeshSystem {

   
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

    
    class BufferLayoutElement {
    public:
        static size_t getDataTypeByteSize(DataType type);
        BufferLayoutElement(const std::string& tag, DataType type);
        size_t getElementCount() const noexcept;
    public:
        std::string tag;        ///< The tag name of the element (e.g., "position", "color").
        DataType type;          ///< The data type of the element.
        size_t byteSize;        ///< The byte size of the element in the buffer.
        size_t offset;          ///< The memory offset of the element in the buffer.
        bool normalised;        ///< Flag indicating if the element is normalized.
    };

    class BufferLayout {
    public:
        
        BufferLayout();
        BufferLayout(const std::vector<BufferLayoutElement>& elements);
        BufferLayout(std::vector<BufferLayoutElement>&& elements);

        inline const std::vector<BufferLayoutElement>& getElements() const noexcept {
            return this->mElements;
        }

        inline size_t getStride() {
            return this->mStride;
        }

        std::vector<BufferLayoutElement>::iterator begin();
        std::vector<BufferLayoutElement>::iterator end();
        std::vector<BufferLayoutElement>::const_iterator cbegin() const;
        std::vector<BufferLayoutElement>::const_iterator cend() const;

    private:
        void calculateOffsetAndStride();
        std::vector<BufferLayoutElement> mElements; 
        size_t mStride = { 0 }; 
    };

   
    struct VertexBuffer {
       
        static VertexBuffer* create(float* data, size_t byteSize);

        virtual ~VertexBuffer() {}; 
        virtual void bind() = 0;
        virtual void unBind() = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& getLayout() const noexcept = 0;
    };

    struct IndexBuffer {
       
        static IndexBuffer* create(unsigned int* data, size_t indexCount);

        virtual ~IndexBuffer() {};
        virtual void bind() = 0;
        virtual void unBind() = 0;
        virtual size_t getCount() const noexcept = 0;
    };
}
