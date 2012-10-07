//
//  componentrender.cpp
//  icarus
//
//  Created by Robert Powell on 12-04-19.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "service.h"
#include "renderable.h"

Renderable::Renderable(int gID, int t)
{
	typeID = t;
	globalID = gID;
	type = SERVICE_TYPE_RENDER;
  tex = 0;
  col.r = -1;
  col.g = -1;
  col.b = -1;
  col.a = -1;
	w = -1;
	h = -1;
  filename = "/Users/Stefan/dev/icarus/icarus/ball.png";
	
}

bool Renderable::certifyParams()
{
	if (type == COMPONENT_TYPE_RENDERABLE_TEXTURE)
    {
        if (filename == "" || tex == 0) 
            return false;
    }
    else if (type == COMPONENT_TYPE_RENDERABLE_COLOR)
    {
        if (col.r == -1 || col.g == -1 || col.b == -1 || col.a == -1) 
            return false;
    }
    else return false;
    return true;
}