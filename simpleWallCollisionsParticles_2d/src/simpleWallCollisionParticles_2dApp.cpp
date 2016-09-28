#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Particle.h"
#include "ParticleController.h"
#include "cinder/Text.h"
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;

class simpleWallCollision_App : public App {
public:
    void prepareSettings(Settings *settings);
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    Font mFont;
    
    
    ParticleController mParticleController;
};

void simpleWallCollision_App::prepareSettings(Settings *settings){
    settings->setWindowSize(1000, 800);
    settings->setFrameRate(60.0f);
}

void simpleWallCollision_App::setup()
{
    mParticleController.addParticles(500);
}

void simpleWallCollision_App::mouseDown( MouseEvent event )
{
}

void simpleWallCollision_App::update()
{
    mParticleController.update();
}

void simpleWallCollision_App::draw()
{
    gl::clear( Color(0.2f, 0.2f, 0.2f) );
    mParticleController.draw();
    cout << "Average FPS: " + to_string(getAverageFps()) + "!\n";
}

CINDER_APP( simpleWallCollision_App, RendererGl )
