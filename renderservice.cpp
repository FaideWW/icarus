#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "physical.h"
#include "transform.h"
#include "renderservice.h"

RenderService::RenderService(int ID)
{
	serviceType = SERVICE_TYPE_RENDER;
	serviceID = ID;
}

RenderService::RenderService(int ID, EntityManager *e)
{
	em = e;
	serviceType = SERVICE_TYPE_RENDER;
	serviceID = ID;
}

RenderService::~RenderService()
{
    
}

bool RenderService::init()
{
	return true;
}

void RenderService::step(int deltaTime)
{
	//we want to render as fast as possible, so ignore deltaTime
	draw();
}

void RenderService::cleanup()
{
    
}

int RenderService::addComponent(Component *c)
{
	if ((c->typeID != COMPONENT_TYPE_RENDERABLE_COLOR) && (c->typeID != COMPONENT_TYPE_RENDERABLE_TEXTURE))
		return -1;
	if (!loadComponentInfo((Renderable*)c)) return -1;
	components.push_back((Renderable*)c);
	c->serviceID = serviceID;
	components = sortComponents(components);
	c->componentID = components.size()-1;
	c->certifyParams();
	return (components.size()-1);
}

void RenderService::removeComponent(int componentID)
{
	components[componentID] = NULL;
	components = sortComponents(components);
}

void RenderService::clearAllComponents()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i] = NULL;
	}
	components.clear();
}

bool RenderService::loadComponentInfo(Renderable *c)
{
	if (c->typeID == COMPONENT_TYPE_RENDERABLE_TEXTURE)
		return loadTextureInfo(c);
	else if (c->typeID == COMPONENT_TYPE_RENDERABLE_COLOR)
		return loadColorInfo(c);
	else
		return false;
}

/**
 *	component parameter requirements:
 *		"filename" : std::string => path to the image/texture file
 */
bool RenderService::loadColorInfo(Renderable *c)
{
	//don't really need to do anything here, there are no IO failure sources
	return true;
}

/**
 *	this is identical to the old TextureRender::load()
 *
 *	component parameter requirements:
 *		"filename" : std::string => path to the image/texture file
 *
 *	TODO: add crop support
 */
bool RenderService::loadTextureInfo(Renderable *c)
{
	printf("loading new sprite\n");
	SDL_Surface *surf;
	if ((surf = IMG_Load(c->filename.c_str())))
	{
	
		//if the dimensions are not specified use the texture dimensions
		if (c->w == -1 && c->h == -1)
		{
			c->w = surf->w;
			c->h = surf->h;
		}
		
		if ((surf->w & (surf->w - 1)) != 0)
		{
			printf("Error loading %s: width is not a power of 2 (%ix%i)\n", c->filename.c_str(), surf->w, surf->h);
			return false;
		}
		if ((surf->h & (surf->h - 1)) != 0)
		{
			printf("Error loading %s: height is not a power of 2 (%ix%i)\n", c->filename.c_str(), surf->w, surf->h);
			return false;
		}
		
		GLint nColors = surf->format->BytesPerPixel;
		GLenum format;
		if (nColors == 4)
		{
			if (surf->format->Rmask == 0x000000ff)
				format = GL_RGBA;
			else
				format = GL_BGRA;
		}
		else if (nColors == 3)
		{
			if (surf->format->Rmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_BGR;
		}
		else
		{
			printf("Error loading %s: image is not truecolor (%ibpp)\n", c->filename.c_str(), nColors);
		}
		
		GLuint t;
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &t);
		glBindTexture(GL_TEXTURE_2D, t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, nColors, surf->w, surf->h, 0, 
								 format, GL_UNSIGNED_BYTE, surf->pixels);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glDisable(GL_TEXTURE_2D);
		
		c->tex = t;
		if (surf)
			SDL_FreeSurface(surf);
		
		return true;
	}
	else
	{
		printf("Error loading %s: invalid file\n", c->filename.c_str());
		printf("SDL: %s\n", SDL_GetError());
		return false;
	}
}




std::vector<Component*> RenderService::sortComponents(std::vector<Component*> x)
{	
	
	//x = sortComponentsRecursive(x);
	std::vector<Component*> n;
	int count = 0;
	//printf("begin loop\n");
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] != NULL) 
		{
			n.push_back(x[i]);
			int c = count++;
			n[c]->serviceID = c;
		}
	}
	
	//printf("end loop\n");
	return n;
}

/**
 *
 *	right now this just iterates through each component and renders individually
 *	
 *	TODO: implement VBOs, saves CPU cycles
 *
 */
void RenderService::draw()
{
	for (int i = 0;i < components.size(); i++)
	{	
		if ((Renderable*) components[i]) //double check that we don't accidentally reference an empty slot
		{
			if (((Renderable*)components[i])->typeID == COMPONENT_TYPE_RENDERABLE_TEXTURE)
				drawTexturePoly((Renderable*) components[i]);
			else if (((Renderable*)components[i])->typeID == COMPONENT_TYPE_RENDERABLE_COLOR)
				drawColorPoly((Renderable*) components[i]);
		}
	}
}
				
void RenderService::drawColorPoly(Renderable *c)
{
	Physical p = *(Physical *)em->pollEntityState(c->entityID)[COMPONENT_TYPE_EVENT_PHYSICAL];
  Transform l = *(Transform *)em->pollEntityState(c->entityID)[COMPONENT_TYPE_DATA_TRANSFORM];
	float tX = l.wh.x / 2.0f;
	float tY = l.wh.y / 2.0f;
	float colorpush[4];
	glGetFloatv(GL_CURRENT_COLOR, colorpush);
	glPushMatrix();
	Triplet xyz = p.getPosition3D();
	glTranslatef(xyz.x,xyz.y,xyz.z);
	glTranslatef(l.xyz.x, l.xyz.y, l.xyz.z);
	glRotatef(l.r, 0.0f, 0.0f, 1.0f);
	glColor4f((c->col.r * colorpush[0]), (c->col.g * colorpush[1]), (c->col.b * colorpush[2]), (c->col.a * colorpush[3]));
	glBegin(GL_QUADS);
		glVertex3i(-tX,-tY,0);
		glVertex3i(tX, -tY, 0);
		glVertex3i(tX, tY, 0);
		glVertex3i(-tX, tY, 0);
	glEnd();
	glPopMatrix();
	glColor4fv(colorpush);
}

void RenderService::drawTexturePoly(Renderable *c)
{
	printf("loading physical\n");
	Physical p = *(Physical *)em->pollEntityState(c->entityID)[COMPONENT_TYPE_EVENT_PHYSICAL];
	printf("loaded physical\n");
	Transform l = *(Transform *)em->pollEntityState(c->entityID)[COMPONENT_TYPE_DATA_TRANSFORM];
	glEnable(GL_TEXTURE_2D);
	float tX = (c->w * l.wh.x) / 2.0f;
	float tY = (c->h * l.wh.y) / 2.0f;
	glBindTexture(GL_TEXTURE_2D, c->tex);
	glPushMatrix();
	Triplet xyz = p.getPosition3D();
	glTranslatef(xyz.x,xyz.y,xyz.z);
	glTranslatef(l.xyz.x, l.xyz.y, l.xyz.z);
	glRotatef(l.r, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3i(-tX, -tY, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3i(tX, -tY, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3i(tX, tY, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3i(-tX, tY, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

