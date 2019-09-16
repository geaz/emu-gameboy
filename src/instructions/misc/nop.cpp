#include "nop.h"

Nop::Nop()
{
    group[0x00] =
    {
        1, 0x00,
        [](int opcode) -> std::string { return "NOP"; }
    };
}