#ifndef CLOTH_H
#define CLOTH_H
#include "shapes/Shape.h"
#include "ClothParticle.h"

class Cloth:public Shape
{
public:
    Cloth(float resolution, int particleWidth, int particleHeight);

    enum SpringForceType {
            STRUCTURAL, SHEAR, FLEXION
    };

    void buildShape(int param1,int param2, int param3);
    void buildFace(int param1,int param2, int param3);
    void update(float deltaTime);
    int getParticleIndexFromCoordinates(int i, int j);
    void draw();
    std::vector<ClothParticle> particles;
    void buildVAO();

    bool isValidCoordinate(int i, int j);
    void computeNormals();
    glm::vec3 getSpringForce(glm::vec3 p, glm::vec3 q, Cloth::SpringForceType forceType);
    glm::vec3 getStructuralSpringForce(int i, int j);
    glm::vec3 getShearSpringForce(int i, int j);
    glm::vec3 getFlexionSpringForce(int i, int j);
    bool isValidNeighborDistance(int curr_i, int curr_j, int nbr_i, int nbr_j);

    void updateBuffer();

    GLuint m_vaohandle;
    GLuint m_vbohandle;
    int numVertices;

    float m_resolution;
    const float Cv = 0.5;
    const float Cd = 0.05;
    const float K_structural = 1.f;
    const float K_shear = 1.f;
    const float K_flexion = 1.f;
    const float L_structural;
    const float L_shear;
    const float L_flexion;
    const glm::vec3 Ufluid = glm::vec3(0,1,0);
};

#endif // CLOTH_H
