#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void prepareSettings( Settings* settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	float brightness;
	float brightness2;
	float brightness3;
	Surface* mySurface;
	static const int kTextureSize = 1024; //must be a root of 2
	gl::Texture myImage;
};

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(800,600);
	(*settings).setResizable(false);
}

void CatPictureApp::setup()
{
	//Loaded my picture from the Asset folder
	mySurface = new Surface(kTextureSize,kTextureSize,false);
	brightness = 0.0;
	brightness2 = 0.2;
	brightness3 = .5;
	
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	brightness = brightness + 0.01;
	if(brightness > 1.0f) {
		brightness = 0.0f;
	}
	brightness2 = brightness2 + 0.02;
	if(brightness2 > 1.0f) {
		brightness2 = 0.0f;
	}
	brightness3 = brightness3 + 0.01;
	if(brightness3 > 1.0f) {
		brightness3 = 0.0f;
	}
}

void CatPictureApp::draw()
{
	// clear out the window with black
	
	gl::clear( Color( brightness, brightness2, brightness3 ) );
	gl::drawSolidCircle( Vec2f ( 20.0f, 25.0f ), 50.0f, 8);
	//gl::draw( *mySurface );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
