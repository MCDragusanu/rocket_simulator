#pragma once
#include <assert.h>


/**
 * @namespace Core::Gfx::RenderingSystem
 * @brief Contains core rendering functionality for different graphics APIs.
 */
namespace Core::Gfx::RenderingSystem {

  
    enum class RenderingAPI {
        OpenGL,   ///< Use OpenGL as the rendering API.
        DirectX,  ///< Use DirectX as the rendering API.
        None      ///< No rendering API selected.
    };

    class RenderContext {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
        virtual void release() = 0;

       
        static RenderingAPI getAPI() {
            assert(instance != nullptr);
            return instance->getRenderingAPIUsed();
        }

    protected:
        static RenderContext* instance; 
        virtual RenderingAPI getRenderingAPIUsed() const noexcept = 0;
    };

}




