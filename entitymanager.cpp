//
//  entitymanager.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-05-08.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

/**
 *	June 14 2012
 *		-Refactored this class to handle entity IDs differently.
 *		-I/O with the entity manager now deals exclusively in global IDs
 *		-Entities are reorganized in the array now, so entityID is privately handled now.
 */



#include <stdio.h>

#include "entitymanager.h"

EntityManager::EntityManager()
{
	factory = new EntityFactory();	
}

EntityManager::~EntityManager()
{
}

int EntityManager::countEntities()
{
	
	return entities.size();
}


//returns global ID of entity
int EntityManager::addEntity()
{
	entities.push_back(factory->createEntity());
	return entities[entities.size()-1]->globalID;
}

int EntityManager::getEntityIDFromGlobalID(int gID)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->globalID == gID)
			return i;
	}
	printf("---SUPER ERROR---\ninvalid entity ID\n");
	return -1;
}

bool EntityManager::addComponentToEntity(int gID, Service *s, Component *c)
{
    if (entities[getEntityIDFromGlobalID(gID)]->bindComponent(c))
    {
        if (s != NULL)
            s->addComponent(c);
        return true;
    }
	return false;
}

void EntityManager::removeComponentFromEntity(int gID, int cType)
{
	entities[getEntityIDFromGlobalID(gID)]->unbindComponent(cType);
}

void EntityManager::removeComponentFromEntity(int gID, Component *c)
{
	entities[getEntityIDFromGlobalID(gID)]->unbindComponent(c->typeID);
}

bool EntityManager::entityHasComponent(int gID, int cType)
{
	return entities[getEntityIDFromGlobalID(gID)]->c_bits.test(cType);
}

std::vector<Component*> EntityManager::pollEntityState(int gID)
{
	
	return entities[getEntityIDFromGlobalID(gID)]->c;
}

void EntityManager::deleteEntity(int gID)
{
	if (entities[getEntityIDFromGlobalID(gID)] == NULL) return;
	for (int i = 0; i < COMPONENT_COUNT; i++)
	{
		removeComponentFromEntity(gID, i);
	}
	int eID = getEntityIDFromGlobalID(gID);
	entities[eID]->cleanup();
	delete entities[eID];
	entities[eID] = NULL;
	shiftDownEntities(eID);
}

//index is the position of the NULL pointer
void EntityManager::shiftDownEntities(int index)
{
	while (++index < entities.size())
	{
		entities[index-1] = entities[index];
	}
	entities.resize(index-1);
}

void EntityManager::clearAllEntities()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->cleanup();
		delete entities[i];
	}
	entities.clear();
	delete factory;
	factory = new EntityFactory();
}

void EntityManager::cleanup()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i] == NULL) continue;
		entities[i]->cleanup();
		delete entities[i];
	}
	entities.clear();
	delete factory;
}