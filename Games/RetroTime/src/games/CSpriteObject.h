#ifndef CSPRITEOBJECT_H
#define CSPRITEOBJECT_H

#include "../CSprites.h"
#include "../Vec2F.h"

struct CSpriteObject
{
		bool alive;
		Vec2F vel;
		Vec2F pos;
		SDL_Point tz;
		CSprite* spr;
		int healthpoints;
		int freeze;
		int state;
		int stateticks;
		//used in toad
		int rowtype;
		int id;
		//used in pang
		float force;
		float speed;
		float curforce;
		//used in fast eddy
		int floory;
		int jumpdown;
		int group;
		int row;
};

void Initialize_CSpriteObject(CSpriteObject *SpriteObject)
{
	SpriteObject->alive = false;
	SpriteObject->vel.x =0;
	SpriteObject->vel.y =0;
	SpriteObject->pos.x =0;
	SpriteObject->pos.y =0;
	SpriteObject->tz.x = 0;
	SpriteObject->tz.y = 0;
	SpriteObject->spr = NULL;
	SpriteObject->healthpoints = 0;
	SpriteObject->freeze = 0;
	SpriteObject->state = 0;
	SpriteObject->stateticks = 0;
	//used in toad
	SpriteObject->rowtype = 0;
	SpriteObject->id = 0;
	//used in pang
	SpriteObject->force = 0.0;
	SpriteObject->speed = 0.0;
	SpriteObject->curforce = 0.0;
	//used in fast eddy
	SpriteObject->floory = 0;
	SpriteObject->jumpdown = 0;
	SpriteObject->group = 0;
	SpriteObject->row = 0;
}

#endif