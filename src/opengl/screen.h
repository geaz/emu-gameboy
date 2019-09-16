#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

#include "widgets/widget.h"

class Screen {
   public:

      Screen(int row,  int column) : row(row), column(column) { }

      void render()
      {        
         update();
         for(Widget* widget : widgets)
         {
            widget->draw(startX, startY);
         }
      }    

      void addWidget(Widget* widget)
      {
         widgets.push_back(widget);
      }

      void setScreenCords(const float newStartX, const float newStartY, const float newEndX, const float newEndY)
      {
         startX = newStartX;
         startY = newStartY;
         endX = newEndX;
         endY = newEndY;
      }

      virtual void handleKeys(const int key, const int scancode, const int action, const int mods) {};
      virtual void update() = 0;

      int row, column;
      float startX, startY, endX, endY; 

   private:
      std::vector<Widget*> widgets;
};

#endif // SCREEN_H