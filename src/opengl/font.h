#pragma once
#ifndef FONT_H
#define FONT_H

#include "stb/stb_truetype.h"
#include <glad/glad.h>
#include <string>

#include "shader.h"
#include "structs.h"

class Font
{
    public:
        Font() { };
        Font(const char* fontPath);

        void renderText(float x, float y, const std::string text, const Color color);

    private:        
        GLuint ftex;
        Shader textShader;
        unsigned int VBO, VAO;
        stbtt_bakedchar charData[96];
};

#endif //FONT_H