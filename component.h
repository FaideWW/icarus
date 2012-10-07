/**
 *
 *	Component.h
 *	Last update: 17.4.12
 *	
 *	Abstract superclass for all components
 *
 *	Contains a collection of IDs which identify the component to its handlers, 
 *	a typeID which designates the service it is intended for, and a hashmap of 
 *	the component's parameters.
 */

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

enum 
{
	COMPONENT_TYPE_DATA_BOUNDINGBOX = 0,
	COMPONENT_TYPE_DATA_TRANSFORM,
	COMPONENT_TYPE_DATA_RIGIDBODY,
	COMPONENT_TYPE_EVENT_COLLIDABLE, //requires boundingbox
	COMPONENT_TYPE_EVENT_PHYSICAL,
  COMPONENT_TYPE_RENDERABLE_COLOR, //requires location
	COMPONENT_TYPE_RENDERABLE_TEXTURE, //requires location
	COMPONENT_COUNT //used to initialize entity component vectors with the appropriate size
};

enum
{
	BOUNDINGBOX_TYPE_AXISALIGNED = 0,
	BOUNDINGBOX_COUNT
};

class Component
{
public:
	//ID of the component in the global scope (primary key, there is no default)
	int globalID;
	//ID of the service this component is tied to (default is -1, or no service)
	int serviceID;
	//ID of the component within the service (default is -1)
	int componentID;
	//ID of the entity this component is tied to
	int entityID;
	//ID of the component type (see above enum) (default is -1, or no type)
	int typeID;
	
	//component specific parameter checks - ensures that the appropriate parameters are delcared
	virtual bool certifyParams() = 0;
	
};

#endif
