#pragma once
#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <string>

#include "widget.h"
#include "../structs.h"
#include "../resource_manager.h"

class TextWidget : public Widget
{
    public:
        TextWidget(const float x, const float y);

        void setColor(const Color color);
        void setText(const std::string text);
        void setFont(const std::string fontName, const std::string fontPath);
        void draw(const float offsetX, const float offsetY) override;

    private:
        float x, y;
        std::string currentText;
        Color currentColor = { 50, 50, 50, 255 };
        Font font = ResourceManager::LoadFont("Minecraft", "Minecraft.ttf");
};

#endif // TEXTWIDGET_H