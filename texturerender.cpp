#include "texturerender.h"

TextureRender::TextureRender()
{
}

TextureRender::~TextureRender()
{
	
}

int TextureRender::getDriver()
{
    return driver;
}

bool TextureRender::init()
{
	tex = NULL;
	tex_format = NULL;
	num_colors = 0;
	width, height = 0;
}

void TextureRender::handleEvent()
{
    
}

bool TextureRender::load(std::string filename)
{
	SDL_Surface *surf;

	if ((surf = IMG_Load(filename.c_str())))
	{

		width = surf->w;
		height = surf->h;

		if ((width & (width - 1)) != 0)
		{
			printf("Error loading %s: width is not 2^n\n", filename.c_str());
			return false;
		}

		if ((height & (height - 1)) != 0)
		{
			printf("Error loading %s: height is not 2^n\n", filename.c_str());
			return false;
		}

		//check for alpha channel
		num_colors = surf->format->BytesPerPixel;
		if (num_colors == 4)
		{
			if (surf->format->Rmask == 0x000000ff)
				tex_format = GL_RGBA;
			else
				tex_format = GL_BGRA;
		}
		else if (num_colors == 3) //no alpha
		{
			if (surf->format->Rmask == 0x000000ff)
				tex_format = GL_RGB;
			else
				tex_format = GL_BGR;
		}
		else
		{
			printf("Error loading %s: non-truecolor format\n", filename.c_str());
			return false;
		}
		
		glEnable(GL_TEXTURE_2D);
		//bind and format GL textures
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, num_colors, width, height, 0, 
			tex_format, GL_UNSIGNED_BYTE, surf->pixels);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		printf("Error loading %s: invalid file\n", filename.c_str());
		return false;
	}
	if (surf)
		SDL_FreeSurface(surf);

	return true;
}

void TextureRender::scale(int w, int h)
{
	width = w;
	height = h;
}

void TextureRender::cleanup()
{	
	glDeleteTextures(1, &tex);	
	
	tex = NULL;
	tex_format = NULL;
}

void TextureRender::update(int deltaTime)
{
	
}

int TextureRender::draw(Coord xy, float z, float r)
{	return draw(xy.x, xy.y, z, r);	}

int TextureRender::draw(float x, float y, float z, float r)
{
	glEnable(GL_TEXTURE_2D);
	//vertex offsets
	float tX = width/2.0f;
	float tY = height/2.0f;
	//fetch tex
	glBindTexture(GL_TEXTURE_2D, tex);
	//save modelview mat
	glPushMatrix();
	//apply mat transformations
	glTranslatef(x, y, z);
	glRotatef(r, 0.0f, 0.0f, 1.0f);
	//draw texture to screen 
	// (winding order is clockwise starting top left)
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3i(-tX, -tY, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3i(tX, -tY, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3i(tX, tY, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3i(-tX, tY, 0);
	glEnd();
	//restore modelview
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	return 1;
}

int TextureRender::getWidth()
{	return width;	}

int TextureRender::getHeight()
{	return height;	}