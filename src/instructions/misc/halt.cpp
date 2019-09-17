#include "halt.h"
#include "../../helper/string_helper.h"

Halt::Halt()
{
    Halt* self = this;
    group[0x76] =
    {
        1,
        [self](int opcode) -> std::string { return "HALT "; }
    };

}