#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"

#include <vector>

class Particle
{
public:
    Particle();
    Particle(glm::vec2);
    void update();
    void draw();
    void updateVel(Particle a, glm::vec2);
    
    glm::vec2   mLoc;
    glm::vec2   mDir;
    glm::vec2   mVel;
    glm::vec2   mAcc;
    float   r;
    float   g;
    float   b;
    int mass;
    
    float dist;
    float delta;
    float theta;
    float       mRadius;
};