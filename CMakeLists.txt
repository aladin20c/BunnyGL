cmake_minimum_required(VERSION 3.15)
project(BunnyGL LANGUAGES C CXX)

# Standard C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Fetch GLFW ---
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# --- 2. Organize Source Files ---
# file(GLOB_RECURSE ...) searches all subfolders in /src for .cpp files.
# This way, src/Renderer/Shader.cpp is added automatically.
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

# --- 3. Define the Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 4. Set Include Paths ---
target_include_directories(${PROJECT_NAME} PRIVATE
    include          # This allows #include <BunnyGL/Core/Window.h>
    external         # For glad.h
)

# --- 5. Link Libraries ---
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)

# --- 6. (Optional) Copy Shaders to Build Folder ---
# This ensures your program can find your .glsl files when running
# --- file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})