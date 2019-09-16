#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

class Screen {
   public:

      Screen(int row,  int column) : row(row), column(column) { }

      void render()
      {        
         update();
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
};

#endif // SCREEN_H