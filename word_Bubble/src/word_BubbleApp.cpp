#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Particle.h"
#include "ParticleController.h"
#include "cinder/Text.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;

class word_Bubble_App : public App {
public:
    void prepareSettings(Settings *settings);
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    Font mFont;
    gl::Texture2dRef mTex;

    
    ParticleController mParticleController;
};

void word_Bubble_App::prepareSettings(Settings *settings){
    settings->setWindowSize(1080, 800);
    settings->setFrameRate(60.0f);
}

void word_Bubble_App::setup()
{
    setWindowSize(607.5, 1080);
    mParticleController.addParticles(50);
    auto img = loadImage( loadAsset( "background.jpg" ) );
    mTex = gl::Texture2d::create( img );
}

void word_Bubble_App::mouseDown( MouseEvent event )
{
}

void word_Bubble_App::update()
{
    mParticleController.update();
}

void word_Bubble_App::draw()
{
    gl::clear( Color(0.2f, 0.2f, 0.2f) );
    gl::draw( mTex, Rectf( 0,0,getWindowWidth(),getWindowHeight() ));
    gl::color(1, 1, 1);
    mParticleController.draw();
    cout << "Average FPS: " + to_string(getAverageFps()) + "!\n";
}


CINDER_APP( word_Bubble_App, RendererGl )
