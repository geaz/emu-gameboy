#pragma once
#ifndef MISCSCREEN_H
#define MISCSCREEN_H

#include "../opengl/structs.h"
#include "../opengl/screen.h"

class MiscScreen : public Screen
{   
    public:
        MiscScreen();

        void update() override;
};

#endif // MISCSCREEN_H