#include "rl.h"
#include "../../helper/string_helper.h"

Rl::Rl()
{
    Rl* self = this;
    group[0x10] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   B"; },
        // Cycles: 8
    };
    group[0x11] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   C"; },
        // Cycles: 8
    };
    group[0x12] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   D"; },
        // Cycles: 8
    };
    group[0x13] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   E"; },
        // Cycles: 8
    };
    group[0x14] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   H"; },
        // Cycles: 8
    };
    group[0x15] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   L"; },
        // Cycles: 8
    };
    group[0x16] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   (HL)"; },
        // Cycles: 16
    };
    group[0x17] =
    {
        2,
        [self](int opcode) -> std::string { return "RL   A"; },
        // Cycles: 8
    };

}