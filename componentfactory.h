//
//  Header.h
//  icarus
//
//  Created by Robert Powell on 12-04-23.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _COMPONENTFACTORY_H_
#define _COMPONENTFACTORY_H_

#include <map>
#include <string>

#include "component.h"


class ComponentFactory
{
private:
	int id_ref;
public:
	ComponentFactory();
	~ComponentFactory();
	
	Component *createComponent(int type, std::map<std::string,std::string> params);
};

#endif
