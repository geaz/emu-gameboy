#include "pop.h"
#include "../../helper/string_helper.h"

Pop::Pop()
{
    Pop* self = this;
    group[0xc1] =
    {
        1,
        [self](int opcode) -> std::string { return "POP  BC"; },
        // Cycles: 12
    };
    group[0xd1] =
    {
        1,
        [self](int opcode) -> std::string { return "POP  DE"; },
        // Cycles: 12
    };
    group[0xe1] =
    {
        1,
        [self](int opcode) -> std::string { return "POP  HL"; },
        // Cycles: 12
    };
    group[0xf1] =
    {
        1,
        [self](int opcode) -> std::string { return "POP  AF"; },
        // Cycles: 12
    };

}