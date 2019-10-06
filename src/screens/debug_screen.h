#pragma once
#ifndef DEBUGSCREEN_H
#define DEBUGSCREEN_H

#include "../opengl/screen.h"
#include "../debugger.h"

namespace GGB
{
    extern bool ShowDebugScreen;
    extern bool ShowAppMetrics;

    /**
     * The DebugScreen renders the debugging view of the emulator.
     * It closing / opening mechanism is triggered by the 'handleKeys'
     * method in the GameBoyScreen. The GUI gets rendered by ImGUI.
     **/
    class DebugScreen : public OpenGL::Screen
    {   
        public:
            DebugScreen(Debugger& debugger);

            void handleKeys(const int key, const int scancode, const int action, const int mods) override; 
            void update() override;

        private:
            Debugger& debugger;
    };
}

#endif // DEBUGSCREEN_H