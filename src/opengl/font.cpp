#include <fstream>
#include <gtc/matrix_transform.hpp>

#include "font.h"
#include "resource_manager.h"

Font::Font(const char* fontPath)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    textShader = ResourceManager::LoadShader("TextShader", "shaders\\text.vshader", "shaders\\text.fshader");

    std::basic_ifstream<unsigned char> fontFile;
    fontFile.open(fontPath, std::ofstream::binary);

    fontFile.seekg(0, fontFile.end);
    long fontSize = (unsigned long) fontFile.tellg();
    fontFile.seekg(0, fontFile.beg);
    
    unsigned char* fontBuffer = new unsigned char[fontSize];
    fontFile.read(fontBuffer, fontSize);
    fontFile.close();

    unsigned char temp_bitmap[512*512];
    stbtt_BakeFontBitmap(fontBuffer, 0, 16.0, temp_bitmap,512, 512, 32, 96, charData); 

    glGenTextures(1, &ftex);
    glBindTexture(GL_TEXTURE_2D, ftex);
    glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA, 512, 512, 0,  GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::renderText(float x, float y, const std::string text, const Color color)
{    
    glBindTexture(GL_TEXTURE_2D, ftex);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto projection = glm::ortho(
        0.0f,         
        static_cast<GLfloat>(ResourceManager::ViewportWidth), 
        static_cast<GLfloat>(ResourceManager::ViewportHeight), 
        0.0f);
    textShader.use();
    textShader.setVec4("textColor", color.red/255, color.green/255, color.blue/255, color.alpha/255);
    textShader.setMatrix4("projection", projection);

    for(unsigned int i = 0; i < text.length(); i++)
    {
        if (text[i] >= 32 && text[i] < 128) 
        {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(charData, 512, 512, text[i]-32, &x, &y, &q, 1);
            
            GLfloat vertices[6][4] = 
            {
                { q.x0, q.y1, q.s0, q.t1 },
                { q.x1, q.y0, q.s1, q.t0 },
                { q.x0, q.y0, q.s0, q.t0 },

                { q.x0, q.y1, q.s0, q.t1 },
                { q.x1, q.y1, q.s1, q.t1 },
                { q.x1, q.y0, q.s1, q.t0 }
            };
            
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }        
}