cmake_minimum_required (VERSION 3.10)

# サポートされている場合は、MSVC コンパイラのホット リロードを有効にします。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Volante")

# C++ 標準設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ライブラリ検索
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# ソースファイル
add_executable (Volante
    "Volante.cpp"
    "Volante.h"
    "Engine.cpp"
    "Engine.h"
    "IWindow.h"
    "GLFWWindow.cpp"
    "GLFWWindow.h"
    "Shader.h"
    "Mesh.h"
)

# ライブラリのリンク
target_link_libraries(Volante PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
)

# Windows 用 OpenGL ライブラリ
if(WIN32)
    target_link_libraries(Volante PRIVATE opengl32)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Volante PROPERTY CXX_STANDARD 20)
endif()

