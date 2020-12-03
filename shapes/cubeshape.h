#ifndef CUBESHAPE_H
#define CUBESHAPE_H


#include "Shape.h"


class CubeShape: public Shape
{


public:
    CubeShape();
    void buildShape(int param1,int param2, int param3);
//    glm::vec4 getNormalAtHit(glm::vec4 p);
//   glm::vec2 getTextureAtHit(glm::vec4 p);
    glm::mat4 planeSpace;
protected:
    int numPoints;
};

#endif // CUBESHAPE_H
