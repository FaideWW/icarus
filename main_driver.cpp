#include <cstdio>
#include <sstream>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include "entity.h"
#include "aaboundingbox.h"
#include "component.h"
#include "componentfactory.h"
#include "entitymanager.h"
#include "transform.h"
#include "renderservice.h"

SDL_Event event;

int init()
{
	srand(time(NULL));
	SDL_Surface *screen;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("error init sdl: %s\n", SDL_GetError());
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_OPENGL);
	if (!screen)
	{
		printf("error setting video mode: %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}

void init_GL()
{
	glClearColor(0,0,0,0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glAlphaFunc ( GL_GREATER, 0.1 ) ;
	glEnable ( GL_ALPHA_TEST ) ;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void clean_up()
{
	SDL_Quit();
}

std::string itoa(int number)
{
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}


int main(int argc, char *argv[])
{
	bool quit = false;
	if (init() == 0)
		return 0;
	init_GL();
	
	std::string abs_filepath = "";
	
	std::string file1_name = "ball.png";
	std::string mapfile_name = "map1.map";
	
	std::string file1 = file1_name;
	std::string mapfile = abs_filepath + mapfile_name;
	
	ComponentFactory *cf = new ComponentFactory();
	
	EntityManager *em = new EntityManager();
	
	RenderService *r = new RenderService(1);
	r->init();
	r->em = em;
	
	int counter = SDL_GetTicks();
	int counter_interim = 0;

	//there's a ridiculous amount of input lag when mousemotion events are handled, so I'm ignoring them for now.
	//maybe later we can throw each event type into a thread for asynchronous handling
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	
	/*	----	loop phase	----	*/
	while(quit == false)
	{
		
		/*	----  event phase	----  */
		if (SDL_PollEvent(&event))
		{

			//high priority events (pause, quit)
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
				{
					break;
				}
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_SPACE:
						{
							//this will be done in lua
							std::map<std::string, std::string> lProps, rProps, bbProps, pProps;
							int x = rand() % WINDOW_WIDTH;
							int y = rand() % WINDOW_HEIGHT;
							lProps.insert(std::pair<std::string, std::string>("x", "0"));
							lProps.insert(std::pair<std::string, std::string>("y", "0"));
							lProps.insert(std::pair<std::string, std::string>("z", "0"));
							
							float width = (float)(rand() % 500) / 100;
							float height = (float)(rand() % 500) / 100;
							std::string w, h;							
							std::stringstream in (std::stringstream::in | std::stringstream::out);
							in<<width;
							w = in.str();
							in.clear();//clear any bits set
							in.str(std::string());
							in<<height;
							h = in.str();
							in.clear();//clear any bits set
							in.str(std::string());
							lProps.insert(std::pair<std::string, std::string>("w", w));
							lProps.insert(std::pair<std::string, std::string>("h", h));
							float rot = rand() % 360;
							lProps.insert(std::pair<std::string, std::string>("r", itoa(rot)));
							
							rProps.insert(std::pair<std::string, std::string>("filename", file1));
							rProps.insert(std::pair<std::string, std::string>("w", "16"));
							rProps.insert(std::pair<std::string, std::string>("h", "16"));
							
							width *= 8;
							height *= 8;
							
							in<<width;
							w = in.str();
							in.clear();//clear any bits set
							in.str(std::string());
							in<<height;
							h = in.str();
							in.clear();//clear any bits set
							in.str(std::string());
							 
							bbProps.insert(std::pair<std::string, std::string>("bb_type", ""+BOUNDINGBOX_TYPE_AXISALIGNED));
							bbProps.insert(std::pair<std::string, std::string>("half_x", w));
							bbProps.insert(std::pair<std::string, std::string>("half_y", h));
							bbProps.insert(std::pair<std::string, std::string>("offset_x", "0"));
							bbProps.insert(std::pair<std::string, std::string>("offset_y", "0"));
							bbProps.insert(std::pair<std::string, std::string>("r", itoa(rot)));

							pProps.insert(std::pair<std::string, std::string>("fps", "60"));
							pProps.insert(std::pair<std::string, std::string>("vMax", "300"));
							pProps.insert(std::pair<std::string, std::string>("vX", "5"));
							pProps.insert(std::pair<std::string, std::string>("vY", "5"));
							pProps.insert(std::pair<std::string, std::string>("pX", itoa(x)));
							pProps.insert(std::pair<std::string, std::string>("pY", itoa(y)));
							pProps.insert(std::pair<std::string, std::string>("pZ", "0"));
							
							
							
							int ent = em->addEntity();
							em->addComponentToEntity(ent, NULL, cf->createComponent(COMPONENT_TYPE_DATA_TRANSFORM, lProps));
							em->addComponentToEntity(ent, r, cf->createComponent(COMPONENT_TYPE_RENDERABLE_TEXTURE, rProps)); 
							em->addComponentToEntity(ent, NULL, cf->createComponent(COMPONENT_TYPE_DATA_BOUNDINGBOX, bbProps));
							em->addComponentToEntity(ent, NULL, cf->createComponent(COMPONENT_TYPE_EVENT_PHYSICAL, pProps));
						break;
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						printf("click! %d\n", counter);
						bool clickedOnEntity = false;
						Coord mouse;
						int x = event.button.x;
						int y = event.button.y;
						mouse.x = x;
						mouse.y = y;
						std::vector<bool> toDelete;
						toDelete.assign(em->countEntities(), false);
						for (int i = 0; i < em->countEntities(); i++)
						{
							if (!em->entities[i]) continue;
							if (em->entities[i]->c_bits.test(COMPONENT_TYPE_DATA_BOUNDINGBOX) && em->entities[i]->c_bits.test	(COMPONENT_TYPE_DATA_TRANSFORM))
							{
								Triplet position = ((Transform*)em->entities[i]->c[COMPONENT_TYPE_DATA_TRANSFORM])->xyz;
								
								
								if (((AxisAlignedBoundingBox*)em->entities[i]->c[COMPONENT_TYPE_DATA_BOUNDINGBOX])->pointInPoly(position, mouse))
								{
									toDelete[i] = true;
									clickedOnEntity = true;
									printf("deleting entity\n");
								}
							}
						}
					
						for (int i = 0; i < em->countEntities(); i++)
						{
							if (toDelete[i]) 
							{
								r->removeComponent(em->pollEntityState(em->entities[i]->globalID)[COMPONENT_TYPE_RENDERABLE_TEXTURE]->serviceID);
								em->deleteEntity(em->entities[i]->globalID);
							}
						}
					
					
						if (!clickedOnEntity)
						{
							printf("adding entity\n");
							//this will be done in lua
							std::map<std::string, std::string> lProps, rProps, bbProps, pProps;
							lProps.insert(std::pair<std::string, std::string>("x", itoa(event.button.x)));
							lProps.insert(std::pair<std::string, std::string>("y", itoa(event.button.y)));
							lProps.insert(std::pair<std::string, std::string>("z", "0"));
						
							rProps.insert(std::pair<std::string, std::string>("filename", file1));
							rProps.insert(std::pair<std::string, std::string>("w", "16"));
							rProps.insert(std::pair<std::string, std::string>("h", "16"));
						
							bbProps.insert(std::pair<std::string, std::string>("bb_type", ""+BOUNDINGBOX_TYPE_AXISALIGNED));
							bbProps.insert(std::pair<std::string, std::string>("half_x", "8"));
							bbProps.insert(std::pair<std::string, std::string>("half_y", "8"));
							bbProps.insert(std::pair<std::string, std::string>("offset_x", "0"));
							bbProps.insert(std::pair<std::string, std::string>("offset_y", "0"));

							pProps.insert(std::pair<std::string, std::string>("fps", "60"));
							pProps.insert(std::pair<std::string, std::string>("vMax", "300"));
							pProps.insert(std::pair<std::string, std::string>("vX", "5"));
							pProps.insert(std::pair<std::string, std::string>("vY", "5"));
							pProps.insert(std::pair<std::string, std::string>("pX", itoa(x)));
							pProps.insert(std::pair<std::string, std::string>("pY", itoa(y)));
							pProps.insert(std::pair<std::string, std::string>("pZ", "0"));
						
							int ent = em->addEntity();
							em->addComponentToEntity(ent, NULL, cf->createComponent(COMPONENT_TYPE_DATA_TRANSFORM, lProps));
							em->addComponentToEntity(ent, r, cf->createComponent(COMPONENT_TYPE_RENDERABLE_TEXTURE, rProps)); 
							em->addComponentToEntity(ent, NULL, cf->createComponent(COMPONENT_TYPE_DATA_BOUNDINGBOX, bbProps));
							em->addComponentToEntity(ent, NULL, cf->createComponent(COMPONENT_TYPE_EVENT_PHYSICAL, pProps));
						}
						
					}else{
						r->clearAllComponents();
						em->clearAllEntities();
						
					}
					break;
				}
			}
		}
		
		
		
		counter_interim = SDL_GetTicks();
		int deltaTime = counter_interim - counter;
		
		if (deltaTime > 0) //if we need to update the screen anything
		{
			/*	----	update/draw phase	----	*/
			counter = counter_interim;
			
			//start draw sequence
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//map ALWAYS renders first
			r->step(deltaTime);
			SDL_GL_SwapBuffers();
			//end draw sequence
		}
	}
	
	/*	----	unload phase	----	*/
	r->cleanup();
	em->cleanup();
	
	delete r;
	delete em;
	delete cf;
	clean_up();
	exit(0);
	return 0;
}

/*int main_(int argc, char *argv[])
{
	bool quit = false;
	if (init() == 0)
		return 0;
	init_GL();
	
	std::string abs_filepath = "/Users/robertpowell/dev/icarus/icarus/";
	
	std::string file1_name = "ball.png";
	std::string mapfile_name = "map1.map";
	
	std::string file1 = abs_filepath + file1_name;
	std::string mapfile = abs_filepath + mapfile_name;
	
	Entity *e1 = new Entity();
	Map *m1 = new Map();
	
	//	----	init phase	----	
	e1->init();
	m1->init();
	
	//	----	load phase	---- 
	e1->load(file1);
	m1->load(mapfile);
	
	//TODO: devise a better solution than this, this blows
	//		31/3/12: this will probably end up being done in LUA
	e1->setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
	e1->control()->setZ(0.0f);
	e1->control()->setXVelocity(0);
	e1->control()->setYVelocity(0);
	//e1->resize(20, 20);

	int counter = SDL_GetTicks();
	int counter_interim = 0;

	//	----	loop phase	----	
	while(quit == false)
	{
		
		//	----  event phase	----  
		if (SDL_PollEvent(&event))
		{
			//high priority events (pause, quit)
			if (event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = true;
						break;
				}	
			}
			//low priority events (input)
			e1->onEvent(event);
		}

		counter_interim = SDL_GetTicks();
		int deltaTime = counter_interim - counter;
		
		if (deltaTime > 0) //if we need to update the screen anything
		{
			//	----	update/draw phase	----
			
			e1->update(deltaTime, *m1);
			
			counter = counter_interim;

			//start draw sequence

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//map ALWAYS renders first
			m1->draw();
			e1->draw();
			SDL_GL_SwapBuffers();
			//end draw sequence

		}
	}
 
	//	----	unload phase	----	
	e1->cleanup();
	m1->cleanup();
	delete e1;
	delete m1;
	clean_up();
	exit(0);
	return 0;
}*/