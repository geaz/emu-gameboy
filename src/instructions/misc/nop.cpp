#include "nop.h"
#include "../../helper/string_helper.h"

Nop::Nop()
{
    Nop* self = this;
    group[0x00] =
    {
        1,
        [self](int opcode) -> std::string { return "NOP  "; }
    };

}