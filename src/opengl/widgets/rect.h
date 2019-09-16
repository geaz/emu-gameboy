#pragma once
#ifndef RECTWIDGET_H
#define RECTWIDGET_H

#include <string>

#include "widget.h"
#include "../structs.h"
#include "../resource_manager.h"

class RectWidget : public Widget
{
    public:
        RectWidget(const float x, const float y, const float width, const float height);

        void setColor(const Color color);
        void draw(const float offsetX, const float offsetY) override;

    private:
        Shader rectShader;
        float x, y, width, height;
        unsigned int VBO, VAO, EBO;
};

#endif // RECTWIDGET_H