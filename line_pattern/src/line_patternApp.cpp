#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/FBO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include  <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class line_patternApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void drawRow(int y);
    void drawIntoBuffer();
    
    gl::FboRef myFBO;
};

void line_patternApp::setup()
{
    setWindowSize(1100, 800);
    gl::Fbo::Format format;
    myFBO = gl::Fbo::create(1100, 800, format);
}

void line_patternApp::mouseDown( MouseEvent event )
{
}

void line_patternApp::update()
{
}

void line_patternApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    myFBO->bindFramebuffer();
    drawIntoBuffer();
    myFBO->unbindFramebuffer();
    
}

void line_patternApp::drawRow(int y){
    gl::drawLine(vec2(y,y-10), vec2(y,y));
    gl::drawLine(vec2(0, y), vec2(getWindowWidth()-10,y));
    gl::drawLine(vec2(getWindowWidth()-10,y), vec2(getWindowWidth()-10,y+5));
    for (int i=getWindowWidth()-10; i>20; i-=30) {
        gl::drawLine(vec2(i,y+5), vec2(i-10,y+5));
        if (randInt(100) >= 50) {
            gl::drawLine(vec2(i-10,y+5), vec2(i-10,y-5));
            gl::drawLine(vec2(i-10,y-5), vec2(i-20,y-5));
            gl::drawLine(vec2(i-20,y-5), vec2(i-20,y+5));
            gl::drawLine(vec2(i-20,y+5), vec2(i-30,y+5));
        }
        gl::drawLine(vec2(i-10,y+5), vec2(i-30,y+5));
    }
}

void line_patternApp::drawIntoBuffer(){
    gl::ScopedFramebuffer buffer(myFBO);
    gl::ScopedViewport(0,800,1000,800);
    gl::color(.4, .5, .7);
    gl::drawSolidCircle(vec2(getWindowWidth()/2, getWindowHeight()/2), 100);
    for (int i=10; i<getWindowHeight(); i+=10) {
        drawRow(i);
    }
    gl::ScopedColor color(Color(1,1,1));
}

CINDER_APP( line_patternApp, RendererGl )
