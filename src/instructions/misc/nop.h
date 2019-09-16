#pragma once
#ifndef NOP_H
#define NOP_H

#include "../instruction_group.h"

class Nop : public InstructionGroup
{
    public:
        Nop();
};

#endif // NOP_H