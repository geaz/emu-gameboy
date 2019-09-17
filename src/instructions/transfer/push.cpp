#include "push.h"
#include "../../helper/string_helper.h"

Push::Push()
{
    Push* self = this;
    group[0xc5] =
    {
        1,
        [self](int opcode) -> std::string { return "PUSH BC"; }
    };
    group[0xd5] =
    {
        1,
        [self](int opcode) -> std::string { return "PUSH DE"; }
    };
    group[0xe5] =
    {
        1,
        [self](int opcode) -> std::string { return "PUSH HL"; }
    };
    group[0xf5] =
    {
        1,
        [self](int opcode) -> std::string { return "PUSH AF"; }
    };

}