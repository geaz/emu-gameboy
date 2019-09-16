#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <glad/glad.h>

struct Color {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
};

struct GridDefinition {
    int index;
    float sizePercentage;

    bool operator < (const GridDefinition& defintion) const
    {
        return (index < defintion.index);
    }
};

#endif // STRUCTS_H