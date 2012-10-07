//
//  oboundingbox.h
//  icarus
//
//  Created by Stefan Rezko on 12-06-25.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _OBOUNDINGBOX_H_
#define _OBOUNDINGBOX_H_

#include <vector>

//much more complex (and slower) than AABB; AABB is to be used if at all possible
class OrientedBoundingBox
{
	
public:
	std::vector<Coord> vertices;
	std::vector<bool> collidableSides;
	Coord offsetVectors;
	float zeroAxis;	//angle (from 0) at which the OBB is to be rotated
	
	OrientedBoundingBox(int gID);
	//gets point relative to the object origin
	Coord getRelativePoint(int p);
	
	//returns true if the point p is inside the bounding box
	//uses ray casting algorithm
	bool pointInPoly(Triplet xyz, Coord p);
	
	bool certifyParams();
	
};

#endif
