#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>

#include "gameboy_screen.h"

GameboyScreen::GameboyScreen(Gameboy& gameboy) : 
    gameboy(gameboy),
    pixelShader("shaders\\rect.vshader", "shaders\\rect.fshader")
{ 
    pixelShader.use();
    pixelShader.setVec4("clearColor", 0, 0, 0, 255);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void GameboyScreen::update()
{
    gameboy.process();
    updateDisplay();
}

void GameboyScreen::updateDisplay()
{
    for(int i = 0; i < 144; i++)
    {
        for(int j = 0; j < 160; j++)
        {
            if(gameboy.ppu.backgroundBuffer[i][j] != 0)
            {
                drawPixelAt(i, j);
            }
        }        
    }
}
    
/**
 *  Sets a rectangle on the screeen. It takes the native Game Boy
 *  x and y coordinates and sets the pixel of the current screen
 *  by taking screen scales into consideration.
 * 
 *  @param  x   The x coordinate of the pixel on the Game Boy (0-159)
 *  @param  y   The y coordinate of the pixel on the Game Boy (0-143)
*/
void GameboyScreen::drawPixelAt(const int y, const int x)
{
    float onePixelX = 320 / 160;
    float onePixelY = 288 / 144;
    float scaledX = onePixelX * x;
    float scaledY = onePixelY * y;

    float vertices[] = {
        scaledX, scaledY, //Top Left
        scaledX + onePixelX, scaledY, //Top Right
        scaledX + onePixelX, scaledY + onePixelY, // Bottom Right
        scaledX, scaledY + onePixelY // Bottom Left
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };
    drawRect(vertices, indices, sizeof(vertices), sizeof(indices));
}

void GameboyScreen::drawRect(float vertices[], unsigned int indices[], int sizeofVertices, int sizeofIndices)
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    auto projection = glm::ortho(
        0.0f,         
        static_cast<GLfloat>(ResourceManager::ViewportWidth), 
        static_cast<GLfloat>(ResourceManager::ViewportHeight), 
        0.0f);
    pixelShader.use();
    pixelShader.setMatrix4("projection", projection);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}