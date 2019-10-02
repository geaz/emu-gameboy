#include "resource_manager.h"

namespace OpenGL
{    
    int ViewportWidth = 0;
    int ViewportHeight = 0;
    std::map<std::string, Shader> LoadedShaders;

    Shader ResourceManager::LoadShader(const char* shaderName, const char* vertextPath, const char* fragmentPath)
    {
        if (LoadedShaders.find(shaderName) == LoadedShaders.end() )
        {
            LoadedShaders[shaderName] = Shader(vertextPath, fragmentPath);
        }
        return LoadedShaders[shaderName];
    }
}