#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"

#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;
using std::string;

class Particle {
 public:
    Particle();
    Particle(glm::vec2);
    void update();
    void draw();
    

    Font				mFont;
    gl::TextureFontRef	mTextureFont;
    std::vector<std::string> mWords;
    string textFile;
    gl::Texture2dRef mTex;
    glm::vec2   mLoc;
    glm::vec2   mDir;
    float   r;
    float   g;
    float   b;
    float       mVel;
    int     word;
    float       mRadius;
};