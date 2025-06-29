#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Core/HAL/PlatformTypes.h"

namespace Volante {

class GLFWKeyMapper {
public:
    static int ToGLFWKey(KeyCode key) {
        switch (key) {
        case KeyCode::Escape:
            return GLFW_KEY_ESCAPE;
        case KeyCode::Enter:
            return GLFW_KEY_ENTER;
        case KeyCode::Tab:
            return GLFW_KEY_TAB;
        case KeyCode::Backspace:
            return GLFW_KEY_BACKSPACE;
        case KeyCode::Space:
            return GLFW_KEY_SPACE;
        case KeyCode::A:
            return GLFW_KEY_A;
        case KeyCode::B:
            return GLFW_KEY_B;
        case KeyCode::C:
            return GLFW_KEY_C;
        case KeyCode::D:
            return GLFW_KEY_D;
        case KeyCode::E:
            return GLFW_KEY_E;
        case KeyCode::F:
            return GLFW_KEY_F;
        case KeyCode::G:
            return GLFW_KEY_G;
        case KeyCode::H:
            return GLFW_KEY_H;
        case KeyCode::I:
            return GLFW_KEY_I;
        case KeyCode::J:
            return GLFW_KEY_J;
        case KeyCode::K:
            return GLFW_KEY_K;
        case KeyCode::L:
            return GLFW_KEY_L;
        case KeyCode::M:
            return GLFW_KEY_M;
        case KeyCode::N:
            return GLFW_KEY_N;
        case KeyCode::O:
            return GLFW_KEY_O;
        case KeyCode::P:
            return GLFW_KEY_P;
        case KeyCode::Q:
            return GLFW_KEY_Q;
        case KeyCode::R:
            return GLFW_KEY_R;
        case KeyCode::S:
            return GLFW_KEY_S;
        case KeyCode::T:
            return GLFW_KEY_T;
        case KeyCode::U:
            return GLFW_KEY_U;
        case KeyCode::V:
            return GLFW_KEY_V;
        case KeyCode::W:
            return GLFW_KEY_W;
        case KeyCode::X:
            return GLFW_KEY_X;
        case KeyCode::Y:
            return GLFW_KEY_Y;
        case KeyCode::Z:
            return GLFW_KEY_Z;
        case KeyCode::Num0:
            return GLFW_KEY_0;
        case KeyCode::Num1:
            return GLFW_KEY_1;
        case KeyCode::Num2:
            return GLFW_KEY_2;
        case KeyCode::Num3:
            return GLFW_KEY_3;
        case KeyCode::Num4:
            return GLFW_KEY_4;
        case KeyCode::Num5:
            return GLFW_KEY_5;
        case KeyCode::Num6:
            return GLFW_KEY_6;
        case KeyCode::Num7:
            return GLFW_KEY_7;
        case KeyCode::Num8:
            return GLFW_KEY_8;
        case KeyCode::Num9:
            return GLFW_KEY_9;
        case KeyCode::F1:
            return GLFW_KEY_F1;
        case KeyCode::F2:
            return GLFW_KEY_F2;
        case KeyCode::F3:
            return GLFW_KEY_F3;
        case KeyCode::F4:
            return GLFW_KEY_F4;
        case KeyCode::F5:
            return GLFW_KEY_F5;
        case KeyCode::F6:
            return GLFW_KEY_F6;
        case KeyCode::F7:
            return GLFW_KEY_F7;
        case KeyCode::F8:
            return GLFW_KEY_F8;
        case KeyCode::F9:
            return GLFW_KEY_F9;
        case KeyCode::F10:
            return GLFW_KEY_F10;
        case KeyCode::F11:
            return GLFW_KEY_F11;
        case KeyCode::F12:
            return GLFW_KEY_F12;
        case KeyCode::LeftShift:
            return GLFW_KEY_LEFT_SHIFT;
        case KeyCode::RightShift:
            return GLFW_KEY_RIGHT_SHIFT;
        case KeyCode::LeftControl:
            return GLFW_KEY_LEFT_CONTROL;
        case KeyCode::RightControl:
            return GLFW_KEY_RIGHT_CONTROL;
        case KeyCode::LeftAlt:
            return GLFW_KEY_LEFT_ALT;
        case KeyCode::RightAlt:
            return GLFW_KEY_RIGHT_ALT;
        case KeyCode::LeftSuper:
            return GLFW_KEY_LEFT_SUPER;
        case KeyCode::RightSuper:
            return GLFW_KEY_RIGHT_SUPER;
        case KeyCode::Up:
            return GLFW_KEY_UP;
        case KeyCode::Down:
            return GLFW_KEY_DOWN;
        case KeyCode::Left:
            return GLFW_KEY_LEFT;
        case KeyCode::Right:
            return GLFW_KEY_RIGHT;
        default:
            return GLFW_KEY_UNKNOWN;
        }
    }

    static KeyCode FromGLFWKey(int glfwKey) {
        switch (glfwKey) {
        case GLFW_KEY_ESCAPE:
            return KeyCode::Escape;
        case GLFW_KEY_ENTER:
            return KeyCode::Enter;
        case GLFW_KEY_TAB:
            return KeyCode::Tab;
        case GLFW_KEY_BACKSPACE:
            return KeyCode::Backspace;
        case GLFW_KEY_SPACE:
            return KeyCode::Space;
        case GLFW_KEY_A:
            return KeyCode::A;
        case GLFW_KEY_B:
            return KeyCode::B;
        case GLFW_KEY_C:
            return KeyCode::C;
        case GLFW_KEY_D:
            return KeyCode::D;
        case GLFW_KEY_E:
            return KeyCode::E;
        case GLFW_KEY_F:
            return KeyCode::F;
        case GLFW_KEY_G:
            return KeyCode::G;
        case GLFW_KEY_H:
            return KeyCode::H;
        case GLFW_KEY_I:
            return KeyCode::I;
        case GLFW_KEY_J:
            return KeyCode::J;
        case GLFW_KEY_K:
            return KeyCode::K;
        case GLFW_KEY_L:
            return KeyCode::L;
        case GLFW_KEY_M:
            return KeyCode::M;
        case GLFW_KEY_N:
            return KeyCode::N;
        case GLFW_KEY_O:
            return KeyCode::O;
        case GLFW_KEY_P:
            return KeyCode::P;
        case GLFW_KEY_Q:
            return KeyCode::Q;
        case GLFW_KEY_R:
            return KeyCode::R;
        case GLFW_KEY_S:
            return KeyCode::S;
        case GLFW_KEY_T:
            return KeyCode::T;
        case GLFW_KEY_U:
            return KeyCode::U;
        case GLFW_KEY_V:
            return KeyCode::V;
        case GLFW_KEY_W:
            return KeyCode::W;
        case GLFW_KEY_X:
            return KeyCode::X;
        case GLFW_KEY_Y:
            return KeyCode::Y;
        case GLFW_KEY_Z:
            return KeyCode::Z;
        case GLFW_KEY_0:
            return KeyCode::Num0;
        case GLFW_KEY_1:
            return KeyCode::Num1;
        case GLFW_KEY_2:
            return KeyCode::Num2;
        case GLFW_KEY_3:
            return KeyCode::Num3;
        case GLFW_KEY_4:
            return KeyCode::Num4;
        case GLFW_KEY_5:
            return KeyCode::Num5;
        case GLFW_KEY_6:
            return KeyCode::Num6;
        case GLFW_KEY_7:
            return KeyCode::Num7;
        case GLFW_KEY_8:
            return KeyCode::Num8;
        case GLFW_KEY_9:
            return KeyCode::Num9;
        case GLFW_KEY_F1:
            return KeyCode::F1;
        case GLFW_KEY_F2:
            return KeyCode::F2;
        case GLFW_KEY_F3:
            return KeyCode::F3;
        case GLFW_KEY_F4:
            return KeyCode::F4;
        case GLFW_KEY_F5:
            return KeyCode::F5;
        case GLFW_KEY_F6:
            return KeyCode::F6;
        case GLFW_KEY_F7:
            return KeyCode::F7;
        case GLFW_KEY_F8:
            return KeyCode::F8;
        case GLFW_KEY_F9:
            return KeyCode::F9;
        case GLFW_KEY_F10:
            return KeyCode::F10;
        case GLFW_KEY_F11:
            return KeyCode::F11;
        case GLFW_KEY_F12:
            return KeyCode::F12;
        case GLFW_KEY_LEFT_SHIFT:
            return KeyCode::LeftShift;
        case GLFW_KEY_RIGHT_SHIFT:
            return KeyCode::RightShift;
        case GLFW_KEY_LEFT_CONTROL:
            return KeyCode::LeftControl;
        case GLFW_KEY_RIGHT_CONTROL:
            return KeyCode::RightControl;
        case GLFW_KEY_LEFT_ALT:
            return KeyCode::LeftAlt;
        case GLFW_KEY_RIGHT_ALT:
            return KeyCode::RightAlt;
        case GLFW_KEY_LEFT_SUPER:
            return KeyCode::LeftSuper;
        case GLFW_KEY_RIGHT_SUPER:
            return KeyCode::RightSuper;
        case GLFW_KEY_UP:
            return KeyCode::Up;
        case GLFW_KEY_DOWN:
            return KeyCode::Down;
        case GLFW_KEY_LEFT:
            return KeyCode::Left;
        case GLFW_KEY_RIGHT:
            return KeyCode::Right;
        default:
            return KeyCode::None;
        }
    }

    static MouseButton FromGLFWButton(int button) {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT:
            return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            return MouseButton::Middle;
        case GLFW_MOUSE_BUTTON_4:
            return MouseButton::Button4;
        case GLFW_MOUSE_BUTTON_5:
            return MouseButton::Button5;
        default:
            return MouseButton::None;
        }
    }

    static InputAction FromGLFWAction(int action) {
        switch (action) {
        case GLFW_PRESS:
            return InputAction::Press;
        case GLFW_RELEASE:
            return InputAction::Release;
        case GLFW_REPEAT:
            return InputAction::Repeat;
        default:
            return InputAction::None;
        }
    }
};

} // namespace Volante