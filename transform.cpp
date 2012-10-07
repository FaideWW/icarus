//
//  transform.cpp
//  icarus
//
//  
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

// --NOTE: on the matter of translation, the actual world-position is owned by Controllable;
//				 Transform is for camera-position, used for drawing via RenderService

#include <iostream>

#include "global.h"
#include "transform.h"

Transform::Transform(int gID)
{
	typeID = COMPONENT_TYPE_DATA_TRANSFORM;
	globalID = gID;
	xyz.x = 0.0f;
	xyz.y = 0.0f;
	xyz.z = 0.0f;
	wh.x = 1.0f;
	wh.y = 1.0f;
	r = 0.0f;
}

void Transform::translate(float x, float y, float z)
{
	xyz.x += x;
	xyz.y += y;
	xyz.z += z;
	certifyParams();
}

void Transform::translate(Coord xy, float z)
{
	xyz.x += xy.x;
	xyz.y += xy.y;
	xyz.z += z;
	certifyParams();
}

void Transform::translate(Triplet relXYZ)
{
	xyz.x += relXYZ.x;
	xyz.y += relXYZ.y;
	xyz.z += relXYZ.z;
	certifyParams();
}

//arithmetic (linear) scale, not geometric (quadratic)
void Transform::scale(float w, float h)
{
	wh.x += w;
	wh.y += h;
	certifyParams();
}

void Transform::scale(Coord relWH)
{
	wh.x += relWH.x;
	wh.y += relWH.y;
	certifyParams();
}

void Transform::rotate(float relR)
{
	r += relR;
	certifyParams();
}

bool Transform::certifyParams()
{
	while (r > 360) r -= 360;
	while (r < 0) r += 360;
	if ((xyz.x > 0 && xyz.x < WINDOW_WIDTH) && 
			(xyz.y > 0 && xyz.y < WINDOW_HEIGHT) && 
			(xyz.z > -1 && xyz.z < 1) &&
			(wh.x != 0 && wh.y != 0) &&
			(r >= 0.0f && r < 360.0f)) 
		return true;
	return false;
}