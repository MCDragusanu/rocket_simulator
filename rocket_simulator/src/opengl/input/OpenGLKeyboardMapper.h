#pragma once
#include "../../core/events/EventHandler.h"
namespace OpenGL::Input {
    class OpenGLKeyCodeMapper : public Core::Events::KeyCodeMapper {

    public:
        Core::Events::KeyCode translateCode(long int keyCode) override;
        static OpenGLKeyCodeMapper getInstance() {
            static OpenGLKeyCodeMapper _instance;
            return _instance;
        }
    };
}