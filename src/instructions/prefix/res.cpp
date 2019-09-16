#include "res.h"

Res::Res()
{
    group[0xBE] =
    {
        1, 0xBE,
        [](int opcode) -> std::string { return "RES 7, (HL)"; }
    };
}