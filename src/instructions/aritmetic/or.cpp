#include "or.h"
#include "../../helper/string_helper.h"

Or::Or()
{
    Or* self = this;
    group[0xb0] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   B"; }
    };
    group[0xb1] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   C"; }
    };
    group[0xb2] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   D"; }
    };
    group[0xb3] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   E"; }
    };
    group[0xb4] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   H"; }
    };
    group[0xb5] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   L"; }
    };
    group[0xb6] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   (HL)"; }
    };
    group[0xb7] =
    {
        1,
        [self](int opcode) -> std::string { return "OR   A"; }
    };
    group[0xf6] =
    {
        2,
        [self](int opcode) -> std::string { return "OR   " + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}