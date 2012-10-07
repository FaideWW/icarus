/**
 *
 *	Service.h
 *	Last update: 17.4.12
 *	
 *	Abstract superclass for all services.  
 *
 *	Enforces predictable and standardized performance for all loop-driven subsystems.
 *	This includes rendering, physics, audio, behavior, movement/control, etc.
 *
 *	terminology:
 *		service/subsystem - collection of common game-wide subroutines which handle a specific aspect of the functionality
 *		loop iteration		- one complete call of all services.  also referred to as the "main loop"
 *												note: there are actually two loops: the logic loop which is capped at a specific iteration rate,
 *															and the render loop which is not capped.
 *		step							-	one execution of a service.  The frequency of the step is determined by the service, and measured
 *												and measured in loop iterations.
 *		component					-	data block which contains parameters specifying how a service should perform for a given entity.
 *		entity						-	an aggregation of components which defines a single object in the game world.
 *		
 */

#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <vector>

#include "global.h"
#include "component.h"

enum
{
	SERVICE_TYPE_RENDER = 0,
	SERVICE_TYPE_INPUT,
	SERVICE_TYPE_PHYSICS,
	SERVICE_COUNT_MAX
};

class Service
{
protected:
	//unique ID of service (governed by a global enumeration)
	int serviceID;
	//type
	int serviceType;
	//note: Services do not have ownership of their Components; the EntityManager is responsible for pointer management
	std::vector<Component*> components;
	
	//stepTime is the static loop frequency (how many loop iterations between steps).  
	int stepTime;
	//currentTime is the current number of iterations left before the next update (counts down from (stepTime - 1) to 0)
	int currentTime;
	std::vector<Component*> sortComponents(std::vector<Component*> x);
public:
	
	//Perform initialization routines to ensure the service will perform properly. 
	//Includes dependency checking and system polling.  
	//Returns false if any checks fail, true otherwise.
	virtual bool init() = 0;
	
	//Called on every iteration of the loop.  Primary subsystem procedures are executed when the next step is reached.
	//note: actual logic is not contained here, only calls to service-specific member functions
	//Paramater deltaTime indicates the time passed since the last loop iteration, used for asynchronous
	//steps (saves performance)
	virtual void step(int deltaTime) = 0;
	
	//Called when a service is no longer required (normally when the game changes state or exits).
	virtual void cleanup() = 0;
	
	//Adds a component and returns its ID in the system (for random access efficiency), or -1 if the component is invalid (e.g. wrong type)
	//Also performs any service-specific logic required to add a component
	virtual int addComponent(Component *c) = 0;
	
	//Removes a component from the service based on its componentID
	//Also performs service-specific removal logic
	//note: Component removal may not be evident until the next step
	virtual void removeComponent(int componentID) = 0;
};

#endif
