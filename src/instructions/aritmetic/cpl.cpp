#include "cpl.h"
#include "../../helper/string_helper.h"

Cpl::Cpl()
{
    Cpl* self = this;
    group[0x2f] =
    {
        1,
        [self](int opcode) -> std::string { return "CPL  "; },
        // Cycles: 4
    };

}