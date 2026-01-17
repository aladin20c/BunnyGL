#include <BunnyGL/Resources/ResourceManager.hpp>
#include <BunnyGL/Renderer/Shader.hpp>
#include <BunnyGL/Core/Log.hpp>

#include <algorithm>

namespace BunnyGL {

    // Initialize static members
    std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::m_Shaders;
    std::mutex ResourceManager::m_ShaderMutex;

    // Load or get cached shader
    std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& name,const std::string& vertexPath,  const std::string& fragmentPath) {

        std::lock_guard<std::mutex> lock(m_ShaderMutex);
        // Check if already loaded
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end()) {
            BG_WARN("Shader ",name," already loaded, returning cached version");
            return it->second;
        }

        try {
            auto shader = std::make_shared<Shader>(vertexPath, fragmentPath);

            if (!shader || shader->GetRendererID() == 0) {
                BG_FATAL("Failed to create shader", name);
                return nullptr;
            }

            m_Shaders[name] = shader;
            return shader;

        } catch (const std::exception& e) {
            BG_FATAL("Exception while loading shader ",name, " : ", e.what());
            return nullptr;
        }
    }

    // Get existing shader
    std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name) {
        std::lock_guard<std::mutex> lock(m_ShaderMutex);

        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end()) {
            return it->second;
        }
        BG_WARN("Shader ",name," not found in cache");
        return nullptr;
    }

    // Check if shader exists
    bool ResourceManager::HasShader(const std::string& name) {
        std::lock_guard<std::mutex> lock(m_ShaderMutex);
        return m_Shaders.find(name) != m_Shaders.end();
    }

    // Get all loaded shader names
    std::vector<std::string> ResourceManager::GetLoadedShaders() {
        std::lock_guard<std::mutex> lock(m_ShaderMutex);

        std::vector<std::string> names;
        names.reserve(m_Shaders.size());

        for (const auto& pair : m_Shaders) {
            names.push_back(pair.first);
        }

        return names;
    }

    // Clear all shaders
    void ResourceManager::ClearShaders() {
        std::lock_guard<std::mutex> lock(m_ShaderMutex);

        size_t count = m_Shaders.size();
        m_Shaders.clear();
    }

    // Clear all resources
    void ResourceManager::ClearAll() {
        ClearShaders();
        // Add other resource types here as you implement them
    }
}