#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <cstdio>

#include "tile.h"
#include "collider.h"
#include "controller.h"

class Map
{
private:
	//1D vector of tiles
	std::vector<Tile> tileset; 
	ColorRender *r;
	//dimensions in tile units
	int width, height;
	int tWidth, tHeight;

public:
	Map();
	~Map();
	int init();
	int load(std::string filename);
	void draw();
	void cleanup();
	
	void collapseTileSides();
	Tile getTile(Coord xy);
	Tile getTile(float x, float y);
	int collide(Collider *col, Controller	*c, int deltaTime);
	int getTileWidth();
	int getTileHeight();

};

#endif