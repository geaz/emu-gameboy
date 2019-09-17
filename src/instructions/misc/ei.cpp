#include "ei.h"
#include "../../helper/string_helper.h"

Ei::Ei()
{
    Ei* self = this;
    group[0xfb] =
    {
        1,
        [self](int opcode) -> std::string { return "EI   "; },
        // Cycles: 4
    };

}