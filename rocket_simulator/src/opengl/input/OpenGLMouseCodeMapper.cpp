#include "OpenGLMouseCodeMapper.h"
namespace OpenGL::Input {

    Core::Events::MouseButton OpenGLMouseButtonMapper::translateCode(int keyCode)  {
        switch (keyCode) {
        case 0: return Core::Events::MouseButton::Left;
        case 1: return Core::Events::MouseButton::Right;
        case 2: return Core::Events::MouseButton::Middle;
        case 3: return Core::Events::MouseButton::Button4;
        case 4: return Core::Events::MouseButton::Button5;
        case 5: return Core::Events::MouseButton::Button6;
        case 6: return Core::Events::MouseButton::Button7;
        case 7: return Core::Events::MouseButton::Button8;
        default: return Core::Events::MouseButton::Count;
        }
    }
}



