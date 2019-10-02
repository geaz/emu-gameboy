#pragma once
#ifndef SCREEN_H
#define SCREEN_H

namespace OpenGL
{
   class Screen {
      public:
         virtual void handleKeys(const int key, const int scancode, const int action, const int mods) {};
         virtual void update() = 0;
   };
}

#endif // SCREEN_H