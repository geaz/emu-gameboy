#include "input.hpp"

namespace GGB::Hardware
{
    Input::Input(Mmu& mmu) : mmu(mmu) { }

    void Input::cycle()
    {
        bool changed = false;
        uint8_t newPadState;
        
        if(!mmu.readIORegisterBit(Const::AddrRegInput, Const::FlagPadButtonsSet))
        {
            newPadState = padState & 0x0F;
            changed = (mmu.read(Const::AddrRegInput) & 0x0F) ^ newPadState;
        }
        else if(!mmu.readIORegisterBit(Const::AddrRegInput, Const::FlagPadDirectionSet))
        {
            newPadState = ((padState & 0xF0) >> 4);
            changed = (mmu.read(Const::AddrRegInput) & 0x0F) ^ newPadState;
        }

        if(changed)
        {
            mmu.rawWrite(Const::AddrRegInput, (mmu.read(Const::AddrRegInput) & 0xF0) | newPadState);
            mmu.writeIORegisterBit(Const::AddrRegInterruptFlag, Const::FlagInterruptInput, true);
        }
    }

    void Input::toggleButton(const Enum::PadButton button, const bool pressed)
    {
        uint8_t buttonValue = static_cast<uint8_t>(button);
        if(pressed) padState &= ~buttonValue;
        else padState |= buttonValue;
    }
}