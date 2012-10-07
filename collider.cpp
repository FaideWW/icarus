#include <algorithm>
#include <cstdio>
/*
#include "collider.h"

Collider::Collider()
{
	bb = new xAxisAlignedBoundingBox();
	r = new BoundingBoxRender();
	drawBB = false;
}

Collider::~Collider()
{
	delete bb;
	delete r;
}

int Collider::getDriver()
{
    return driver;
}

bool Collider::init()
{
    return true;
}

void Collider::handleEvent()
{
    
}

void Collider::update(int deltaTime)
{
    
}

void Collider::setBoundingBox(xAxisAlignedBoundingBox box)
{	*bb = box;	}

void Collider::moveBoundingBox(Coord xy)
{	bb->setBoundingBox(xy, bb->getHalfVectors());	}

void Collider::setBoundingBox(Coord xy, int width, int height)
{
	bb->setBoundingBox(xy, width, height);	
	r->loadBB(bb);
}

void Collider::setBoxDisplay(bool sw)
{	drawBB = sw;	}

void Collider::draw()
{
	if (drawBB)
		r->draw();
}

/**
 *	returns side with which there is a collision (or -1 if no collision)
 *
 *		Algorithm (uses SAT method)
 * 1)find the normal (for AABB this will just be the x and y axes)
 * 2)project the two AABB onto both axes and look for overlap (called penetration vector)
 * 3)if both overlap, there is a collision! otherwise quit
 * 4)the shorter penetration vector is the collision side
 *
int Collider::collideWith(xAxisAlignedBoundingBox *bb2)
{
	r->resetAllSides();
	
	//we're only dealing with AABB for now, so skip step 1
	Coord vXAxis;
	vXAxis.x = 1;
	vXAxis.y = 0;
	Coord vYAxis;
	vYAxis.x = 0;
	vYAxis.y = 1;
	
	//determines whether the collision occured in a positive or negative direction from bb2
	bool isXPositiveCollision = false;
	bool isYPositiveCollision = false;
	
	//winding order is clockwise starting top left
	//0-3 are this collider's bounding box, 4-7 are the comparator
	Coord boundingPoints[8] = {bb->getPoint(AABB_POINT_TOPLEFT), bb->getPoint(AABB_POINT_TOPRIGHT), bb->getPoint(AABB_POINT_BOTRIGHT), bb->getPoint(AABB_POINT_BOTLEFT), bb2->getPoint(AABB_POINT_TOPLEFT), bb2->getPoint(AABB_POINT_TOPRIGHT), bb2->getPoint(AABB_POINT_BOTRIGHT), bb2->getPoint(AABB_POINT_BOTLEFT)};
	
	float xProjections1[4];
	float xProjections2[4];
	float yProjections1[4];
	float yProjections2[4];
	
	for (int i = 0;i < 4;i++)
	{
		//xProjections
		xProjections1[i] = ((boundingPoints[i].x * vXAxis.x) + (boundingPoints[i].y * vXAxis.y));
		xProjections2[i] = ((boundingPoints[i + 4].x * vXAxis.x) + (boundingPoints[i + 4].y * vXAxis.y));		
		//yProjections
		yProjections1[i] = ((boundingPoints[i].x * vYAxis.x) + (boundingPoints[i].y * vYAxis.y));
		yProjections2[i] = ((boundingPoints[i + 4].x * vYAxis.x) + (boundingPoints[i + 4].y * vYAxis.y));		
	}
	
	float min1, min2, max1, max2;
	//test x axis
	min1 = *std::min_element(xProjections1, xProjections1+4);
	min2 = *std::min_element(xProjections2, xProjections2+4);
	max1 = *std::max_element(xProjections1, xProjections1+4);
	max2 = *std::max_element(xProjections2, xProjections2+4);
	float xCollision = 0.0f;
	
	if (min1 < min2) //bb1 is to the left of bb2
	{
		isXPositiveCollision = true;
		if (max1 > min2)
			xCollision = max1 - min2;
	}
	else						 //bb1 is to the right of bb2
	{
		if (max2 > min1)
			xCollision = max2 - min1;
	}
	
	
	//test y axis
	min1 = *std::min_element(yProjections1, yProjections1+4);
	min2 = *std::min_element(yProjections2, yProjections2+4);
	max1 = *std::max_element(yProjections1, yProjections1+4);
	max2 = *std::max_element(yProjections2, yProjections2+4);
	float yCollision = 0.0f;
	
	if (min1 < min2) //bb1 is above bb2
	{
		isYPositiveCollision = true;
		if (max1 > min2)
			yCollision = max1 - min2;
	}
	else						 //bb1 is below bb2
	{
		if (max2 > min1)
			yCollision = max2 - min1;
	}
	
	if (xCollision > 0.0f && yCollision > 0.0f) //collision!
	{
		if (xCollision < yCollision)
		{
			if (isXPositiveCollision && bb2->sideIsCollidable(AABB_SIDE_LEFT))
			{
					r->toggleSide(AABB_SIDE_RIGHT);
					return AABB_SIDE_RIGHT;
			}
			else if (bb2->sideIsCollidable(AABB_SIDE_RIGHT))
			{
				r->toggleSide(AABB_SIDE_LEFT);
				return AABB_SIDE_LEFT;
			}
		}
		else 
		{
			if (isYPositiveCollision && bb2->sideIsCollidable(AABB_SIDE_TOP))
			{
				r->toggleSide(AABB_SIDE_BOT);
				return AABB_SIDE_BOT;
			}
			else if (bb2->sideIsCollidable(AABB_SIDE_BOT))
			{
				r->toggleSide(AABB_SIDE_TOP);
				return AABB_SIDE_TOP;
			}
		}
	}
	
	return -1;
}

Coord Collider::reactToCollision(Controller *c, int collisionType, int deltaTime)
{
	//if there's a collision, snap entity to its colliding tile
	
	Coord xy = c->getPosition();
	Coord vel;
	vel.x = c->getXVelocity() / 1000.0f;
	vel.y = c->getYVelocity() / 1000.0f;
	Coord newXY;
	newXY.x = xy.x + (deltaTime * vel.x);
	newXY.y = xy.y + (deltaTime * vel.y);
	float xDist = (newXY.x > xy.x) ? (newXY.x - xy.x) : (xy.x - newXY.x);
	float yDist = (newXY.y > xy.y) ? (newXY.y - xy.y) : (xy.y - newXY.y);
	double trueDT = 0.0;
	double interpolation = 1;
	if (collisionType % 2 == 0)
	{
		int round = newXY.y;
		if (collisionType == 0)
		{
			//top collision: reverse movement until top side of bounding box aligns with bottom side of tile
			round = (int)(newXY.y + 0.5);
			while (((int)(round - getBoundingBox()->getYVect()) % 20) != 0)
				round++;
			
		}
		else
		{
			//bot collision
			round = (int)(newXY.y);
			while (((int)(round + getBoundingBox()->getYVect()) % 20) != 0)
				round--;
		}
		float delDist = (newXY.y > round) ? (newXY.y - round) : (round - newXY.y);
		interpolation = 1 - (delDist / yDist);
		trueDT = interpolation * deltaTime;
		c->setYVelocity(c->getYVelocity() * -1);
	}
	else
	{
		int round = newXY.x;
		if (collisionType == 1)
		{
			//right collision
			round = (int)(newXY.x);
			while (((int)(round + getBoundingBox()->getXVect()) % 20) != 0)
				round--;
		}
		else
		{
			//left collision
			round = (int)(newXY.x + 0.5);
			while (((int)(round - getBoundingBox()->getXVect()) % 20) != 0)
				round++;
		}
		float delDist = (newXY.x > round) ? (newXY.x - round) : (round - newXY.x);
		interpolation = 1 - (delDist / xDist);
		trueDT = interpolation * deltaTime;
		
		c->setXVelocity(c->getXVelocity() * -1);
	}
	
	newXY.x = xy.x + (trueDT * vel.x);
	newXY.y = xy.y + (trueDT * vel.y);
	return newXY;
}

void Collider::cleanup()
{	r->cleanup();	}

xAxisAlignedBoundingBox *Collider::getBoundingBox()
{	return bb;	}

*/