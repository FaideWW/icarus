//
//  boundingbox.cpp
//  icarus
//
//  Created by faide on 12-04-03.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "_boundingbox.h"

xAxisAlignedBoundingBox::xAxisAlignedBoundingBox()
{
	p.x = 0;
	p.y = 0;
	
	
	collidableSides.set();
}

xAxisAlignedBoundingBox::xAxisAlignedBoundingBox(Coord _p, float _x, float _y)
{
	p = _p;
	halfVectors.x = _x / 2;
	halfVectors.y = _y / 2;
	collidableSides.set();
}

xAxisAlignedBoundingBox::xAxisAlignedBoundingBox(xAxisAlignedBoundingBox const &b)
{
	p = b.p;
	halfVectors = b.halfVectors;
	collidableSides = b.collidableSides;
}

xAxisAlignedBoundingBox::~xAxisAlignedBoundingBox()
{
	p.x = 0;
	p.y = 0;
}

int xAxisAlignedBoundingBox::getDriver()
{
	return driver;
}

bool xAxisAlignedBoundingBox::init()
{
	return true;   
}

void xAxisAlignedBoundingBox::handleEvent()
{
	
}

void xAxisAlignedBoundingBox::update(int deltaTime)
{
	
}

void xAxisAlignedBoundingBox::cleanup()
{
	
}

Coord xAxisAlignedBoundingBox::getPosition()
{
	return p;
}
float xAxisAlignedBoundingBox::getXVect()
{
	return halfVectors.x;
}
float xAxisAlignedBoundingBox::getYVect()
{
	return halfVectors.y;
}

Coord xAxisAlignedBoundingBox::getHalfVectors()
{
	return halfVectors;
}

void xAxisAlignedBoundingBox::setBoundingBox(Coord _p, int width, int height)
{
	p = _p;
	halfVectors.x = width / 2;
	halfVectors.y = height / 2;
}

void xAxisAlignedBoundingBox::setBoundingBox(xAxisAlignedBoundingBox b)
{
	p = b.p;
	halfVectors = b.halfVectors;
	collidableSides = b.collidableSides;
}

void xAxisAlignedBoundingBox::setBoundingBox(Coord _p, Coord hVects)
{
	p = _p;
	halfVectors = hVects;
}

/*Coord xAxisAlignedBoundingBox::getPoint(int point)
{
	Coord xy;
	switch (point) {
		case AABB_POINT_TOPLEFT:
		{
			xy.x = p.x - halfVectors.x;
			xy.y = p.y - halfVectors.y;
			break;
		}	
		case AABB_POINT_TOPRIGHT:
		{
			xy.x = p.x + halfVectors.x;
			xy.y = p.y - halfVectors.y;
			break;
		}	
		case AABB_POINT_BOTRIGHT:
		{
			xy.x = p.x + halfVectors.x;
			xy.y = p.y + halfVectors.y;
			break;
		}	
		case AABB_POINT_BOTLEFT:
		{
			xy.x = p.x - halfVectors.x;
			xy.y = p.y + halfVectors.y;
			break;
		}	
		default:
			break;
	}
	return xy;
}*/


std::bitset<4> xAxisAlignedBoundingBox::getCollidableSides()
{
	return collidableSides;
}

bool xAxisAlignedBoundingBox::sideIsCollidable(int side)
{
	return collidableSides.test(side);
}

void xAxisAlignedBoundingBox::disableSide(int side)
{
	collidableSides.reset(side);
}

void xAxisAlignedBoundingBox::enableSide(int side)
{
	collidableSides.set(side);
}
