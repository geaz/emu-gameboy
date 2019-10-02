#include "input.h"
#include "memory/io_register_flags.h"

namespace GGB::Hardware
{
    Input::Input(Mmu& mmu) : mmu(mmu) { }

    void Input::cycle()
    {
        bool changed = false;
        uint8_t newPadState;
        
        if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_PAD, Enums::JOYPAD_FLAG::BUTTONS_SET))
        {
            newPadState = padState & 0x0F;
            changed = (mmu.readIORegister(Enums::IO_REGISTER::REG_PAD) & 0x0F) ^ newPadState;
        }
        else if(!mmu.readIORegisterBit(Enums::IO_REGISTER::REG_PAD, Enums::JOYPAD_FLAG::DIRECTION_SET))
        {
            newPadState = ((padState & 0xF0) >> 4);
            changed = (mmu.readIORegister(Enums::IO_REGISTER::REG_PAD) & 0x0F) ^ newPadState;
        }

        if(changed)
        {
            mmu.rawWrite(Enums::IO_REGISTER::REG_PAD, (mmu.readIORegister(Enums::IO_REGISTER::REG_PAD) & 0xF0) | newPadState);
            mmu.writeIORegisterBit(Enums::IO_REGISTER::REG_INTERRUPT_FLAG, Enums::INTERRUPT_FLAG::INPUT, true);
        }
    }

    void Input::toggleButton(const Enums::JOYPAD button, const bool pressed)
    {
        if(pressed) padState &= ~button;
        else padState |= button;
    }
}