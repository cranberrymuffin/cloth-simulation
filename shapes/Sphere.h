#ifndef SPHERE_H
#define SPHERE_H

#include "common/common.h"
#include "Shape.h"
class Sphere:public Shape
{
public:
    Sphere();
    void buildShape(int param1,int param2, int param3);
};

#endif // SPHERE_H
