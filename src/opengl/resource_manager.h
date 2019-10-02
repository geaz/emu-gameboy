#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "shader.h"

namespace OpenGL
{
    extern int ViewportWidth;
    extern int ViewportHeight;
    extern std::map<std::string, Shader> LoadedShaders;

    class ResourceManager
    {
        public:
            static Shader LoadShader(const char* shaderName, const char* vertextPath, const char* fragmentPath);
    };
}

#endif // RESOURCEMANAGER_H