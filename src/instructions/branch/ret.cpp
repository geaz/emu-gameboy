#include "ret.h"
#include "../../helper/string_helper.h"

Ret::Ret()
{
    Ret* self = this;
    group[0xc0] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  NZ"; }
    };
    group[0xc8] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  Z"; }
    };
    group[0xc9] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  "; }
    };
    group[0xd0] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  NC"; }
    };
    group[0xd8] =
    {
        1,
        [self](int opcode) -> std::string { return "RET  C"; }
    };

}