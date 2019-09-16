#pragma once
#ifndef HALT_H
#define HALT_H

#include "../instruction_group.h"

class Halt : public InstructionGroup
{
    public:
        Halt();
};

#endif // HALT_H