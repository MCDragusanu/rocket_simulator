#include "Cube.h"
#include "../../mesh_api/VertexArray.h"

namespace Core::Gfx::EntitySystem {

    Primitives::Cube Core::Gfx::EntitySystem::Primitives::createUnitCube()
    {
        using namespace Core::Gfx::EntitySystem;
        using namespace Core::Gfx::MeshSystem;
        using namespace Core::Math;

        // Vertex data: position (x, y, z) and color (r, g, b)
        float vertexData[] = {
            // Positions         // Colors
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // 0
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // 1
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // 2
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // 3
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // 4
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // 5
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // 6
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f  // 7
        };

        // Index data for drawing triangles
        unsigned int indexData[] = {
            0, 1, 2, 2, 3, 0, // Front face
            1, 5, 6, 6, 2, 1, // Right face
            5, 4, 7, 7, 6, 5, // Back face
            4, 0, 3, 3, 7, 4, // Left face
            3, 2, 6, 6, 7, 3, // Top face
            4, 5, 1, 1, 0, 4  // Bottom face
        };

        auto indexBuffer = std::make_shared<IndexBuffer>(IndexBuffer::create(indexData, sizeof(indexData) / sizeof(indexData[0])));
        auto vertexBuffer = std::make_shared<VertexBuffer>(VertexBuffer::create(vertexData, sizeof(vertexData)));

        // Define buffer layout
        auto elements = std::vector<BufferLayoutElement>{
            { "aPos", DataType::Float3 },  // Position attribute
            { "aColor", DataType::Float3 } // Color attribute
        };
        BufferLayout layout = BufferLayout(elements);
        vertexBuffer->setLayout(layout);

        // Create and configure vertex array
        VertexArray* array = VertexArray::create();
        array->addIndexBuffer(indexBuffer);
        array->addVertexBuffer(vertexBuffer);

        // Create the mesh and cube
        Mesh mesh = Mesh(std::move(*array));
        Identity4 transform;
        return Cube(std::move(mesh), transform);
    }


	Core::Gfx::EntitySystem::Primitives::Cube::Cube(Core::Gfx::MeshSystem::Mesh&& mesh, Core::Math::Matrix4f& transform) : Entity(std :: move(mesh), transform)
	{
	}
}
