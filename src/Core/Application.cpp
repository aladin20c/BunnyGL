#include <BunnyGL/Core/Application.h>
#include <BunnyGL/Utils/Log.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <BunnyGL/Renderer/Renderer.h>
#include <BunnyGL/Renderer/RenderCommand.h>
#include <glm/glm.hpp>

namespace BunnyGL {

    Application::Application(const std::string& name, uint32_t width, uint32_t height)
        : m_Name(name), m_Width(width), m_Height(height)
    {
        BGL_CORE_INFO("Creating Application: ", name, " (", width, "x", height, ")");

        if (!Init()) {
            BGL_CORE_ERROR("Application failed to initialize!");
        }
    }

    Application::~Application() {
        BGL_CORE_INFO("Shutting down Application...");
        Shutdown();
    }

    bool Application::Init() {
        if (!glfwInit()) {
            BGL_CORE_ERROR("Failed to initialize GLFW!");
            return false;
        }

        // macOS Specific Hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_Window = glfwCreateWindow((int)m_Width, (int)m_Height, m_Name.c_str(), nullptr, nullptr);

        if (!m_Window) {
            BGL_CORE_ERROR("Failed to create GLFW window!");
            return false;
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            BGL_CORE_ERROR("Failed to initialize GLAD!");
            return false;
        }

        BGL_CORE_INFO("OpenGL Context Initialized.");
        BGL_CORE_INFO("Vendor:   ", glGetString(GL_VENDOR));
        BGL_CORE_INFO("Renderer: ", glGetString(GL_RENDERER));
        BGL_CORE_INFO("Version:  ", glGetString(GL_VERSION));

        // =======================================================
        // NEW: RENDERER INTEGRATION STARTS HERE
        // =======================================================

        // 1. Initialize Renderer (Enables Depth Test, Blending, etc.)
        Renderer::Init();

        // 2. Create a Triangle
        // Define Vertices (Position X, Y, Z)
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f, // Bottom Left
             0.5f, -0.5f, 0.0f, // Bottom Right
             0.0f,  0.5f, 0.0f  // Top Center
        };

        // Define Indices (Connect the dots)
        uint32_t indices[3] = { 0, 1, 2 };

        // 3. Setup Vertex Array (The Container)
        m_VertexArray.reset(new VertexArray());

        // 4. Setup Vertex Buffer (The Data)
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));

        // 5. Define Layout (How the data looks)
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // 6. Setup Index Buffer
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(new IndexBuffer(indices, 3));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // 7. Create Shader
        // Note: You can load from file or use a string for testing
        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            void main() {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            void main() {
                color = vec4(0.8, 0.2, 0.3, 1.0); // Red color
            }
        )";

        m_Shader.reset(new Shader("TriangleShader", vertexSrc, fragmentSrc));

        return true;
    }

 void Application::Run() {
         if (!m_Window) return;

         while (m_Running) {
             if (glfwWindowShouldClose(m_Window))
                 m_Running = false;

             // =======================================================
             // NEW: RENDER LOOP
             // =======================================================

             // 1. clear command
             RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
             RenderCommand::Clear();

             // 2. Create a dummy camera (Identity matrix for now)
             // Since we are drawing coordinates between -1 and 1, Identity works fine.
             glm::mat4 cameraViewProj = glm::mat4(1.0f);

             // 3. Begin Scene
             Renderer::BeginScene(cameraViewProj);

             // 4. Submit Geometry
             Renderer::Submit(m_Shader, m_VertexArray);

             // 5. End Scene
             Renderer::EndScene();

             // =======================================================

             glfwSwapBuffers(m_Window);
             glfwPollEvents();
         }
     }


    void Application::Shutdown() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
    }

}