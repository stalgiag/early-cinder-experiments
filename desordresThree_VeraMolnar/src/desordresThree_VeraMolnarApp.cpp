#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Cell.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;
using std::list;

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
    std::list<Cell> mCells;
};

void desordresThree_VeraMolnarApp::prepareSetting(Settings *settings)
{
    
}

void desordresThree_VeraMolnarApp::setup()
{
    setWindowSize(800, 800);
    setFrameRate(8.0);
    for(int i=0; i<app::getWindowWidth(); i+=100){
        for (int j=0; j<app::getWindowHeight(); j+=100) {
            mCells.push_back(Cell(i, j));
        }
    }
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
    for (list<Cell>::iterator p = mCells.begin();p != mCells.end(); p++) {
        p->display();
    }
}





CINDER_APP( desordresThree_VeraMolnarApp, RendererGl )
