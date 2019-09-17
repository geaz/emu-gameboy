#pragma once
#ifndef STRING_H
#define STRING_H

#include <string>

class StringHelper
{
    public:
        static std::string IntToHexString(const int data, int stringWidth = 4, bool widthPrefix = true);
        static std::string Pad(const std::string text, int width, const char fillChar);
};

#endif // STRING_H
