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
	void drawCircle(uint8_t* pixels);
	int frames;
};

void CatPictureApp::drawRectangles(uint8_t* pixels){
	int rect_Start = 0;
	int rect_Height = 10;
	int rect_Width = 20;
	int color_Start = 0;
	int color_Max = 255;

	Color8u c;
	while(rect_Start < kAppHeight){
	for(int y = rect_Start; y < rect_Height; y++){
		for(int x = rect_Start; x < rect_Width; x++){
			c = Color8u(color_Start, color_Start, color_Start);
			color_Start++;
			pixels[3*(x + y*kTextureSize)] = c.r;
			pixels[3*(x + y*kTextureSize)+1] = c.g;
			pixels[3*(x + y*kTextureSize)+2] = c.b;
			if(color_Start > color_Max){
				color_Start = 0;
			}
			
		}
	}

	rect_Start = rect_Start+rect_Height + 10;
	if(rect_Height < rect_Start){
		rect_Height = rect_Start + rect_Height;
	}

	if(rect_Width < rect_Start){
		rect_Width = rect_Start + rect_Width;
	}
}
}

void CatPictureApp::drawCircle(uint8_t* pixels){

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
