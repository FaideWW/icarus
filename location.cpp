//
//  location.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-05-07.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "location.h"
#include "global.h"


Location::Location(int gID)
{
	//typeID = COMPONENT_TYPE_DATA_LOCATION;
	globalID = gID;
	xyz.x = 0;
	xyz.y = 0;
	xyz.z = 0;
}

bool Location::certifyParams()
{
	if ((xyz.x > 0 && xyz.x < WINDOW_WIDTH) && (xyz.y > 0 && xyz.y < WINDOW_HEIGHT) && (xyz.z > -1 && xyz.z < 1)) return true;
	return false;
}