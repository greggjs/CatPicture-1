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
	void drawCircle(uint8_t* pixels, int y_Center, int x_Center, int radius, int cG, int cB, int cR);
	void colorWholeSurface(uint8_t* pixels, int cG, int cB, int cR);
	void drawLine(uint8_t*);
	void blurSurface(uint8_t*);
	int cG;
	int cB;
	int cR;
	int frames;
};

void CatPictureApp::drawRectangles(uint8_t* pixels){
	int rect_X_Start = 250;
	int rect_Y_Start = 450;
	int rect_Height = 550;
	int rect_Width = 550;
	cR = 200;
	cG = 0;
	cB = 0;

	Color8u c;
	for(int y = rect_Y_Start; y < rect_Height; y++){
		for(int x = rect_X_Start; x < rect_Width; x++){
			c = Color8u(cG,cB,cR);
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
		}
	}
}

void CatPictureApp::drawCircle(uint8_t* pixels, int y_Center, int x_Center, int radius, int cG, int cB, int cR){
	Color8u c;

	for(int y = y_Center - radius; y <= y_Center+radius; y++){
		for(int x = x_Center - radius; x <= x_Center+radius; x++){
			//int dist = (
			c = Color8u(cG,cB,cR);
			int dist = (int)sqrt((double)((x-x_Center)*(x-x_Center))+((y-y_Center)*(y-y_Center)));
			if(dist < radius){
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
			}

		}
	}
}

void CatPictureApp::drawLine(uint8_t* pixels){
	Color8u c;
	int color = 0;
	int y_Coord = 300;

	for(int x = 200; x <= 600; x++){
		c = Color8u(color, color, color);
		if(y_Coord <= 400){
		y_Coord++;
		pixels[(3*(x + y_Coord*kTextureSize))] = c.r;
		pixels[(3*(x + y_Coord*kTextureSize)+1)] = c.g;
		pixels[(3*(x + y_Coord*kTextureSize)+2)] = c.b;
		}
		if(y_Coord > 400){
			for(int i = 0; i <= 100; i++){
				y_Coord--;
				pixels[(3*(x + y_Coord*kTextureSize))] = c.r;
				pixels[(3*(x + y_Coord*kTextureSize)+1)] = c.g;
				pixels[(3*(x + y_Coord*kTextureSize)+2)] = c.b;
			}
		}
	}
}

void CatPictureApp::colorWholeSurface(uint8_t* pixels, int cG, int cB, int cR){
	Color8u c;

	for(int y = 0; y <= kAppHeight; y++){
		for(int x = 0; x <= kAppWidth; x++){		
			c = Color8u(cR, cG, cB);
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
		}	
	}
}

void CatPictureApp::blurSurface(uint8_t* pixels){
	static uint8_t work_buffer[3*kTextureSize*kTextureSize];
	memcpy(work_buffer, pixels, 3*kTextureSize*kTextureSize);


}

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup()
{
	//Loaded my picture from the Asset folder
	mySurface = new Surface(kTextureSize,kTextureSize,false);
	cG = 10;
	cB = 250;
	cR = 100;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	uint8_t* pixels = (*mySurface).getData();	

	//How do I keep changing color?
		cG++;
		cB++;
		if(cG > kColorMax){
			cG = 0;
		}
		if(cB > kColorMax) {
			cB = 0;
		}
	colorWholeSurface(pixels, cG, cB, cR);
	drawRectangles(pixels);
	drawLine(pixels);
	drawCircle(pixels, 150, 250, 50, 20, 230, 100);
	drawCircle(pixels, 150, 550, 50, 20, 230, 100);
	drawCircle(pixels, 250, 400, 25, 125, 125, 125);

	//Saves the image to a png file
	writeImage("brennerCatPic.png",*mySurface);
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::draw( *mySurface );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
