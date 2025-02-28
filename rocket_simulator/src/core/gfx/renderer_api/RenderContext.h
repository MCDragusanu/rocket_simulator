#pragma once
#include <assert.h>


/**
 * @namespace Core::Gfx::RenderingSystem
 * @brief Contains core rendering functionality for different graphics APIs.
 */
namespace Core::Gfx::RenderingSystem {

    /**
     * @enum RenderingAPI
     * @brief Defines the available rendering APIs.
     */
    enum class RenderingAPI {
        OpenGL,   ///< Use OpenGL as the rendering API.
        DirectX,  ///< Use DirectX as the rendering API.
        None      ///< No rendering API selected.
    };

    /**
     * @class RenderContext
     * @brief Abstract class for managing a rendering context.
     */
    class RenderContext {
    public:
        /**
         * @brief Initializes the rendering context.
         */
        virtual void init() = 0;

        /**
         * @brief Swaps the front and back buffers for rendering.
         */
        virtual void swapBuffers() = 0;

        /**
         * @brief Releases the rendering context resources.
         */
        virtual void release() = 0;

        /**
         * @brief Gets the currently used rendering API.
         * @return The rendering API in use.
         * @note The function asserts if no instance exists.
         */
        static RenderingAPI getAPI() {
            assert(instance != nullptr);
            return instance->getRenderingAPIUsed();
        }

    protected:
        static RenderContext* instance; ///< Singleton instance of the rendering context.

        /**
         * @brief Retrieves the rendering API used by this context.
         * @return The rendering API in use.
         */
        virtual RenderingAPI getRenderingAPIUsed() const noexcept = 0;
    };

}




