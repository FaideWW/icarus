//
//  boundingbox.h
//  icarus
//
//  Created by Robert Powell on 12-04-03.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include <bitset>

#include "component.h"
#include "coord.h"

/*enum 
{
	AABB_POINT_TOPLEFT = 0,
	AABB_POINT_TOPRIGHT,
	AABB_POINT_BOTRIGHT,
	AABB_POINT_BOTLEFT,
};

enum
{
	AABB_SIDE_TOP = 0,
	AABB_SIDE_RIGHT,
	AABB_SIDE_BOT,
	AABB_SIDE_LEFT,
};*/

class xAxisAlignedBoundingBox
{
private:
	Coord p;
	Coord halfVectors;
	std::bitset<4> collidableSides;
	int driver;
	
public:
	xAxisAlignedBoundingBox();
		//use this if half vects are already formatted
	xAxisAlignedBoundingBox(Coord _p, float _x, float _y);
	xAxisAlignedBoundingBox(xAxisAlignedBoundingBox const &b);
	~xAxisAlignedBoundingBox();
	
	int getDriver();
	bool init();
	void handleEvent();
	void update(int deltaTime);
	void cleanup();
	
	Coord getPosition();
	float getXVect();
	float getYVect();
	Coord getHalfVectors();
	
	std::bitset<4> getCollidableSides();
	bool sideIsCollidable(int side);
	void disableSide(int side);
	void enableSide(int side);
	
	void setBoundingBox(Coord _p, int width, int height);
	void setBoundingBox(Coord _p, Coord hVects);
	void setBoundingBox(xAxisAlignedBoundingBox b);
	
	
	Coord getPoint(int p);
};

#endif
