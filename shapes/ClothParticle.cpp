#include "ClothParticle.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>


ClothParticle::ClothParticle(glm::vec3 pos, float mass, glm::vec2 texCoord):
    isStatic(false),
    m_pos(pos),
    m_mass(mass),
    m_normal(glm::vec3(0,1,0)),
    m_velocity(glm::vec3(0,0,0)),
    m_force(glm::vec3(0,0,0))
{}

ClothParticle::~ClothParticle()
{}

void ClothParticle::step(float timeStep)
{
    if (!isStatic){
        m_velocity = m_velocity + (timeStep * (m_force/m_mass));
        m_pos = m_pos + (timeStep * m_velocity);
    }
}


