#ifndef PLANESHAPE_H
#define PLANESHAPE_H
#include "shapes/Shape.h"

class PlaneShape: public Shape
{
public:
    PlaneShape(int param1,int param2, int param3);
    void buildShape(int param1,int param2, int param3);
};

#endif // PLANESHAPE_H
