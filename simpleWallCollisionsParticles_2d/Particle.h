#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"

#include <vector>

class Particle {
 public:
    Particle();
    Particle(glm::vec2);
    void update();
    void draw();
    
    glm::vec2   mLoc;
    glm::vec2   mDir;
    float   r;
    float   g;
    float   b;
    float       mVel;
    
    float       mRadius;
};