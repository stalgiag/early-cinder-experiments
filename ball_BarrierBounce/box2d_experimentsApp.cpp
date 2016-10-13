#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include <stdio.h>
#include <fstream>
#include <string.h>

#include "Box2d.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using std::list;

class box2d_experimentsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void addBall( const vec2 &pos);
    void deleteBarriers();
    void makeBarrier();
    void drawDeleteBox();
    void makeGround();
    void readTextFile();
    void makeWalls();
    
    b2World     *world;
    vector<b2Body*> balls;
    b2EdgeShape edgeShape;
    std::vector<b2Body*> toDestroy;
    
    std::list<vec2> points;
    
    bool switcher = false;
    bool newLine = false;
    
    long int counter = 0;
    
    gl::Texture2dRef text;
    Font myFont = Font( "Comic Sans MS", 9 );
    gl::TextureFontRef textureFont = gl::TextureFont::create( myFont );
    
    
    string textFile = loadString(loadAsset("text.txt"));
    std::vector<std::string> mWords;
    int word;
    std::vector<int> words;
    
    
    
    vec2 dbuttonTopLeft = vec2(50,50);
    vec2 dbuttonBottonRight = vec2(150, 150);
    
};



void box2d_experimentsApp::setup()
{
    setWindowSize(1000, 800);
    
    b2Vec2 gravity(0.0f, 10.0f);
    world = new b2World(gravity);
    
    makeGround();
    makeWalls();
    
    readTextFile();
    
}




void box2d_experimentsApp::update()
{
    for(int i=0; i<10; ++i)
    {
        world->Step(1/30.0f, 10, 10);
    }
    for ( b2Body *body : toDestroy)
    {
        body->GetWorld()->DestroyBody (body);
    }
    toDestroy.clear();
}




void box2d_experimentsApp::draw()
{
    if(counter <= 0)
    {
        addBall(vec2(getWindowWidth()/2 +randInt(-7,7), 0));
        counter = 100;
        word = randInt(0,mWords.size());
    }
    --counter;
    
    
	gl::clear();
    gl::color(1, 1, 1);

    
    gl::drawLine(points.front(), points.back());
    
    if (newLine)
    {
        makeBarrier();
        newLine = false;
    }
    
    for( const auto &ball : balls ) {
        gl::pushModelMatrix();
        gl::translate( ball->GetPosition().x, ball->GetPosition().y );
        
        gl::rotate( ball->GetAngle() );
        textureFont->drawString(mWords[word], vec2( 0,0));
        gl::color( 1, 0.5f, 0.25f );
        gl::drawStrokedCircle(vec2(0,0), 30);
        gl::popModelMatrix();
    }

    drawDeleteBox();
    
}




void box2d_experimentsApp::makeGround()
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, getWindowHeight());
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    b2PolygonShape groundBox;
    
    groundBox.SetAsBox(getWindowWidth(), 10.0f);
    
    groundBody->CreateFixture(&groundBox, 0.0f);
}



void box2d_experimentsApp::makeWalls()
{
    b2BodyDef wallBodyDefRight;
    b2BodyDef wallBodyDefLeft;
    
    wallBodyDefRight.position.Set(getWindowWidth(), 0.0f);
    wallBodyDefLeft.position.Set(0.0f, 0.0f);
    
    b2Body* wallBodyRight = world->CreateBody(&wallBodyDefRight);
    b2Body* wallBodyLeft = world->CreateBody(&wallBodyDefLeft);
    
    b2PolygonShape rightBox;
    b2PolygonShape leftBox;
    
    rightBox.SetAsBox(10.0f, getWindowHeight());
    leftBox.SetAsBox(10.0f, getWindowHeight());
    
    wallBodyRight->CreateFixture(&rightBox, 0.0f);
    wallBodyLeft->CreateFixture(&leftBox, 0.0f);
}




void box2d_experimentsApp::readTextFile()
{
    std::size_t pos = 0, found;
    
    while((found = textFile.find_first_of(' ', pos)) != std::string::npos)
    {
        mWords.push_back(textFile.substr(pos, found - pos));
        pos = found+1;
    }
    mWords.push_back(textFile.substr(pos));
    
    word = randInt(0,mWords.size());
}




void box2d_experimentsApp::addBall(const vec2 &pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set( pos.x, pos.y );
    
    b2Body *body = world->CreateBody( &bodyDef );
    
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = 30;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f; // bounce
    
    body->CreateFixture( &fixtureDef );
    balls.push_back( body );
    
}




void box2d_experimentsApp::mouseDown( MouseEvent event )
{
    if(event.getPos().x < dbuttonBottonRight.x && event.getPos().y < dbuttonBottonRight.y && event.getPos().x > dbuttonTopLeft.x && event.getPos().y > dbuttonTopLeft.y)
    {
        deleteBarriers();
    }
    else
    {
        points.push_back(event.getPos());
        if (points.size() == 2)
        {
            newLine = true;
        }
        
        if (points.size()>2)
        {
            points.clear();
            points.push_back(event.getPos());
        }
    }
}




void box2d_experimentsApp::makeBarrier()
{
    b2BodyDef line;
    b2Body* barrier = world->CreateBody(&line);
    
    b2EdgeShape shape;
    shape.Set(b2Vec2(points.front().x, points.front().y), b2Vec2(points.back().x, points.back().y));
    barrier->CreateFixture(&shape, 0.0f);
}




void box2d_experimentsApp::drawDeleteBox()
{
    gl::color(.9,.9,.9);
    gl::drawSolidRect(Rectf(dbuttonTopLeft.x, dbuttonTopLeft.y, dbuttonBottonRight.x, dbuttonBottonRight.y));
    gl::color(0,0,0);
    textureFont->drawString("RESET", vec2(dbuttonTopLeft.x+30, dbuttonTopLeft.y+50) );
}




void box2d_experimentsApp::deleteBarriers()
{
    auto bodies = world->GetBodyList();
    while (bodies != NULL)
    {
        toDestroy.push_back(bodies);
        bodies = bodies->GetNext();
    }
    
    //remake ground because I suck
    makeGround();
    makeWalls();
    gl::clear();
    balls.clear();
    points.clear();
}


CINDER_APP( box2d_experimentsApp, RendererGl )
