#pragma once
#ifndef ROM_H
#define ROM_H

#include <string>

class Rom
{
    public:
        Rom(std::string path);

        std::string romPath;
        unsigned long romSize;
        char* romData;
};

#endif // ROM_H