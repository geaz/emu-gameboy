#include "cp.h"
#include "../../helper/string_helper.h"

Cp::Cp()
{
    Cp* self = this;
    group[0xb8] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   B"; },
        // Cycles: 4
    };
    group[0xb9] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   C"; },
        // Cycles: 4
    };
    group[0xba] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   D"; },
        // Cycles: 4
    };
    group[0xbb] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   E"; },
        // Cycles: 4
    };
    group[0xbc] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   H"; },
        // Cycles: 4
    };
    group[0xbd] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   L"; },
        // Cycles: 4
    };
    group[0xbe] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   (HL)"; },
        // Cycles: 8
    };
    group[0xbf] =
    {
        1,
        [self](int opcode) -> std::string { return "CP   A"; },
        // Cycles: 4
    };
    group[0xfe] =
    {
        2,
        [self](int opcode) -> std::string { return "CP   " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };

}