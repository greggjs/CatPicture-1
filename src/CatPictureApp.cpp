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
	Surface* mySurface;
	static const int kTextureSize = 1024; //must be a square of 2
	static const int kAppHeight = 600;
	static const int kAppWidth = 800;
	void drawRectangles(uint8_t* pixels);
	int frames;
};

void CatPictureApp::drawRectangles(uint8_t* pixels){
	int rect_Height_Start = 5;
	int rect_Width_Length = 10;
	int rect_Height_Length = 15;
	int rect_Width_Start = 3;

	Color8u c = Color8u(255,0,0);
	for(int y = 100; y < 300; y++){
		for(int x = 100; x < 200; x++){
			pixels[3*(x + y*kTextureSize)] = c.r;
			pixels[3*(x + y*kTextureSize)+1] = c.g;
			pixels[3*(x + y*kTextureSize)+2] = c.b;
		}
	}
	/*for(int y = rect_Width_Start; y <= rect_Width_Length; y++){
		for(int x = rect_Height_Start; x <= rect_Width_Length; x++){
			int index = (x+y)*3;
			pixels[index] = 34;
		}
	}*/

	
}

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup()
{
	//Loaded my picture from the Asset folder
	mySurface = new Surface(kTextureSize,kTextureSize,false);
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	uint8_t* pixels = (*mySurface).getData();

	/*
	for(int y = 5; y<kAppHeight; y+5) {
		int index = (y*kTextureSize +5)*3;
		pixels[index] = 100;
	}
	for(int y=0; y<kAppHeight; y++){
		for(int x=0; x<kAppWidth; x++){
			int index = (y*kTextureSize + x)*3;
			pixels[index] = 255;
		}
	}*/
	
	drawRectangles(pixels);
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::draw( *mySurface );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
