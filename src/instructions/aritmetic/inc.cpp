#include "inc.h"
#include "../../helper/string_helper.h"

Inc::Inc()
{
    Inc* self = this;
    group[0x03] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  BC"; },
        // Cycles: 8
    };
    group[0x04] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  B"; },
        // Cycles: 4
    };
    group[0x0c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  C"; },
        // Cycles: 4
    };
    group[0x13] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  DE"; },
        // Cycles: 8
    };
    group[0x14] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  D"; },
        // Cycles: 4
    };
    group[0x1c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  E"; },
        // Cycles: 4
    };
    group[0x23] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  HL"; },
        // Cycles: 8
    };
    group[0x24] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  H"; },
        // Cycles: 4
    };
    group[0x2c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  L"; },
        // Cycles: 4
    };
    group[0x33] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  SP"; },
        // Cycles: 8
    };
    group[0x34] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  (HL)"; },
        // Cycles: 12
    };
    group[0x3c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  A"; },
        // Cycles: 4
    };

}