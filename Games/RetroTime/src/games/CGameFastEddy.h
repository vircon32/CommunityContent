#ifndef CGAMEFASTEDDY_H
#define CGAMEFASTEDDY_H

#include "math.h"
#include "CGameBase.h"
#include "CSpriteObject.h"
#include "../Common.h"
#include "../CGame.h"
#include "../Vec2F.h"
#include "../SDL_HelperTypes.h"


#define GameFastEddy_candie true

#define GameFastEddy_playerstateunknown -1
#define GameFastEddy_playerstateidle 0
#define GameFastEddy_playerstateleft 1
#define GameFastEddy_playerstateleftjump 2
#define GameFastEddy_playerstateright 3
#define GameFastEddy_playerstaterightjump 4
#define GameFastEddy_playerstatejump 5
#define GameFastEddy_playerstateclimbup 6
#define GameFastEddy_playerstateclimbdown 7

#define GameFastEddy_enemystateidle 0
#define GameFastEddy_enemystatemoveleft 1
#define GameFastEddy_enemystatewaitmove 2
#define GameFastEddy_enemystatemoveright 3

#define GameFastEddy_collectablestatemoveleft 0
#define GameFastEddy_collectablestatemoveright 1
#define GameFastEddy_collectablestateidle 2

#define GameFastEddy_laddersfitrows 10
//tilesize / 2 oroginals are 64x64 was 32x32 
#define GameFastEddy_rowfloorsizex (32 * xscale*20)
//tilesize / 2 oroginals are 64x64 was 32x32 
#define GameFastEddy_rowfloorsizey (32 * yscale)
#define GameFastEddy_rows 5

#define GameFastEddy_playerspeed (6.4*xscale )
#define GameFastEddy_playerjumpspeed 2.0 
#define GameFastEddy_playerclimbspeed (2.0 * yscale )
#define GameFastEddy_collectablespeed (2*xscale )

#define GameFastEddy_maxenemies 10
#define GameFastEddy_maxcollectables 2

//(rows - 1) * 2;
#define GameFastEddy_maxladders 8
//(int)(ScreenWidth / rowfloorsizex * rows)
#define GameFastEddy_maxfloors (int)(ScreenWidth / GameFastEddy_rowfloorsizex * GameFastEddy_rows)


struct CGameFastEddy {
	CGameBase *GameBase;
	 
	float playerjumpspeeddec;

	int numfloortilesperrow;
	int maxfloortiles;
	float rowspacingsize;
	float ladderwidth;
	float rowsize;
	float playerheight;
	float enemyheight;
	float playerjumpheight;
	float collectableheight;
	float keyheight;

	int spritesheet;
	int spritesheetladder;
	int spritesheetplayerclimb;
	int spritesheetplayerrun;
	int spritesheetplayeridle;
	int spritesheetplayerjump;
	int spritesheetenemy;
	int spritesheetenemy2;
	int spritesheetcollectable;
	int spritesheetkey;
	int background;

	int MusMusic, SfxSucces, SfxCollect, SfxDie;
	bool playerdeath;
	int playeardeathtime;
	int rowzeroenemyindex;
	int collecteditems;
	int collectedcreated;
	int NeedToMoveGroupLeftCount;
	int NeedToMoveGroupRightCount;
	CSpriteObject player;
	CSpriteObject[GameFastEddy_maxladders] ladders;
	CSpriteObject[GameFastEddy_maxfloors] floors; 
	CSpriteObject[GameFastEddy_maxenemies] enemies;
	int[GameFastEddy_maxenemies] NeedToMoveGroupLeft;
	int[GameFastEddy_maxenemies] NeedToMoveGroupRight;
	CSpriteObject[GameFastEddy_maxcollectables] collectables;
	CSpriteObject key;
};


CGameFastEddy* Create_CGameFastEddy()
{
	CSprites_SetSpriteMax(GameFastEddy_maxfloors + GameFastEddy_maxladders + GameFastEddy_maxenemies + GameFastEddy_maxcollectables + 2); //2 = key & player
	CGameFastEddy* GameFastEddy = (CGameFastEddy*) malloc(sizeof(CGameFastEddy));
	GameFastEddy->GameBase = Create_CGameBase(GSEddy, true);

	GameFastEddy->MusMusic = -1;
	GameFastEddy->SfxSucces = -1;
	GameFastEddy->SfxDie = -1;

	GameFastEddy->GameBase->playfieldwidth = ScreenWidth;
	GameFastEddy->GameBase->playfieldheight = ScreenHeight;
	GameFastEddy->GameBase->screenleft = (ScreenWidth - GameFastEddy->GameBase->playfieldwidth) / 2;
	GameFastEddy->GameBase->screenright = GameFastEddy->GameBase->screenleft + GameFastEddy->GameBase->playfieldwidth;
	GameFastEddy->GameBase->screentop = (ScreenHeight - GameFastEddy->GameBase->playfieldheight) / 2;
	GameFastEddy->GameBase->screenbottom = GameFastEddy->GameBase->screentop + GameFastEddy->GameBase->playfieldheight;
	GameFastEddy->numfloortilesperrow = (int)(GameFastEddy->GameBase->playfieldwidth / GameFastEddy_rowfloorsizex);
	GameFastEddy->maxfloortiles = GameFastEddy->numfloortilesperrow * GameFastEddy_rows;
	GameFastEddy->rowspacingsize = (float)(GameFastEddy->GameBase->playfieldheight / GameFastEddy_rows);
	GameFastEddy->ladderwidth = (float)(GameFastEddy->GameBase->playfieldwidth / GameFastEddy_laddersfitrows);
	GameFastEddy->rowsize = GameFastEddy->rowspacingsize - GameFastEddy_rowfloorsizey;
	GameFastEddy->playerheight = GameFastEddy->rowsize * 3 / 4;
	GameFastEddy->enemyheight = GameFastEddy->rowsize * 2 / 5;
	GameFastEddy->playerjumpheight = GameFastEddy->rowsize * 2/ 4;
	GameFastEddy->collectableheight = GameFastEddy->rowsize / 2;
	GameFastEddy->keyheight = GameFastEddy->rowsize / 4;
	GameFastEddy->playerjumpspeeddec = GameFastEddy_playerjumpspeed / GameFastEddy->playerjumpheight ;
	GameFastEddy->NeedToMoveGroupLeftCount = 0;
	GameFastEddy->NeedToMoveGroupRightCount = 0;
	Initialize_CSpriteObject(&GameFastEddy->player);
	for (int i = 0; i < GameFastEddy_maxladders; i++)
		Initialize_CSpriteObject(&GameFastEddy->ladders[i]);
	
	for (int i = 0; i < (int)(ScreenWidth / GameFastEddy_rowfloorsizex * GameFastEddy_rows); i++)
		Initialize_CSpriteObject(&GameFastEddy->floors[i]);

	for (int i = 0; i < GameFastEddy_maxenemies; i++)
	{
		Initialize_CSpriteObject(&GameFastEddy->enemies[i]);
		GameFastEddy->NeedToMoveGroupLeft[i] = -1;
		GameFastEddy->NeedToMoveGroupRight[i] = -1;
	}

	for (int i = 0; i < GameFastEddy_maxcollectables; i++)
		Initialize_CSpriteObject(&GameFastEddy->collectables[i]);

	Initialize_CSpriteObject(&GameFastEddy->key);

	return GameFastEddy;
}

void Destroy_CGameFastEddy(CGameFastEddy* GameFastEddy)
{
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GameFastEddy->GameBase);
	free(GameFastEddy);
	GameFastEddy = NULL;
}

void CGameFastEddy_enemyenablelevelend(CGameFastEddy* GameFastEddy)
{
	int index = GameFastEddy->rowzeroenemyindex;
	SDL_Point tz = {32, 32};
	Vec2F scale = {ceil(GameFastEddy->enemyheight) / tz.y, ceil(GameFastEddy->enemyheight) / tz.y};
	GameFastEddy->enemies[index].tz.x = (int)(tz.x * scale.x);
	GameFastEddy->enemies[index].tz.y = (int)(tz.y * scale.y);
	GameFastEddy->enemies[index].pos.y = (0 + 1) * GameFastEddy->rowspacingsize - GameFastEddy_rowfloorsizey / 2 - GameFastEddy->enemies[index].tz.y / 2;
	GameFastEddy->enemies[index].spr->sxscale = scale.x;
	GameFastEddy->enemies[index].spr->syscale = scale.y;
	CSprites_SetSpriteCollisionShape(GameFastEddy->enemies[index].spr, SHAPE_BOX, tz.x - 10.0, tz.y-10.0,0, 0, 0);
	GameFastEddy->enemies[index].spr->x = GameFastEddy->enemies[index].pos.x;
	GameFastEddy->enemies[index].spr->y = GameFastEddy->enemies[index].pos.y;
}




//collectables ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_destroycollectable(CGameFastEddy* GameFastEddy, int index)
{
	if (GameFastEddy->collectables[index].alive)
	{
		CSprites_RemoveSprite(GameFastEddy->collectables[index].spr);
		GameFastEddy->collectables[index].alive = false;
	}
}

void CGameFastEddy_destroyallcollectables(CGameFastEddy* GameFastEddy)
{
	for (int i = 0; i < GameFastEddy_maxcollectables; i++)
		CGameFastEddy_destroycollectable(GameFastEddy,i);
}


void CGameFastEddy_createcollectables(CGameFastEddy* GameFastEddy, int ignorerow)
{
	SDL_Point tz = {128, 128};
	for (int i = 0; i < GameFastEddy_maxcollectables; i++)
	{
		if(GameFastEddy->collectedcreated < 10)
		{
			if (!GameFastEddy->collectables[i].alive)
			{
				bool bok = false;
				int row = ignorerow;
				while (!bok)
				{
					row = 1 + (rand() % (GameFastEddy_rows-1));
					while(row == ignorerow)
						row = 1 + (rand() % (GameFastEddy_rows-1));
					bool bnocollision = true;
					for(int j = 0; j < GameFastEddy_maxcollectables; j++)
					{
						if(GameFastEddy->collectables[j].alive)
						{
							if(GameFastEddy->collectables[j].row == row)
							{
								bnocollision = false;
								break;
							}
						}
					}
					bok = bnocollision;
				}

				GameFastEddy->collectables[i].spr = CSprites_CreateSprite();
				GameFastEddy->collectables[i].alive = true;
				GameFastEddy->collectables[i].row = row;
				GameFastEddy->collectables[i].state = rand() % 3;
				Vec2F scale = {GameFastEddy->collectableheight / tz.y, GameFastEddy->collectableheight / tz.y};
				GameFastEddy->collectables[i].tz.x = (int)(tz.x * scale.x);
				GameFastEddy->collectables[i].tz.y = (int)(tz.y * scale.y);
				CSprites_SetSpriteImageTiles(GameFastEddy->collectables[i].spr, &GameFastEddy->spritesheetcollectable, 5, 1);
				GameFastEddy->collectables[i].spr->sxscale = scale.x;
				GameFastEddy->collectables[i].spr->syscale = scale.y;
				CSprites_SetSpriteAnimation(GameFastEddy->collectables[i].spr, ((GameFastEddy->GameBase->level-1) % 5), ((GameFastEddy->GameBase->level-1) % 5), 0);
				CSprites_SetSpriteCollisionShape(GameFastEddy->collectables[i].spr, SHAPE_CIRCLE, tz.x - 66.0, tz.y - 66.0, 0, 0, 0);
				//Game->CSprites_SetSpriteCollisionShape(GameFastEddy->collectables[i].spr, SHAPE_BOX, tz.x - 66, tz.y - 66, 0, 0, 0);
				GameFastEddy->collectables[i].pos.y = (row) * GameFastEddy->rowspacingsize + GameFastEddy_rowfloorsizey / 2;
				GameFastEddy->collectables[i].pos.x = (float)(((GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) /7) +
					(rand() % (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft - ((GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) /6 ))));
				GameFastEddy->collectables[i].spr->x = GameFastEddy->collectables[i].pos.x;
				GameFastEddy->collectables[i].spr->y = GameFastEddy->collectables[i].pos.y;
				GameFastEddy->collectedcreated += 1;
			}
		}
	}
}

void CGameFastEddy_updatecollectables(CGameFastEddy* GameFastEddy)
{
	for(int i = 0; i < GameFastEddy_maxcollectables; i++)
	{
		if (GameFastEddy->collectables[i].alive)
		{
			if (GameFastEddy->collectables[i].state == GameFastEddy_collectablestatemoveleft)
			{
				GameFastEddy->collectables[i].pos.x -= GameFastEddy_collectablespeed;
				if (GameFastEddy->collectables[i].pos.x + GameFastEddy->collectables[i].tz.x / 2 < GameFastEddy->GameBase->screenleft)
					GameFastEddy->collectables[i].pos.x = (float)(GameFastEddy->GameBase->screenright + GameFastEddy->collectables[i].tz.x / 2.0);
				GameFastEddy->collectables[i].spr->x =  GameFastEddy->collectables[i].pos.x;
				GameFastEddy->collectables[i].spr->y =  GameFastEddy->collectables[i].pos.y;
			}

			if (GameFastEddy->collectables[i].state == GameFastEddy_collectablestatemoveright)
			{
				GameFastEddy->collectables[i].pos.x += GameFastEddy_collectablespeed;
				if(GameFastEddy->collectables[i].pos.x - GameFastEddy->collectables[i].tz.x / 2 > GameFastEddy->GameBase->screenright)
					GameFastEddy->collectables[i].pos.x = (float)(GameFastEddy->GameBase->screenleft - GameFastEddy->collectables[i].tz.x / 2.0);
				GameFastEddy->collectables[i].spr->x = GameFastEddy->collectables[i].pos.x;
				GameFastEddy->collectables[i].spr->y = GameFastEddy->collectables[i].pos.y;
			}

			if (CSprites_DetectSpriteCollision(GameFastEddy->collectables[i].spr, GameFastEddy->player.spr))
			{
				CAudio_PlaySound(GameFastEddy->SfxCollect, 0);
				int ignorerow = GameFastEddy->collectables[i].row;
				CGameFastEddy_destroycollectable(GameFastEddy, i);
				GameFastEddy->collecteditems += 1;
				CGame_AddToScore(GameFastEddy->collecteditems * 10);
				if(GameFastEddy->collecteditems >= 9)
					CGameFastEddy_enemyenablelevelend(GameFastEddy);
				CGameFastEddy_createcollectables(GameFastEddy,ignorerow);
			}
		}
	}
}

//enemies ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_destroyenemies(CGameFastEddy* GameFastEddy)
{
	for(int i = 0; i < GameFastEddy_maxenemies; i++)
	{
		if (GameFastEddy->enemies[i].alive)
		{
			CSprites_RemoveSprite(GameFastEddy->enemies[i].spr);
			GameFastEddy->enemies[i].alive = false;
		}
	}
}

void CGameFastEddy_createenemy(CGameFastEddy* GameFastEddy, int row, float x, int state, int group, int multiply)
{
	SDL_Point tz = {32, 32};
	for (int i = 0; i < GameFastEddy_maxenemies; i++)
	{
		if (!GameFastEddy->enemies[i].alive)
		{
			if(row == 0)
				GameFastEddy->rowzeroenemyindex = i;
			GameFastEddy->enemies[i].spr = CSprites_CreateSprite();
			GameFastEddy->enemies[i].alive = true;
			GameFastEddy->enemies[i].row = row;
			GameFastEddy->enemies[i].group = group;
			GameFastEddy->enemies[i].state = state;
			Vec2F scale = {(ceil(GameFastEddy->enemyheight) / tz.y * multiply), (ceil(GameFastEddy->enemyheight) / tz.y * multiply)};
			GameFastEddy->enemies[i].tz.x = (int)(tz.x * scale.x);
			GameFastEddy->enemies[i].tz.y = (int)(tz.y * scale.y);
			CSprites_SetSpriteImageTiles(GameFastEddy->enemies[i].spr, &GameFastEddy->spritesheetenemy, 3, 4);
			GameFastEddy->enemies[i].spr->sxscale = scale.x;
			GameFastEddy->enemies[i].spr->syscale = scale.y;
			if (GameFastEddy->enemies[i].state == GameFastEddy_enemystatemoveright)
				CSprites_SetSpriteAnimation(GameFastEddy->enemies[i].spr, 6, 8, 10);

			if (GameFastEddy->enemies[i].state == GameFastEddy_enemystateidle)
				CSprites_SetSpriteAnimation(GameFastEddy->enemies[i].spr, 0, 2, 10);

			if (GameFastEddy->enemies[i].state == GameFastEddy_enemystatemoveleft)
				CSprites_SetSpriteAnimation(GameFastEddy->enemies[i].spr, 3, 5, 10);

			if (GameFastEddy->enemies[i].state == GameFastEddy_enemystatewaitmove)
			{
				GameFastEddy->enemies[i].stateticks = 60 * 6;
				CSprites_SetSpriteAnimation(GameFastEddy->enemies[i].spr, 0, 2, 10);
			}

			CSprites_SetSpriteCollisionShape(GameFastEddy->enemies[i].spr, SHAPE_BOX, tz.x - 10.0, tz.y-10.0,0, 0, 0);
			GameFastEddy->enemies[i].pos.y = (row + 1) * GameFastEddy->rowspacingsize - GameFastEddy_rowfloorsizey / 2 - GameFastEddy->enemies[i].tz.y / 2;
			GameFastEddy->enemies[i].pos.x = x;
			GameFastEddy->enemies[i].spr->x = GameFastEddy->enemies[i].pos.x;
			GameFastEddy->enemies[i].spr->y = GameFastEddy->enemies[i].pos.y;
			break;
		}
	}
}

void CGameFastEddy_createenemies(CGameFastEddy* GameFastEddy, bool levelsucces)
{
	if (GameFastEddy->GameBase->level-1 < 5)
	{
		CGameFastEddy_createenemy(GameFastEddy,0, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 0, 2);
		if (levelsucces)
			CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 4.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
		else
			CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 10.0, GameFastEddy_enemystateidle, 1, 1);

		CGameFastEddy_createenemy(GameFastEddy,2, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 2, 1);
		if (levelsucces)
			CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 6.0 / 10.0, GameFastEddy_enemystatemoveright, 3, 1);
		else
			CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 6.0 / 10.0, GameFastEddy_enemystateidle, 3, 1);

		CGameFastEddy_createenemy(GameFastEddy,4, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 10.0, GameFastEddy_enemystatewaitmove, 4, 1);
	}
	else
	{
		if (GameFastEddy->GameBase->level-1 < 10)
		{
			CGameFastEddy_createenemy(GameFastEddy,0, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 0, 2);
			CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 4.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
			CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 5.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
			CGameFastEddy_createenemy(GameFastEddy,2, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 2, 1);
			CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 6.0 / 10.0, GameFastEddy_enemystatemoveleft, 3, 1);
			CGameFastEddy_createenemy(GameFastEddy,4, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 10.0, GameFastEddy_enemystatewaitmove, 4, 1);
		}
		else
		{
			if (GameFastEddy->GameBase->level-1 < 15)
			{
				CGameFastEddy_createenemy(GameFastEddy,0, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 0, 2);
				CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 4.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
				CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 5.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
				CGameFastEddy_createenemy(GameFastEddy,2, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 2, 1);
				CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 6.0 / 10.0, GameFastEddy_enemystatemoveleft, 3, 1);
				CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 7.0 / 10.0, GameFastEddy_enemystatemoveleft, 3, 1);
				CGameFastEddy_createenemy(GameFastEddy,4, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 10.0, GameFastEddy_enemystatewaitmove, 4, 1);
			}
			else
			{
				CGameFastEddy_createenemy(GameFastEddy,0, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 0, 2);
				CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 4.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
				CGameFastEddy_createenemy(GameFastEddy,1, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 5.0 / 10.0, GameFastEddy_enemystatemoveright, 1, 1);
				CGameFastEddy_createenemy(GameFastEddy,2, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2.0, GameFastEddy_enemystatemoveright, 2, 1);
				CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 1.0 / 10.0, GameFastEddy_enemystatemoveright, 3, 1);
				CGameFastEddy_createenemy(GameFastEddy,3, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) * 6.0 / 10.0, GameFastEddy_enemystatemoveright, 4, 1);
				CGameFastEddy_createenemy(GameFastEddy,4, (GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 10.0, GameFastEddy_enemystatewaitmove, 5, 1);
			}
		}
	}
}

void CGameFastEddy_updateenemies(CGameFastEddy* GameFastEddy)
{
	for (int i = 0; i < GameFastEddy_maxenemies; i++)
	{
		if (GameFastEddy->enemies[i].alive)
		{
			if (GameFastEddy->enemies[i].state == GameFastEddy_enemystatewaitmove)
			{
				if (GameFastEddy->enemies[i].stateticks > 0)
					GameFastEddy->enemies[i].stateticks -= 1;
				else
				{
					GameFastEddy->enemies[i].state = GameFastEddy_enemystatemoveright;
					CSprites_SetSpriteAnimation(GameFastEddy->enemies[i].spr, 6, 8, 10);
				}
			}

			if (GameFastEddy->enemies[i].state == GameFastEddy_enemystatemoveright)
			{
				GameFastEddy->enemies[i].pos.x += GameFastEddy_playerspeed;
				if (GameFastEddy->enemies[i].pos.x + GameFastEddy->enemies[i].tz.x / 2 + GameFastEddy_playerspeed >= GameFastEddy->GameBase->screenright)
				{
					GameFastEddy->NeedToMoveGroupLeft[GameFastEddy->NeedToMoveGroupLeftCount++] = i;
					for(int j = 0; j < GameFastEddy_maxenemies; j++)
					{
						if (GameFastEddy->enemies[j].alive)
						{
							if(GameFastEddy->enemies[i].group == GameFastEddy->enemies[j].group)
							{
								GameFastEddy->NeedToMoveGroupLeft[GameFastEddy->NeedToMoveGroupLeftCount++] = j;
							}
						}
					}
				}
			}

			if(GameFastEddy->enemies[i].state == GameFastEddy_enemystatemoveleft)
			{
				GameFastEddy->enemies[i].pos.x -= GameFastEddy_playerspeed;
				if ( GameFastEddy->enemies[i].pos.x - GameFastEddy->enemies[i].tz.x / 2 - GameFastEddy_playerspeed <= GameFastEddy->GameBase->screenleft)
				{
					GameFastEddy->NeedToMoveGroupRight[GameFastEddy->NeedToMoveGroupRightCount++] = i;
					for(int j = 0; j < GameFastEddy_maxenemies; j++)
					{
						if(GameFastEddy->enemies[j].alive)
						{
							if(GameFastEddy->enemies[i].group == GameFastEddy->enemies[j].group)
							{
								GameFastEddy->NeedToMoveGroupRight[GameFastEddy->NeedToMoveGroupRightCount++] = j;								
							}
						}
					}
				}
			}

			GameFastEddy->enemies[i].spr->x = GameFastEddy->enemies[i].pos.x;
			GameFastEddy->enemies[i].spr->y = GameFastEddy->enemies[i].pos.y;

			if (CSprites_DetectSpriteCollision(GameFastEddy->enemies[i].spr, GameFastEddy->player.spr))
			{
				if (((GameFastEddy->player.state != GameFastEddy_playerstateclimbup) &&
					(GameFastEddy->player.state != GameFastEddy_playerstateclimbdown) &&
					(GameFastEddy->player.state != GameFastEddy_playerstateunknown)) ||
					(GameFastEddy->enemies[i].row == 0))
				{
					if(!GameFastEddy->playerdeath && GameFastEddy_candie)
					{
						GameFastEddy->playerdeath = true;
						GameFastEddy->playeardeathtime = getCurrentTimeMilliseconds() + 500;
						CAudio_PlaySound(GameFastEddy->SfxDie, 0);
						if (!(GameMode == GMGame))
							CGame_AddToScore(-100);
					}
					break;
				}
			}
		}
	}

	//switch positions at the end to make sure all enemies had moved
	int index;
	for (int i=0; i < GameFastEddy->NeedToMoveGroupLeftCount; i++)
	{
		index = GameFastEddy->NeedToMoveGroupLeft[i];
		GameFastEddy->enemies[index].state = GameFastEddy_enemystatemoveleft;
		CSprites_SetSpriteAnimation(GameFastEddy->enemies[index].spr, 3, 5, 10);
	}

	for (int i=0; i < GameFastEddy->NeedToMoveGroupRightCount; i++)
	{
		index = GameFastEddy->NeedToMoveGroupRight[i];
		GameFastEddy->enemies[index].state = GameFastEddy_enemystatemoveright;
		CSprites_SetSpriteAnimation(GameFastEddy->enemies[index].spr, 6, 8, 10);
	}

	GameFastEddy->NeedToMoveGroupLeftCount = 0;
	GameFastEddy->NeedToMoveGroupRightCount = 0;

}

//player ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_destroyplayer(CGameFastEddy* GameFastEddy)
{
	if (GameFastEddy->player.alive)
	{
		CSprites_RemoveSprite(GameFastEddy->player.spr);
		GameFastEddy->player.alive = false;
	}
}

void CGameFastEddy_createplayer(CGameFastEddy* GameFastEddy)
{
	GameFastEddy->playerdeath = false;
	GameFastEddy->player.spr = CSprites_CreateSprite();
	GameFastEddy->player.alive = true;
	SDL_Point tz = {238/10, 342/10};
	Vec2F scale = {GameFastEddy->playerheight / tz.y, GameFastEddy->playerheight / tz.y};
	GameFastEddy->player.tz.x = (int)(tz.x * scale.x);
	GameFastEddy->player.tz.y = (int)(tz.y * scale.y);
	GameFastEddy->player.state = GameFastEddy_playerstateunknown;
	CSprites_SetSpriteDepth(GameFastEddy->player.spr, 5);
	CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayeridle, 1, 15);
	GameFastEddy->player.spr->sxscale = scale.x;
	GameFastEddy->player.spr->syscale = scale.y;
	CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 14, 10);
	CSprites_SetSpriteCollisionShape(GameFastEddy->player.spr, SHAPE_BOX, tz.x - 120.0/10, tz.y-30.0/10,0,0,0);
	GameFastEddy->player.pos.x = (float)(GameFastEddy->GameBase->screenright - GameFastEddy->GameBase->screenleft) / 2;
	GameFastEddy->player.pos.y = 5 * GameFastEddy->rowspacingsize - GameFastEddy_rowfloorsizey / 2 - GameFastEddy->player.tz.y / 2;
	GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
	GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
}

void CGameFastEddy_updateplayer(CGameFastEddy* GameFastEddy)
{
	bool jump = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;
	if (GameFastEddy->player.alive)
	{
		if ((GameFastEddy->player.state != GameFastEddy_playerstatejump) &&
			(GameFastEddy->player.state != GameFastEddy_playerstateleftjump) &&
			(GameFastEddy->player.state != GameFastEddy_playerstaterightjump) &&
			(GameFastEddy->player.state != GameFastEddy_playerstateclimbup) &&
			(GameFastEddy->player.state != GameFastEddy_playerstateclimbdown))
		{

			if (gamepad_button_a() == 1)
				jump = true;

			if (gamepad_up() > 0)
				up = true;

			if (gamepad_down() > 0)
				down = true;

			if (gamepad_left() > 0)
				left = true;

			if (gamepad_right() > 0)
				right = true;

			if (jump)
			{
				if (left)
				{
					if (GameFastEddy->player.state != GameFastEddy_playerstateleftjump)
					{
						CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerjump, 1, 6);
						CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 3, 3, 10);

						GameFastEddy->player.state = GameFastEddy_playerstateleftjump;
						GameFastEddy->player.floory = (int)(GameFastEddy->player.pos.y);
						GameFastEddy->player.jumpdown = false;
						GameFastEddy->player.force = GameFastEddy_playerjumpspeed;
					}
				}
				else
				{
					if (right)
					{
						if (GameFastEddy->player.state != GameFastEddy_playerstaterightjump)
						{
							CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerjump, 1, 6);
							CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 3, 3, 10);

							GameFastEddy->player.floory = (int)(GameFastEddy->player.pos.y);
							GameFastEddy->player.state = GameFastEddy_playerstaterightjump;
							GameFastEddy->player.jumpdown = false;
							GameFastEddy->player.force = GameFastEddy_playerjumpspeed;
						}
					}
					else
					{
						if(GameFastEddy->player.state != GameFastEddy_playerstatejump)
						{
							CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerjump, 1, 6);
							CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 3, 3, 10);
							GameFastEddy->player.floory = (int)(GameFastEddy->player.pos.y);
							GameFastEddy->player.state = GameFastEddy_playerstatejump;
							GameFastEddy->player.jumpdown = false;
							GameFastEddy->player.force = GameFastEddy_playerjumpspeed;
						}
					}
				}
			}
			else
			{
				if(up)
				{
					GameFastEddy->player.pos.y -= GameFastEddy->rowspacingsize/4;
					GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
					GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
					bool found = false;
					for (int i = 0; i < GameFastEddy_maxladders; i++)
					{
						if (CSprites_DetectSpriteCollision(GameFastEddy->player.spr, GameFastEddy->ladders[i].spr))
						{
							CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerclimb, 1, 15);
							CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 14, 20);

							GameFastEddy->player.pos.x = GameFastEddy->ladders[i].pos.x;
							GameFastEddy->player.state = GameFastEddy_playerstateclimbup;
							GameFastEddy->player.floory = (int)(GameFastEddy->player.pos.y +GameFastEddy->rowspacingsize/4);
							found = true;
							break;
						};
					};
					GameFastEddy->player.pos.y += GameFastEddy->rowspacingsize/4;
					GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
					GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
					if (!found)
					{
						if (GameFastEddy->player.state != GameFastEddy_playerstateidle)
						{
							CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayeridle, 1, 15);
							CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 14, 10);
							GameFastEddy->player.state = GameFastEddy_playerstateidle;
						}
					}
				}
				else
				{
					if (down)
					{
						GameFastEddy->player.pos.y += GameFastEddy->rowspacingsize - GameFastEddy->playerheight / 4;
						GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
						GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
						bool found = false;
						for (int i = 0; i < GameFastEddy_maxladders; i++)
						{
							if (CSprites_DetectSpriteCollision(GameFastEddy->player.spr, GameFastEddy->ladders[i].spr))
							{
								CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerclimb, 1, 15);
								CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 14, 0, 20);

								GameFastEddy->player.pos.x = GameFastEddy->ladders[i].pos.x;
								GameFastEddy->player.state = GameFastEddy_playerstateclimbdown;
								GameFastEddy->player.floory = (int)(GameFastEddy->player.pos.y - GameFastEddy->rowspacingsize + GameFastEddy->playerheight / 4);
								found = true;
								break;
							};
						};
						GameFastEddy->player.pos.y -= GameFastEddy->rowspacingsize - GameFastEddy->playerheight / 4;
						GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
						GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
						if (!found)
						{
							if (GameFastEddy->player.state != GameFastEddy_playerstateidle)
							{
								CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayeridle, 1, 15);
								CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 14, 10);
								GameFastEddy->player.state = GameFastEddy_playerstateidle;
							}
						}
					}
					else
					{
						if (left)
						{
							if (GameFastEddy->player.state != GameFastEddy_playerstateleft)
							{
								CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerrun, 1, 7);
								CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 6, 10);
								GameFastEddy->player.spr->sxscale = -(fabs(GameFastEddy->player.spr->sxscale));
								GameFastEddy->player.state = GameFastEddy_playerstateleft;
							}
						}
						else
						{
							if (right)
							{
								if (GameFastEddy->player.state != GameFastEddy_playerstateright)
								{
									CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayerrun, 1, 7);
									CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 6, 10);
									GameFastEddy->player.spr->sxscale = (fabs(GameFastEddy->player.spr->sxscale));
									GameFastEddy->player.state = GameFastEddy_playerstateright;
								}
							}
							else
							{
								if (GameFastEddy->player.state != GameFastEddy_playerstateidle)
								{
									CSprites_SetSpriteImageTiles(GameFastEddy->player.spr, &GameFastEddy->spritesheetplayeridle, 1, 15);
									CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 14, 10);
									GameFastEddy->player.state = GameFastEddy_playerstateidle;
								}
							}
						}
					}
				}
			}
		}

		if (GameFastEddy->player.state == GameFastEddy_playerstateclimbup)
		{
			if (GameFastEddy->player.pos.y > GameFastEddy->player.floory - GameFastEddy->rowspacingsize)
				GameFastEddy->player.pos.y -= GameFastEddy_playerclimbspeed;
			else
			{
				GameFastEddy->player.pos.y = GameFastEddy->player.floory - GameFastEddy->rowspacingsize;
				GameFastEddy->player.state = GameFastEddy_playerstateunknown;
			}

			GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
			GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
		}

		if (GameFastEddy->player.state == GameFastEddy_playerstateclimbdown)
		{
			if (GameFastEddy->player.pos.y < GameFastEddy->player.floory + GameFastEddy->rowspacingsize)
				GameFastEddy->player.pos.y += GameFastEddy_playerclimbspeed;
			else
			{
				GameFastEddy->player.pos.y = GameFastEddy->player.floory + GameFastEddy->rowspacingsize;
				GameFastEddy->player.state = GameFastEddy_playerstateunknown;
			}
			GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
			GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
		};

		if (GameFastEddy->player.state == GameFastEddy_playerstatejump)
		{
			if (!GameFastEddy->player.jumpdown)
			{
				if (GameFastEddy->player.pos.y > GameFastEddy->player.floory - GameFastEddy->playerjumpheight)
				{
					GameFastEddy->player.pos.y -= GameFastEddy->player.force;
					GameFastEddy->player.force -= GameFastEddy->playerjumpspeeddec;
				}
				else
					GameFastEddy->player.jumpdown = true;
			}
			else
			{
				if (GameFastEddy->player.pos.y < GameFastEddy->player.floory)
				{
					GameFastEddy->player.pos.y += GameFastEddy->player.force;
					GameFastEddy->player.force += GameFastEddy->playerjumpspeeddec;
				}
				else
				{
					GameFastEddy->player.pos.y = (float)(GameFastEddy->player.floory);
					GameFastEddy->player.state = GameFastEddy_playerstateunknown;
				}
			}
			GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
			GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
			if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 5/6 * GameFastEddy->playerjumpheight)
				CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 5, 5, 0);
			else
			{
				if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 4/6 * GameFastEddy->playerjumpheight)
					CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 4, 4, 0);
				else
				{
					if(GameFastEddy->player.pos.y < GameFastEddy->player.floory - 3/6 * GameFastEddy->playerjumpheight)
						CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 3, 3, 0);
					else
					{
						if(GameFastEddy->player.pos.y < GameFastEddy->player.floory - 2/6 * GameFastEddy->playerjumpheight)
							CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 2, 2, 0);
						else
						{
							if(GameFastEddy->player.pos.y < GameFastEddy->player.floory - 1/6 * GameFastEddy->playerjumpheight)
								CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 1, 1, 0);
							else
							{
								if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 0/6 * GameFastEddy->playerjumpheight)
									CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 0, 0);
							}
						}
					}
				}
			}
		}

		if ((GameFastEddy->player.state == GameFastEddy_playerstateleftjump) ||
			(GameFastEddy->player.state == GameFastEddy_playerstaterightjump))
		{
			if (! GameFastEddy->player.jumpdown)
			{
				if (GameFastEddy->player.pos.y > GameFastEddy->player.floory - GameFastEddy->playerjumpheight)
				{
					GameFastEddy->player.pos.y -= GameFastEddy->player.force;
					GameFastEddy->player.force -= GameFastEddy->playerjumpspeeddec;
				}
				else
					GameFastEddy->player.jumpdown = true;
			}
			else
			{
				if (GameFastEddy->player.pos.y < GameFastEddy->player.floory)
				{
					GameFastEddy->player.pos.y += GameFastEddy->player.force;
					GameFastEddy->player.force += GameFastEddy->playerjumpspeeddec;
				}
				else
				{
					GameFastEddy->player.pos.y = (float)(GameFastEddy->player.floory);
					GameFastEddy->player.state = GameFastEddy_playerstateunknown;
				}
			}

			if (GameFastEddy->player.spr->sxscale / fabs(GameFastEddy->player.spr->sxscale) == 1)
			{
				if ( GameFastEddy->player.pos.x + GameFastEddy->player.tz.x / 2 + GameFastEddy_playerspeed < GameFastEddy->GameBase->screenright)
					GameFastEddy->player.pos.x += GameFastEddy_playerspeed ;
				else
					GameFastEddy->player.pos.x = (float)(GameFastEddy->GameBase->screenright - GameFastEddy->player.tz.x / 2.0);
			}
			else
			{
				if ( GameFastEddy->player.pos.x - GameFastEddy->player.tz.x / 2 - GameFastEddy_playerspeed > GameFastEddy->GameBase->screenleft)
					GameFastEddy->player.pos.x -= GameFastEddy_playerspeed;
				else
					GameFastEddy->player.pos.x = (float)(GameFastEddy->GameBase->screenleft + GameFastEddy->player.tz.x / 2.0);
			}

			if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 5/6 * GameFastEddy->playerjumpheight)
				CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 5, 5, 0);
			else
			{
				if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 4/6 * GameFastEddy->playerjumpheight)
					CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 4, 4, 0);
				else
				{
					if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 3/6 * GameFastEddy->playerjumpheight)
						CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 3, 3, 0);
					else
					{
						if (GameFastEddy->player.pos.y < GameFastEddy->player.floory - 2/6 * GameFastEddy->playerjumpheight)
							CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 2, 2, 0);
						else
						{
							if(GameFastEddy->player.pos.y < GameFastEddy->player.floory - 1/6 * GameFastEddy->playerjumpheight)
								CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 1, 1, 0);
							else
							{
								if(GameFastEddy->player.pos.y < GameFastEddy->player.floory - 0/6 * GameFastEddy->playerjumpheight)
									CSprites_SetSpriteAnimation(GameFastEddy->player.spr, 0, 0, 0);
							}
						}
					}
				}
			}

			GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
			GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
		}

		if (GameFastEddy->player.state == GameFastEddy_playerstateright)
		{
			if ( GameFastEddy->player.pos.x + GameFastEddy->player.tz.x / 2 + GameFastEddy_playerspeed < GameFastEddy->GameBase->screenright)
				GameFastEddy->player.pos.x += GameFastEddy_playerspeed;
			else
				GameFastEddy->player.pos.x = (float)(GameFastEddy->GameBase->screenright - GameFastEddy->player.tz.x / 2.0);
			GameFastEddy->player.spr->x =  GameFastEddy->player.pos.x;
			GameFastEddy->player.spr->y =  GameFastEddy->player.pos.y;
		}

		if (GameFastEddy->player.state == GameFastEddy_playerstateleft)
		{
			if ( GameFastEddy->player.pos.x - GameFastEddy->player.tz.x / 2 - GameFastEddy_playerspeed > GameFastEddy->GameBase->screenleft)
				GameFastEddy->player.pos.x -= GameFastEddy_playerspeed;
			else
				GameFastEddy->player.pos.x = (float)(GameFastEddy->GameBase->screenleft + GameFastEddy->player.tz.x / 2.0);
			GameFastEddy->player.spr->x = GameFastEddy->player.pos.x;
			GameFastEddy->player.spr->y = GameFastEddy->player.pos.y;
		}
	}
}



//floors ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_destroyfloors(CGameFastEddy* GameFastEddy)
{
	for (int i = 0; i < GameFastEddy->maxfloortiles; i++)
		CSprites_RemoveSprite(GameFastEddy->floors[i].spr);
}

void CGameFastEddy_createfloors(CGameFastEddy* GameFastEddy)
{
	int tilenr = 0;
	int i = 0;
	SDL_Point* tz = CImage_ImageSize(GameFastEddy->spritesheet);
	tz->x = tz->x /9;
	tz->y = tz->y /10;
	for (int y = 0; y < GameFastEddy_rows; y++)
	{
		for (int x = 0; x < GameFastEddy->numfloortilesperrow; x++)
		{
			GameFastEddy->floors[i].spr = CSprites_CreateSprite();
			GameFastEddy->floors[i].alive = true;
			CSprites_SetSpriteImageTiles(GameFastEddy->floors[i].spr, &GameFastEddy->spritesheet, 9, 10);
			GameFastEddy->floors[i].spr->x = (float)x * GameFastEddy_rowfloorsizex + GameFastEddy_rowfloorsizex / 2;
			GameFastEddy->floors[i].spr->y = (float)(y + 1) * GameFastEddy->rowspacingsize - GameFastEddy_rowfloorsizey / 2;
			Vec2F scale = {(float)GameFastEddy_rowfloorsizex / tz->x , (float)GameFastEddy_rowfloorsizey / tz->y};
			GameFastEddy->floors[i].spr->sxscale =  scale.x;
			GameFastEddy->floors[i].spr->syscale =  scale.y;
			tilenr = 37;
			CSprites_SetSpriteAnimation(GameFastEddy->floors[i].spr, tilenr, tilenr, 0);
			i += 1;
		}
	}
	free(tz);
}

//ladders ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_destroyladders(CGameFastEddy* GameFastEddy)
{
	for (int i = 0; i < GameFastEddy_maxladders; i++)
		CSprites_RemoveSprite(GameFastEddy->ladders[i].spr);
}

void CGameFastEddy_createladders(CGameFastEddy* GameFastEddy)
{
	int i = 0;
	SDL_Point* tz = CImage_ImageSize(GameFastEddy->spritesheetladder);
	for (int y = 1; y < GameFastEddy_rows; y++)
	{
		int x1 = 1 + rand() % ((int)(GameFastEddy_laddersfitrows / 2)-1);
		GameFastEddy->ladders[i].spr = CSprites_CreateSprite();
		GameFastEddy->ladders[i].alive = true;
		GameFastEddy->ladders[i].pos.x = x1 * GameFastEddy->ladderwidth + GameFastEddy->ladderwidth / 2;
		GameFastEddy->ladders[i].pos.y = y * GameFastEddy->rowspacingsize + GameFastEddy->rowspacingsize / 2 - GameFastEddy_rowfloorsizey / 2;
		CSprites_SetSpriteImage(GameFastEddy->ladders[i].spr, &GameFastEddy->spritesheetladder);
		CSprites_SetSpriteCollisionShape(GameFastEddy->ladders[i].spr, SHAPE_BOX, tz->x - 20.0, tz->y-10.0,0,0,0);

		GameFastEddy->ladders[i].spr->x = GameFastEddy->ladders[i].pos.x;
		GameFastEddy->ladders[i].spr->y = GameFastEddy->ladders[i].pos.y;
		Vec2F scale = {GameFastEddy->ladderwidth / tz->x , (GameFastEddy->rowspacingsize + GameFastEddy_rowfloorsizey/2) / tz->y};
		GameFastEddy->ladders[i].spr->sxscale = scale.x;
		GameFastEddy->ladders[i].spr->syscale = scale.y;

		i += 1;
		int x2 = x1 + (int)(GameFastEddy_laddersfitrows / 2);
		GameFastEddy->ladders[i].spr = CSprites_CreateSprite();
		GameFastEddy->ladders[i].alive = true;		
		GameFastEddy->ladders[i].pos.x = x2 * GameFastEddy->ladderwidth + GameFastEddy->ladderwidth / 2;
		GameFastEddy->ladders[i].pos.y = y * GameFastEddy->rowspacingsize + GameFastEddy->rowspacingsize / 2 - GameFastEddy_rowfloorsizey / 2;
		CSprites_SetSpriteImage(GameFastEddy->ladders[i].spr, &GameFastEddy->spritesheetladder);
		CSprites_SetSpriteCollisionShape(GameFastEddy->ladders[i].spr, SHAPE_BOX, tz->x - 20.0, tz->y-10.0,0,0,0);
		GameFastEddy->ladders[i].spr->x = GameFastEddy->ladders[i].pos.x;
		GameFastEddy->ladders[i].spr->y = GameFastEddy->ladders[i].pos.y;
		GameFastEddy->ladders[i].spr->sxscale = scale.x;
		GameFastEddy->ladders[i].spr->syscale = scale.y;
		i += 1;
	}
	free(tz);
}

//end level key ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_createkey(CGameFastEddy* GameFastEddy)
{
	GameFastEddy->key.spr = CSprites_CreateSprite();
	GameFastEddy->key.alive = true;
	SDL_Point* tz = CImage_ImageSize(GameFastEddy->spritesheetkey);
	Vec2F scale = {GameFastEddy->keyheight / tz->y, GameFastEddy->keyheight / tz->y};
	GameFastEddy->key.tz.x = (int)(tz->x * scale.x);
	GameFastEddy->key.tz.y = (int)(tz->y * scale.y);
	CSprites_SetSpriteImageTiles(GameFastEddy->key.spr, &GameFastEddy->spritesheetkey, 1, 1);
	GameFastEddy->key.spr->sxscale = scale.x;
	GameFastEddy->key.spr->syscale = scale.y;
	CSprites_SetSpriteAnimation(GameFastEddy->key.spr, 0, 0, 0);
	CSprites_SetSpriteCollisionShape(GameFastEddy->key.spr, SHAPE_BOX, tz->x - 20.0, (float)tz->y, 0, 0, 0);
	GameFastEddy->key.pos.y = GameFastEddy->enemies[GameFastEddy->rowzeroenemyindex].pos.y - GameFastEddy->enemies[GameFastEddy->rowzeroenemyindex].tz.y;
	GameFastEddy->key.pos.x = GameFastEddy->enemies[GameFastEddy->rowzeroenemyindex].pos.x;
	GameFastEddy->key.spr->x = GameFastEddy->key.pos.x;
	GameFastEddy->key.spr->y = GameFastEddy->key.pos.y;
	free(tz);
}

void CGameFastEddy_destroykey(CGameFastEddy* GameFastEddy)
{
	if (GameFastEddy->key.alive)
	{
		CSprites_RemoveSprite(GameFastEddy->key.spr);
		GameFastEddy->key.alive = false;
	}
}

void CGameFastEddy_updatekey(CGameFastEddy* GameFastEddy)
{
	if (GameFastEddy->key.alive)
	{
		GameFastEddy->key.pos.x = GameFastEddy->enemies[GameFastEddy->rowzeroenemyindex].pos.x;
		GameFastEddy->key.pos.y = GameFastEddy->enemies[GameFastEddy->rowzeroenemyindex].pos.y - GameFastEddy->enemies[GameFastEddy->rowzeroenemyindex].tz.y;
		GameFastEddy->key.spr->x = GameFastEddy->key.pos.x;
		GameFastEddy->key.spr->y = GameFastEddy->key.pos.y;

		if (CSprites_DetectSpriteCollision(GameFastEddy->key.spr, GameFastEddy->player.spr))
		{
			CAudio_PlaySound(GameFastEddy->SfxSucces, 0);
			CGame_AddToScore(200);
			sleep(30);
			GameFastEddy->GameBase->level += 1;
			GameFastEddy->collecteditems = 0;
			GameFastEddy->collectedcreated = 0;
			CGameFastEddy_destroyenemies(GameFastEddy);
			CGameFastEddy_destroyplayer(GameFastEddy);
			CGameFastEddy_destroyallcollectables(GameFastEddy);
			CGameFastEddy_destroykey(GameFastEddy);
			CGameFastEddy_destroyladders(GameFastEddy);
			CGameFastEddy_createladders(GameFastEddy);
			CGameFastEddy_createplayer(GameFastEddy);
			CGameFastEddy_createenemies(GameFastEddy,true);
			CGameFastEddy_createcollectables(GameFastEddy,-1);
			CGameFastEddy_createkey(GameFastEddy);
		}
	}
}


//background ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_DrawBackground(CGameFastEddy* GameFastEddy)
{
	CImage_DrawImage(GameFastEddy->background, 0, NULL, NULL);
}

//init - deinit ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_LoadSound(CGameFastEddy* GameFastEddy)
{
	GameFastEddy->SfxDie = CAudio_LoadSound("common/die");
	GameFastEddy->SfxSucces = CAudio_LoadSound("common/succes");
	GameFastEddy->SfxCollect = CAudio_LoadSound("common/coin");
	GameFastEddy->MusMusic = CAudio_LoadMusic("fasterdave/music");
}

void CGameFastEddy_UnLoadSound(CGameFastEddy* GameFastEddy)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GameFastEddy->MusMusic);
	CAudio_UnLoadSound(GameFastEddy->SfxDie);
	CAudio_UnLoadSound(GameFastEddy->SfxSucces);
	CAudio_UnLoadSound(GameFastEddy->SfxCollect);
}

void CGameFastEddy_UnloadGraphics(CGameFastEddy* GameFastEddy)
{
	CImage_UnLoadImage(GameFastEddy->background);
	CImage_UnLoadImage(GameFastEddy->spritesheet);
	CImage_UnLoadImage(GameFastEddy->spritesheetladder);
	CImage_UnLoadImage(GameFastEddy->spritesheetplayerclimb);
	CImage_UnLoadImage(GameFastEddy->spritesheetplayerrun);
	CImage_UnLoadImage(GameFastEddy->spritesheetplayeridle);
	CImage_UnLoadImage(GameFastEddy->spritesheetplayerjump);
	CImage_UnLoadImage(GameFastEddy->spritesheetenemy);
	CImage_UnLoadImage(GameFastEddy->spritesheetcollectable);
	CImage_UnLoadImage(GameFastEddy->spritesheetkey);
}

void CGameFastEddy_LoadGraphics(CGameFastEddy* GameFastEddy)
{
	GameFastEddy->background = CImage_LoadImage("fasterdave/background.png");
	GameFastEddy->spritesheet = CImage_LoadImage("fasterdave/floortileset.png");
	GameFastEddy->spritesheetladder = CImage_LoadImage("fasterdave/ladder.png");
	GameFastEddy->spritesheetplayerclimb = CImage_LoadImage("fasterdave/Character_character_climb.png");
	GameFastEddy->spritesheetplayerrun = CImage_LoadImage("fasterdave/Character_character_run.png");
	GameFastEddy->spritesheetplayeridle = CImage_LoadImage("fasterdave/Character_character_idle.png");
	GameFastEddy->spritesheetplayerjump = CImage_LoadImage("fasterdave/Character_character_jump_up.png");
	GameFastEddy->spritesheetenemy = CImage_LoadImage("fasterdave/enemy.png");
	GameFastEddy->spritesheetcollectable = CImage_LoadImage("fasterdave/orbs.png");
	GameFastEddy->spritesheetkey = CImage_LoadImage("fasterdave/key.png");
}

void CGameFastEddy_init(CGameFastEddy* GameFastEddy)
{
	GameFastEddy->collecteditems = 0;
	GameFastEddy->collectedcreated = 0;
	GameFastEddy->GameBase->level = 1;
	GameFastEddy->GameBase->HealthPoints = 3;
	CGameFastEddy_LoadGraphics(GameFastEddy);
	CGameFastEddy_createfloors(GameFastEddy);
	CGameFastEddy_createladders(GameFastEddy);
	CGameFastEddy_createenemies(GameFastEddy,false);
	CGameFastEddy_createcollectables(GameFastEddy,-1);
	CGameFastEddy_createkey(GameFastEddy);
	CGameFastEddy_createplayer(GameFastEddy);
	CGameFastEddy_LoadSound(GameFastEddy);
	CurrentGameMusicID = GameFastEddy->MusMusic;
	CAudio_PlayMusic(GameFastEddy->MusMusic, -1);
}

void CGameFastEddy_deinit(CGameFastEddy* GameFastEddy)
{
	CGameFastEddy_destroyfloors(GameFastEddy);
	CGameFastEddy_destroyladders(GameFastEddy);
	CGameFastEddy_destroyenemies(GameFastEddy);
	CGameFastEddy_destroyallcollectables(GameFastEddy);
	CGameFastEddy_destroykey(GameFastEddy);
	CGameFastEddy_destroyplayer(GameFastEddy);
	CGameFastEddy_UnLoadSound(GameFastEddy);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
	CGameFastEddy_UnloadGraphics(GameFastEddy);
}



//Update ----------------------------------------------------------------------------------------------------------------

void CGameFastEddy_UpdateObjects(CGameFastEddy* GameFastEddy, bool IsGameState)
{
	if (IsGameState)
	{
		CGameFastEddy_updateplayer(GameFastEddy);
		CGameFastEddy_updateenemies(GameFastEddy);
		CGameFastEddy_updatecollectables(GameFastEddy);
		CGameFastEddy_updatekey(GameFastEddy);
	}
}

void CGameFastEddy_UpdateLogic(CGameFastEddy* GameFastEddy)
{
	CGameBase_UpdateLogic(GameFastEddy->GameBase);

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	if (!GameFastEddy->playerdeath)
	{
		CGameFastEddy_UpdateObjects(GameFastEddy, SubGameState == SGGame);
		if (SubGameState == SGGame)
			CSprites_UpdateSprites();
	}
	else
	{
		if (GameFastEddy->GameBase->HealthPoints > 1)
		{
			if (GameFastEddy->playeardeathtime < getCurrentTimeMilliseconds())
			{
				
				if (GameMode == GMGame)
					GameFastEddy->GameBase->HealthPoints -= 1;
			
				CGameFastEddy_destroyenemies(GameFastEddy);
				CGameFastEddy_destroyplayer(GameFastEddy);
				CGameFastEddy_destroykey(GameFastEddy);
				CGameFastEddy_createplayer(GameFastEddy);
				CGameFastEddy_createenemies(GameFastEddy, false);
				CGameFastEddy_createkey(GameFastEddy);
				if (GameFastEddy->collecteditems >= 9)
					CGameFastEddy_enemyenablelevelend(GameFastEddy);
				SubGameState = SGReadyGo;
				SubStateTime = getCurrentTimeMilliseconds() + 500;
			}
		}
		else
			if (GameMode == GMGame)
				if (GameFastEddy->GameBase->HealthPoints > 0)
					GameFastEddy->GameBase->HealthPoints -= 1;

	}


}

void CGameFastEddy_Draw(CGameFastEddy* GameFastEddy)
{
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameFastEddy_DrawBackground(GameFastEddy);
	CSprites_DrawSprites();
	CGameBase_DrawScoreBar(GameFastEddy->GameBase);
	CGameBase_DrawSubstateText(GameFastEddy->GameBase);
}
#endif