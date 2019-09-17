#include "rl.h"
#include "../../helper/string_helper.h"

Rl::Rl()
{
    Rl* self = this;
    group[0x10] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   B"; }
    };
    group[0x11] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   C"; }
    };
    group[0x12] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   D"; }
    };
    group[0x13] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   E"; }
    };
    group[0x14] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   H"; }
    };
    group[0x15] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   L"; }
    };
    group[0x16] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   (HL)"; }
    };
    group[0x17] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   A"; }
    };

}