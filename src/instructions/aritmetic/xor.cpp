#include "xor.h"
#include "../../helper/string_helper.h"

Xor::Xor()
{
    Xor* self = this;
    group[0xa8] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  B"; },
        // Cycles: 4
    };
    group[0xa9] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  C"; },
        // Cycles: 4
    };
    group[0xaa] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  D"; },
        // Cycles: 4
    };
    group[0xab] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  E"; },
        // Cycles: 4
    };
    group[0xac] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  H"; },
        // Cycles: 4
    };
    group[0xad] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  L"; },
        // Cycles: 4
    };
    group[0xae] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  (HL)"; },
        // Cycles: 8
    };
    group[0xaf] =
    {
        1,
        [self](int opcode) -> std::string { return "XOR  A"; },
        // Cycles: 4
    };
    group[0xee] =
    {
        2,
        [self](int opcode) -> std::string { return "XOR  " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };

}