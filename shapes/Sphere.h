#ifndef SPHERE_H
#define SPHERE_H

#include "common/common.h"
#include "Shape.h"
class Sphere:public Shape
{
public:
    Sphere();
    void buildShape(int param1,int param2, int param3);
//    glm::vec4 getNormalAtHit(glm::vec4 p);
//    glm::vec4 getPositionAtHit(Ray& ray,float t);
//    glm::vec2 getTextureAtHit(glm::vec4 point);
};

#endif // SPHERE_H
