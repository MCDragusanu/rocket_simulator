#pragma once
#include "Buffer.h"
#include <memory>
namespace Core::Gfx::Mesh{

    /**
     * @class VertexArray
     * @brief Represents a collection of vertex buffers and an index buffer.
     * @details A vertex array binds together one or more vertex buffers and an optional index buffer.
     *          It provides methods to manage and bind/unbind buffers for rendering operations.
     */
    class VertexArray
    {
    public:
        /**
         * @brief Binds the vertex array to the current rendering context.
         * @details This method ensures that the vertex array and its associated buffers are set up for drawing operations.
         */
        virtual void bind() = 0;

        /**
         * @brief Unbinds the vertex array from the current rendering context.
         * @details This method ensures that no vertex array or its buffers are active for drawing operations.
         */
        virtual void unBind() = 0;

        /**
         * @brief Adds a vertex buffer to the vertex array.
         * @param buffer A shared pointer to a `VertexBuffer` object.
         * @details This method adds a vertex buffer, which contains vertex data (positions, colors, etc.), to the vertex array.
         */
        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;

        /**
         * @brief Adds an index buffer to the vertex array.
         * @param buffer A shared pointer to an `IndexBuffer` object.
         * @details This method adds an index buffer, which stores indices into the vertex array, allowing for indexed drawing.
         */
        virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

        /**
         * @brief Gets the index buffer of the vertex array.
         * @return A constant pointer to the `IndexBuffer` object.
         * @details This method returns the associated index buffer, which contains the indices used to draw elements in the vertex array.
         */
        virtual const IndexBuffer* getIndexBuffer() const noexcept = 0;

        /**
         * @brief Creates a new vertex array.
         * @return A pointer to the newly created `VertexArray` object.
         * @details This static method creates and returns a new instance of a vertex array.
         */
        static VertexArray* create();
    };
}

