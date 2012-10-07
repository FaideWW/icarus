/**
 *
 *	RenderService.h
 *	Last update: 17.4.12
 *	
 *	The subsystem that handles drawing entities with the Renderable component
 *	to the GL context.  
 *	This service can manage both textures and pure color polys, and is part of 
 *	the render-driven loop.
 *	
 *	Note: the render loop is not FPS limited; the GPU will draw frames as fast
 *	as possible.  (this might need to change if it turns out we are drawing
 *	too fast)
 *
 */

#ifndef _RENDERSERVICE_H_
#define _RENDERSERVICE_H_

#include "entitymanager.h"
#include "renderable.h"
#include "service.h"

class RenderService : public Service
{
public:	
	RenderService(int ID);
	RenderService(int ID, EntityManager *e);
	~RenderService();
	
	EntityManager *em;
	bool init();
	void step(int deltaTime);
	void cleanup();
	int addComponent(Component *c);
	void removeComponent(int componentID);
	void clearAllComponents();
private:
	bool loadComponentInfo(Renderable *c);
	bool loadColorInfo(Renderable *c);
	bool loadTextureInfo(Renderable *c);
	std::vector<Component*> sortComponents(std::vector<Component*> x);
	std::vector<Component*> sortComponentsRecursive(std::vector<Component*> x);
	
	void draw();
	void drawColorPoly(Renderable *c);
	void drawTexturePoly(Renderable *c);
};

#endif
