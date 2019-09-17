#include "stop.h"
#include "../../helper/string_helper.h"

Stop::Stop()
{
    Stop* self = this;
    group[0x10] =
    {
        2,
        [self](int opcode) -> std::string { return "STOP 0"; },
        // Cycles: 4
    };

}