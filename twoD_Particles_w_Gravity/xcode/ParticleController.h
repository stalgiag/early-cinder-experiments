#pragma once
#include "Particle.h"
#include <list>
class ParticleController{
public:
    ParticleController();
    void update();
    void draw();
    void addParticles(int amt);
    void removeParticles(int amt);
    void locateParticles(Particle current);
    std::list<Particle> mParticles;
};