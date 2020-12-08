#include "ClothParticle.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>


ClothParticle::ClothParticle(glm::vec3 pos, float mass, glm::vec2 texCoord):
    isStatic(false),
    m_normal(glm::vec3(0.f,1.f,0.f)),
    m_velocity(glm::vec3(0.f,0.f,0.f)),
    m_pos(pos),
    m_force(glm::vec3(0.f,0.f,0.f)),
    m_uv(texCoord),
    m_mass(mass)
{}

ClothParticle::~ClothParticle()
{}

void ClothParticle::step(float timeStep)
{
    m_velocity = m_velocity + (timeStep * (m_force/m_mass));
    if (!isStatic){
        m_pos = m_pos + (timeStep * m_velocity);
    }
    m_force = glm::vec3(0.f, 0.f, 0.f);
}


