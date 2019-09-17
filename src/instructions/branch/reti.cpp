#include "reti.h"
#include "../../helper/string_helper.h"

Reti::Reti()
{
    Reti* self = this;
    group[0xd9] =
    {
        1,
        [self](int opcode) -> std::string { return "RETI "; },
        // Cycles: 16
    };

}