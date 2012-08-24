#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	float brightness;
	float brightness2;
};

void CatPictureApp::setup()
{
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
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
