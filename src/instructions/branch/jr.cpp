#include "jr.h"
#include "../../helper/string_helper.h"

Jr::Jr()
{
    Jr* self = this;
    group[0x18] =
    {
        2,
        [self](int opcode) -> std::string { return "JR   a'" + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x20] =
    {
        2,
        [self](int opcode) -> std::string { return "JR   NZ, a'" + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x28] =
    {
        2,
        [self](int opcode) -> std::string { return "JR   Z, a'" + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x30] =
    {
        2,
        [self](int opcode) -> std::string { return "JR   NC, a'" + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };
    group[0x38] =
    {
        2,
        [self](int opcode) -> std::string { return "JR   C, a'" + StringHelper::IntToHexString(opcode & 0x00FF, 2); }
    };

}