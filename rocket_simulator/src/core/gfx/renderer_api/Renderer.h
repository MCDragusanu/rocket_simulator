#pragma once
#include <thread>
#include "../mesh_api/VertexArray.h"
#include "../scene_api/Scene.h"
/**
 * @namespace Core::Gfx::RenderingSystem
 * @brief Provides rendering commands and renderer management.
 */
namespace Core::Gfx::RenderingSystem {

    enum class CommandType {
        DrawIndexed  ///< Command to draw indexed geometry.
    };

    class RenderCommand {
    public:
        virtual CommandType getType() = 0;
        virtual void execute() = 0;
    };

   
    class Renderer {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
        virtual void addCommand(const RenderCommand* command) = 0;
        virtual void addCommand(RenderCommand* command) = 0;
    protected:
       
        virtual void setClearColor(float r, float g, float b) = 0;
        virtual void clear() = 0;

       
        static Renderer* pRendererAPI; ///< Renderer API instance.
    };

}
