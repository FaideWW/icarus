//
//  entityfactory.h
//  icarus
//
//  Created by Stefan Rezko on 12-05-08.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include "entity.h"

class EntityFactory
{
private:
	int id_ref;
public:
	EntityFactory();
	~EntityFactory();
	
	Entity *createEntity();
};

#endif
