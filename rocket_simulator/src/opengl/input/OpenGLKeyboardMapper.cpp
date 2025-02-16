#include "OpenGLKeyboardMapper.h"

Core::Events::KeyCode OpenGL::Input::OpenGLKeyCodeMapper::translateCode(long int keyCode)
{
    switch (keyCode) {
    case 48:return Core::Events::KeyCode::Digit0;
    case 48+1:return Core::Events::KeyCode::Digit1;
    case 48+2:return Core::Events::KeyCode::Digit2;
    case 48+3:return Core::Events::KeyCode::Digit3;
    case 48+4:return Core::Events::KeyCode::Digit4;
    case 48+5:return Core::Events::KeyCode::Digit5;
    case 48+6:return Core::Events::KeyCode::Digit6;
    case 48+7:return Core::Events::KeyCode::Digit7; 
    case 48+8:return Core::Events::KeyCode::Digit8;
    case 48+9:return Core::Events::KeyCode::Digit9;
    case 65: return Core::Events::KeyCode::A;
    case 66: return Core::Events::KeyCode::B;
    case 67: return Core::Events::KeyCode::C;
    case 68: return Core::Events::KeyCode::D;
    case 69: return Core::Events::KeyCode::E;
    case 70: return Core::Events::KeyCode::F;
    case 71: return Core::Events::KeyCode::G;
    case 72: return Core::Events::KeyCode::H;
    case 73: return Core::Events::KeyCode::I;
    case 74: return Core::Events::KeyCode::J;
    case 75: return Core::Events::KeyCode::K;
    case 76: return Core::Events::KeyCode::L;
    case 77: return Core::Events::KeyCode::M;
    case 78: return Core::Events::KeyCode::N;
    case 79: return Core::Events::KeyCode::O;
    case 80: return Core::Events::KeyCode::P;
    case 81: return Core::Events::KeyCode::Q;
    case 82: return Core::Events::KeyCode::R;
    case 83: return Core::Events::KeyCode::S;
    case 84: return Core::Events::KeyCode::T;
    case 85: return Core::Events::KeyCode::U;
    case 86: return Core::Events::KeyCode::V;
    case 87: return Core::Events::KeyCode::W;
    case 88: return Core::Events::KeyCode::X;
    case 89: return Core::Events::KeyCode::Y;
    case 90: return Core::Events::KeyCode::Z;
    case 32: return Core::Events::KeyCode::Space;
    case 257: return Core::Events::KeyCode::Enter;
    case 258: return Core::Events::KeyCode::Tab;
    case 259: return Core::Events::KeyCode::Backspace;
    case 260: return Core::Events::KeyCode::Insert;
    case 261: return Core::Events::KeyCode::Delete;
    case 262: return Core::Events::KeyCode::ArrowRight;
    case 263: return Core::Events::KeyCode::ArrowLeft;
    case 264: return Core::Events::KeyCode::ArrowDown;
    case 265: return Core::Events::KeyCode::ArrowUp;
    default: return  Core::Events::KeyCode::Count;
    }
    return Core::Events::KeyCode();
}
