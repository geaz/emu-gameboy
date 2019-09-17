#include "and.h"
#include "../../helper/string_helper.h"

And::And()
{
    And* self = this;
    group[0xa0] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  B"; },
        // Cycles: 4
    };
    group[0xa1] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  C"; },
        // Cycles: 4
    };
    group[0xa2] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  D"; },
        // Cycles: 4
    };
    group[0xa3] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  E"; },
        // Cycles: 4
    };
    group[0xa4] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  H"; },
        // Cycles: 4
    };
    group[0xa5] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  L"; },
        // Cycles: 4
    };
    group[0xa6] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  (HL)"; },
        // Cycles: 8
    };
    group[0xa7] =
    {
        1,
        [self](int opcode) -> std::string { return "AND  A"; },
        // Cycles: 4
    };
    group[0xe6] =
    {
        2,
        [self](int opcode) -> std::string { return "AND  " + StringHelper::IntToHexString(opcode & 0x00FF, 2); },
        // Cycles: 8
    };

}