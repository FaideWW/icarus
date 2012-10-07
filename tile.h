#ifndef _TILE_H_
#define _TILE_H_

#include <bitset>

#include "global.h"
#include "_boundingbox.h"



enum 
{
	TILE_TYPE_NONE = 0,
	TILE_TYPE_SOLID,
	TILE_TYPE_SLOW,
	TILE_TYPE_FRONT
};

struct Tile
{
	int texID;
	int tileType;
	
	//bitset reads right->left, so winding order will appear reversed if printed but forwards if iterated over
	xAxisAlignedBoundingBox *b;
};

#endif