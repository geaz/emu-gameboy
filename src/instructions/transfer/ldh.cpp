#include "ldh.h"
#include "../../helper/string_helper.h"

Ldh::Ldh()
{
    Ldh* self = this;
    group[0xe0] =
    {
        2,
        [self](int opcode) -> std::string { return "LDH  (a8), A"; }
    };
    group[0xf0] =
    {
        2,
        [self](int opcode) -> std::string { return "LDH  A, (a8)"; }
    };

}