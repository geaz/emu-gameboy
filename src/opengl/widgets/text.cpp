#include "text.h"

TextWidget::TextWidget(const float x, const float y)
    : x(x), y(y) { }

void TextWidget::setColor(const Color color)
{
    currentColor = color;
}

void TextWidget::setText(const std::string text)
{
    currentText = text;
}

void TextWidget::setFont(const std::string fontName, const std::string fontPath)
{
    font = ResourceManager::LoadFont(fontName.c_str(), fontPath.c_str());
}

void TextWidget::draw(const float offsetX, const float offsetY)
{
    font.renderText(x+offsetX, y+offsetY, currentText, currentColor);
}