#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

class Particle
{
public:
    Particle();
    Particle(glm::vec4 position, glm::vec4 velocity, float mass);
};

#endif // PARTICLE_H
