#include "sbc.h"
#include "../../helper/string_helper.h"

Sbc::Sbc()
{
    Sbc* self = this;
    group[0x98] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, B"; }
    };
    group[0x99] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, C"; }
    };
    group[0x9a] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, D"; }
    };
    group[0x9b] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, E"; }
    };
    group[0x9c] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, H"; }
    };
    group[0x9d] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, L"; }
    };
    group[0x9e] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, (HL)"; }
    };
    group[0x9f] =
    {
        1,
        [self](int opcode) -> std::string { return "SBC  A, A"; }
    };
    group[0xde] =
    {
        2,
        [self](int opcode) -> std::string { return "SBC  A, " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}