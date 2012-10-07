//
//  transform.h
//  icarus
//
//  Created by Stefan Rezko on 12-06-18.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "component.h"
#include "coord.h"
#include "triplet.h"



/**
 *
 *  NOTE: Occam's Razor applies here; all transformations are linear,
 *      relative additions.  Any complex transformations must be calculated
 *      outside of the component and then added to the transform after
 */
class Transform : public Component
{
public:
	int type;
	Triplet xyz; //translate
	Coord wh; //scale
	float r; //rotate
	
	Transform (int gID); 
	
	void translate(float x, float y, float z);
	void translate(Coord xy, float z);
	void translate(Triplet relXYZ);
	
	void scale(float w, float h);
	void scale(Coord relWH);
	
	void rotate(float relR);
	
	bool certifyParams();
};

#endif
