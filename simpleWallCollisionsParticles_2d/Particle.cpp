#include "Particle.h"
#include "cinder/Rand.h"    
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace ci;

Particle::Particle()
{
}

Particle::Particle( glm::vec2 loc)
{
    mLoc = loc;
    mDir = Rand::randVec2();
    mVel = Rand::randFloat();
    r = randFloat();
    g = randFloat();
    b = randFloat();
    mRadius = 5;
    
}

void Particle::update()
{
    mLoc += mDir * mVel;
    
    if(mLoc.x > app::getWindowWidth() - mRadius || mLoc.x <= 0 + mRadius){
        mDir.x *= -1;
    }
    if(mLoc.y > app::getWindowHeight() - mRadius || mLoc.y <= 0 + mRadius){
        mDir.y *= -1;
    }
}

void Particle::draw()
{
    gl::color( Color(255, 255, 255));
    gl::drawSolidCircle(mLoc, mRadius,7);
}