// Simple polygon triangle to be used in mesh
// Contains 3D vectors of each point

#ifndef Tri_H
#define Tri_H

#include <vector>

#include "../../math/RVector.h"

struct Tri
{
    RVector verts[3];
};

#endif