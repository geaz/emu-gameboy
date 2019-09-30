#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <imgui.h>

#include "gameboy_screen.h"
#include "debug_screen.h"

GameboyScreen::GameboyScreen(Gameboy& gameboy) : 
    gameboy(gameboy),
    textureShader("shaders\\texture.vshader", "shaders\\texture.fshader")
{    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
}

void GameboyScreen::update()
{
    gameboy.process();
    renderBackground();
}

void GameboyScreen::handleKeys(const int key, const int scancode, const int action, const int mods) 
{
    if(key == GLFW_KEY_D && action == GLFW_PRESS) DebugScreen::showCpu = !DebugScreen::showCpu;
}

/**
 * This method creates a texture out of the current Game Boy Background
 * and just renders one rectangle with the background texture
 **/
void GameboyScreen::renderBackground()
{   
    float vertices[] = {
        // positions          // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, // top right
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create a texture array for OpenGL
    GLuint* data = new GLuint[144*160];
    for(int y = 0; y < 144; y++)
    {
        for(int x = 0; x < 160; x++)
        {
            uint8_t pixelData = gameboy.ppu.backgroundBuffer[y][x];
            switch(gameboy.ppu.backgroundPalette.colors[pixelData])
            {
                case WHITE:
                    data[160*y + x] = colorWhite;
                    break;
                case LIGHT_GRAY:
                    data[160*y + x] = colorLightGray;
                    break;
                case DARK_GRAY:
                    data[160*y + x] = colorDarkGray;
                    break;
                case BLACK:
                    data[160*y + x] = colorBlack;
                    break;
                default:
                    data[160*y + x] = colorWhite;
                    break;
            }
        }        
    }
    
    textureShader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 160, 144, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, (GLvoid*)data);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}