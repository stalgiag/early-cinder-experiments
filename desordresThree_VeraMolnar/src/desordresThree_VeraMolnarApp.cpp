#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class desordresThree_VeraMolnarApp : public App {
  public:
    void prepareSetting(Settings *settings);
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void makeSquare(int topLeft, int bottomLeft, int topRight, int bottomRight);
    void makeInsetSquares(int x, int y);
    void drawAllInsets();
    int rectSize = 80;
};

void desordresThree_VeraMolnarApp::prepareSetting(Settings *settings)
{
    
}

void desordresThree_VeraMolnarApp::setup()
{
    setWindowSize(800, 800);
    setFrameRate(8.0);
    
    //////////////////////////////////////
    /*As far as I can tell I can't write to the graphics buffer from setup to get a still-image
     it looks like opengl is still accessing the videocard's graphics buffer at a loop with the framerate even
     when nothing new is being drawn to it
     
     So for now I guess it is stuck animating. I will make a class for the cells so they can remember which rects they 
     have later. :/
     */
    /////////////////////////////////////
}

void desordresThree_VeraMolnarApp::mouseDown( MouseEvent event )
{
}

void desordresThree_VeraMolnarApp::update()
{
}

void desordresThree_VeraMolnarApp::draw()
{
    gl::clear(Color(255,255,255));
    drawAllInsets();
}

////Draws square
void desordresThree_VeraMolnarApp::makeSquare(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
    gl::drawStrokedRect( Rectf( topLeftX, topLeftY, bottomRightX, bottomRightY), 1);
}


////Draws cell with inset squares (which each have an 80% chance to not exist)
void desordresThree_VeraMolnarApp::makeInsetSquares(int x, int y){
    for (int k=0;k<rectSize;k+=8){
        if(Rand::randInt(0,100) >= 20){
            makeSquare(x+k, y+k, x+(rectSize-k), y+(rectSize-k));
        }
    }
}

////Draws multiple cells with inset squares

void desordresThree_VeraMolnarApp::drawAllInsets()
{
    gl::color( 0, 0, 1 ); // set color to blue
    for(int i=0; i<app::getWindowWidth(); i+=80){
        for (int j=0; j<app::getWindowHeight(); j+=80) {
            makeInsetSquares(i, j);
        }
    }
}




CINDER_APP( desordresThree_VeraMolnarApp, RendererGl )
