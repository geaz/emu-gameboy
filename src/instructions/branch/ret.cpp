#include "ret.h"
#include "../../helper/string_helper.h"

Ret::Ret()
{
    Ret* self = this;
    group[0xc0] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  NZ"; },
        // Cycles: 20/8
    };
    group[0xc8] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  Z"; },
        // Cycles: 20/8
    };
    group[0xc9] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  "; },
        // Cycles: 16
    };
    group[0xd0] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  NC"; },
        // Cycles: 20/8
    };
    group[0xd8] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  C"; },
        // Cycles: 20/8
    };

}