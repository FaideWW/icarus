//
//  aaboundingbox.h
//  icarus
//
//  Created by Stefan Rezko on 12-05-11.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//
/**
 *	we assume that the AABB is a rectangle (i.e. perpendicular axes) to simplify calculations
 *
 */

#ifndef _AABOUNDINGBOX_H_
#define _AABOUNDINGBOX_H_

#include <bitset>

#include "boundingbox.h"
#include "component.h"
#include "coord.h"
#include "triplet.h"

enum 
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
};



class AxisAlignedBoundingBox : public BoundingBox
{
	
public:
	Coord halfVectors;
	Coord offsetVectors;
	float zeroAxis;	//angle (from 0) at which the AABB is to be rotated
	std::bitset<4> collidableSides;
	
	AxisAlignedBoundingBox(int gID);
	AxisAlignedBoundingBox(int gID, Coord hv, float angle);
	AxisAlignedBoundingBox(int gID, AxisAlignedBoundingBox const &bb);
	~AxisAlignedBoundingBox();
	
	//gets point relative to the object origin
	Coord getRelativePoint(int p);
	
	//returns true if the point p is inside the bounding box
	bool pointInPoly(Triplet, Coord);
	bool vecIntersectsVec(Coord, Coord, Coord, Coord); 
	
	bool certifyParams();
	
};

#endif
