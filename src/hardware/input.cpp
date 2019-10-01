#include "input.h"
#include "memory/io_register_flags.h"

Input::Input(Mmu& mmu) : mmu(mmu) { }

void Input::cycle(const uint8_t cycles)
{
    cycleCount += cycles;
    if(cycleCount >= PAD_FREQUENCY)
    {
        bool changed = false;
        uint8_t newPadState;
        if(mmu.readIORegisterBit(REG_PAD, BUTTONS_SET))
        {
            newPadState = padState & 0x0F;
            changed = (mmu.readIORegister(REG_PAD) & 0x0F) ^ newPadState;
        }
        else if(mmu.readIORegisterBit(REG_PAD, DIRECTION_SET))
        {
            newPadState = ((padState & 0xF0) >> 4);
            changed = (mmu.readIORegister(REG_PAD) & 0x0F) ^ newPadState;
        }

        if(changed)
        {
            mmu.rawWrite(REG_PAD, (mmu.readIORegister(REG_PAD) & 0xF0) | newPadState);
            mmu.writeIORegisterBit(REG_INTERRUPT_FLAG, INTERRUPT_INPUT, true);
        }
        
        cycleCount -= PAD_FREQUENCY;
    }
}

void Input::toggleButton(const Button button, const bool pressed)
{
    if(button == GB_A) pressed ? padState &= ~GB_A : padState |= GB_A;
    if(button == GB_B) pressed ? padState &= ~GB_B : padState |= GB_B;
    if(button == GB_SELECT) pressed ? padState &= ~GB_SELECT : padState |= GB_SELECT;
    if(button == GB_START) pressed ? padState &= ~GB_START : padState |= GB_START;
    if(button == GB_UP) pressed ? padState &= ~GB_UP : padState |= GB_UP;
    if(button == GB_DOWN) pressed ? padState &= ~GB_DOWN : padState |= GB_DOWN;
    if(button == GB_LEFT) pressed ? padState &= ~GB_LEFT : padState |= GB_LEFT;
    if(button == GB_RIGHT) pressed ? padState &= ~GB_RIGHT : padState |= GB_RIGHT;
}