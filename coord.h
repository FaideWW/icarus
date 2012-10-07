#ifndef _COORD_H_
#define _COORD_H_

//coord is used for any generic pair of values (2d vectors most commonly)
struct Coord
{
	float x;
	float y;
  const Coord operator+(const Coord &other) const 
	{
    Coord result = *this;    
    result.x += other.x;
    result.y += other.y;
    return result;
	}
	
  const Coord operator-(const Coord &other) const 
	{
    Coord result = *this;    
    result.x -= other.x;
    result.y -= other.y;
    return result;
	}
	
	Coord & operator+=(const Coord &add)
	{
		x += add.x;
		y += add.y;
		return *this;
	}
	
	Coord & operator-=(const Coord &add)
	{
		x -= add.x;
		y -= add.y;
		return *this;
	}

	//scalar multiplication
	Coord & operator*(const float &scalar)
	{
		x = x * scalar;
		y = y * scalar;
	}

	Coord & operator*(const int &scalar)
	{
		x = x * scalar;
		y = y * scalar;
	}
};

#endif