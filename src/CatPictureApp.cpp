/**
 * @file CatPictureApp.cpp
 * CSE 274 - Fall 2012
 * My solution for HW01.
 *
 * @author Bridget Brener
 * @date 2012-09-04
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 *
 * @note This project satisfies goals A.1 (rectangle), A.2 (circle), A.3 (line),
 * A.7 (triangle), B.1 (blur), and E.6 (mouse interaction)
 */

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

	//constants to keep my window size correct and uniform
	static const int kTextureSize = 1024; //must be a square of 2
	static const int kAppHeight = 600;
	static const int kAppWidth = 800;
	static const int kColorMax = 255;

	//Methods that I created to help draw my face
	void drawRectangles(uint8_t* pixels);
	void drawCircle(uint8_t* pixels, int y_Center, int x_Center, int radius, int cG, int cB, int cR);
	void colorWholeSurface(uint8_t* pixels, int cG, int cB, int cR);
	void drawLine(uint8_t* pixels, int x_beg, int y_beg, int x_end, int y_end);
	void drawTriangle(uint8_t* pixels);
	void blurSurface(uint8_t* pixels);
	int cG;
	int cB;
	int cR;
};

	/*
	* Method to draw a rectangle, satisfies the rectangle requirement in A.1
	* This draws a blue triangle that is used for the mouth of the face
	* starting at (250, 450) and extending to (550, 550).
	*/
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

	/*
	* Method to draw circles, satisfies the circle requirement in A.2
	* This draws a circle at a specified place.  It takes the center y point and center x point,
	* then it takes the desired radius of the circle along with the green, blue, and red integers
	* of what color the user desires the circle to be. These circles are used as eyes, pupils,
	* and a nose.
	*/
void CatPictureApp::drawCircle(uint8_t* pixels, int y_Center, int x_Center, int radius, int cG, int cB, int cR){
	Color8u c;

	for(int y = y_Center - radius; y <= y_Center+radius; y++){
		for(int x = x_Center - radius; x <= x_Center+radius; x++){
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

	/*
	* Method to draw lines using Bresenhams line algorithm, satisfies the line requirement in A.3
	* This draws a white line between two specified points.  It takes the beginning x point, beginning y
	* point, ending x point, and ending y point.  I used part of the code from
	* http://programming-technique.blogspot.com/2012/01/implementing-bresenhams-line-drawing.html
	* These lines are used as eyebrows.
	*/
void CatPictureApp::drawLine(uint8_t* pixels, int x_beg, int y_beg, int x_end, int y_end){
	Color8u c = Color8u(255, 255, 255);
	int x_change = abs(x_beg - x_end), y_change = abs(y_beg - y_end);
	int p = 2* y_change - x_change;
	int two_change_y = 2*y_change, two_change_x_y = 2*(y_change - x_change);
	int x, y, end;

	if(x_beg > x_end){
		x = x_end;
		y = y_end;
		end = x_beg;
	}
	else{
		x = x_beg;
		y = y_beg;
		end = x_end;
	}
	
	pixels[(3*(x + y*kTextureSize))] = c.r;
	pixels[(3*(x + y*kTextureSize)+1)] = c.g;
	pixels[(3*(x + y*kTextureSize)+2)] = c.b;

	while(x < end){
		x++;
		if(p<0){
			p += two_change_y;
		}
		else{
			y++;
			p += two_change_x_y;
		}

		pixels[(3*(x + y*kTextureSize))] = c.r;
		pixels[(3*(x + y*kTextureSize)+1)] = c.g;
		pixels[(3*(x + y*kTextureSize)+2)] = c.b;
	}
}

	/*
	* Method to draw two right triangles, satisfies the triangle requirement in A.7
	* This draws a white triangle in the bottom left corner and in the top right corner.
	*/
void CatPictureApp::drawTriangle(uint8_t* pixels){
	Color8u c = Color8u(250,250,250);

	//Triangle in bottom left corner
	for(int y = 400; y < kAppHeight; y++){
		for(int x = 0; x < (y-400); x++){
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
		}
	}

	//Triangle in top right corner
	for(int y = 200; y > 0; y--){
		for(int x = 800; x > (y+600); x--){
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
		}
	}
}

	/*
	* Method to fill the surface with a specific color.  It takes the pixels
	* array, and three ints for the green color, blue color, and red color
	*/
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

	/*
	* Method to blur the surface pixels with the pixels around them, satisfies the blur requirement in B.1
	* This should take each pixel, minus the edge pixels, take the average of all pixels around the specific
	* pixel, and return that color the specified pixel.
	* Took code from http://processing.org/learning/pixels/
	*/
void CatPictureApp::blurSurface(uint8_t* pixels){

	//Create a copy of the surface
	static uint8_t work_buffer[3*kTextureSize*kTextureSize];
	memcpy(work_buffer, pixels, 3*kTextureSize*kTextureSize);
	int offset;
	Color8u c;
	uint8_t* red = 0;
	uint8_t* green = 0;
	uint8_t* blue = 0;

	//kernels to blur image
	float kernelA[9] = {1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0, 1/9.0};

	for(int y = 1; y < kAppHeight; y++){
		for(int x = 1; x < kAppWidth; x++){
			offset = 3*(x+y*kAppWidth);
			red = 0;
			green = 0;
			blue = 0;

			for(int i = 0; i < 9; i++){
				for(int j = 0; j < 9; j++){
					offset = 3*(x+j + (y+i)*kTextureSize);
					int k = kernelA[j + i*3];
					int xloc = x+i-offset;
					int yloc = y+j-offset;
					int loc = xloc + yloc*kAppWidth;

					red += (work_buffer[offset] >> k);
					green += (work_buffer[offset+1] >> k);
					blue += (work_buffer[offset+2] >> k);
				}
			}
			c = Color8u((int)red, (int)green, (int)blue);
			pixels[(3*(x + y*kTextureSize))] = c.r;
			pixels[(3*(x + y*kTextureSize)+1)] = c.g;
			pixels[(3*(x + y*kTextureSize)+2)] = c.b;
		}
	}
}

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup()
{
	mySurface = new Surface(kTextureSize,kTextureSize,false);
}

/*
* Method that pops up a message box when the user clicks on the screen.
* This satisfies requirement E.6
*/
void CatPictureApp::mouseDown( MouseEvent event )
{
	uint8_t* pixels = (*mySurface).getData();
	MessageBox(NULL, L"Hello, my name is Bobby.", NULL, MB_OK);
}

void CatPictureApp::update()
{
	uint8_t* pixels = (*mySurface).getData();

	colorWholeSurface(pixels, 0,0,0);
	
	//draws the mouth
	drawRectangles(pixels);

	//draws the mustache
	drawLine(pixels, 250, 50, 300, 100);
	drawLine(pixels, 550, 50, 600, 100);

	//draws the eyes
	drawCircle(pixels, 150, 250, 50, 20, 230, 100);
	drawCircle(pixels, 150, 550, 50, 20, 230, 100);

	//draws the nose
	drawCircle(pixels, 250, 400, 25, 125, 125, 125);

	//draws the pupils
	drawCircle(pixels, 175, 260, 10, 0, 0, 0);
	drawCircle(pixels, 175, 560, 10, 0, 0, 0);

	//draws the triangles
	drawTriangle(pixels); 

	blurSurface(pixels);

	//Saves the image to a png file, satisfies requirement D
	writeImage("brennerCatPic.png",*mySurface);
}

void CatPictureApp::draw()
{
	gl::draw( *mySurface );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
