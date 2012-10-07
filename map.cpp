#include <cmath>
#include <cstdio>
/*
#include "map.h"

Map::Map()
{
	r = NULL;
	width, height = 0;
	tWidth, tHeight = 0;
}

Map::~Map()
{
	r = NULL;
	width, height = 0;
	tWidth, tHeight = 0;
}

int Map::init()
{
	//does nothing for now
	return 1;
}

int Map::load(std::string filename)
{
	FILE * mapfile;
	mapfile = fopen(filename.c_str(), "r");

	if (mapfile == NULL)
		return 0;

	fscanf(mapfile, "%d:%d", &width, &height);
	fscanf(mapfile, "\n");
	
	tWidth = WINDOW_WIDTH / width;
	tHeight = WINDOW_HEIGHT / height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile temp;
			fscanf(mapfile, "%d:%d ", &temp.texID, &temp.tileType);
			tileset.push_back(temp);
			
			Coord p = {static_cast<float>(((tWidth * x) + (tWidth / 2))),static_cast<float>(((tHeight * y) + (tHeight / 2)))};
			
			//this is getting a bit cumbersome; perhaps move this to a tile constructor?
			
			int id = y * width + x;
			tileset[id].b = new xAxisAlignedBoundingBox(p, tWidth, tHeight);
			tileset[id].r = new BoundingBoxRender();
			tileset[id].r->loadBB(tileset[id].b);
		}
		fscanf(mapfile, "\n");
	}
	
	fclose(mapfile);
	collapseTileSides();
	r = new ColorRender();
	
	//we assume these are never 0 from now on
	return 1;
}

//takes adjacent tiles and collapses them (removes their collidable edges since nothing will ever collide with an inner edge
void Map::collapseTileSides()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int id = y * width + x;
			//       4-directional flood-fill check 
			
			//checking directions (eg. right checks the tile to the right against the right edge of the current tile)
			int up = id - width;
			int right = id + 1;
			int down = id + width;
			int left = id - 1;
			if (up > 0 && tileset[up].tileType == TILE_TYPE_SOLID)
				tileset[id].b->disableSide(AABB_SIDE_TOP);
			if (right < tileset.size() && tileset[right].tileType == TILE_TYPE_SOLID)
				tileset[id].b->disableSide(AABB_SIDE_RIGHT);
			if (down < tileset.size() && tileset[down].tileType == TILE_TYPE_SOLID)
				tileset[id].b->disableSide(AABB_SIDE_BOT);
			if (left > 0 && tileset[left].tileType == TILE_TYPE_SOLID)
				tileset[id].b->disableSide(AABB_SIDE_LEFT);
		}
	}
}

void Map::draw()
{

	int id = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (tileset[id].tileType == TILE_TYPE_NONE)
			{
				id++;
				continue;
			}
			Color c;
			if (tileset[id].tileType == TILE_TYPE_SOLID)
			{
				c.r = 0.2f;
				c.g = 0.0f;
				c.b = 0.0f;
				c.a = 1.0f;
			}
			else if (tileset[id].tileType == TILE_TYPE_SLOW)
			{
				c.r = 0.1f;
				c.g = 0.0f;
				c.b = 0.0f;
				c.a = 0.5f;
			}
			else if (tileset[id].tileType == TILE_TYPE_FRONT)
			{
				c.r = 0.2f;
				c.g = 0.0f;
				c.b = 0.0f;
				c.a = 1.0f;
			}
			
			r->load(c, tWidth, tHeight);
			r->draw((x * tWidth), (y * tHeight), 0.0f, 0.0f);
			tileset[id].r->draw();
			id++;
		}
	}
}

Tile Map::getTile(Coord xy)
{	return getTile(xy.x, xy.y);	}

Tile Map::getTile(float x, float y)
{
	int id = ((((int)(y / tHeight)) * width) + ((int)(x / tWidth)));
	
	//segfault if the location is invalid (as long as it works, this is pre alpha after all)
	return tileset[id];
}

/** 
 *     changed apr 9 12: this works now
 *
 *			TODO: -works for small maps and slow velocities, but will break down if the velocity
 *						 is too high (one step moves an object through a tile)
 *						-implement ray casting broadphase collision detection: all tiles in an object's 
 *						 given trajectory step will be activated and narrowphase collision performed on them
 *
 *	very simple broadphase collision: checks all tiles intersecting the collider's bounding box,
 *	and performs narrowphase collision via the collider's functionality
 *
 *
 
int Map::collide(Collider *col, Controller *c, int deltaTime)
{
	
	Coord savedPos = c->getPosition();
	c->move(deltaTime);
	Coord newPos = c->getPosition();
	c->setPosition(savedPos);
	col->moveBoundingBox(newPos);
	
	Tile activated[4];
	activated[0] = getTile(col->getBoundingBox()->getPoint(AABB_POINT_TOPLEFT));
	activated[1] = getTile(col->getBoundingBox()->getPoint(AABB_POINT_TOPRIGHT));
	activated[2] = getTile(col->getBoundingBox()->getPoint(AABB_POINT_BOTRIGHT));
	activated[3] = getTile(col->getBoundingBox()->getPoint(AABB_POINT_BOTLEFT));
	int collisionSide = -1;
	for (int i = 0; i < 4; i++)
	{
		if (activated[i].tileType == TILE_TYPE_NONE) 
		{	continue;	}
		int collides = col->collideWith(activated[i].b);
		if (collides >= 0)
		{
			if (collides % 2 == 0)
				collisionSide = collides;
			else if (collides % 2 != 0)
				collisionSide = collides;
		}
	}
	
	col->moveBoundingBox(savedPos);
	
	//y collisions are dominant, since this game subscribes to the laws of gravity
	// meaning: if there is a double collision (corner case), the y collision will be handled first
	//  hopefully this causes 0 issues (doodling on napkins leads me to believe otherwise however, but one step at a time)
	
	return collisionSide;
}
void Map::cleanup()
{
	delete r;
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tileset[y * width + x].r->cleanup();
			delete tileset[y * width + x].r;
			delete tileset[y * width + x].b;
			
		}
	}
}

int Map::getTileWidth()
{	return tWidth;	}

int Map::getTileHeight()
{	return tHeight;	}

*/