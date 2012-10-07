#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "component.h"
#include "coord.h"
#include "triplet.h"

class BoundingBox : public Component
{
public:
	virtual bool pointInPoly(Triplet, Coord) = 0;
	virtual bool vecIntersectsVec(Coord, Coord, Coord, Coord) = 0;
	virtual bool certifyParams() = 0;
};


#endif