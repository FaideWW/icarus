//
//  physicsservice.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-06-28.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "physicsservce.h"
#include "transform.h"

PhysicsService::PhysicsService(int ID)
{
	serviceType = SERVICE_TYPE_PHYSICS;
	serviceID = ID;
	fps = 60;
}

PhysicsService::PhysicsService(int ID, EntityManager *e)
{
	serviceType = SERVICE_TYPE_PHYSICS;
	serviceID = ID;
	em = e;
	fps = 60;
}

PhysicsService::~PhysicsService()
{
	
}

bool PhysicsService::init()
{
	return true;
}

void PhysicsService::step(int deltaTime)
{
	//we have a fixed update rate of 60 per second, so interpolate based on deltaTime
	
	float interpolation = (deltaTime * fps) / 1000;
	
	update(interpolation);
	
}

void PhysicsService::cleanup()
{
	
}

int PhysicsService::addComponent(Component *c)
{
	if (c->typeID != COMPONENT_TYPE_DATA_RIGIDBODY)
		return -1;
	components.push_back((RigidBody*)c);
	c->serviceID = serviceID;
	components = sortComponents(components);
	c->componentID = components.size()-1;
	c->certifyParams();
	return (components.size()-1);
}

void PhysicsService::removeComponent(int componentID)
{
	components[componentID] = NULL;
	components = sortComponents(components);
}

void PhysicsService::clearAllComponents()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i] = NULL;
	}
	components.clear();
}

std::vector<Component*> PhysicsService::sortComponents(std::vector<Component *> x)
{
	//x = sortComponentsRecursive(x);
	std::vector<Component*> n;
	int count = 0;
	//printf("begin loop\n");
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] != NULL) 
		{
			n.push_back(x[i]);
			int c = count++;
			n[c]->serviceID = c;
		}
	}
	
	//printf("end loop\n");
	return n;
}

/**
 *	float interpolation: time between updates (0 being the same time as the last call, and 1 being one full update cycle or 1/60 of a second)
 *
 **/
void PhysicsService::update(float interpolation)
{
	if (interpolation <= 0) return;
	
	for (int i = 0; i < components.size(); i++)
	{
		 RigidBody *x = (RigidBody*)components[i];
		//update flag checks
		if (x->flags.test(RIGIDBODY_FLAGS_SKIP) || x->flags.test(RIGIDBODY_FLAGS_PERSISTENT_PAUSED))
		{
			x->flags.reset(RIGIDBODY_FLAGS_SKIP);
			if (x->flags.test(RIGIDBODY_FLAGS_FORCEUPDATE))
				x->flags.reset(RIGIDBODY_FLAGS_FORCEUPDATE);
			else
				continue;
		}
		if (x->flags.test(RIGIDBODY_FLAGS_PERSISTENT_IMMOVABLE))
			kinematicUpdate(interpolation, i);
	}
	for (int i = 0; i < components.size(); i++)
	{
		for (int j = i; j < components.size(); ++j)
		{
			if (findCollision(i, j))
			{
				Coord x = {i, j};
				collisionQueue.push_back(x);
			}
		}
	}
	
	for (int i = 0; i < collisionQueue.size(); i++)
	{
		RigidBody *x = (RigidBody*)components[collisionQueue[i].x];
		RigidBody *y = (RigidBody*)components[collisionQueue[i].y];
		if (!(x->flags.test(RIGIDBODY_FLAGS_PERSISTENT_NOCOLLISION) || y->flags.test(RIGIDBODY_FLAGS_PERSISTENT_NOCOLLISION)))
			handleCollision(x, y);
	}
	collisionQueue.empty();
	
}

void PhysicsService::kinematicUpdate(float interpolation, int componentID)
{
	RigidBody *c = (RigidBody *)components[componentID];
	
	Physical *p = (Physical *)em->pollEntityState(c->entityID)[COMPONENT_TYPE_EVENT_PHYSICAL];
		
	p->move(interpolation);
	
}	  
	
bool PhysicsService::findCollision(int componentOne, int componentTwo)
{
	RigidBody *c = (RigidBody *)components[componentID];
	BoundingBox *bb = (BoundingBox *)em->pollEntityState(c->entityID)[COMPONENT_TYPE_DATA_BOUNDINGBOX];

	
}

void PhysicsService::handleCollision(RigidBody *componentOne, RigidBody *componentTwo)
{
	
}

