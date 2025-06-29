#pragma once

namespace Volante {

enum class PlatformType {
    None = -1,
    Windows,
    Mac,
    Linux,
    Max,
};

enum class RHIType {
    None = -1,
    OpenGL,
    Vulkan,
    D3D12,
    Metal,
    Max
};

enum class KeyCode {
    None = -1,

    Escape,
    Enter,
    Tab,
    Backspace,
    Space,

    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    Num0, Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8, Num9,

    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,

    LeftShift, RightShift,
    LeftControl, RightControl,
    LeftAlt, RightAlt,
    LeftSuper, RightSuper,

    Up, Down, Left, Right,

    Count
};

enum class MouseButton {
    None = -1,
    Left,
    Right,
    Middle,
    Button4,
    Button5,
    Count
};

enum class InputAction {
    None = -1,
    Release,
    Press,
    Repeat,
    Count
};

}
