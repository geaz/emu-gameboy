#pragma once
#ifndef WIDGET_H
#define WIDGET_H

class Widget
{
    public:
        virtual void draw(const float offsetX, const float offsetY) = 0;
};

#endif // WIDGET_H