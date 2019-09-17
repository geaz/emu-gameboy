#include "rlca.h"
#include "../../helper/string_helper.h"

Rlca::Rlca()
{
    Rlca* self = this;
    group[0x07] =
    {
        1,
        [self](int opcode) -> std::string { return "RLCA "; },
        // Cycles: 4
    };

}