#include "ccf.h"
#include "../../helper/string_helper.h"

Ccf::Ccf()
{
    Ccf* self = this;
    group[0x3f] =
    {
        1,
        [self](int opcode) -> std::string { return "CCF  "; },
        // Cycles: 4
    };

}