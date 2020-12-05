#include "ClothParticle.h"



ClothParticle::ClothParticle(glm::vec3 pos, float mass, glm::vec2 texCoord)
    :m_pos(pos),isStatic(false),m_mass(mass), m_velocity(0)
{

}

ClothParticle::~ClothParticle()
{

}

void ClothParticle::move(glm::vec3 delta)
{
  if(isStatic)
  {
      return;
  }
  m_pos+= delta;
}

void ClothParticle::step(float timeStep)
{
    if (!isStatic){
        m_velocity = m_velocity + (timeStep * (m_force/m_mass));
        m_pos = m_pos + (timeStep * m_velocity);
    }
}


