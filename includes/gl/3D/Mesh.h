// Collection of tris that form a mesh

#ifndef Mesh_H
#define Mesh_H

#include <vector>
#include "Tri.h"

class Mesh
{
private:
    /* data */
public:
    Mesh(/* args */);
    ~Mesh();

    std::vector<Tri> tris;
};

#endif