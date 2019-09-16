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
        TextWidget(const std::string fontName, const std::string fontPath, const float x, const float y);

        void setText(const std::string text);
        void setColor(const Color color);
        void draw(const float offsetX, const float offsetY) override;

    private:
        Font font;
        float x, y;
        std::string currentText;
        Color currentColor = { 50, 50, 50, 255 };
};

#endif // TEXTWIDGET_H