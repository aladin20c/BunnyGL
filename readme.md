- GLFW :  Window Management and Input
- GLAD : Because there are many different versions of OpenGL, the location of the functions (like glCompileShader) isn't known until your program is actually running. GLAD looks at your specific graphics card driver at runtime and finds the "address" of all the OpenGL functions so you can call them in your code
- GLM : OpenGL Mathematics. It is a "header-only" library (meaning you don't have to compile it; you just include the files). 3D graphics is 90% linear algebra (vectors and matrices). GLM is designed to match the syntax of GLSL

Libraries
GLFW : https://www.glfw.org/download.html
GLAD : https://glad.dav1d.de
GLM : https://www.opengl.org/sdk/libs/GLM/

CMAKE

MyOpenGLProject/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   └── glad.c         # Downloaded from the GLAD webservice
├── include/
│   └── glad/          # Downloaded from the GLAD webservice
│       └── glad.h


1. How CMake Works (The 3-Step Process)
Think of CMake as a translator. It takes your high-level instructions and translates them into a language your compiler understands.
The Recipe (CMakeLists.txt): You write a text file describing your source files and libraries.
The Configuration (Generating): You run CMake. It checks your system for a compiler and the libraries you asked for. It then creates a build folder.
The Build (Compiling): You tell CMake to run the actual compiler to create your .exe.

Function,What it does
cmake_minimum_required(),"Sets the version of CMake needed (e.g., 3.10)."
project(),Names your project and sets the language (C++).
add_executable(),Tells CMake the name of your final program and which .cpp files to include.
target_include_directories(),Tells the compiler where to find your .h header files.
target_link_libraries(),"Tells the linker to ""stitch"" your code together with library files (like GLFW)."
find_package(),A powerful command that searches your computer for an installed library.

cmake -B build
cmake --build build



In a professional OpenGL project, you move away from "one-off" drawing commands and toward a Data-Oriented approach. You don't want to think about "How do I draw this cube?" but rather "How do I submit this batch of data to the GPU?"


5. The "Render Loop" Logic
In a professional setup, your main loop should be very thin. It usually looks like this:
Process Input: Check if keys are pressed.
Update: Move the camera, update physics, rotate objects.
Render: * Clear the screen.
Bind the Shader.
Set Uniforms (Camera matrices).
Call mesh.Draw().
Buffer Swap: glfwSwapBuffers.




.
├── CMakeLists.txt
├── include/
│   └── BunnyGL/           <-- "BunnyGL" folder inside include
│       ├── Core/
│       │   └── Window.h
│       └── Renderer/
│           └── Shader.h
├── src/
│   ├── glad.c
│   ├── Core/
│   │   └── Window.cpp
│   └── Renderer/
│       └── Shader.cpp
└── resources/
└── shaders/

