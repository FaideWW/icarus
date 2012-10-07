#ifndef _COLORRENDER_H_
#define _COLORRENDER_H_

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include "component.h"
#include "coord.h"

#include <string>
	

/**
*	things required to have a Colorrenderer:
*  a 4bpp color in [0,1] RGBA format
*/
class ColorRender
{

private:
	int width, height;
	int driver;

public:
	ColorRender();
	~ColorRender();
	
	int getDriver();
	bool init();
	void handleEvent();
	void update(int deltaTime);
	void cleanup();
	
	int load(float r, float g, float b, float a, int w, int h);
	int draw(Coord xy, float z, float r);
	int draw(float x, float y, float z, float r);
	
	void scale(int w, int h);
	int getHeight();
};

#endif