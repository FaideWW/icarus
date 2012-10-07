//
//  aaboundingbox.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-05-11.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include <cmath>
#include <cstdio>

#include "aaboundingbox.h"
#include "global.h"
#include "maths.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(int gID)
{
	globalID = gID;
	typeID = COMPONENT_TYPE_DATA_BOUNDINGBOX;
	halfVectors.x = 0;
	halfVectors.y = 0;
	offsetVectors.x = 0;
	offsetVectors.y = 0;
	zeroAxis = 0.0f;
	collidableSides.reset();
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(int gID, Coord hv, float angle)
{
	globalID = gID;
	typeID = COMPONENT_TYPE_DATA_BOUNDINGBOX;
	halfVectors = hv;
	offsetVectors.x = 0;
	offsetVectors.y = 0;
	zeroAxis = angle;
	collidableSides.reset();
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(int gID, AxisAlignedBoundingBox const &bb)
{
	globalID = gID;
	typeID = bb.typeID;
	halfVectors.x = bb.halfVectors.x;
	halfVectors.y = bb.halfVectors.y;
	offsetVectors.x = bb.offsetVectors.x;
	offsetVectors.y = bb.offsetVectors.y;
	zeroAxis = bb.zeroAxis;
	collidableSides = bb.collidableSides;
}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
	
}

Coord AxisAlignedBoundingBox::getRelativePoint(int p)
{
	Coord xy = {0,0};
	
	switch (p) {
		case AABB_POINT_TOPLEFT:
		{
			xy -= halfVectors;
			//apply rotation
			if (zeroAxis != 0)
			{
				// x' = xcosA - ysinA
				// y' = xsinA + ycosA
				xy.x = xy.x * cos(zeroAxis) - xy.y * sin(zeroAxis);
				xy.y = xy.x * sin(zeroAxis) + xy.y * cos(zeroAxis);
			}
			xy = offsetVectors + xy;
			break;
		}	
		case AABB_POINT_TOPRIGHT:
		{
			xy.x = halfVectors.x;
			xy.y -= halfVectors.y;
			if (zeroAxis != 0)
			{
				// x' = xcosA - ysinA
				// y' = xsinA + ycosA
				xy.x = xy.x * cos(zeroAxis) - xy.y * sin(zeroAxis);
				xy.y = xy.x * sin(zeroAxis) + xy.y * cos(zeroAxis);
			}
			xy = offsetVectors + xy;
			break;
		}	
		case AABB_POINT_BOTRIGHT:
		{
			xy = halfVectors;
			if (zeroAxis != 0)
			{
				// x' = xcosA - ysinA
				// y' = xsinA + ycosA
				xy.x = xy.x * cos(zeroAxis) - xy.y * sin(zeroAxis);
				xy.y = xy.x * sin(zeroAxis) + xy.y * cos(zeroAxis);
			}
			xy = offsetVectors + xy;
			break;
		}	
		case AABB_POINT_BOTLEFT:
		{
			xy.x -= halfVectors.x;
			xy.y = halfVectors.y;
			if (zeroAxis != 0)
			{
				// x' = xcosA - ysinA
				// y' = xsinA + ycosA
				xy.x = xy.x * cos(zeroAxis) - xy.y * sin(zeroAxis);
				xy.y = xy.x * sin(zeroAxis) + xy.y * cos(zeroAxis);
			}
			xy = offsetVectors + xy;
			break;
		}	
		default:
			break;
	}
	return xy;
}

bool AxisAlignedBoundingBox::pointInPoly(Triplet poly, Coord point)
{
	Coord xy = {poly.x, poly.y};
	if (zeroAxis == 0)
	{
		Coord tl = getRelativePoint(AABB_POINT_TOPLEFT);
		Coord br = getRelativePoint(AABB_POINT_BOTRIGHT);
		tl += xy;
		br += xy;
		return (tl.x <= point.x && tl.y <= point.y && br.x >= point.x && br.y >= point.y);
	}
	else //for PIP where the bounding box is not necessarily AA (e.g. it's rotated), use ray casting algorithm
	{
		printf("bounding box is rotated\n");
		int count = 0;
		printf("mouse at %f,%f\n", point.x, point.y);
		for (int i = 0; i < 4; i++)
		{
			printf("%d", i);
			Coord ray = {(WINDOW_WIDTH - point.x), 0};
			int j = (i < 3) ? i+1 : 0;
			if (vecIntersectsVec(point, ray, xy + getRelativePoint(i), (xy + getRelativePoint(j)) - (xy + getRelativePoint(i))))
				count++;
		}
		
		//if count is even, the point is outside the BB
		if (count % 2 == 0)
			return false;
		else	//if count is odd, the point is inside the BB
			return true;
	}
}



/**
 *	determines whether two line segments (<p,p+vecR> and <q,q+vecS>) intersect using parametric
 *		equations. 
 *	given that p + t(vecR) = q + u(vecS) has a solution (otherwise the two lines are parallel),
 *		the intersection point is contained in the line segments if 0 <= t <= 1 AND 0 <= u <= 1
 *
 *	(side note: the intersection point can be found by substituting t/u back into the equation)
 */
bool AxisAlignedBoundingBox::vecIntersectsVec(Coord p, Coord vecR, Coord q, Coord vecS)
{
	printf("p: (%f,%f)\nvecR: (%f,%f)\nq: (%f,%f)\nvecS: (%f,%f)\n", p.x, p.y, vecR.x, vecR.y, q.x, q.y, vecS.x, vecS.y);
	//check if the vectors are parallel
	//(this ignores collinearity, which for
	//our purposes is irrelevant)
	if (imath::vecCrossProduct(vecR, vecS) == 0)
		return false;
	
	
	float t = imath::vecCrossProduct((q - p), vecS) / imath::vecCrossProduct(vecR, vecS);
	float u = imath::vecCrossProduct((q - p), vecR) / imath::vecCrossProduct(vecR, vecS);
	
	if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1))
		return true;
	return false;
}

bool AxisAlignedBoundingBox::certifyParams()
{
	if (halfVectors.x < 0 || halfVectors.y < 0)
		return false;
	return true;
}