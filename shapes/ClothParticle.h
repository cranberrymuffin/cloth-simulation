#ifndef CLOTHPARTICLE_H
#define CLOTHPARTICLE_H
#include "common/common.h"

class ClothParticle
{
public:
    ClothParticle( glm::vec3 pos, float mass, glm::vec2 texCoord);
    ~ClothParticle();
    bool isStatic; // true for pinned particles

    //used for physics calculations
    glm::vec3 m_normal;
    glm::vec3 m_velocity;
    glm::vec3 m_pos;
    glm::vec3 m_force;
    glm::vec2 m_uv;
    float m_mass;

    glm::vec2 texCoord; //texture mapping

    void move(glm::vec3 delta);
    void step(float timeStep);
};

#endif // CLOTHPARTICLE_H
