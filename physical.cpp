#include <vector>
#include <cmath>


#include "global.h"
#include "physical.h"

Physical::Physical(int gID)
{
	globalID = gID;
	typeID = COMPONENT_TYPE_EVENT_PHYSICAL;
	fps = 30; //defaults to 30
	vel.x = 0;
	vel.y = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;

	//default max speed; can be changed as necessary though
	vMax = 300;
}

Physical::~Physical()
{}

int Physical::getDriver()
{
    return driver;
}

bool Physical::init()
{
    
}

void Physical::handleEvent()
{
    
}

void Physical::update(int deltaTime)
{
    
}

void Physical::cleanup()
{
    
}

void Physical::setFPS(int f)
{
	fps = f;
}

void Physical::setXVelocity(float v)
{	vel.x = (v > 0) ? (((v > getRemainingVelocity(vel.y)) ? getRemainingVelocity(vel.y) : v) / 1000.0f) : (((v < (-1)*getRemainingVelocity(vel.y)) ? (-1)*getRemainingVelocity(vel.y) : v) / 1000.0f);	}

void Physical::setYVelocity(float v)
{	vel.y = (v > 0) ? (((v > getRemainingVelocity(vel.x)) ? getRemainingVelocity(vel.x) : v) / 1000.0f) : (((v < (-1)*getRemainingVelocity(vel.x)) ? (-1)*getRemainingVelocity(vel.x) : v) / 1000.0f);	}



void Physical::setPosition(Coord xy)
{	setPosition(xy.x, xy.y);	}

void Physical::setPosition(Triplet xyz)
{	position = xyz;	}

//we assume collision checking has been performed already,
// or it doesn't need to be done
void Physical::setPosition(float xx, float yy)
{
	position.x = xx;
	position.y = yy;
}

void Physical::setMaxSpeed(int ms)
{
	vMax = (ms < 0) ? vMax : ms;
}

void Physical::setX(float x)
{ position.x = x; }

void Physical::setY(float y)
{ position.y = y; }

void Physical::setZ(float z)
{	position.z = z;	}

void Physical::move(int deltaTime)
{	
	setPosition(position.x + (deltaTime * vel.x), position.y + (deltaTime * vel.y));

}

Coord Physical::getPosition2D()
{
	Coord p = {position.x, position.y};
	return p;
}

Triplet Physical::getPosition3D()
{
	return position;
}

Coord Physical::getVelocity()
{	return vel * 1000.0f;	}

float Physical::getTotalVelocity()
{	return sqrt((vel.x * vel.x) + (vel.y * vel.y));	}

//takes a known axis velocity and calculates the maximum velocity possible for the unknown axis
float Physical::getRemainingVelocity(float axisVel)
{
	//total velocity
	float tV = getTotalVelocity();
	float tVsq = tV * tV;
	//known axis velocity
	float aVsq = axisVel * axisVel;

	float rVsq = tVsq - aVsq;
	float rV = sqrt(rVsq);
	return rV;
}

bool Physical::certifyParams()
{

}