#include "sub.h"
#include "../../helper/string_helper.h"

Sub::Sub()
{
    Sub* self = this;
    group[0x90] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  B"; },
        // Cycles: 4
    };
    group[0x91] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  C"; },
        // Cycles: 4
    };
    group[0x92] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  D"; },
        // Cycles: 4
    };
    group[0x93] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  E"; },
        // Cycles: 4
    };
    group[0x94] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  H"; },
        // Cycles: 4
    };
    group[0x95] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  L"; },
        // Cycles: 4
    };
    group[0x96] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  (HL)"; },
        // Cycles: 8
    };
    group[0x97] =
    {
        1,
        [self](int opcode) -> std::string { return "SUB  A"; },
        // Cycles: 4
    };
    group[0xd6] =
    {
        2,
        [self](int opcode) -> std::string { return "SUB  " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };

}