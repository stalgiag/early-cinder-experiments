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

class twoD_Particles_w_GravityApp : public App {
public:
    void prepareSettings(Settings *settings);
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    Font mFont;
    
    
    ParticleController mParticleController;
};

void twoD_Particles_w_GravityApp::prepareSettings(Settings *settings){
    settings->setWindowSize(1000, 800);
    settings->setFrameRate(60.0f);
}

void twoD_Particles_w_GravityApp::setup()
{
    mParticleController.addParticles(500);
}

void twoD_Particles_w_GravityApp::mouseDown( MouseEvent event )
{
}

void twoD_Particles_w_GravityApp::update()
{
    mParticleController.update();
}

void twoD_Particles_w_GravityApp::draw()
{
    gl::clear( Color(0.2f, 0.2f, 0.2f) );
    mParticleController.draw();
    cout << "Average FPS: " + to_string(getAverageFps()) + "!\n";
}

CINDER_APP( twoD_Particles_w_GravityApp, RendererGl )
