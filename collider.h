#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <vector>

#include "_boundingbox.h"
#include "controller.h"
#include "coord.h"
#include "colorrender.h"
#include "component.h"

class Collider
{
private:
	xAxisAlignedBoundingBox *bb;
	bool renderBox;
	bool drawBB;
	int driver;
public:
	Collider();
	~Collider();
	
	int getDriver();
	bool init();
	void handleEvent();
	void update(int deltaTime);
	
	void setBoxDisplay(bool sw);
	
	void setBoundingBox(xAxisAlignedBoundingBox box);
	void setBoundingBox(Coord xy, int width, int height);
	
	void moveBoundingBox(Coord xy);
	
	int collideWith(xAxisAlignedBoundingBox *bb2);
	
	Coord reactToCollision(Controller *c, int collisionType, int deltaTime);
	
	void draw();
	void cleanup();
	
	xAxisAlignedBoundingBox *getBoundingBox();
};

#endif