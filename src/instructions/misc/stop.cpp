#include "stop.h"

Stop::Stop()
{
    group[0x10] =
    {
        2, 0x10,
        [](int opcode) -> std::string { return "STOP 0"; }
    };
}