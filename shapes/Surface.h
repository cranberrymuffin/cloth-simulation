#ifndef SURFACE_H
#define SURFACE_H


#include "common/common.h"

class Surface
{
public:
    Surface();
    virtual  void buildSurface(int param1, int param2, int param3,
                               std::vector<Vertex>&,std::vector<Normal>&, std::vector<TextureCoord>&) = 0;

};

#endif // SURFACE_H
