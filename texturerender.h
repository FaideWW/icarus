#ifndef _TEXTURERENDER_H_
#define _TEXTURERENDER_H_

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include "component.h"
#include "coord.h"


#include <string>

/**
*	things required to have a Texturerenderer:
*  a path to a texture
*/
class TextureRender
{

private:
	GLuint tex;
	GLenum tex_format;
	GLint num_colors;

	int width, height;
	int driver;

public:
	TextureRender();
	~TextureRender();
	
	int getDriver();
	bool init();
	void handleEvent();
	void update(int deltaTime);
	void cleanup();
	
	bool load(std::string filename);
	void scale(int w, int h);
	int draw(Coord xy, float z, float r);
	int draw(float x, float y, float z, float r);

	int getWidth();
	int getHeight();
};

#endif