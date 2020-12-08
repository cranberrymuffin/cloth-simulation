#ifndef CLOTH_H
#define CLOTH_H
#include "shapes/Shape.h"
#include "ClothParticle.h"

namespace CS123 { namespace GL {
class VBO;
}}


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
    int getIndex(int i, int j);
    void draw();
    std::vector<ClothParticle> particles;
    void buildVAO();

    bool isValid(int i, int j);
    void computeNormals();
    glm::vec3 getSpringForce(glm::vec3 p, glm::vec3 q, float K, float L_0);
    void settingsChanged() override;
    void updateBuffer();

    GLuint m_vaohandle;
    GLuint m_vbohandle;
    float m_particleWidth;
    float m_particleHeight;
    int numVertices;
    std::vector<float>m_normalData;
    float m_resolution;
    float Cv = 0.5f;
    float Cd = 0.5f;
    float K_structural = 25000.f;
    float K_shear = 25000.f;
    float K_flexion = 25000.f;
    float particleMass = 5.f;
    float L_structural;
    float L_shear;
    float L_flexion;
    std::unique_ptr<CS123::GL::VBO> m_VBO;

    const glm::vec3 Ufluid = glm::vec3(0,0,1.f);
};

#endif // CLOTH_H
