#include "rect.h"

RectWidget::RectWidget(const float x, const float y, const float width, const float height)
    : x(x), y(y), width(width), height(height)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    setColor({255, 255, 255, 255});
}

void RectWidget::setColor(const Color color)
{
    rectShader.use();
    rectShader.setVec4("clearColor", color.red / 255.0f, color.green  / 255.0f, color.blue  / 255.0f, color.alpha  / 255.0f);
}

void RectWidget::draw(const float offsetX, const float offsetY)
{
    float vertices[] = {
        x+offsetX, y+offsetY,           // top left
        width+offsetX, y+offsetY,       // top right
        width+offsetX, height+offsetY,  // bottom right
        x+offsetX, height+offsetY,      // bottom left 
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    auto projection = glm::ortho(
    0.0f,         
    static_cast<GLfloat>(ResourceManager::ViewportWidth), 
    static_cast<GLfloat>(ResourceManager::ViewportHeight), 
    0.0f);
    rectShader.use();
    rectShader.setMatrix4("projection", projection);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}