#include "sbc.h"
#include "../../helper/string_helper.h"

Sbc::Sbc()
{
    Sbc* self = this;
    group[0x98] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, B"; },
        // Cycles: 4
    };
    group[0x99] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, C"; },
        // Cycles: 4
    };
    group[0x9a] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, D"; },
        // Cycles: 4
    };
    group[0x9b] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, E"; },
        // Cycles: 4
    };
    group[0x9c] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, H"; },
        // Cycles: 4
    };
    group[0x9d] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, L"; },
        // Cycles: 4
    };
    group[0x9e] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, (HL)"; },
        // Cycles: 8
    };
    group[0x9f] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, A"; },
        // Cycles: 4
    };
    group[0xde] =
    {
        2,
        [self](int opcode) -> std::string { return "SBC  A, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };

}