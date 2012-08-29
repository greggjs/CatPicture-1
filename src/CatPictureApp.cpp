#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	float brightness;
	float brightness2;
	Surface* mySurface;
	gl::Texture myImage;
};

void CatPictureApp::prepareSettings( Settings *settings) 
{
	//set the window size to 800 by 600
	settings->setWindowSize( 800, 600 );
	settings->setFrameRate( 60.0f );
}

void CatPictureApp::setup()
{
	//Loaded my picture from the Asset folder
	myImage = gl::Texture( loadImage( loadAsset( "Ballet.jpg" ) ) );
	//mySurface = new Surface(200,200,false);
	//Surface ballet(loadImage( loadResources("Ballet.jpeg"));
	brightness = 0.0;
	brightness2 = 0.3;
	
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
	brightness2 = brightness2 + 0.01;
	if(brightness2 > 1.0f) {
		brightness2 = 0.0f;
	}
}

void CatPictureApp::draw()
{
	// clear out the window with black
	
	gl::clear( Color( brightness, brightness2, brightness ) );
	gl::draw( myImage, getWindowBounds() );
	//gl::draw( mySurface* );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
