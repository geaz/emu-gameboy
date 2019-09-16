#include "halt.h"

Halt::Halt()
{
    group[0x76] =
    {
        1, 0x76,
        [](int opcode) -> std::string { return "HALT"; }
    };
}