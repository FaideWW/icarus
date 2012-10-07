#include "colorrender.h"

ColorRender::ColorRender()
{
	c.r = 0.0f;
	c.g = 0.0f;
	c.b = 0.0f;
	c.a = 0.0f;
	width, height = 0;
}

ColorRender::~ColorRender()
{
	c.r = 0.0f;
	c.g = 0.0f;
	c.b = 0.0f;
	c.a = 0.0f;
	width, height = 0;
}

int ColorRender::getDriver()
{
    return driver;
}

bool ColorRender::init()
{
    return true;
}

void ColorRender::handleEvent()
{
    
}

void ColorRender::update(int deltaTime)
{
    
}

int ColorRender::load(Color c, int w, int h)
{
	return load(c.r, c.g, c.b, c.a, w, h);
}

int ColorRender::load(float r, float g, float b, float a, int w, int h)
{
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;

	width = w;
	height = h;
	return 1;
}

void ColorRender::scale(int w, int h)
{
	width = w;
	height = h;
}

void ColorRender::setColor(Color newC)
{	c = newC;	}

int ColorRender::draw (Coord xy, float z, float r)
{	return draw(xy.x, xy.y, z, r);	}

//color sprites render differently than textured sprites;
// the origin is set top left instead of center (to fix rounding issues)
// TODO: should probably do this to texture rendering too, but is not currently a problem
int ColorRender::draw(float x, float y, float z, float r)
{

	//save modelview mat
	glPushMatrix();
	//apply mat transformations
	glTranslatef(x, y, z);
	glRotatef(r, 0.0f, 0.0f, 1.0f);
	//set the color
	glColor4f(c.r, c.g, c.b, c.a);
	// (winding order is clockwise starting top left)
	glBegin(GL_QUADS);
		glVertex3i(0, 0, 0);
		glVertex3i(width, 0, 0);
		glVertex3i(width, height, 0);
		glVertex3i(0, height, 0);
	glEnd();
	//restore the color
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//restore modelview
	glPopMatrix();
	
	return 1;
}

void ColorRender::cleanup()
{		}

Color ColorRender::getColor()
{	return c;	}

int ColorRender::getWidth()
{	return width;	}

int ColorRender::getHeight()
{	return height;	}