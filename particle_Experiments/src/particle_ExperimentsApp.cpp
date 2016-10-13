#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

struct Particle
{
    vec3    pos;
    vec3    ppos;
    vec3    home;
    ColorA  color;
    float   damping;
    
};

cont int NUM_PARTICLES = 600e3;


class particle_ExperimentsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
private:
    gl::GlslProgRef mRenderProg;
    gl::GlslProgRef mUpdateProg;
    
    gl::VaoRef  mAttributes[2];
    gl::VboRef  mParticleBuffer[2];
    
    std::uint32_t   mSourceIndex    =0;
    std::uint32_t   mDestinationIndex =1;
    
    bool            mMouseDown = false;
    float           mMouseForce = 0.0f;
    vec3            mMousePos = vec3(0,0,0);
};

void particle_ExperimentsApp::setup()
{
}

void particle_ExperimentsApp::mouseDown( MouseEvent event )
{
}

void particle_ExperimentsApp::update()
{
}

void particle_ExperimentsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( particle_ExperimentsApp, RendererGl )
