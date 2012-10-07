//
//  entityfactory.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-05-08.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "entityfactory.h"

EntityFactory::EntityFactory()
{
	id_ref = 0;
}

EntityFactory::~EntityFactory()
{
	
}

Entity *EntityFactory::createEntity()
{
	return new Entity(id_ref++);
}