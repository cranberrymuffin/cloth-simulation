#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder:public Shape
{
public:
    Cylinder();
    void buildShape(int param1,int param2, int param3);
//    glm::vec4 getNormalAtHit(glm::vec4 p);
//    glm::vec2 getTextureAtHit(glm::vec4 point);
};

#endif // CYLINDER_H
