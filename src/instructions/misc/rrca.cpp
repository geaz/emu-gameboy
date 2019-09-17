#include "rrca.h"
#include "../../helper/string_helper.h"

Rrca::Rrca()
{
    Rrca* self = this;
    group[0x0f] =
    {
        1,
        [self](int opcode) -> std::string { return "RRCA "; }
    };

}