//
//  controlservice.h
//  icarus
//
//  Created by Stefan Rezko on 12-05-10.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _INPUTSERVICE_H_
#define _INPUTSERVICE_H_

#include "SDL.h"

#include "service.h"

class InputService : public Service
{
public:
	InputService(int ID);
	~InputService();
	
	EntityManager *em;
	bool init();
	void step(int deltaTime);
	void cleanup();
	int addComponent(Component *c);
	void removeComponent(int componentID);
private:
	void handleEvent(SDL_Event e);
}

#endif
