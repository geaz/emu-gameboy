#include "scf.h"
#include "../../helper/string_helper.h"

Scf::Scf()
{
    Scf* self = this;
    group[0x37] =
    {
        1,
        [self](int opcode) -> std::string { return "SCF  "; },
        // Cycles: 4
    };

}