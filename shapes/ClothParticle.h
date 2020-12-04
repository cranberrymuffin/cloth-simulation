#ifndef CLOTHPARTICLE_H
#define CLOTHPARTICLE_H
#include "common/common.h"

class ClothParticle
{
public:
    ClothParticle( glm::vec3 pos, float mass, float damping,glm::vec2 texCoord);
    ~ClothParticle();
    bool isStatic;
    glm::vec3 normal;
    glm::vec3 m_pos;
    glm::vec3 lastPos;
    glm::vec2 texCoord;
    float m_damping;
    float m_mass;
    glm::vec3 force;
    void move(glm::vec3 delta);
    void step(float timeStep);
};

#endif // CLOTHPARTICLE_H
