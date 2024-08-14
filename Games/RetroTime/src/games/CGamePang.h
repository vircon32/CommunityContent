#ifndef CGAMEPANG_H
#define CGAMEPANG_H

#include "CGameBase.h"
#include "CSpriteObject.h"
#include "../Common.h"
#include "../Vec2F.h"
#include "../CGame.h"


#define CGamePang_backgroundcopyheight (30*yscale)

#define CGamePang_enemyspeed 1.0*yscale
#define CGamePang_playerspeed 8.0*xscale
#define CGamePang_bulletspeed 10.0*yscale

#define CGamePang_playerstateidle 0
#define CGamePang_playerstatemoveleft 2
#define CGamePang_playerstatemoveright 4
#define CGamePang_playerstateshoot 8
#define CGamePang_playerstatereviving 16

#define CGamePang_ballbig 3
#define CGamePang_ballmedium 2
#define CGamePang_ballsmall 1

#define CGamePang_maxbigballs 6
//maxbigballs * 7
#define CGamePang_maxballs (CGamePang_maxbigballs * 7)

struct CGamePang 
{

	CGameBase *GameBase;

	Vec2F playerscale;
	Vec2F bulletscale;
	Vec2F ballscale;

	int background;
	int backgroundsub;
	int spritesheetplayer;
	int spritesheetbullet;
	int spritesheetball;

	SDL_Point spritesheetballtz;

	int deaths;
	int levelcleared;
	CSpriteObject[CGamePang_maxballs] balls;
	CSpriteObject player;
	CSpriteObject bullet;

	int MusMusic, SfxSucces, SfxDie, SfxShoot, SfxPop;


};


CGamePang* Create_CGamePang()
{
	CSprites_SetSpriteMax(CGamePang_maxballs + 2); //2 = bullet & player
	CGamePang* GamePang = (CGamePang*) malloc(sizeof(CGamePang));
	GamePang->GameBase = Create_CGameBase(GSPang, true);

	GamePang->MusMusic = -1;
	GamePang->SfxSucces = -1;
	GamePang->SfxDie = -1;
	GamePang->SfxShoot = -1;
	GamePang->SfxPop = -1;
	GamePang->GameBase->screenleft = 0;
	GamePang->GameBase->screenright = ScreenWidth;
	GamePang->GameBase->screentop = 0;
	GamePang->GameBase->screenbottom = ScreenHeight;

	GamePang->playerscale.x = 2.0*yscale;
	GamePang->playerscale.y = 2.0*yscale;
	GamePang->bulletscale.x = 1.0*yscale;
	GamePang->bulletscale.y = 0.8*yscale;
	GamePang->ballscale.x = 1.5*yscale;
	GamePang->ballscale.y = 1.5*yscale;

	GamePang->deaths = 0;
	GamePang->levelcleared = false;

	for (int i=0; i < CGamePang_maxballs; i++)
		Initialize_CSpriteObject(&GamePang->balls[i]);
	
	Initialize_CSpriteObject(&GamePang->player);
	Initialize_CSpriteObject(&GamePang->bullet);

	return GamePang;
}

void Destroy_CGamePang(CGamePang* GamePang)
{
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GamePang->GameBase);
	free(GamePang);
	GamePang = NULL;
}

//bullet ----------------------------------------------------------------------------------------------------------------
void CGamePang_addplayerstate(CGamePang* GamePang, int state)
{
	GamePang->player.state |= state;
}

bool CGamePang_playerstate(CGamePang* GamePang, int state)
{
	return ((GamePang->player.state & state) == state);
}

void CGamePang_remplayerstate(CGamePang* GamePang, int state)
{
	if ((GamePang->player.state & state) == state)
		GamePang->player.state -= state;
}


void CGamePang_destroybullet(CGamePang* GamePang)
{
	if (GamePang->bullet.alive)
	{
		CSprites_RemoveSprite(GamePang->bullet.spr);
		GamePang->bullet.alive = false;
	}
}

void CGamePang_createbullet(CGamePang* GamePang)
{
	GamePang->bullet.spr = CSprites_CreateSprite();
	CSprites_SetSpriteImageTiles(GamePang->bullet.spr, &GamePang->spritesheetbullet, 1, 2);
	CSprites_SetSpriteAnimation(GamePang->bullet.spr, 0, 0, 0);
	SDL_Point *tmpTz = CSprites_TileSize(GamePang->bullet.spr);
	CSprites_SetSpriteCollisionShape(GamePang->bullet.spr, SHAPE_BOX, tmpTz->y-18.0, tmpTz->x+160.0,0,0,0);
	free(tmpTz);
	CSprites_SetSpriteRotation(GamePang->bullet.spr, 90);
	GamePang->bullet.spr->sxscale = GamePang->bulletscale.x;
	GamePang->bullet.spr->syscale = GamePang->bulletscale.y;
	CSprites_SetSpriteDepth(GamePang->bullet.spr, 3);
	tmpTz = CSprites_TileSize(GamePang->bullet.spr);
	GamePang->bullet.tz = *tmpTz;
	GamePang->bullet.tz.x = (int)(GamePang->bullet.tz.x * GamePang->bulletscale.x);
	GamePang->bullet.tz.y = (int)(GamePang->bullet.tz.y * GamePang->bulletscale.y);
	int tmpx = GamePang->bullet.tz.x;
	GamePang->bullet.tz.x = (int)(GamePang->bullet.tz.y);
	GamePang->bullet.tz.y = tmpx;
	GamePang->bullet.pos.x = GamePang->player.pos.x;
	GamePang->bullet.pos.y = GamePang->player.pos.y - (GamePang->player.tz.y) + (GamePang->bullet.tz.y /2);
	GamePang->bullet.vel.x = 0;
	GamePang->bullet.vel.y = -CGamePang_bulletspeed;
	GamePang->bullet.spr->x = GamePang->bullet.pos.x;
	GamePang->bullet.spr->y = GamePang->bullet.pos.y;
	GamePang->bullet.alive = true;
	free(tmpTz);
}

void CGamePang_updatebullet(CGamePang* GamePang)
{
	if (GamePang->bullet.alive)
	{
		if (GamePang->bullet.freeze > 0)
		{
			GamePang->bullet.freeze -= 1;
			if (GamePang->bullet.freeze == 0)
			{
				CGamePang_remplayerstate(GamePang,CGamePang_playerstateshoot);
				CGamePang_destroybullet(GamePang);
			}
		}
		else
		{
			GamePang->bullet.pos.x += GamePang->bullet.vel.x;
			GamePang->bullet.pos.y += GamePang->bullet.vel.y;
			if (GamePang->bullet.pos.y - GamePang->bullet.tz.y /2 <= GamePang->GameBase->screentop)
			{
				GamePang->bullet.freeze = 6;
				CSprites_SetSpriteAnimation(GamePang->bullet.spr, 0, 1, 10);
			}
			GamePang->bullet.spr->x = GamePang->bullet.pos.x;
			GamePang->bullet.spr->y = GamePang->bullet.pos.y;
		}
	}
}

void CGamePang_drawbullet(CGamePang* GamePang)
{
	if (GamePang->bullet.alive)
	{

		CSprites_DrawSprite(GamePang->bullet.spr);
		SDL_Point* ts = CImage_ImageSize(GamePang->backgroundsub);
		CImage_DrawImageFuze(GamePang->backgroundsub,0,false, 0, GamePang->GameBase->screenbottom - ts->y, 0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		free(ts);
	}
}

//player ----------------------------------------------------------------------------------------------------------------

void CGamePang_destroyplayer(CGamePang* GamePang)
{
	if(GamePang->player.alive)
	{
		CSprites_RemoveSprite(GamePang->player.spr);
		GamePang->player.alive = false;
	}
}

void CGamePang_createplayer(CGamePang* GamePang)
{
	GamePang->player.spr = CSprites_CreateSprite();
	CSprites_SetSpriteImageTiles(GamePang->player.spr, &GamePang->spritesheetplayer, 12, 8);
	CSprites_SetSpriteAnimation(GamePang->player.spr, 37, 37, 0);
	SDL_Point *tmpTz =  CSprites_TileSize(GamePang->player.spr); 
	CSprites_SetSpriteCollisionShape(GamePang->player.spr, SHAPE_BOX, tmpTz->x - 24.0, tmpTz->y-14.0,0,0,14*yscale);
	free(tmpTz);
	GamePang->player.spr->sxscale = GamePang->playerscale.x;
	GamePang->player.spr->syscale = GamePang->playerscale.y;
	CSprites_SetSpriteDepth(GamePang->player.spr, 37);
	GamePang->player.state = CGamePang_playerstateidle;
	tmpTz = CSprites_TileSize(GamePang->player.spr);
	GamePang->player.tz = *tmpTz;
	GamePang->player.tz.x = (int)(GamePang->player.tz.x * GamePang->playerscale.x);
	GamePang->player.tz.y = (int)(GamePang->player.tz.y * GamePang->playerscale.y);
	GamePang->player.pos.x = (float)(GamePang->GameBase->screenright - GamePang->GameBase->screenleft) / 2;
	GamePang->player.pos.y = (float)GamePang->GameBase->screenbottom -10- GamePang->player.tz.y / 2;
	GamePang->GameBase->HealthPoints = 3;
	GamePang->player.spr->x = GamePang->player.pos.x;
	GamePang->player.spr->y = GamePang->player.pos.y;
	GamePang->player.alive = true;
	GamePang->player.state = CGamePang_playerstateidle;
	free(tmpTz);
}

void CGamePang_updateplayer(CGamePang* GamePang)
{
	CSprites_SetSpriteVisibility(GamePang->player.spr, GamePang->player.alive);

	if (GamePang->player.alive)
	{
		if (GamePang->player.stateticks > 0)
			GamePang->player.stateticks -= 1;
		else
		{
			if (CGamePang_playerstate(GamePang,CGamePang_playerstateshoot))
				CGamePang_remplayerstate(GamePang,CGamePang_playerstateshoot);
			else
			{
				if (CGamePang_playerstate(GamePang,CGamePang_playerstatereviving))
					CGamePang_remplayerstate(GamePang,CGamePang_playerstatereviving);
			}
		}

		if (!CGamePang_playerstate(GamePang,CGamePang_playerstateshoot))
		{
			if (gamepad_left() > 0)
			{
				if ( GamePang->player.pos.x - GamePang->player.tz.x / 2 - CGamePang_playerspeed > GamePang->GameBase->screenleft)
				{
					GamePang->player.pos.x -=CGamePang_playerspeed;
					if (!CGamePang_playerstate(GamePang,CGamePang_playerstatemoveleft))
					{
						CGamePang_addplayerstate(GamePang,CGamePang_playerstatemoveleft);
						CSprites_SetSpriteAnimation(GamePang->player.spr, 12, 14, 10);
					}
				}
				else
				{
					GamePang->player.pos.x = (float)(GamePang->GameBase->screenleft + GamePang->player.tz.x / 2.0);
					if (CGamePang_playerstate(GamePang,CGamePang_playerstatemoveleft))
					{
						CGamePang_remplayerstate(GamePang,CGamePang_playerstatemoveleft);
						CSprites_SetSpriteAnimation(GamePang->player.spr, 37, 37, 0);
					}
				}
			}
			else
			{
				if (gamepad_right() > 0)
				{
					if ( GamePang->player.pos.x + GamePang->player.tz.x / 2 + CGamePang_playerspeed < GamePang->GameBase->screenright)
					{
						GamePang->player.pos.x += CGamePang_playerspeed;
						if (!CGamePang_playerstate(GamePang,CGamePang_playerstatemoveright))
						{
							CGamePang_addplayerstate(GamePang,CGamePang_playerstatemoveright);
							CSprites_SetSpriteAnimation(GamePang->player.spr, 24, 26, 10);
						}
					}
					else
					{
						GamePang->player.pos.x = (float)(GamePang->GameBase->screenright - GamePang->player.tz.x / 2.0);
						if (CGamePang_playerstate(GamePang,CGamePang_playerstatemoveleft))
						{
							CGamePang_remplayerstate(GamePang,CGamePang_playerstatemoveright);
							CSprites_SetSpriteAnimation(GamePang->player.spr,37, 37, 0);
						}
					}
				}
				else
				{
					CGamePang_remplayerstate(GamePang,CGamePang_playerstatemoveright);
					CGamePang_remplayerstate(GamePang,CGamePang_playerstatemoveleft);
					CSprites_SetSpriteAnimation(GamePang->player.spr, 37, 37, 0);
				}
			}

			if ((!CGamePang_playerstate(GamePang,CGamePang_playerstatereviving)) && (gamepad_button_a() == 1))
			{
				if (!GamePang->bullet.alive)
				{
					CGamePang_addplayerstate(GamePang,CGamePang_playerstateshoot);
					CGamePang_remplayerstate(GamePang,CGamePang_playerstatemoveright);
					CGamePang_remplayerstate(GamePang,CGamePang_playerstatemoveleft);
					CSprites_SetSpriteAnimation(GamePang->player.spr, 37, 37, 10);
					GamePang->player.stateticks = 15;
					CGamePang_createbullet(GamePang);
					CAudio_PlaySound(GamePang->SfxShoot, 0);
				}
			}
			GamePang->player.spr->x = GamePang->player.pos.x;
			GamePang->player.spr->y = GamePang->player.pos.y;
		}
	}
	else
	{
		if (GamePang->player.freeze > 0)
			GamePang->player.freeze -= 1;
		else
			GamePang->player.alive = true;
	}
}

void CGamePang_drawplayer(CGamePang* GamePang)
{
	if (GamePang->player.alive)
	{
		if (CGamePang_playerstate(GamePang,CGamePang_playerstatereviving))
		{
			if (GamePang->player.stateticks % 3 == 0)
				CSprites_DrawSprite(GamePang->player.spr);
		}
		else
			CSprites_DrawSprite(GamePang->player.spr);
	}
}


//balls ----------------------------------------------------------------------------------------------------------------

void CGamePang_createball(CGamePang* GamePang, int size, float x, float y, float speed)
{
	for (int i = 0; i < CGamePang_maxballs; i++)
	{
		if (!GamePang->balls[i].alive)
		{
			GamePang->balls[i].spr = CSprites_CreateSprite();
			CSprites_SetSpriteImage(GamePang->balls[i].spr, &GamePang->spritesheetball);
			CSprites_SetSpriteCollisionShape(GamePang->balls[i].spr, SHAPE_CIRCLE, 35,35,0,0,0);
			//CSprites_SetSpriteCollisionShape(GamePang->balls[i].spr, SHAPE_BOX, 27,27,0,0,0);
			CSprites_SetSpriteColour(GamePang->balls[i].spr, 1, 1, 1, 0.85);
			Vec2F Scale = GamePang->ballscale;
			Scale.x = Scale.x * size;
			Scale.y = Scale.y * size;
			GamePang->balls[i].spr->sxscale = Scale.x;
			GamePang->balls[i].spr->syscale = Scale.y;
			CSprites_SetSpriteDepth(GamePang->balls[i].spr, 6);
			SDL_Point *tmpTz = CImage_ImageSize(GamePang->spritesheetball);
			GamePang->balls[i].tz = *tmpTz;
			GamePang->balls[i].tz.x =(int)(GamePang->balls[i].tz.x * Scale.x);
			GamePang->balls[i].tz.x =(int)(GamePang->balls[i].tz.y * Scale.y);
			GamePang->balls[i].pos.x = x;
			GamePang->balls[i].pos.y = y;
			GamePang->balls[i].spr->x = x;
			GamePang->balls[i].spr->y = y;
			GamePang->balls[i].alive = true;
			GamePang->balls[i].speed = speed*0.1;
			GamePang->balls[i].force = -fabs(speed);
			GamePang->balls[i].curforce = GamePang->balls[i].force/3;
			GamePang->balls[i].id = size;
			free(tmpTz);
			break;
		}
	}
}

void CGamePang_destroyball(CGamePang* GamePang, int index, bool nocreate)
{
	if (!nocreate)
	{
		if (GamePang->balls[index].id > CGamePang_ballsmall)
		{
			CGamePang_createball(GamePang,GamePang->balls[index].id - 1, GamePang->balls[index].pos.x - 25*yscale, GamePang->balls[index].pos.y, -10.0*yscale);
			CGamePang_createball(GamePang,GamePang->balls[index].id - 1, GamePang->balls[index].pos.x + 25*yscale, GamePang->balls[index].pos.y, 10.0*yscale);
		}
	}
	if (GamePang->balls[index].alive)
	{
		CSprites_RemoveSprite(GamePang->balls[index].spr);
		GamePang->balls[index].alive = false;
	}
}


void CGamePang_destroyallballs(CGamePang* GamePang)
{
	for(int i = 0; i < CGamePang_maxballs; i++)
		CGamePang_destroyball(GamePang,i, true);
}
void CGamePang_createballs(CGamePang* GamePang)
{
	int added = 0;
	float speed = 10.0*yscale;
	for (int i = GamePang->GameBase->screenleft; i < GamePang->GameBase->screenright; i += (int)((GamePang->GameBase->screenright - GamePang->GameBase->screenleft) / (GamePang->GameBase->level + 1)) + 1)
	{
		if ((i > GamePang->GameBase->screenleft) && (i < GamePang->GameBase->screenright))
		{
			CGamePang_createball(GamePang,CGamePang_ballbig, (float)i, 160.0*yscale, speed);
			speed *= -1;
			added += 1;
			if (added >= GamePang->GameBase->level)
				break;
		}
	}
}



void CGamePang_updateballs(CGamePang* GamePang)
{
	GamePang->levelcleared = true;
	for (int i = 0; i < CGamePang_maxballs; i++)
	{
		if (GamePang->balls[i].alive)
		{
			GamePang->levelcleared = false;
			if (GamePang->balls[i].pos.x + GamePang->balls[i].speed > GamePang->GameBase->screenright)
			{
				if (GamePang->balls[i].speed > 0)
					GamePang->balls[i].speed = -fabs(GamePang->balls[i].speed);

			}

			if (GamePang->balls[i].pos.x + GamePang->balls[i].speed < GamePang->GameBase->screenleft)
			{
				if (GamePang->balls[i].speed < 0)
					GamePang->balls[i].speed = fabs(GamePang->balls[i].speed);
			}


			GamePang->balls[i].pos.x += GamePang->balls[i].speed*2;

			if (GamePang->balls[i].id == CGamePang_ballbig)
				GamePang->balls[i].curforce += 0.1*yscale;
			else
			{
				if(GamePang->balls[i].id == CGamePang_ballmedium)
					GamePang->balls[i].curforce += 0.15*yscale;
				else
				{
					if (GamePang->balls[i].id == CGamePang_ballsmall)
						GamePang->balls[i].curforce += 0.25*yscale;
				}
			}

			GamePang->balls[i].pos.y += GamePang->balls[i].curforce;

			if (GamePang->balls[i].id == CGamePang_ballbig)
				if (GamePang->balls[i].pos.y >= GamePang->GameBase->screenbottom - 135.0*yscale)
					GamePang->balls[i].curforce = GamePang->balls[i].force;

			if (GamePang->balls[i].id == CGamePang_ballmedium)
				if (GamePang->balls[i].pos.y >= GamePang->GameBase->screenbottom - 100.0*yscale)
					GamePang->balls[i].curforce = GamePang->balls[i].force;

			if (GamePang->balls[i].id == CGamePang_ballsmall)
				if (GamePang->balls[i].pos.y >= GamePang->GameBase->screenbottom - 75.0*yscale)
					GamePang->balls[i].curforce = GamePang->balls[i].force;

			GamePang->balls[i].spr->x = GamePang->balls[i].pos.x;
			GamePang->balls[i].spr->y = GamePang->balls[i].pos.y;

			if (!CGamePang_playerstate(GamePang,CGamePang_playerstatereviving) && CSprites_DetectSpriteCollision(GamePang->balls[i].spr, GamePang->player.spr))
			{
				if (!(GameMode == GMGame))
					CGame_AddToScore(-25);
				GamePang->GameBase->HealthPoints -= 1;
				CGamePang_addplayerstate(GamePang,CGamePang_playerstatereviving);
				CGamePang_remplayerstate(GamePang,CGamePang_playerstateshoot);
				GamePang->player.stateticks = 90;
				CAudio_PlaySound(GamePang->SfxDie, 0);
			}

			if (GamePang->bullet.alive && (GamePang->bullet.freeze == 0))
			{
				if (CSprites_DetectSpriteCollision(GamePang->balls[i].spr, GamePang->bullet.spr))
				{
					CGame_AddToScore(GamePang->balls[i].id * 7);
					CGamePang_destroyball(GamePang,i, false);
					GamePang->bullet.freeze = 4;
					CSprites_SetSpriteAnimation(GamePang->bullet.spr, 0, 1, 10);
					CAudio_PlaySound(GamePang->SfxPop, 0);
				}
			}
		}
	}
	if (GamePang->levelcleared)
	{
		if (GamePang->GameBase->level < CGamePang_maxbigballs)
			GamePang->GameBase->level += 1;
		CAudio_PlaySound(GamePang->SfxSucces, 0);
		CGame_AddToScore(100);
		CGamePang_createballs(GamePang);
	}
}

void CGamePang_drawballs(CGamePang* GamePang)
{
	for (int i = 0; i < CGamePang_maxballs; i++)
	{
		if (GamePang->balls[i].alive)
			CSprites_DrawSprite(GamePang->balls[i].spr);

	}
}


//background ----------------------------------------------------------------------------------------------------------------

void CGamePang_DrawBackground(CGamePang* GamePang)
{
	CImage_DrawImage(GamePang->background, 0, NULL, NULL);
}

//init - deinit ----------------------------------------------------------------------------------------------------------------

void CGamePang_LoadSound(CGamePang* GamePang)
{
	GamePang->SfxDie = CAudio_LoadSound("common/die");
	GamePang->SfxSucces = CAudio_LoadSound("common/succes");
	GamePang->SfxShoot = CAudio_LoadSound("pang/shoot");
	GamePang->SfxPop = CAudio_LoadSound("pang/pop");
	GamePang->MusMusic = CAudio_LoadMusic("pang/music");
}

void CGamePang_UnLoadSound(CGamePang* GamePang)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GamePang->MusMusic);
	CAudio_UnLoadSound(GamePang->SfxDie);
	CAudio_UnLoadSound(GamePang->SfxSucces);
	CAudio_UnLoadSound(GamePang->SfxShoot);
	CAudio_UnLoadSound(GamePang->SfxPop);
}

void CGamePang_UnloadGraphics(CGamePang* GamePang)
{
	CImage_UnLoadImage(GamePang->spritesheetplayer);
	CImage_UnLoadImage(GamePang->spritesheetbullet);
	CImage_UnLoadImage(GamePang->spritesheetball);
	CImage_UnLoadImage(GamePang->background);
	CImage_UnLoadImage(GamePang->backgroundsub);
}


void CGamePang_LoadGraphics(CGamePang* GamePang)
{
	GamePang->background = CImage_LoadImage("pang/background.png");
	GamePang->spritesheetplayer = CImage_LoadImage("pang/character.png");
	GamePang->spritesheetbullet = CImage_LoadImage("pang/weapon.png");
	GamePang->spritesheetball = CImage_LoadImage("pang/ball.png");
	GamePang->backgroundsub = CImage_LoadImage("pang/backgroundsub.png");
		
	SDL_Point *tmpTz = CImage_ImageSize(GamePang->spritesheetball);
	GamePang->spritesheetballtz = *tmpTz;
	free(tmpTz);

}


void CGamePang_init(CGamePang* GamePang)
{
	CGamePang_LoadGraphics(GamePang);
	GamePang->GameBase->level = 1;
	CGamePang_LoadSound(GamePang);
	CGamePang_createplayer(GamePang);
	CGamePang_createballs(GamePang);
	CurrentGameMusicID = GamePang->MusMusic;
	CAudio_PlayMusic(GamePang->MusMusic, -1);
}

void CGamePang_deinit(CGamePang* GamePang)
{
	CGamePang_destroyplayer(GamePang);
	CGamePang_destroyallballs(GamePang);
	CGamePang_destroybullet(GamePang);
	CGamePang_UnLoadSound(GamePang);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
	CGamePang_UnloadGraphics(GamePang);
}
//Update ----------------------------------------------------------------------------------------------------------------

void CGamePang_UpdateObjects(CGamePang* GamePang, bool IsGameState)
{
	if (IsGameState)
	{
		CGamePang_updateplayer(GamePang);
		CGamePang_updateballs(GamePang);
		CGamePang_updatebullet(GamePang);
	}
}

void CGamePang_UpdateLogic(CGamePang* GamePang)
{
	CGameBase_UpdateLogic(GamePang->GameBase);

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGamePang_UpdateObjects(GamePang, SubGameState == SGGame);
	if(SubGameState == SGGame)
		CSprites_UpdateSprites();
}

bool CGamePang_DrawObjects(CGamePang* GamePang)
{
	CGamePang_drawballs(GamePang);
	CGamePang_drawbullet(GamePang);
	CGamePang_drawplayer(GamePang);
	//don't call drawsprites
	return false;
}

void CGamePang_Draw(CGamePang* GamePang)
{
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGamePang_DrawBackground(GamePang);
	if (CGamePang_DrawObjects(GamePang))
		CSprites_DrawSprites();
	CGameBase_DrawScoreBar(GamePang->GameBase);
	CGameBase_DrawSubstateText(GamePang->GameBase);
}

#endif