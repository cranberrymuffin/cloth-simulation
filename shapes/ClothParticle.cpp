#include "ClothParticle.h"



ClothParticle::ClothParticle(glm::vec3 pos, float mass, float damping,glm::vec2 texCoord)
    :m_pos(pos),isStatic(false),m_damping(damping),m_mass(mass)
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
    if (isStatic)
    {
        return;
    }

        //apply force
        glm::vec3 temp = m_pos;
        m_pos += (m_pos-lastPos) * m_damping + (force/m_mass)*(timeStep/100);
        lastPos = temp;
        force = glm::vec3(0,0,0);
}


