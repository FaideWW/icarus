//
//  componentrender.h
//  icarus
//
//  Created by Robert Powell on 12-04-19.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <string>
#include "SDL/SDL_opengl.h"

#include "component.h"
#include "triplet.h"

struct Color
{
	float r;
	float g;
	float b;
	float a;
};


class Renderable : public Component
{
public:
	//global params
	int type;
	//Triplet pos;
	int w;
	int h;
	//float r;
	
	//texture params
	std::string filename;
	GLuint tex;
	
	//color params
	Color col;
	
	Renderable(int gID, int t);
	bool certifyParams();
};

#endif
