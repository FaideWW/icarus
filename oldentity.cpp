/*
#include "oldentity.h"

#include <iostream>
#include <cmath>

OldEntity::OldEntity()
{
	r = NULL;
	c = NULL;
	b = NULL;
	isUp, isRight, isDown, isLeft, isSpace = false;
}

OldEntity::~OldEntity()
{
	r = NULL;
	c = NULL;
	b = NULL;
}

void OldEntity::init()
{
	r = new TextureRender();
	c = new Controller();
	b = new Collider();
	r->init();
	b->setBoxDisplay(true);
}

bool OldEntity::load(std::string tex_filepath)
{
	bool ret = r->load(tex_filepath);
	Coord xy = {0,0};
	b->setBoundingBox(xy, r->getWidth(), r->getHeight());
	return ret;
}

void OldEntity::onEvent(SDL_Event event)
{
	
	if (event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT:
			{
				isLeft = true;
				break;
			}
			case SDLK_RIGHT:
			{	
				isRight = true;
				break;
			}
			case SDLK_UP:
			{
				isUp = true;
				break;
			}
			case SDLK_DOWN:
			{
				isDown = true;
				break;
			}
			case SDLK_SPACE:
			{
				isSpace = true;
				break;
			}
			default:
				break;
		}	
	}
	else if (event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT:
			{
				isLeft = false;
				break;
			}
			case SDLK_RIGHT:
			{	
				isRight = false;
				break;
			}
			case SDLK_UP:
			{
				isUp = false;
				break;
			}
			case SDLK_DOWN:
			{
				isDown = false;
				break;
			}
			case SDLK_SPACE:
			{
				isSpace = false;	
				break;
			}
			default:
				break;
		}	
	}
}


/**
 *
 *
 *				APRIL 11 2012
 *			------------------this is broken, I need to fix it tomorrow
 *
 *				APRIL 16 2012
 *			------------------es fixed, and is delegated to the collider
 *
 *
 *
bool OldEntity::checkCollisions(Map m, int deltaTime)
{
	int action = m.collide(b, c, deltaTime);
	if (action >= 0 && action < 4)
	{
		Coord newXY = b->reactToCollision(c, action, deltaTime);
		reposition(newXY);
		return true;
	}
	return false;
}

void OldEntity::reposition(Coord xy)
{
	c->setPosition(xy);
	b->moveBoundingBox(xy);
}

void OldEntity::update(int deltaTime, Map m)
{
	if (isUp)
		c->setYVelocity(c->getYVelocity() - 1);
	if (isRight)
		c->setXVelocity(c->getXVelocity() + 1);
	if (isDown)
		c->setYVelocity(c->getYVelocity() + 1);
	if (isLeft)
		c->setXVelocity(c->getXVelocity() - 1);
	if (isSpace)
	{
		c->setXVelocity(c->getXVelocity() / 1.1);
		c->setYVelocity(c->getYVelocity() / 1.1);
	}
	
	
	if (!checkCollisions(m, deltaTime))
	{
		c->move(deltaTime);
		b->moveBoundingBox(c->getPosition());
	}
}

void OldEntity::draw()
{
	r->draw(c->getPosition(), c->getZ(), 0);
	b->draw();
}

void OldEntity::cleanup()
{
	r->cleanup();
	b->cleanup();
	delete r;
	delete c;
	delete b;
}

void OldEntity::setPosition(float x, float y)
{
	Coord xy;
	xy.x = x;
	xy.y = y;
	c->setPosition(xy);
	b->moveBoundingBox(xy);
}

void OldEntity::translate(float x, float y)
{
	Coord xy;
	xy.x += x;
	xy.y += y;
	c->setPosition(xy);
	b->moveBoundingBox(xy);
}


void OldEntity::resize(int w, int h)
{
	r->scale(w, h);
	b->setBoundingBox(b->getBoundingBox()->getPosition(), w, h);
}

Controller *OldEntity::control()
{
	return c;
}

TextureRender *OldEntity::render()
{
	return r;
}

Collider *OldEntity::boundingbox()
{
	return b;
}
*/