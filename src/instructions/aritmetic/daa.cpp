#include "daa.h"
#include "../../helper/string_helper.h"

Daa::Daa()
{
    Daa* self = this;
    group[0x27] =
    {
        1,
        [self](int opcode) -> std::string { return "DAA  "; },
        // Cycles: 4
    };

}