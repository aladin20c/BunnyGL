#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <mutex>
#include <vector>

namespace BunnyGL {

    class Shader;

    class ResourceManager {

    private:
        static std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
        static std::mutex m_ShaderMutex;

    public:
        // Shader management
        static std::shared_ptr<Shader> LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        static std::shared_ptr<Shader> GetShader(const std::string& name);
        static bool HasShader(const std::string& name);

        // Get all loaded shader names
        static std::vector<std::string> GetLoadedShaders();

        // Cleanup
        static void ClearShaders();
        static void ClearAll();

        // Prevent instantiation
        ResourceManager() = delete;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
    };
}