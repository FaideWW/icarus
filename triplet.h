//
//  triplet.h
//  icarus
//
//  Created by Robert Powell on 12-04-23.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#ifndef _TRIPLET_H_
#define _TRIPLET_H_

struct Triplet 
{
	float x;
	float y;
	float z;
	
  const Triplet operator+(const Triplet &other) const 
	{
    Triplet result = *this;    
    result.x += other.x;
    result.y += other.y;
		result.z += other.z;
    return result;
	}
	
	Triplet & operator+=(const Triplet &add)
	{
		x += add.x;
		y += add.y;
		z += add.z;
		return *this;
	}
};

#endif
