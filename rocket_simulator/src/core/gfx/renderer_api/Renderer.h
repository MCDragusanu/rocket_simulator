#pragma once
#include <thread>
#include "../VertexArray.h"
#include "../scene_api/Scene.h"
/**
 * @namespace Core::Gfx::RenderingSystem
 * @brief Provides rendering commands and renderer management.
 */
namespace Core::Gfx::RenderingSystem {

    /**
     * @enum CommandType
     * @brief Represents different types of rendering commands.
     */
    enum class CommandType {
        DrawIndexed  ///< Command to draw indexed geometry.
    };

    /**
     * @class RenderCommand
     * @brief Abstract class representing a rendering command.
     * @details Each render command encapsulates an action, such as drawing indexed geometry.
     */
    class RenderCommand {
        friend class Renderer;

    public:
        /**
         * @brief Retrieves the type of the render command.
         * @return The command type.
         */
        virtual CommandType getType() = 0;

        /**
         * @brief Executes the render command.
         */
        virtual void execute() = 0;

        /**
         * @brief Sets the renderer API instance for executing commands.
         * @param instance Pointer to the renderer instance.
         */
        static void setRendererAPI(Renderer* instance);

    protected:
        static Renderer* pRendererAPI; ///< Renderer API instance used by commands.
    };

    /**
     * @class Renderer
     * @brief Abstract base class for handling rendering operations.
     */
    class Renderer {
        friend class RenderCommand;

    public:
        /**
         * @brief Begins rendering a scene.
         * @param scene The scene to be rendered.
         */
        virtual void beginScene(const Core::Gfx::SceneSystem::Scene& scene) = 0;

        /**
         * @brief Ends the current scene rendering.
         */
        virtual void endScene() = 0;

        /**
         * @brief Submits all recorded render commands for execution.
         */
        virtual void submit() = 0;

    protected:
        /**
         * @brief Retrieves the list of render commands for a given scene.
         * @param scene The scene from which to get commands.
         * @return A reference to a vector of render commands.
         */
        virtual const std::vector<RenderCommand*>& getCommands(const Core::Gfx::SceneSystem::Scene& scene) const = 0;

        /**
         * @brief Sets the background clear color.
         * @param r Red component (0.0 - 1.0).
         * @param g Green component (0.0 - 1.0).
         * @param b Blue component (0.0 - 1.0).
         */
        virtual void setClearColor(float r, float g, float b) = 0;

        /**
         * @brief Clears the screen using the current clear color.
         */
        virtual void clear() = 0;

        /**
         * @brief Sets the rendering thread.
         * @param renderingThread Reference to the thread handling rendering.
         */
        virtual void setThread(std::thread& renderingThread) = 0;

        /**
         * @brief Adds a render command to the execution queue.
         * @param command Pointer to the render command.
         */
        virtual void addCommand(RenderCommand* command) = 0;

        /**
         * @brief Executes all stored render commands.
         */
        virtual void executeCommands() = 0;

        /**
         * @brief Issues a draw call using indexed rendering.
         * @param vertexArray The vertex array to be drawn.
         */
        virtual void drawIndexed(const std::shared_ptr<Core::Gfx::VertexArray>& vertexArray) = 0;

        static Renderer* pRendererAPI; ///< Renderer API instance.
    };

}
