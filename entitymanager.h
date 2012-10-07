//
//  entitymanager.h
//  icarus
//
//  Created by Stefan Rezko on 12-05-07.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <vector>

#include "entityfactory.h"
#include "entity.h"
#include "service.h"

//contains and manages entities, their creation/deletion, adding components and binding them to the proper services
class EntityManager
{
private:
	EntityFactory *factory;
    void shiftDownEntities(int index);
    int getEntityIDFromGlobalID(int gID);
public:
	std::vector<Entity*> entities;
	
	EntityManager();
	~EntityManager();
    
  int countEntities();
	
	int addEntity();
	bool addComponentToEntity(int eID, Service *s, Component *c);
	void removeComponentFromEntity(int eID, int cType);
	void removeComponentFromEntity(int eID, Component *c);
	bool entityHasComponent(int eID, int cType);
	std::vector<Component*> pollEntityState(int eID);
	void deleteEntity(int eID);
    
    
    void clearAllEntities();
	
    void cleanup();
};

#endif
