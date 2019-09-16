#include "text.h"

TextWidget::TextWidget(const std::string fontName, const std::string fontPath, const float x, const float y)
    : font(ResourceManager::LoadFont(fontName.c_str(), fontPath.c_str())), x(x), y(y) { }

void TextWidget::setText(const std::string text)
{
    currentText = text;
}

void TextWidget::setColor(const Color color)
{
    currentColor = color;
}

void TextWidget::draw(const float offsetX, const float offsetY)
{
    font.renderText(x+offsetX, y+offsetY, currentText, currentColor);
}