#include "rra.h"
#include "../../helper/string_helper.h"

Rra::Rra()
{
    Rra* self = this;
    group[0x1f] =
    {
        1,
        [self](int opcode) -> std::string { return "RRA  "; },
        // Cycles: 4
    };

}