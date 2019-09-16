#pragma once
#ifndef PREFIX_INSTRUCTION_H
#define PREFIX_INSTRUCTION_H

#include <map>
#include <string>
#include <functional>

#include "instruction_group.h"
#include "prefix/res.h"

class InstructionGroupPrefix
{
    public:
        InstructionGroupPrefix()
        {  
            Res res;
            add(res.group);

            InstructionGroupPrefix* self = this;
            // Every PREFIX CB instruction is two bytes long
            // Every function in this struct acts as a dispatcher to the prefixGroup
            group[0xCB] =
            {
                2, 0xCB,
                [self](int opcode) -> std::string { return self->getPrefixInstruction(opcode & 0x00FF).getMnemonic(opcode & 0x00FF); }
            };
        }

        std::map<unsigned char, Instruction> group;

    private:
        void add(std::map<unsigned char, Instruction> instructionGroup)
        {
            prefixGroup.insert(instructionGroup.begin(), instructionGroup.end());
        }     
        
        Instruction getPrefixInstruction(int opcode)
        {
            // We will throw an exception here by not checking the code,
            // if the prefix opcode is not implemented.
            // Because if a 0xCBaa opcode is not implemented
            // this is defintely an error. We don't do the same for the other codes,
            // because it could also be binary data.
            if(prefixGroup.find(opcode) != prefixGroup.end())
            {
                return prefixGroup[opcode]; 
            } 
            return {
                0, 0x00, [](int opcode) -> std::string { return "NOT DEFINED PREFIX"; }
            };     
        }
        
        std::map<unsigned char, Instruction> prefixGroup;   
};

#endif // PREFIX_INSTRUCTION_H