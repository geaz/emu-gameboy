#include "di.h"
#include "../../helper/string_helper.h"

Di::Di()
{
    Di* self = this;
    group[0xf3] =
    {
        1,
        [self](int opcode) -> std::string { return "DI   "; },
        // Cycles: 4
    };

}