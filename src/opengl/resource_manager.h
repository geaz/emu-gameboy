#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "shader.h"

namespace OpenGL
{
    static int ViewportWidth;
    static int ViewportHeight;
    static std::map<std::string, Shader> LoadedShaders;

    class ResourceManager
    {
        public:
            static Shader LoadShader(const char* shaderName, const char* vertextPath, const char* fragmentPath);
    };
}

#endif // RESOURCEMANAGER_H