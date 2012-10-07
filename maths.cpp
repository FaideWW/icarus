//
//  maths.cpp
//  icarus
//
//  Created by Stefan Rezko on 12-06-26.
//  Copyright (c) 2012 Alien Swordfish Labs. All rights reserved.
//

#include "maths.h"


//miscellaneous math functions that are used > 1 times

//returns vecR x vecS
float imath::vecCrossProduct(Coord vecR, Coord vecS)
{
	return (vecR.x * vecS.y) - (vecR.y * vecS.x);
}