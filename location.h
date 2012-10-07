//
//  location.h
//  icarus
//
//  Created by Stefan Rezko on 12-05-07.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _LOCATION_H_
#define _LOCATION_H_


#include "component.h"
#include "triplet.h"

class Location : public Component
{
public:
	int type;
	Triplet xyz;
	
	Location (int gID); 
	bool certifyParams();
};

#endif
