#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "component.h"
#include "coord.h"
#include "triplet.h"


/*
 *	Physical: used for any component that has a manifestation in the game world: controls position, velocity
 *
 *
 */

class Physical : public Component
{
private:
	int fps;
	Coord vel; //velocity in units per millisecond (saves division op in updates)
	int vMax;
	Triplet position;
	int driver;
public:
	Physical(int gID);
	~Physical();
	
	int getDriver();
	bool init();
	void handleEvent();
	void update(int deltaTime);
	void cleanup();
	
	void setFPS(int f);
	void setXVelocity(float v);
	void setYVelocity(float v);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setPosition(Coord xy);
	void setPosition(Triplet xyz);
	void setPosition(float xx, float yy);
	void setMaxSpeed(int ms);
	void move(int deltaTime);

	int getFPS();
  Coord getPosition2D();
  Triplet getPosition3D();
  float getZ();
  Coord getVelocity();
  float getTotalVelocity();
  float getRemainingVelocity(float axisVel);

  bool certifyParams();
};

#endif