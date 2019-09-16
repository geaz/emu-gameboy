#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "shader.h"

class ResourceManager
{
    public:
        static Shader LoadShader(const char* shaderName, const char* vertextPath, const char* fragmentPath);
        
        static int ViewportWidth;
        static int ViewportHeight;

        static std::map<std::string, Shader> Shaders;
};

#endif // RESOURCEMANAGER_H