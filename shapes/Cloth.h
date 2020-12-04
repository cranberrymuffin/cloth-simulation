#ifndef CLOTH_H
#define CLOTH_H
#include "shapes/Shape.h"
#include "ClothParticle.h"

class Cloth:public Shape
{
public:
    Cloth(float width, float height, int particleWidth, int particleHeight, float weight, float damping);

    void buildShape(int param1,int param2, int param3);
    void buildFace(int param1,int param2, int param3);
    void update(float deltaTime);
    void draw();
    std::vector<ClothParticle> particles;
     void buildVAO();

    void updateBuffer();

    GLuint m_vaohandle;
    GLuint m_vbohandle;
    int numVertices;
};

#endif // CLOTH_H
