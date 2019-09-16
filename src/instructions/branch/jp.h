#pragma once
#ifndef JP_H
#define JP_H

#include "../instruction_group.h"

class Jp : public InstructionGroup
{
    public:
        Jp();
    
    private:
        int getAddress(int opcode);
};

#endif // JP_H