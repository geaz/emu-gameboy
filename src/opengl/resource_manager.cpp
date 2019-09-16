#include "resource_manager.h"

// Instantiate static variables
int ResourceManager::ViewportWidth;
int ResourceManager::ViewportHeight;

std::map<std::string, Shader>       ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* shaderName, const char* vertextPath, const char* fragmentPath)
{
    if (ResourceManager::Shaders.find(shaderName) == ResourceManager::Shaders.end() )
    {
        ResourceManager::Shaders[shaderName] = Shader(vertextPath, fragmentPath);
    }
    return ResourceManager::Shaders[shaderName];
}