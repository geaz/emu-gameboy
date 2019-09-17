#include "rla.h"
#include "../../helper/string_helper.h"

Rla::Rla()
{
    Rla* self = this;
    group[0x17] =
    {
        1,
        [self](int opcode) -> std::string { return "RLA  "; },
        // Cycles: 4
    };

}