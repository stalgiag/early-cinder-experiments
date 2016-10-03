#include "Particle.h"
#include "cinder/Rand.h"    
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace ci;
using std::list;

#include <iostream>
#include <string>
#include <math.h>



Particle::Particle()
{
}

Particle::Particle( glm::vec2 loc)
{
    mLoc = loc;
    mDir = Rand::randVec2();
    mVel = Rand::randVec2();
    r = randFloat();
    g = randFloat();
    b = randFloat();
    mRadius = 5;
    mass = 1;
    dist = 0;
    
}

void Particle::update()
{
    mLoc += mVel;
    
    if(mLoc.x > app::getWindowWidth() - mRadius || mLoc.x <= 0 + mRadius){
        mVel.x *= -1;
    }
    if(mLoc.y > app::getWindowHeight() - mRadius || mLoc.y <= 0 + mRadius){
        mVel.y *= -1;
    }
}

void Particle::draw()
{
    gl::color( Color(255, 255, 255));
    gl::drawSolidCircle(mLoc, mRadius,7);
}

void updateVel(Particle a, glm::vec2 loc){
 float dist = sqrtf((loc.x - a.mLoc.x)*(loc.x - a.mLoc.x) + (loc.y - a.mLoc.y)*(loc.y - a.mLoc.y));
    a.mLoc.x -= 5 * (loc.x - a.mLoc.x) / dist;
    a.mLoc.y -= 5 * (loc.y - a.mLoc.y) / dist;
}