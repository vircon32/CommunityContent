#ifndef CGAMEINVADERS_H
#define CGAMEINVADERS_H

#include "math.h"
#include "CGameBase.h"
#include "CSpriteObject.h"
#include "../Common.h"
#include "../CTween.h"
#include "../Vec2F.h"
#include "../CGame.h"
#include "../SDL_HelperTypes.h"

#define CGameInvaders_candie 1
#define CGameInvaders_tweenenemypositions 0
#define CGameInvaders_tweenenemydeath 1

#define CGameInvaders_enemyrows 5
#define CGameInvaders_enemycols 7
#define CGameInvaders_enemystartxoffset (50*xscale)
#define CGameInvaders_enemystartyoffset (ScoreBarHeight + (50*yscale))
#define CGameInvaders_enemyspacing (60*yscale)
#define CGameInvaders_enemyhorzspacing (50*xscale)

#define CGameInvaders_enemyspeed (1.0*xscale)
#define CGameInvaders_enemyspeedinc (0.15*xscale)
#define CGameInvaders_playerspeed (8.0*xscale)
#define CGameInvaders_bulletspeed (10.0*yscale)
#define CGameInvaders_asteroidsoffset (150*xscale)
#define CGameInvaders_endscreenconstant ((45*xscale) + 150*xscale)
#define CGameInvaders_maxexplosion 10
#define CGameInvaders_maxasteroids 6
#define CGameInvaders_asteroidscale (2.5*xscale)
#define CGameInvaders_asteroidmaxhealthpoints 50
#define CGameInvaders_maxenemybullets 5
#define CGameInvaders_enemybulletrandomizer 100

#define CGameInvaders_maxenemies 35 //rows * cols

struct senemyinfo
{
	int mostleft;
	int mostright;
	int mostbottom;
};

struct CGameInvaders {

	CGameBase *GameBase;
	
	int deaths;
	int pattern;
	float backgroundfade;
	float backgroundfadeinc;
	Vec2F enemyvel;
	Vec2F enemyscale;
	
	senemyinfo enemyinfo;
	CSpriteObject player;
	CSpriteObject bullet;
	CSpriteObject[CGameInvaders_maxenemies] enemies;
	CSpriteObject[CGameInvaders_maxexplosion] explosions;
	CSpriteObject[CGameInvaders_maxasteroids] asteroids;
	CSpriteObject[CGameInvaders_maxenemybullets] enemybullets;

	CTweenInfo*[CGameInvaders_maxenemies][2] tweens;

	int background;

	int spritesheetBullet;
	int spritesheetExplosion;
	int spritesheetAsteroid;
	int spritesheetEnemy1;
	int spritesheetEnemy2;
	int spritesheetEnemy3;
	int spritesheetPlayer;

	int MusMusic, SfxPlayerShoot, SfxPlayerDeath, SfxEnemyShoot, SfxEnemyDeath, SfxSucces, SfxDie;
};

CGameInvaders* Create_CGameInvaders()
{
	CSprites_SetSpriteMax(CGameInvaders_maxenemies + CGameInvaders_maxexplosion + CGameInvaders_maxasteroids + CGameInvaders_maxenemybullets ); //2 = bullet & player
	CGameInvaders* GameInvaders = (CGameInvaders*) malloc(sizeof(CGameInvaders));
	GameInvaders->GameBase = Create_CGameBase(GSSpaceInvaders, false);

	GameInvaders->MusMusic = -1;
	GameInvaders->SfxSucces = -1;
	GameInvaders->SfxPlayerShoot = -1;
	GameInvaders->SfxPlayerDeath = -1;
	GameInvaders->SfxEnemyShoot = -1;
	GameInvaders->SfxEnemyDeath = -1;
	GameInvaders->SfxDie = -1;
	GameInvaders->GameBase->screenleft = 0;
	GameInvaders->GameBase->screenright = ScreenWidth;
	GameInvaders->GameBase->screentop = ScoreBarHeight;
	GameInvaders->GameBase->screenbottom = ScreenHeight;

	GameInvaders->enemyvel.x = CGameInvaders_enemyspeed;
	GameInvaders->enemyvel.y = 0;
	GameInvaders->enemyscale.x = 1.5*xscale;
	GameInvaders->enemyscale.y = 1.5*yscale;

	GameInvaders->deaths = 0;
	GameInvaders->pattern = 0;
	GameInvaders->backgroundfade = 0.0;
	GameInvaders->backgroundfadeinc = 0.0;
	

	Initialize_CSpriteObject(&GameInvaders->player);
	Initialize_CSpriteObject(&GameInvaders->bullet);

	for (int i = 0; i < CGameInvaders_maxenemies; i++)
	{
		Initialize_CSpriteObject(&GameInvaders->enemies[i]);
		
		GameInvaders->tweens[i][0] = (CTweenInfo*) malloc(sizeof(CTweenInfo));
		GameInvaders->tweens[i][1] = (CTweenInfo*) malloc(sizeof(CTweenInfo));
		initialize_CTweenInfo(GameInvaders->tweens[i][0]);
		initialize_CTweenInfo(GameInvaders->tweens[i][1]);
	}

	for (int i = 0; i < CGameInvaders_maxexplosion; i++)
		Initialize_CSpriteObject(&GameInvaders->explosions[i]);

	for (int i = 0; i < CGameInvaders_maxasteroids; i++)
		Initialize_CSpriteObject(&GameInvaders->asteroids[i]);

	for (int i = 0; i < CGameInvaders_maxenemybullets; i++)
		Initialize_CSpriteObject(&GameInvaders->enemybullets[i]);

	return GameInvaders;
}

void Destroy_CGameInvaders(CGameInvaders* GameInvaders)
{
	for (int i = 0; i < CGameInvaders_maxenemies; i++)
	{	
		free(GameInvaders->tweens[i][0]);
		free(GameInvaders->tweens[i][1]);
	}
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GameInvaders->GameBase);
	free(GameInvaders);
	GameInvaders = NULL;
}

bool CGameInvaders_tweenactive(CGameInvaders* GameInvaders, int id)
{
	bool result = false;
	for(int i = 0; i < CGameInvaders_maxenemies; i++)
	{
		if (GameInvaders->enemies[i].alive && GameInvaders->tweens[i][id]->active)
		{
			result = true;
			break;
		}
	}
	return result;
}

void CGameInvaders_destroyallinvaders(CGameInvaders* GameInvaders)
{
	for(int i = 0; i < CGameInvaders_maxenemies; i++)
	{
		if (GameInvaders->enemies[i].alive)
		{
			GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->active = false;
			CSprites_RemoveSprite(GameInvaders->enemies[i].spr);
		}
	}
}

void CGameInvaders_destroyinvader(CGameInvaders* GameInvaders, int index)
{
	GameInvaders->enemies[index].alive = false;
	CSprites_RemoveSprite(GameInvaders->enemies[index].spr);
}


//explosions ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_destroyexploison(CGameInvaders* GameInvaders, int index)
{
	if (GameInvaders->explosions[index].alive)
	{
		CSprites_RemoveSprite(GameInvaders->explosions[index].spr);
		GameInvaders->explosions[index].alive = false;
	}
}

void CGameInvaders_checkexplosions(CGameInvaders* GameInvaders)
{
	for(int i = 0; i < CGameInvaders_maxexplosion; i++)
	{
		if (GameInvaders->explosions[i].alive)
		{
			if (CSprites_GetSpriteAnimFrame(GameInvaders->explosions[i].spr) == CSprites_GetSpriteAnimFrameCount(GameInvaders->explosions[i].spr) -1)
			{
				CGameInvaders_destroyexploison(GameInvaders,i);
			}
		}
	}
}

void CGameInvaders_destroyallexplosion(CGameInvaders* GameInvaders)
{
	for (int i = 0; i < CGameInvaders_maxexplosion; i++)
		CGameInvaders_destroyexploison(GameInvaders,i);
}


void CGameInvaders_createexplosion(CGameInvaders* GameInvaders, Vec2F* pos)
{
	for(int i = 0; i < CGameInvaders_maxexplosion;i++)
	{
		if (!GameInvaders->explosions[i].alive)
		{
			GameInvaders->explosions[i].spr = CSprites_CreateSprite();
			CSprites_SetSpriteImageTiles(GameInvaders->explosions[i].spr, &GameInvaders->spritesheetExplosion, 7, 1);
			GameInvaders->explosions[i].spr->sxscale = GameInvaders->enemyscale.x;
			GameInvaders->explosions[i].spr->syscale = GameInvaders->enemyscale.y;
			CSprites_SetSpriteDepth(GameInvaders->explosions[i].spr, 1);
			CSprites_SetSpriteAnimation(GameInvaders->explosions[i].spr,2, 6, 15);
			GameInvaders->explosions[i].spr->x = pos->x;
			GameInvaders->explosions[i].spr->y = pos->y;
			GameInvaders->explosions[i].alive = true;
			CAudio_PlaySound(GameInvaders->SfxPlayerDeath, 0);
			break;
		}
	}
}

//asteroids ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_destroyasteroid(CGameInvaders* GameInvaders, int index)
{
	if (GameInvaders->asteroids[index].alive)
	{
		CSprites_RemoveSprite(GameInvaders->asteroids[index].spr);
		GameInvaders->asteroids[index].alive = false;
	}
}

void CGameInvaders_destroyallasteroids(CGameInvaders* GameInvaders)
{
	for(int i = 0; i < CGameInvaders_maxasteroids; i++)
		CGameInvaders_destroyasteroid(GameInvaders,i);
}


void CGameInvaders_createasteroids(CGameInvaders* GameInvaders)
{
	for(int i = 0; i < CGameInvaders_maxasteroids; i++)
	{
		GameInvaders->asteroids[i].spr = CSprites_CreateSprite();
		GameInvaders->asteroids[i].healthpoints = CGameInvaders_asteroidmaxhealthpoints;
		GameInvaders->asteroids[i].alive = true;
		CSprites_SetSpriteImage(GameInvaders->asteroids[i].spr, &GameInvaders->spritesheetAsteroid);
		CSprites_SetSpriteAnimation(GameInvaders->asteroids[i].spr, 0, 0, 0);
		GameInvaders->asteroids[i].spr->x = (float)i * (GameInvaders->GameBase->screenright - GameInvaders->GameBase->screenleft) / (CGameInvaders_maxasteroids-1);
		GameInvaders->asteroids[i].spr->y = (float)GameInvaders->GameBase->screenbottom - CGameInvaders_asteroidsoffset;
		GameInvaders->asteroids[i].spr->sxscale = CGameInvaders_asteroidscale;
		GameInvaders->asteroids[i].spr->syscale = CGameInvaders_asteroidscale;
		CSprites_SetSpriteCollisionShape(GameInvaders->asteroids[i].spr, SHAPE_BOX, 45,45,0, 0 , 2);
		CSprites_SetSpriteRotation(GameInvaders->asteroids[i].spr, (float)(rand() % (360)));
	}
}

void CGameInvaders_updateasteroids(CGameInvaders* GameInvaders)
{
	for(int i = 0; i < CGameInvaders_maxasteroids;i++)
	{
		if (GameInvaders->asteroids[i].alive)
		{
			GameInvaders->asteroids[i].spr->sxscale = CGameInvaders_asteroidscale - ((CGameInvaders_asteroidscale / CGameInvaders_asteroidmaxhealthpoints) * (CGameInvaders_asteroidmaxhealthpoints - GameInvaders->asteroids[i].healthpoints));
			GameInvaders->asteroids[i].spr->syscale = CGameInvaders_asteroidscale - ((CGameInvaders_asteroidscale / CGameInvaders_asteroidmaxhealthpoints) * (CGameInvaders_asteroidmaxhealthpoints - GameInvaders->asteroids[i].healthpoints));
			CSprites_SetSpriteRotation(GameInvaders->asteroids[i].spr, GameInvaders->asteroids[i].spr->rotation + 0.5);
		}
	}
}


//enemy bullets ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_destroyenemybullet(CGameInvaders* GameInvaders, int index)
{
	if (GameInvaders->enemybullets[index].alive)
	{
		CSprites_RemoveSprite(GameInvaders->enemybullets[index].spr);
		GameInvaders->enemybullets[index].alive = false;
	}
}

void CGameInvaders_destroyallenemybullet(CGameInvaders* GameInvaders)
{
	for(int i = 0; i < CGameInvaders_maxenemybullets; i++)
		CGameInvaders_destroyenemybullet(GameInvaders,i);
}

void CGameInvaders_createnemybullet(CGameInvaders* GameInvaders, Vec2F* pos)
{
	for(int i = 0; i < CGameInvaders_maxenemybullets; i++)
	{
		if (!GameInvaders->enemybullets[i].alive)
		{
			GameInvaders->enemybullets[i].spr = CSprites_CreateSprite();
			CSprites_SetSpriteImageTiles(GameInvaders->enemybullets[i].spr, &GameInvaders->spritesheetBullet, 2, 1);
			CSprites_SetSpriteColour(GameInvaders->enemybullets[i].spr, 0.75,0.65,0.65,1);
			CSprites_SetSpriteAnimation(GameInvaders->enemybullets[i].spr, 1, 1, 0);
			GameInvaders->enemybullets[i].spr->sxscale = GameInvaders->enemyscale.x;
			GameInvaders->enemybullets[i].spr->syscale = GameInvaders->enemyscale.y;
			CSprites_SetSpriteDepth(GameInvaders->enemybullets[i].spr, -1);
			SDL_Point* tmpTz = CSprites_TileSize(GameInvaders->enemybullets[i].spr);
			GameInvaders->enemybullets[i].tz = *tmpTz;
			GameInvaders->enemybullets[i].tz.x = (int)(GameInvaders->enemybullets[i].tz.x * GameInvaders->enemyscale.x);
			GameInvaders->enemybullets[i].tz.y = (int)(GameInvaders->enemybullets[i].tz.y * GameInvaders->enemyscale.y);
			GameInvaders->enemybullets[i].pos = *pos;
			GameInvaders->enemybullets[i].vel.x = 0;
			GameInvaders->enemybullets[i].vel.y = CGameInvaders_bulletspeed;
			GameInvaders->enemybullets[i].alive = true;
			CAudio_PlaySound(GameInvaders->SfxEnemyShoot, 0);
			free(tmpTz);
			break;
		}
	}
}

void CGameInvaders_updateenemybullet(CGameInvaders* GameInvaders)
{
	if (!CGameInvaders_tweenactive(GameInvaders,CGameInvaders_tweenenemypositions))
	{
		if (rand() % (CGameInvaders_enemybulletrandomizer) == 0)
		{
			int col = rand() % (CGameInvaders_enemycols);
			int y = 0;
			bool fired = false;
			while (!fired)
			{
				y = CGameInvaders_enemyrows -1;
				while (y >= 0)
				{
					if (GameInvaders->enemies[col + y * CGameInvaders_enemycols].alive)
					{
						CGameInvaders_createnemybullet(GameInvaders,&GameInvaders->enemies[col + y * CGameInvaders_enemycols].pos);
						fired = true;
						break;
					}
					y -= 1;
				}
				col += 1;
				if (col >= CGameInvaders_enemycols)
					col = 0;
			}
		}
	}

	for(int i = 0; i < CGameInvaders_maxenemybullets; i++)
	{
		if (GameInvaders->enemybullets[i].alive)
		{
			GameInvaders->enemybullets[i].pos.x += GameInvaders->enemybullets[i].vel.x;
			GameInvaders->enemybullets[i].pos.y += GameInvaders->enemybullets[i].vel.y;
			GameInvaders->enemybullets[i].spr->x = GameInvaders->enemybullets[i].pos.x;
			GameInvaders->enemybullets[i].spr->y = GameInvaders->enemybullets[i].pos.y;
			if (GameInvaders->enemybullets[i].pos.y >= GameInvaders->GameBase->screenbottom)
				CGameInvaders_destroyenemybullet(GameInvaders,i);

			if (GameInvaders->enemybullets[i].alive && GameInvaders->player.alive)
			{
				if (CSprites_DetectSpriteCollision(GameInvaders->enemybullets[i].spr, GameInvaders->player.spr) && CGameInvaders_candie)
				{
					GameInvaders->player.alive = false;
					GameInvaders->player.freeze = 30;
					CGameInvaders_createexplosion(GameInvaders,&GameInvaders->player.pos);
					CGameInvaders_destroyenemybullet(GameInvaders,i);
					if (!(GameMode == GMGame))
						CGame_AddToScore(-150);
					GameInvaders->deaths += 1;
					GameInvaders->GameBase->HealthPoints -= 1;
					CAudio_PlaySound(GameInvaders->SfxDie, 0);
				}
			}


			for (int j = 0; j < CGameInvaders_maxasteroids; j++)
			{
				if (GameInvaders->enemybullets[i].alive && GameInvaders->asteroids[j].alive)
				{
					if (CSprites_DetectSpriteCollision(GameInvaders->enemybullets[i].spr, GameInvaders->asteroids[j].spr))
					{
						CGameInvaders_createexplosion(GameInvaders,&GameInvaders->enemybullets[i].pos);
						CGameInvaders_destroyenemybullet(GameInvaders,i);
						GameInvaders->asteroids[j].healthpoints -= 1;
						if (GameInvaders->asteroids[j].healthpoints == 0)
							CGameInvaders_destroyasteroid(GameInvaders,j);
					}
				}
			}

		}
	}
}


//player bullet ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_createbullet(CGameInvaders* GameInvaders)
{
	if (!GameInvaders->bullet.alive)
	{
		GameInvaders->bullet.spr = CSprites_CreateSprite();
		CSprites_SetSpriteImageTiles(GameInvaders->bullet.spr, &GameInvaders->spritesheetBullet, 2, 1);
		CSprites_SetSpriteAnimation(GameInvaders->bullet.spr, 1, 1, 0);
		GameInvaders->bullet.spr->sxscale = GameInvaders->enemyscale.x;
		GameInvaders->bullet.spr->syscale = GameInvaders->enemyscale.y;
		CSprites_SetSpriteDepth(GameInvaders->bullet.spr, -1);
		SDL_Point* tmpTz = CSprites_TileSize(GameInvaders->bullet.spr);
		GameInvaders->bullet.tz = *tmpTz;
		GameInvaders->bullet.tz.x = (int)(GameInvaders->bullet.tz.x * GameInvaders->enemyscale.x);
		GameInvaders->bullet.tz.y = (int)(GameInvaders->bullet.tz.y * GameInvaders->enemyscale.y);
		GameInvaders->bullet.pos = GameInvaders->player.pos ;
		GameInvaders->bullet.vel.x = 0;
		GameInvaders->bullet.vel.y = -CGameInvaders_bulletspeed;
		GameInvaders->bullet.alive = true;
		free(tmpTz);
		CAudio_PlaySound(GameInvaders->SfxPlayerShoot, 0);
	}
}

void CGameInvaders_destroybullet(CGameInvaders* GameInvaders)
{
	if (GameInvaders->bullet.alive)
	{
		CSprites_RemoveSprite(GameInvaders->bullet.spr);
		GameInvaders->bullet.alive = false;
	}
}

void CGameInvaders_updatebullet(CGameInvaders* GameInvaders)
{
	if (GameInvaders->bullet.alive)
	{
		GameInvaders->bullet.pos.x += GameInvaders->bullet.vel.x;
		GameInvaders->bullet.pos.y += GameInvaders->bullet.vel.y;
		GameInvaders->bullet.spr->x = GameInvaders->bullet.pos.x;
		GameInvaders->bullet.spr->y = GameInvaders->bullet.pos.y;

		for (int x = 0; x < CGameInvaders_enemycols; x++)
		{
			for(int y = 0; y < CGameInvaders_enemyrows; y++)
			{
				if (GameInvaders->bullet.alive && GameInvaders->enemies[y * CGameInvaders_enemycols + x].alive)
				{
					if (CSprites_DetectSpriteCollision(GameInvaders->bullet.spr, GameInvaders->enemies[y * CGameInvaders_enemycols + x].spr))
					{
						CGameInvaders_createexplosion(GameInvaders,&GameInvaders->enemies[y * CGameInvaders_enemycols + x].pos);
						CGameInvaders_destroybullet(GameInvaders);
						CGameInvaders_destroyinvader(GameInvaders,y * CGameInvaders_enemycols + x);
						if (y < 1)
							CGame_AddToScore(25);
						else
						{
							if (y < 3)
								CGame_AddToScore(20);
							else
								CGame_AddToScore(10);
						}
						GameInvaders->enemyvel.x += GameInvaders->enemyvel.x / fabs(GameInvaders->enemyvel.x) * CGameInvaders_enemyspeedinc;
					}
				}
			}
		}

		for(int i = 0; i < CGameInvaders_maxasteroids; i++)
		{
			if (GameInvaders->bullet.alive && GameInvaders->asteroids[i].alive)
			{
				if (CSprites_DetectSpriteCollision(GameInvaders->bullet.spr, GameInvaders->asteroids[i].spr))
				{
					CGameInvaders_createexplosion(GameInvaders,&GameInvaders->bullet.pos);
					CGameInvaders_destroybullet(GameInvaders);
					GameInvaders->asteroids[i].healthpoints -= 1;
					if (GameInvaders->asteroids[i].healthpoints == 0)
						CGameInvaders_destroyasteroid(GameInvaders,i);
				}
			}
		}

		if (GameInvaders->bullet.pos.y < GameInvaders->GameBase->screentop)
			CGameInvaders_destroybullet(GameInvaders);
	}
}

//enemies ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_updateenemyinfo(CGameInvaders* GameInvaders)
{
	GameInvaders->enemyinfo.mostleft = -1;
	GameInvaders->enemyinfo.mostright = -1;
	GameInvaders->enemyinfo.mostbottom = -1;

	float x1 = (float)GameInvaders->GameBase->screenright + 1;
	float x2 = (float)GameInvaders->GameBase->screenleft - 1;
	float y = (float)GameInvaders->GameBase->screentop - 1;
	for(int i = 0; i < CGameInvaders_maxenemies; i++)
	{
		if (GameInvaders->enemies[i].alive)
		{
			if (GameInvaders->enemies[i].pos.x < x1)
			{
				x1 = GameInvaders->enemies[i].pos.x;
				GameInvaders->enemyinfo.mostleft = i;
			}
			if (GameInvaders->enemies[i].pos.x > x2)
			{
				x2 = GameInvaders->enemies[i].pos.x;
				GameInvaders->enemyinfo.mostright = i;
			}
			if (GameInvaders->enemies[i].pos.y > y)
			{
				y = GameInvaders->enemies[i].pos.y;
				GameInvaders->enemyinfo.mostbottom = i;
			}
		}
	}
}

void CGameInvaders_createinvaders(CGameInvaders* GameInvaders, bool setposition)
{
	GameInvaders->pattern = rand() % (5);
	for (int x = 0; x < CGameInvaders_enemycols; x++)
	{
		for (int y = 0; y < CGameInvaders_enemyrows; y++)
		{
			setTweenInfo(GameInvaders->tweens[x + y * CGameInvaders_enemycols][CGameInvaders_tweenenemypositions], CGameInvaders_tweenenemypositions, 1.0+ (rand() % 60 )/100.0, funcsmoothstop, 1, true, 60);
			GameInvaders->enemies[x + y * CGameInvaders_enemycols].alive = true;
			GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr = CSprites_CreateSprite();
			GameInvaders->enemies[x + y * CGameInvaders_enemycols].pos.x = (float) x * (CGameInvaders_enemyspacing + CGameInvaders_enemyhorzspacing) + CGameInvaders_enemystartxoffset;
			GameInvaders->enemies[x + y * CGameInvaders_enemycols].pos.y = (float) y * CGameInvaders_enemyspacing + CGameInvaders_enemystartyoffset;
			if (setposition)
			{
				GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->x = GameInvaders->enemies[x + y * CGameInvaders_enemycols].pos.x;
				GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->y = GameInvaders->enemies[x + y * CGameInvaders_enemycols].pos.y;
			}
			SDL_Point* tz;
			if (y < 1)
			{
				CSprites_SetSpriteImageTiles(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, &GameInvaders->spritesheetEnemy3, 4, 1);
				GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->sxscale =  GameInvaders->enemyscale.x;
				GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->syscale =  GameInvaders->enemyscale.y;
				CSprites_SetSpriteAnimation(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, 0, 3, 5);
				tz = CSprites_TileSize(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr);
				CSprites_SetSpriteCollisionShape(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, SHAPE_BOX, tz->x-8.0, tz->y - 26.0,0, 0 , 6);
			}
			else
			{
				if (y < 3 )
				{
					CSprites_SetSpriteImageTiles(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, &GameInvaders->spritesheetEnemy2, 4, 1);
					GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->sxscale = GameInvaders->enemyscale.x;
					GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->syscale = GameInvaders->enemyscale.y;

					CSprites_SetSpriteAnimation(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, 0, 3, 5);
					tz = CSprites_TileSize(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr);
					CSprites_SetSpriteCollisionShape(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, SHAPE_BOX, tz->x-15.0, tz->y - 18.0,0, 0 , -2);
				}
				else
				{
					CSprites_SetSpriteImageTiles(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, &GameInvaders->spritesheetEnemy1, 5, 1);
					GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->sxscale = GameInvaders->enemyscale.x;
					GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr->syscale = GameInvaders->enemyscale.y;

					CSprites_SetSpriteAnimation(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr,0, 4, 5);
					tz = CSprites_TileSize(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr);
					CSprites_SetSpriteCollisionShape(GameInvaders->enemies[x + y * CGameInvaders_enemycols].spr, SHAPE_BOX, tz->x-17.0, tz->y - 12.0,0, 0 , -2);
				}
			}
			GameInvaders->enemies[x + y * CGameInvaders_enemycols].tz.x = (int)(tz->x * GameInvaders->enemyscale.x);
			GameInvaders->enemies[x + y * CGameInvaders_enemycols].tz.y = (int)(tz->y * GameInvaders->enemyscale.y);
			free(tz);
		}
	}
}

void CGameInvaders_updateinvaders(CGameInvaders* GameInvaders)
{
	CGameInvaders_updateenemyinfo(GameInvaders);

	//all enemies cleared
	if (GameInvaders->enemyinfo.mostleft == -1)
	{
		CGame_AddToScore(250);
		GameInvaders->enemyvel.x = CGameInvaders_enemyspeed;
		GameInvaders->enemyvel.y = 0;
		CGameInvaders_createinvaders(GameInvaders,false);
		CGameInvaders_destroybullet(GameInvaders);
		CGameInvaders_destroyallenemybullet(GameInvaders);
		CAudio_PlaySound(GameInvaders->SfxSucces, 0);
	}

	bool btweenactive = CGameInvaders_tweenactive(GameInvaders,CGameInvaders_tweenenemypositions);

	//enemies reached horizontal screen boundaries
	if (((GameInvaders->enemies[GameInvaders->enemyinfo.mostleft].pos.x - GameInvaders->enemies[GameInvaders->enemyinfo.mostleft].tz.x / 2 + GameInvaders->enemyvel.x < GameInvaders->GameBase->screenleft) ||
		(GameInvaders->enemies[GameInvaders->enemyinfo.mostright].pos.x + GameInvaders->enemies[GameInvaders->enemyinfo.mostright].tz.x / 2 + GameInvaders->enemyvel.x > GameInvaders->GameBase->screenright)) && !btweenactive)
	{
		for(int i = 0; i < CGameInvaders_maxenemies; i++)
		{
			if (GameInvaders->enemies[i].alive)
				GameInvaders->enemies[i].pos.y += CGameInvaders_enemyspacing / 4;
		}
		GameInvaders->enemyvel.x *= -1;
		GameInvaders->enemyvel.y *= -1;
	}

	//update enemy positions
	for(int i = 0; i < CGameInvaders_maxenemies; i++)
	{
		if (GameInvaders->enemies[i].alive)
		{
			if (btweenactive)
			{
				updateTween(GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]);
				Vec2F pos = GameInvaders->enemies[i].pos;

				if (GameInvaders->pattern == 0)
				{
					if ((i % CGameInvaders_enemycols) < CGameInvaders_enemycols / 3)
						pos.x = pos.x * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
					else
					{
						if ((i % CGameInvaders_enemycols) > CGameInvaders_enemycols * 2 / 3)
							pos.x = GameInvaders->GameBase->screenright - (GameInvaders->GameBase->screenright - pos.x) * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
					}
					pos.y = pos.y * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
				}
				else
				{
					if(GameInvaders->pattern == 1)
						pos.y = pos.y * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
					else
					{
						if (GameInvaders->pattern == 2)
						{
							if (i % CGameInvaders_enemycols < CGameInvaders_enemycols / 2)
								pos.x = pos.x * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
							else
								pos.x = GameInvaders->GameBase->screenright - (GameInvaders->GameBase->screenright - pos.x) * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
						}
						else
						{
							if( GameInvaders->pattern == 3)
								pos.x = pos.x * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
							else
							{
								if (GameInvaders->pattern == 4)
									pos.x = GameInvaders->GameBase->screenright - (GameInvaders->GameBase->screenright - pos.x) * GameInvaders->tweens[i][CGameInvaders_tweenenemypositions]->funcval;
							}
						}
					}
				}
				GameInvaders->enemies[i].spr->x = pos.x;
				GameInvaders->enemies[i].spr->y = pos.y;
			}
			else
			{
				if (SubGameState == SGGame)
				{
					GameInvaders->enemies[i].pos.x += GameInvaders->enemyvel.x;
					GameInvaders->enemies[i].pos.y += GameInvaders->enemyvel.y;
					GameInvaders->enemies[i].spr->x = GameInvaders->enemies[i].pos.x;
					GameInvaders->enemies[i].spr->y = GameInvaders->enemies[i].pos.y;
				}
			}
		}
	}

	//enemies reached bottom
	if ((GameInvaders->player.pos.y - GameInvaders->enemies[GameInvaders->enemyinfo.mostbottom].pos.y) < CGameInvaders_endscreenconstant)
	{
		if (!(GameMode == GMGame))
			CGame_AddToScore(-250);
		GameInvaders->enemyvel.x = CGameInvaders_enemyspeed;
		GameInvaders->enemyvel.y = 0;
		CGameInvaders_destroyallinvaders(GameInvaders);
		CGameInvaders_createinvaders(GameInvaders,false);
		CGameInvaders_destroybullet(GameInvaders);
		CGameInvaders_destroyallenemybullet(GameInvaders);
		GameInvaders->GameBase->HealthPoints -= 1;
		CAudio_PlaySound(GameInvaders->SfxDie, 0);
	}
}

//player ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_destroyplayer(CGameInvaders* GameInvaders)
{
	CSprites_RemoveSprite(GameInvaders->player.spr);
	GameInvaders->player.alive = false;
}

void CGameInvaders_createplayer(CGameInvaders* GameInvaders)
{
	GameInvaders->player.spr = CSprites_CreateSprite();
	CSprites_SetSpriteImageTiles(GameInvaders->player.spr, &GameInvaders->spritesheetPlayer, 5,1);
	CSprites_SetSpriteAnimation(GameInvaders->player.spr, 0, 0, 0);
	GameInvaders->player.spr->sxscale = GameInvaders->enemyscale.x;
	GameInvaders->player.spr->syscale = GameInvaders->enemyscale.y;
	SDL_Point *tmpTz = CSprites_TileSize(GameInvaders->player.spr);
	GameInvaders->player.tz = *tmpTz;
	CSprites_SetSpriteCollisionShape(GameInvaders->player.spr, SHAPE_BOX, GameInvaders->player.tz.x-10.0, GameInvaders->player.tz.y - 6.0,0, 0, 12);
	GameInvaders->player.tz.x =(int)(GameInvaders->player.tz.x * GameInvaders->enemyscale.x);
	GameInvaders->player.tz.y =(int)(GameInvaders->player.tz.y * GameInvaders->enemyscale.y);
	GameInvaders->player.pos.x = (float)(GameInvaders->GameBase->screenright - GameInvaders->GameBase->screenleft) / 2;
	GameInvaders->player.pos.y = (float)GameInvaders->GameBase->screenbottom - GameInvaders->player.tz.y / 2;
	GameInvaders->GameBase->HealthPoints = 3;
	GameInvaders->player.freeze = 0;
	GameInvaders->player.spr->x = GameInvaders->player.pos.x;
	GameInvaders->player.spr->y = GameInvaders->player.pos.y;
	free(tmpTz);
}

void CGameInvaders_updateplayer(CGameInvaders* GameInvaders)
{
	CSprites_SetSpriteVisibility(GameInvaders->player.spr, GameInvaders->player.alive);
	if (GameInvaders->player.alive)
	{
		CSprites_SetSpriteAnimation(GameInvaders->player.spr, 0, 0, 0);

		if (gamepad_left() > 0)
		{
			if (GameInvaders->player.pos.x - GameInvaders->player.tz.x / 2 - CGameInvaders_playerspeed > GameInvaders->GameBase->screenleft)
				GameInvaders->player.pos.x -= CGameInvaders_playerspeed;
			else
				GameInvaders->player.pos.x = (float)(GameInvaders->GameBase->screenleft + GameInvaders->player.tz.x / 2.0);
			CSprites_SetSpriteAnimation(GameInvaders->player.spr, 1, 1, 0);
		}

		if (gamepad_right() > 0)
		{
			if ( GameInvaders->player.pos.x + GameInvaders->player.tz.x / 2 + CGameInvaders_playerspeed < GameInvaders->GameBase->screenright)
				GameInvaders->player.pos.x += CGameInvaders_playerspeed;
			else
				GameInvaders->player.pos.x = (float)(GameInvaders->GameBase->screenright - GameInvaders->player.tz.x / 2.0);
			CSprites_SetSpriteAnimation(GameInvaders->player.spr, 4, 4, 0);
		}
		GameInvaders->player.spr->x = GameInvaders->player.pos.x;
		GameInvaders->player.spr->y = GameInvaders->player.pos.y;

		if (gamepad_button_a() == 1)
			CGameInvaders_createbullet(GameInvaders);
	}
	else
	{
		if (GameInvaders->player.freeze > 0)
			GameInvaders->player.freeze -= 1;
		else
			GameInvaders->player.alive = true;
	}
}


//background ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_DrawBackground(CGameInvaders* GameInvaders)
{
	CImage_DrawImage( GameInvaders->background,0, NULL, NULL);
}

//init - deinit ----------------------------------------------------------------------------------------------------------------


void CGameInvaders_LoadSound(CGameInvaders* GameInvaders)
{
	GameInvaders->SfxDie = CAudio_LoadSound("common/die");
	GameInvaders->SfxPlayerShoot = CAudio_LoadSound("invaders/playershoot");
	GameInvaders->SfxPlayerDeath = CAudio_LoadSound("invaders/playerdeath");
	GameInvaders->SfxEnemyShoot = CAudio_LoadSound("invaders/enemyshoot");
	GameInvaders->SfxEnemyDeath = CAudio_LoadSound("invaders/enemydeath");
	GameInvaders->SfxSucces = CAudio_LoadSound("common/succes");
	GameInvaders->MusMusic = CAudio_LoadMusic("invaders/music");
}

void CGameInvaders_UnLoadSound(CGameInvaders* GameInvaders)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GameInvaders->MusMusic);
	CAudio_UnLoadSound(GameInvaders->SfxDie);
	CAudio_UnLoadSound(GameInvaders->SfxPlayerShoot);
	CAudio_UnLoadSound(GameInvaders->SfxPlayerDeath);
	CAudio_UnLoadSound(GameInvaders->SfxEnemyShoot);
	CAudio_UnLoadSound(GameInvaders->SfxEnemyDeath);
	CAudio_UnLoadSound(GameInvaders->SfxSucces);
}

void CGameInvaders_UnloadGraphics(CGameInvaders* GameInvaders)
{
	CImage_UnLoadImage(GameInvaders->spritesheetBullet);
	CImage_UnLoadImage(GameInvaders->spritesheetExplosion);
	CImage_UnLoadImage(GameInvaders->spritesheetAsteroid);
	CImage_UnLoadImage(GameInvaders->spritesheetEnemy1);
	CImage_UnLoadImage(GameInvaders->spritesheetEnemy2);
	CImage_UnLoadImage(GameInvaders->spritesheetEnemy3);
	CImage_UnLoadImage(GameInvaders->spritesheetPlayer);
	CImage_UnLoadImage(GameInvaders->background);
}


void CGameInvaders_LoadGraphics(CGameInvaders* GameInvaders)
{
	GameInvaders->background = CImage_LoadImage("invaders/background.png");

	GameInvaders->spritesheetBullet = CImage_LoadImage("invaders/bullet.png");
	GameInvaders->spritesheetExplosion = CImage_LoadImage("invaders/explosion.png");
	GameInvaders->spritesheetAsteroid = CImage_LoadImage("invaders/asteroid-01.png");
	GameInvaders->spritesheetEnemy1 = CImage_LoadImage("invaders/enemy1.png"); //bottom
	GameInvaders->spritesheetEnemy2 = CImage_LoadImage("invaders/enemy2.png"); //middle
	GameInvaders->spritesheetEnemy3 = CImage_LoadImage("invaders/enemy3.png"); //top
	GameInvaders->spritesheetPlayer = CImage_LoadImage("invaders/player.png"); //top
}


void CGameInvaders_init(CGameInvaders* GameInvaders)
{
	CGameInvaders_LoadGraphics(GameInvaders);

	GameInvaders->deaths = 0;
	GameInvaders->backgroundfade = 0;
	GameInvaders->backgroundfadeinc = 1;
	GameInvaders->enemyvel.x = CGameInvaders_enemyspeed;
	GameInvaders->enemyvel.y = 0;

	CGameInvaders_createinvaders(GameInvaders,false);
	CGameInvaders_createplayer(GameInvaders);
	CGameInvaders_createasteroids(GameInvaders);

	CGameInvaders_LoadSound(GameInvaders);
	CurrentGameMusicID = GameInvaders->MusMusic;
	CAudio_PlayMusic(GameInvaders->MusMusic, -1);
}

void CGameInvaders_deinit(CGameInvaders* GameInvaders)
{
	CGameInvaders_destroyplayer(GameInvaders);
	CGameInvaders_destroyallinvaders(GameInvaders);
	CGameInvaders_destroybullet(GameInvaders);
	CGameInvaders_destroyallasteroids(GameInvaders);
	CGameInvaders_destroyallenemybullet(GameInvaders);
	CGameInvaders_destroyallexplosion(GameInvaders);
	CGameInvaders_UnLoadSound(GameInvaders);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
	CGameInvaders_UnloadGraphics(GameInvaders);
}

//Update ----------------------------------------------------------------------------------------------------------------

void CGameInvaders_UpdateObjects(CGameInvaders* GameInvaders, bool IsGameState)
{
	CGameInvaders_updateinvaders(GameInvaders);
	if (IsGameState)
	{
		CGameInvaders_updateenemybullet(GameInvaders);
		CGameInvaders_updateplayer(GameInvaders);
		CGameInvaders_updatebullet(GameInvaders);
		CGameInvaders_updateasteroids(GameInvaders);
	}
}

void CGameInvaders_UpdateLogic(CGameInvaders* GameInvaders)
{
	CGameBase_UpdateLogic(GameInvaders->GameBase);

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameInvaders_UpdateObjects(GameInvaders,SubGameState == SGGame);
	if(SubGameState == SGGame)
		CSprites_UpdateSprites();
}

bool CGameInvaders_DrawObjects(CGameInvaders* GameInvaders)
{
	//need todo this here so last frame is also drawn
	CGameInvaders_checkexplosions(GameInvaders);
	//call drawsprites
	return true;
}

void CGameInvaders_Draw(CGameInvaders* GameInvaders)
{
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameInvaders_DrawBackground(GameInvaders);
	if (CGameInvaders_DrawObjects(GameInvaders))
		CSprites_DrawSprites();
	CGameBase_DrawScoreBar(GameInvaders->GameBase);
	CGameBase_DrawSubstateText(GameInvaders->GameBase);
}

#endif