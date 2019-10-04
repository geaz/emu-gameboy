#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <imgui.h>

#include "gameboy_screen.h"
#include "debug_screen.h"

namespace GGB
{
    GameBoyScreen::GameBoyScreen(GameBoy& gameBoy) : 
        gameBoy(gameBoy),
        textureShader("shaders/texture.vshader", "shaders/texture.fshader")
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

    void GameBoyScreen::update()
    {
        gameBoy.process();
        renderBackground();
        renderSprites();
    }

    void GameBoyScreen::handleKeys(const int key, const int scancode, const int action, const int mods) 
    {
        using Enums::JOYPAD;
        if(key == GLFW_KEY_D && action == GLFW_PRESS) GGB::ShowDebugScreen = !GGB::ShowDebugScreen;
        if(action == GLFW_PRESS || action == GLFW_RELEASE)
        {
            switch(key)
            {
                case GLFW_KEY_UP:
                    gameBoy.input.toggleButton(JOYPAD::UP, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_DOWN:
                    gameBoy.input.toggleButton(JOYPAD::DOWN, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_LEFT:
                    gameBoy.input.toggleButton(JOYPAD::LEFT, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_RIGHT:
                    gameBoy.input.toggleButton(JOYPAD::RIGHT, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_X:
                    gameBoy.input.toggleButton(JOYPAD::A, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_Z:
                    gameBoy.input.toggleButton(JOYPAD::B, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_ENTER:
                    gameBoy.input.toggleButton(JOYPAD::START, action == GLFW_PRESS);
                    break;
                case GLFW_KEY_SPACE:
                    gameBoy.input.toggleButton(JOYPAD::SELECT, action == GLFW_PRESS);
                    break;
            }
        }
    }

    /**
     * This method creates a texture out of the current Game Boy Background
     * and just renders one rectangle with the background texture. This way
     * we get the best rendering performance.
     **/
    void GameBoyScreen::renderBackground()
    {   
        // Create a texture array for OpenGL
        GLuint data[144*160];
        for(int y = 0; y < 144; y++)
        {
            for(int x = 0; x < 160; x++)
            {
                Enums::GB_SHADE shadeData = gameBoy.ppu.backgroundData[y][x];
                switch(shadeData)
                {
                    case Enums::GB_SHADE::LIGHT_GRAY:
                        data[160*y + x] = glColorLightGray;
                        break;
                    case Enums::GB_SHADE::DARK_GRAY:
                        data[160*y + x] = glColorDarkGray;
                        break;
                    case Enums::GB_SHADE::BLACK:
                        data[160*y + x] = glColorBlack;
                        break;
                    default:
                    case Enums::GB_SHADE::WHITE:
                        data[160*y + x] = glColorWhite;
                        break;
                }
            }        
        }
        
        renderTexture(data);
    }

    void GameBoyScreen::renderSprites()
    {
        // Create a texture array for OpenGL
        GLuint data[144*160];
        for(int y = 0; y < 144; y++)
        {
            for(int x = 0; x < 160; x++)
            {
                Enums::GB_SHADE shadeData = gameBoy.ppu.spriteData[y][x];
                switch(shadeData)
                {
                    case Enums::GB_SHADE::WHITE:
                        data[160*y + x] = glColorWhite;
                        break;
                    case Enums::GB_SHADE::LIGHT_GRAY:
                        data[160*y + x] = glColorLightGray;
                        break;
                    case Enums::GB_SHADE::DARK_GRAY:
                        data[160*y + x] = glColorDarkGray;
                        break;
                    case Enums::GB_SHADE::BLACK:
                        data[160*y + x] = glColorBlack;
                        break;
                    case Enums::GB_SHADE::TRANSPARENT:
                        data[160*y + x] = glColorTransparent;
                        break;
                }
            }        
        }
        
        renderTexture(data);
    }

    void GameBoyScreen::renderTexture(GLuint* data)
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

        textureShader.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 160, 144, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, (GLvoid*)data);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}