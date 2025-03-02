#include "Buffer.h"
#include "../../../opengl/Gfx/mesh_api/OpenGLBuffer.h"
#include "../../Gfx/renderer_api/RenderContext.h"
namespace Core::Gfx::MeshSystem {
    VertexBuffer* VertexBuffer::create(float* data, size_t byteSize) {


        switch (Core::Gfx::RenderingSystem::RenderContext::getAPI()) {

        case Core::Gfx::RenderingSystem::RenderingAPI::DirectX:
        case Core::Gfx::RenderingSystem::RenderingAPI::None:
            assert(false);
            return nullptr;
        case Core::Gfx::RenderingSystem::RenderingAPI::OpenGL: return new OpenGL::Gfx::OpenGLVertexBuffer(data, byteSize);

        }
        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(unsigned int* data, size_t indexCount) {

        switch (Core::Gfx::RenderingSystem::RenderContext::getAPI()) {

        case Core::Gfx::RenderingSystem::RenderingAPI::DirectX:
        case Core::Gfx::RenderingSystem::RenderingAPI::None:
            assert(false);
            return nullptr;
        case Core::Gfx::RenderingSystem::RenderingAPI::OpenGL: return new OpenGL::Gfx::OpenGLIndexBuffer(data, indexCount);

        }
        return nullptr;
    }

    size_t BufferLayoutElement::getDataTypeByteSize(DataType type)
    {
        constexpr auto floatSize = sizeof(float);
        constexpr auto intSize = sizeof(int);
        constexpr auto float2Size = 2 * floatSize;
        constexpr auto float3Size = 3 * floatSize;
        constexpr auto float4Size = 4 * floatSize;
        constexpr auto mat2Size = 4 * floatSize;
        constexpr auto mat3Size = 9 * floatSize;
        constexpr auto mat4Size = 16 * floatSize;
        constexpr auto int2Size = 2 * intSize;
        constexpr auto int3Size = 3 * intSize;
        constexpr auto int4Size = 4 * intSize;

        switch (type)
        {
        case DataType::Float:    return floatSize;
        case DataType::Float2:   return float2Size;
        case DataType::Float3:   return float3Size;
        case DataType::Float4:   return float4Size;
        case DataType::Mat2:     return mat2Size;
        case DataType::Mat3:     return mat3Size;
        case DataType::Mat4:     return mat4Size;
        case DataType::Int:      return intSize;
        case DataType::Int2:     return int2Size;
        case DataType::Int3:     return int3Size;
        case DataType::Int4:     return int4Size;
        case DataType::None:
        default: return 0;
        }
    }

    BufferLayoutElement::BufferLayoutElement(const std::string& tag, DataType type) :
        tag(tag), type(type), byteSize(getDataTypeByteSize(type)), offset(0),normalised(false) {}
     size_t BufferLayoutElement::getElementCount() const noexcept
    {
        switch (this->type)
        {
            case DataType::Float:    return 1;
            case DataType::Float2:   return 2;
            case DataType::Float3:   return 3;
            case DataType::Float4:   return 4;
            case DataType::Mat2:     return 4;
            case DataType::Mat3:     return 9;
            case DataType::Mat4:     return 16;
            case DataType::Int:      return 1;
            case DataType::Int2:     return 2;
            case DataType::Int3:     return 3;
            case DataType::Int4:     return 4;
            case DataType::None:
            default:return 0;

        }
    }
    
    BufferLayout::BufferLayout():mElements() , mStride(0)
    {
    }

    BufferLayout::BufferLayout(const std::vector<BufferLayoutElement>& elements):mElements(elements)
    {
        calculateOffsetAndStride();
    }


    BufferLayout::BufferLayout(std::vector<BufferLayoutElement>&& elements)
    {
        calculateOffsetAndStride();
    }


   

    std::vector <BufferLayoutElement>::iterator BufferLayout::begin()
    {
        return this->mElements.begin();
        
    }

    std::vector <BufferLayoutElement>::iterator BufferLayout::end()
    {
        return this->mElements.end();
    }

    std::vector<BufferLayoutElement>::const_iterator BufferLayout::cbegin()const
    {
         return mElements.cbegin();
    }

    std::vector<BufferLayoutElement>::const_iterator BufferLayout::cend()const 
    {
        return mElements.cend();
    }

    void BufferLayout::calculateOffsetAndStride()
    {
        size_t item_offset = 0;
        for (auto& element : mElements) {
            element.offset = item_offset;
            mStride += element.byteSize;
            item_offset += element.byteSize;
        }
    }

}