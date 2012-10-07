#ifndef _OLDENTITY_H_
#define _OLDENTITY_H_

#include <string>
#include "SDL/SDL.h"

#include "texturerender.h"
#include "collider.h"
#include "controller.h"
#include "global.h"
#include "map.h"


class OldEntity
{
private:
	TextureRender *r;
	Controller *c;
	Collider *b;
	
	bool isUp, isRight, isDown, isLeft, isSpace;
	
	void reposition(Coord xy);
public:
	OldEntity();
	~OldEntity();

	void init();
	bool load(std::string tex_filepath);
	void onEvent(SDL_Event event);
	void update(int deltaTime, Map m);
	void draw();
	void cleanup();

	bool checkCollisions(Map m, int deltaTime);
	
	void setPosition(float x, float y);
	
	//transforms
	void translate(float x, float y);
	void rotate(float r);
	void resize(int w, int h);

	//for debug purposes only, remove in production
	Controller *control();
	TextureRender *render();
	Collider *boundingbox();


};

#endif