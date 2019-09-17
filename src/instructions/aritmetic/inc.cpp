#include "inc.h"
#include "../../helper/string_helper.h"

Inc::Inc()
{
    Inc* self = this;
    group[0x03] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  BC"; }
    };
    group[0x04] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  B"; }
    };
    group[0x0c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  C"; }
    };
    group[0x13] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  DE"; }
    };
    group[0x14] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  D"; }
    };
    group[0x1c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  E"; }
    };
    group[0x23] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  HL"; }
    };
    group[0x24] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  H"; }
    };
    group[0x2c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  L"; }
    };
    group[0x33] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  SP"; }
    };
    group[0x34] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  (HL)"; }
    };
    group[0x3c] =
    {
        1,
        [self](int opcode) -> std::string { return "INC  A"; }
    };

}