//
//  entity.h
//  icarus
//
//  Created by Robert Powell on 12-04-24.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <bitset>

#include "component.h"

class Entity
{
public:
	int globalID;
	std::bitset<COMPONENT_COUNT> c_bits;
	std::vector<Component*> c;
	Entity(int gID);
	
	bool bindComponent(Component *component);
	void unbindComponent(int componentType);
	
	void cleanup();
};

#endif
