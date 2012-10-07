//
//  entity.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-05-07.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "entity.h"
#include <cstdio>

Entity::Entity(int gID)
{
    globalID = gID;
    c_bits.reset();
    c.resize(COMPONENT_COUNT);
	for (int i = 0; i < c.size(); i++)
		c[i] = NULL;
}

bool Entity::bindComponent(Component *component)
{
    if (component == NULL)
    {
        printf("null component at %p\n", component);
    }
    printf("component typeID: %d\n", component->typeID);
    if (!c_bits.test(component->typeID))
    {
			c[component->typeID] = component;
        c[component->typeID]->entityID = globalID;
        c_bits.set(component->typeID);
        return true;
    }
    return false;
}

void Entity::unbindComponent(int componentType)
{
    if (c_bits.test(componentType))
    {
			c_bits.reset(componentType);
			delete c[componentType];
			c[componentType] = NULL;
    }
}

void Entity::cleanup()
{
    for (int i = 0; i < COMPONENT_COUNT; i++)
    {
			if (c[i] == NULL) continue;
			delete c[i];
			c[i] = NULL;
    }
    c_bits.reset();
}