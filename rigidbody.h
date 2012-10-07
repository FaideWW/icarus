//
//  rigidbody.h
//  icarus
//
//  Created by Stefan Rezko on 12-06-27.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include <bitset>

#include "component.h"
#include "coord.h"

//physics flags to be set
//by default these are all set to 0, for special case use only
enum 
{
	RIGIDBODY_FLAGS_SKIP = 0,			//will skip the next cycle (overriden by forceupdate)
	RIGIDBODY_FLAGS_FORCEUPDATE,	//if paused, will force a physics update for one cycle
	RIGIDBODY_FLAGS_PERSISTENT_PAUSED,				//will pause updates indefinitely
	RIGIDBODY_FLAGS_PERSISTENT_NOCOLLISION,
	RIGIDBODY_FLAGS_PERSISTENT_FRICTIONLESS,
	RIGIDBODY_FLAGS_PERSISTENT_IMMOVABLE,
	RIGIDBODY_FLAGS_COUNT
};

class RigidBody : public Component
{
public:
	Coord velocity;
	Coord acceleration;
	float angularVelocity;
	std::bitset<RIGIDBODY_FLAGS_COUNT> flags;
	
	bool certifyParams();
};

#endif
