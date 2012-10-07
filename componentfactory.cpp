//
//  componentfactory.cpp
//  icarus
//
//  Created by Robert Powell on 12-04-23.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include <cstdio>
#include <stdlib.h>
#include <iterator>

#include "aaboundingbox.h"
#include "componentfactory.h"
#include "physical.h"
#include "location.h"
#include "renderable.h"
#include "transform.h"

ComponentFactory::ComponentFactory()
{
	id_ref = 0;
}

ComponentFactory::~ComponentFactory()
{
	
}

Component *ComponentFactory::createComponent(int type, std::map<std::string,std::string> params)
{
	switch (type)
	{
		case COMPONENT_TYPE_DATA_BOUNDINGBOX:
			{
				printf("adding component BOUNDINGBOX\n");
				//AxisAlignedBoundingBox *bb = new AxisAlignedBoundingBox(id_ref++);
				//parse parameters
        //parameters for Location:
        // int {x, y, z}
				
				int type = -1;
				for (std::map<std::string,std::string>::iterator it = params.begin(); it != params.end(); it++)
				{
					if (it->first.compare("bb_type") == 0)
						type = atoi(it->second.c_str());
					else
						continue;
				}
				if (type != -1)
				{
					switch (type)
					{
						case BOUNDINGBOX_TYPE_AXISALIGNED:
						{
							AxisAlignedBoundingBox *bb = new AxisAlignedBoundingBox(id_ref++);
							for (std::map<std::string,std::string>::iterator it = params.begin(); it != params.end(); it++)
			        {
								if (it->first.compare("half_x") == 0)
									bb->halfVectors.x = strtof(it->second.c_str(), NULL);
								else if (it->first.compare("half_y") == 0)
									bb->halfVectors.y = strtof(it->second.c_str(), NULL);
								else if (it->first.compare("offset_x") == 0)
									bb->offsetVectors.x = atoi(it->second.c_str());
								else if (it->first.compare("offset_y") == 0)
									bb->offsetVectors.y = atoi(it->second.c_str());
								else if (it->first.compare("r") == 0)
									bb->zeroAxis = strtof(it->second.c_str(), NULL);
			        }
							bb->certifyParams();
							return bb;
							break;
						}

					}
				}
				else
				{
					return NULL;
				}
				break;
			}
		case COMPONENT_TYPE_DATA_TRANSFORM:
			{
				printf("adding component TRANSFORM\n");
				Transform *t = new Transform(id_ref++);
				
				for (std::map<std::string,std::string>::iterator it = params.begin(); it != params.end(); it++)
        {
					if (it->first.compare("x") == 0)
						t->xyz.x = atoi(it->second.c_str());
					else if (it->first.compare("y") == 0)
						t->xyz.y = atoi(it->second.c_str());
					else if (it->first.compare("z") == 0)
						t->xyz.z = atoi(it->second.c_str());
					else if (it->first.compare("w") == 0)
						t->wh.x = strtof(it->second.c_str(), NULL);
					else if (it->first.compare("h") == 0)
						t->wh.y = strtof(it->second.c_str(), NULL);
					else if (it->first.compare("r") == 0)
						t->r = strtof(it->second.c_str(), NULL);
        }
				t->certifyParams();
				return t;
				break;
			}
		/*case COMPONENT_TYPE_DATA_LOCATION:
			{
				Location *l = new Location(id_ref++);
				//parse parameters
        //parameters for Location:
        // int {x, y, z}
            
        for (std::map<std::string,std::string>::iterator it = params.begin(); it != params.end(); it++)
        {
					if (it->first.compare("x") == 0)
						l->xyz.x = atoi(it->second.c_str());
					else if (it->first.compare("y") == 0)
						l->xyz.y = atoi(it->second.c_str());
					else if (it->first.compare("z") == 0)
						l->xyz.z = atoi(it->second.c_str());
        }
        return l;
			break;
        }*/

    case COMPONENT_TYPE_EVENT_PHYSICAL:
   	{
				printf("adding component PHYSICAL\n");
   		Physical *p = new Physical(id_ref++);

   		for (std::map<std::string, std::string>::iterator it = params.begin(); it != params.end(); it++)
   		{

   			if (it->first.compare("fps") == 0)
   				p->setFPS(atoi(it->second.c_str()));
   			else if (it->first.compare("vMax"))
   				p->setMaxSpeed(atoi(it->second.c_str()));
   			else if (it->first.compare("vX"))
   				p->setXVelocity(atof(it->second.c_str()));
   			else if (it->first.compare("vY"))
   				p->setYVelocity(atof(it->second.c_str()));
   			else if (it->first.compare("pX"))
   				p->setX(strtof(it->second.c_str(), NULL));
   			else if (it->first.compare("pY"))
   				p->setY(strtof(it->second.c_str(), NULL));
   			else if (it->first.compare("pZ"))
   				p->setZ(strtof(it->second.c_str(), NULL));
   		}
    	break;
   	}
		case COMPONENT_TYPE_RENDERABLE_TEXTURE:
        {

				printf("adding component TEXTURERENDER\n");
					Renderable *r = new Renderable(id_ref++, type);
					
					//parse parameters
					//parameters for Renderable Texture:
					// string {filename}
					// int {w, h}
					
					for (std::map<std::string,std::string>::iterator it = params.begin(); it != params.end(); it++)
					{
						if (it->first.compare("filename") == 0)
							r->filename = it->second;
						else if (it->first.compare("w") == 0)
							r->w = atoi(it->second.c_str());
						else if (it->first.compare("h") == 0)
							r->h = atoi(it->second.c_str());
					}
					r->certifyParams();
					return r;
			break;
        }
		case COMPONENT_TYPE_RENDERABLE_COLOR:
		{
				printf("adding component COLORRENDER\n");
			Renderable *r = new Renderable(id_ref++, type);			
			//parse parameters
			//parameters for Renderable Color:
			// int {r, g, b, a, w, h}
			
			for (std::map<std::string,std::string>::iterator it = params.begin(); it != params.end(); ++it)
			{
				if (it->first.compare("r"))
					r->col.r = atoi(it->second.c_str());
				else if (it->first.compare("g"))
					r->col.g = atoi(it->second.c_str());
				else if (it->first.compare("b"))
					r->col.b = atoi(it->second.c_str());
				else if (it->first.compare("a"))
					r->col.a = atoi(it->second.c_str());
				else if (it->first.compare("w"))
					r->w = atoi(it->second.c_str());
				else if (it->first.compare("h"))
					r->h = atoi(it->second.c_str());
			}
			r->certifyParams();
			return r;
			break;
    }

		default:
			return NULL;
	}
}