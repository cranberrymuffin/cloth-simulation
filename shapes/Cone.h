#ifndef CONE_H
#define CONE_H

#include "common/common.h"
#include "Shape.h"

class Cone:public Shape
{
public:
    Cone();
    void buildShape(int param1,int param2, int param3);
    glm::vec4 getNormalAtHit(glm::vec4 p);
    glm::vec2 getTextureAtHit(glm::vec4 point);

private:
    float getSign(float n);
};

#endif // CONE_H
