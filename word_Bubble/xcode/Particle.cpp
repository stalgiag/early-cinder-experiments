#include "Particle.h"
#include "cinder/Rand.h"    
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace ci;
using std::string;

Particle::Particle()
{
    
}

Particle::Particle( glm::vec2 loc)
{
    mLoc = loc;
    mDir = Rand::randVec2();
    mVel = Rand::randFloat(0,0.5);
    r = randFloat();
    g = randFloat();
    b = randFloat();
    mRadius = randInt(50,80);
    auto img = loadImage( loadAsset( "orb-2.png" ) );
    mTex = gl::Texture2d::create( img );
    mFont = Font( "Comic Sans MS", 11 );
    mTextureFont = gl::TextureFont::create( mFont );
    
    textFile = loadString(loadAsset("text.txt"));
    
    
    //
    std::size_t pos = 0, found;
    while((found = textFile.find_first_of(' ', pos)) != std::string::npos) {
        mWords.push_back(textFile.substr(pos, found - pos));
        pos = found+1;
    }
    mWords.push_back(textFile.substr(pos));
    
    word = randInt(0,100);
}

void Particle::update()
{
    mLoc += mDir * mVel;

    if(mLoc.x > 350 - mRadius || mLoc.x <= 20 + mRadius){
        mDir.x *= -1;
    }
    if(mLoc.y > 250 - mRadius || mLoc.y <= 20 + mRadius){
        mDir.y *= -1;
    }
}

void Particle::draw()
{
    gl::draw(mTex, Rectf(mLoc.x, mLoc.y, mLoc.x + mRadius, mLoc.y + mRadius));
    gl::color(0.2, 0, 0);
    mTextureFont->drawString( mWords[word], vec2( mLoc.x + mRadius/5, mLoc.y+mRadius/2));
    gl::color(1, 1, 1);
}
