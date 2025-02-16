#pragma once
#include "../../core/events/EventHandler.h"
namespace OpenGL::Input {
    class OpenGLMouseButtonMapper : public  Core::Events::MouseButtonMapper {
    public:
         Core::Events::MouseButton translateCode(int keyCode) override; 
         static OpenGLMouseButtonMapper getInstance() {
             static OpenGLMouseButtonMapper instance;
             return instance;
         }
    };
}


