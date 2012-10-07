

#ifndef _PHYSICSSERVICE_H_
#define _PHYSICSSERVICE_H_

#include "entitymanager.h"
#include "rigidbody.h"
#include "service.h"

class PhysicsService : public Service
{
public:	
	EntityManager *em;
	int fps; //update cycles per second (default 60)
	
	PhysicsService(int ID);
	PhysicsService(int ID, EntityManager *e);
	~PhysicsService();
	
	bool init();
	void step(int deltaTime);
	void cleanup();
	int addComponent(Component *c);
	void removeComponent(int componentID);
	void clearAllComponents();
	
private:
	std::vector<Component*> sortComponents(std::vector<Component*> x);
	std::vector<Component*> sortComponentsRecursive(std::vector<Component*> x);
	std::vector<Coord> collisionQueue;
	
	void update(float interpolation);
	void kinematicUpdate(float interpolation, int componentID);
	bool findCollision(int componentOne, int componentTwo);
	
	void collisionUpdate();
	void handleCollision(RigidBody *componentOne, RigidBody *componentTwo);
};

#endif
