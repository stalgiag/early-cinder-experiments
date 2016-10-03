#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{
}

void ParticleController::update()
{
    for(list<Particle>::iterator p = mParticles.begin(); p!= mParticles.end(); ++p ){
        p->update();
        locateParticles(*p);
    }
}

void ParticleController::draw()
{
    for(list<Particle>::iterator p = mParticles.begin(); p!= mParticles.end(); ++p ){
        p->draw();
    }
}

void ParticleController::addParticles(int amt)
{
    for(int i=0; i<amt; i++)
    {
        float x = Rand::randFloat(app::getWindowWidth());
        float y = Rand::randFloat(app::getWindowHeight());
        mParticles.push_back(Particle(vec2(x, y)));
    }
}

void ParticleController::removeParticles(int amt)
{
    for(int i=0; i<amt; i++)
    {
        mParticles.pop_back();
    }
}

void ParticleController::locateParticles(Particle current){
    for(list<Particle>::iterator p = mParticles.begin(); p!= mParticles.end(); ++p ){
        current.updateVel(current, p->mLoc);
    }
}