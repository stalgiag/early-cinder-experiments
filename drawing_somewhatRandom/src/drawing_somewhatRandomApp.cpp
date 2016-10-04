#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/FBO.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class drawing_somewhatRandomApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void moveSmooth();
    void drawIntoBuffer();
    
    gl::Texture2dRef mTex;
    bool firstTime = true;
    int counter = 0;
    vec2 mDir;
    vec2 mLoc;
    float mRad = 10;
    gl::FboRef myFBO;
    gl::GlslProgRef mShaderBlur;
};

void drawing_somewhatRandomApp::setup()
{
    auto img = loadImage( loadAsset( "brokenpencil.jpg" ) );
    mTex = gl::Texture2d::create( img );
    gl::Fbo::Format format;
    setWindowSize(1000, 800);
    mLoc.x = Rand::randFloat(20, 600);
    mLoc.y = Rand::randFloat(20, 600);
    mDir = vec2(3, 3);
    myFBO = gl::Fbo::create(580, 580, format);
    //mShaderBlur->uniform( "blurRadius", 5.0f );
    
}

void drawing_somewhatRandomApp::mouseDown( MouseEvent event )
{
}

void drawing_somewhatRandomApp::update()
{
}

void drawing_somewhatRandomApp::draw()
{
    gl::clear(Color(255,255,255));
    gl::color(1, 1, 1);
    myFBO->bindFramebuffer();
    drawIntoBuffer();
    myFBO->unbindFramebuffer();
    moveSmooth();
    gl::clear(Color(255,255,255));
    gl::draw( myFBO->getColorTexture(), Rectf( 20, 20, 600, 600 ));
    gl::color(0, 1, 1);
    gl::drawStrokedRect(Rectf(20, 20, 375, 465)); // this scoped viewport is destroying me this is temporary
    gl::color(1,1,1);
    gl::draw( mTex, Rectf( 400,300,1000,800 ));
    
    counter++;
}

void drawing_somewhatRandomApp::moveSmooth(){
    if(Rand::randInt(100) == 1)
    {
        mDir.x = Rand::randFloat(-8.0f, 8.0f);
    }
    if(Rand::randInt(100) == 1)
    {
        mDir.y = Rand::randFloat(-8.0f, 8.0f);
    }
    
    if(mLoc.x > 600 || mLoc.x <= 20){
        mDir.x *= -1;
    }
    if(mLoc.y > 600 || mLoc.y <= 20){
        mDir.y *= -1;
    }
    if(counter % 40 == 0)
    {
        mRad += Rand::randFloat(-2, 2);
    }
    mLoc += mDir;
}

void drawing_somewhatRandomApp::drawIntoBuffer() {
    gl::ScopedFramebuffer buffer(myFBO);
    gl::ScopedViewport view(ivec2(0), myFBO->getSize());
    if(counter >= 800 || firstTime){
        gl::clear(Color(255, 255, 255));
        firstTime = false;
        counter = 0;
        mRad = 10;
        mLoc.x = Rand::randFloat(20, 600);
        mLoc.y = Rand::randFloat(20, 600);
    }
    gl::ScopedColor color(Color(0,1,1));
    gl::drawSolidCircle(mLoc, mRad);
}

CINDER_APP( drawing_somewhatRandomApp, RendererGl )
