#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#define PI 3.14159;

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
	static const int kColorMax = 255;
	void drawRectangles(uint8_t* pixels);
	void drawCircle(uint8_t* pixels);
	void colorWholeSurface(uint8_t* pixels);
	void drawLine(uint8_t*);
	int frames;
};

void CatPictureApp::drawRectangles(uint8_t* pixels){
	int rect_Start = 0;
	int rect_Height = 10;
	int rect_Width = 20;
	int cR = 200;
	int cG = 100;
	int cB = 0;

	Color8u c;
	while(rect_Start <= kAppHeight && rect_Start <= kAppWidth){
	for(int y = rect_Start; y < rect_Height; y++){
		for(int x = rect_Start; x < rect_Width; x++){
			c = Color8u(cG,cB,cR);
			cG++;
			cB++;
			cR++;
			//pixels[(3*(x + y*kTextureSize))] = c.r;
			//pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;

			if(cR > kColorMax){
				cR = 0;
			}
			if(cG > kColorMax){
				cG = 0;
			}
			if(cB > kColorMax){
				cB = 0;
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
	int y_Center = 10;
	int x_Center = 10;
	int radius = 5;
	Color8u c;
	int cR = 200;
	int cG = 100;
	int cB = 200;

	while(x_Center <= kAppWidth && y_Center <= kAppHeight) {
	for(int y = y_Center - radius; y <= y_Center+radius; y++){
		for(int x = x_Center - radius; x <= x_Center+radius; x++){
			//int dist = (
			c = Color8u(cG,cB,cR);
			cG++;
			cB++;
			cR++;
			pixels[(3*(x + y*kTextureSize))] = c.r;
			//pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			//pixels[(3*(x + y*kTextureSize)+2)] = c.b;
			//pixels[(3*(y*kTextureSize-x))] = c.r;
			//pixels[(3*(y*kTextureSize-x)+1)] = c.g;
			//pixels[(3*(y*kTextureSize-x)+2)] = c.b;

			if(cR > kColorMax){
				cR = 0;
			}
			if(cG > kColorMax){
				cG = 0;
			}
			if(cB > kColorMax){
				cB = 0;
			}
		}
	}
	y_Center = y_Center*2+radius;
	x_Center = x_Center*2+radius;
	}
}

void CatPictureApp::drawLine(uint8_t*){

}

void CatPictureApp::colorWholeSurface(uint8_t* pixels){
	Color8u c;
	int cR = 0;
	int cG = 100;
	int cB = 200;

	for(int y = 0; y <= kAppHeight; y++){
		for(int x = 0; x <= kAppWidth; x++){		
			c = Color8u(cR, cG, cB);
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
			for(int i = cR; i <= kColorMax; i++){
			cR++;
			if(cR > kColorMax){
				cR=0;
			}
		}
	}	
	}
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
	
	colorWholeSurface(pixels);
	drawRectangles(pixels);
	//drawCircle(pixels);
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::draw( *mySurface );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
