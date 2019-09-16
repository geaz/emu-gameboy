#pragma once
#ifndef INSTRUCTION_INCLUDE_H
#define INSTRUCTION_INCLUDE_H

#include "branch/rst.h"
#include "branch/jp.h"
#include "transfer/ld.h"
#include "misc/nop.h"
#include "misc/stop.h"
#include "misc/halt.h"
#include "instruction_group_prefix.h"

class InstructionSet
{
    public:
        InstructionSet()
        {  
            Rst rst;
            Jp jp;
            Ld ld;
            Nop nop;
            Stop stop;  
            Halt halt;

            add(rst.group);
            add(jp.group);
            add(ld.group);
            add(nop.group);
            add(stop.group);
            add(halt.group);
            add(instructionGroupPrefix.group);
        }

        InstructionGroupPrefix instructionGroupPrefix;
        std::map<unsigned char, Instruction> set;       

    private:
        void add(std::map<unsigned char, Instruction> instructionGroup)
        {
            set.insert(instructionGroup.begin(), instructionGroup.end());
        }
};

#endif // INSTRUCTION_INCLUDE_H