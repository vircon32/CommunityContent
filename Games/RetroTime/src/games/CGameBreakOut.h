#ifndef CGAMEBREAKOUT_H
#define CGAMEBREAKOUT_H

//this game updates one frame the logic and one frame it draws the sprites
//but it always reads inputs every frame but only handles them in the logic frame
//speeds have been accounted for this using the NumLogicFrames variable

#include "math.h"
#include "../libs/DrawPrimitives/draw_primitives.h"
#include "CGameBase.h"
#include "CSpriteObject.h"
#include "../CTween.h"
#include "../Common.h"
#include "../Vec2F.h"

#define CGameBreakOut_candie 1
#define CGameBreakOut_NumLogicFrames 2
#define CGameBreakOut_tweenblockpositions 0
#define CGameBreakOut_tweenblockdeath 1
#define CGameBreakOut_blockstatedeath 1
#define CGameBreakOut_ballspeed (6.0*yscale*CGameBreakOut_NumLogicFrames)
#define CGameBreakOut_ballspeedinc (0.1*yscale*CGameBreakOut_NumLogicFrames)
#define CGameBreakOut_ballvelsegments 2
#define CGameBreakOut_playerspeed (8.0*xscale*CGameBreakOut_NumLogicFrames)
#define CGameBreakOut_blockxoffset (120.0*xscale)
#define CGameBreakOut_blockyoffset (80.0*yscale)
#define CGameBreakOut_blockrows 8
#define CGameBreakOut_blockcols 17
#define CGameBreakOut_numblocks (CGameBreakOut_blockrows * CGameBreakOut_blockcols)

struct CGameBreakOut
{

	CGameBase *GameBase;

	Vec2F spritescale; 
	Vec2F blockspritecale;

	int MusMusic, SfxDie, SfxSucces, SfxBat, SfxBrick;
	int background, spritesheetblocks, spritesheetbat, spritesheetball;

	bool uppressed;
	bool downpressed;
	bool leftpressed;
	bool rightpressed;
	bool apressed;

	float curballspeed;
	int pattern;
	int blocksAlive;
	//sblockinfo blockinfo;
	CSpriteObject[CGameBreakOut_numblocks] blocks;
	CTweenInfo*[CGameBreakOut_numblocks][2] tweens;
	CSpriteObject player;
	CSpriteObject ball;

	SDL_Point* BlockTzCache;
};


//blocks ----------------------------------------------------------------------------------------------------------------

void CGameBreakOut_destroyblock(CGameBreakOut* GameBreakOut, int index)
{
	if(GameBreakOut->blocks[index].alive)
	{
		GameBreakOut->blocksAlive--;
		CSprites_RemoveSprite(GameBreakOut->blocks[index].spr);
		GameBreakOut->blocks[index].alive = false;
	}
}

void CGameBreakOut_destroyallblocks(CGameBreakOut* GameBreakOut)
{
	for (int i = 0; i < CGameBreakOut_numblocks; i++)
		CGameBreakOut_destroyblock(GameBreakOut,i);
}


void CGameBreakOut_createblocks(CGameBreakOut* GameBreakOut, bool setlocation)
{
	GameBreakOut->pattern = rand() % 5;
	for (int x = 0; x < CGameBreakOut_blockcols; x++)
	{
		for(int y = 0; y < CGameBreakOut_blockrows; y++)
		{
			setTweenInfo(GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions], CGameBreakOut_tweenblockpositions, 1.0+ ((rand() %(6)) / 10), funcsmoothstop, 1, true, 60/CGameBreakOut_NumLogicFrames);
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr = CSprites_CreateSprite();
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].state = 0;
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].alive = true;
			GameBreakOut->blocksAlive++;
			CSprites_SetSpriteImageTiles(GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr, &GameBreakOut->spritesheetblocks, 6, 1);
			if(GameBreakOut->BlockTzCache == NULL)
			{
				GameBreakOut->BlockTzCache = CSprites_TileSize(GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr);
				GameBreakOut->BlockTzCache->x = GameBreakOut->BlockTzCache->x * GameBreakOut->blockspritecale.x;
				GameBreakOut->BlockTzCache->y = GameBreakOut->BlockTzCache->y * GameBreakOut->blockspritecale.y;
			}
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].tz.x = GameBreakOut->BlockTzCache->x;
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].tz.y = GameBreakOut->BlockTzCache->y;
			CSprites_SetSpriteAnimation(GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr, y % 6, y % 6, 0);

			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->sxscale = GameBreakOut->blockspritecale.x;
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->syscale = GameBreakOut->blockspritecale.y;
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].pos.x = GameBreakOut->GameBase->screenleft + CGameBreakOut_blockxoffset + (x * GameBreakOut->BlockTzCache->x);
			GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].pos.y = GameBreakOut->GameBase->screentop + CGameBreakOut_blockyoffset + (y * GameBreakOut->BlockTzCache->y);
			if (setlocation)
			{
				GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->x = GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].pos.x;
				GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->y = GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].pos.y;
			}
		}
	}
}


void CGameBreakOut_updateblocks(CGameBreakOut* GameBreakOut)
{
	if (GameBreakOut->blocksAlive == 0)
	{
		CGame_AddToScore(500);
		CGameBreakOut_createblocks(GameBreakOut, false);
		CAudio_PlaySound(GameBreakOut->SfxSucces, 0);
		return;
	}
	
	for(int x = 0; x < CGameBreakOut_blockcols; x++)
	{
		for(int y = 0; y < CGameBreakOut_blockrows; y++)
		{
			if(GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].alive)
			{
				if(GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->active)
				{
					updateTween(GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]);
					Vec2F pos = GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].pos;
					if (GameBreakOut->pattern == 0)
					{
						if (x < CGameBreakOut_blockcols / 3)
							pos.x = pos.x * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
						else
						{
							if( x > CGameBreakOut_blockcols * 2 / 3)
								pos.x = GameBreakOut->GameBase->screenright - (GameBreakOut->GameBase->screenright - pos.x) * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
						}
						if (y < CGameBreakOut_blockrows / 2)
							pos.y = pos.y * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
					}
					else
					{
						if(GameBreakOut->pattern == 1)
							pos.y = pos.y * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
						else
						{
							if (GameBreakOut->pattern == 2)
							{
								if (x < CGameBreakOut_blockcols / 2)
									pos.x = pos.x * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
								else
									pos.x = GameBreakOut->GameBase->screenright - (GameBreakOut->GameBase->screenright - pos.x) * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
							}
							else
							{
								if (GameBreakOut->pattern == 3)
									pos.x = pos.x * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
								else
								{
									if (GameBreakOut->pattern == 4)
										pos.x = GameBreakOut->GameBase->screenright - (GameBreakOut->GameBase->screenright - pos.x) * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockpositions]->funcval;
								}
							}
						}
					}

					GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->x = (float)((int)(pos.x));
					GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->y = (float)((int)(pos.y));

				}
				if (GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].state == CGameBreakOut_blockstatedeath)
				{
					if (GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockdeath]->active)
					{
						updateTween(GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockdeath]);
						Vec2F pos = GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].pos;
						pos.y = pos.y + (50 * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockdeath]->funcval);
						pos.x = pos.x + (30 * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockdeath]->funcval);
						GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->x = (float)((int)(pos.x));
						GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr->y = (float)((int)(pos.y));
						CSprites_SetSpriteRotation(GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr, 720 * GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockdeath]->funcval);
						CSprites_SetSpriteColour(GameBreakOut->blocks[x + y * CGameBreakOut_blockcols].spr, 1,1,1, 1- GameBreakOut->tweens[x + y * CGameBreakOut_blockcols][CGameBreakOut_tweenblockdeath]->funcval);
					}
					else
					{
						CGameBreakOut_destroyblock(GameBreakOut,x + y * CGameBreakOut_blockcols);
					}
				}

			}
		}
	}
}

//player ----------------------------------------------------------------------------------------------------------------

void CGameBreakOut_destroyplayer(CGameBreakOut* GameBreakOut)
{
	if (GameBreakOut->player.alive)
	{
		CSprites_RemoveSprite(GameBreakOut->player.spr);
		GameBreakOut->player.alive = false;
	}
}

void CGameBreakOut_createplayer(CGameBreakOut* GameBreakOut)
{
	GameBreakOut->player.spr = CSprites_CreateSprite();
	CSprites_SetSpriteImage(GameBreakOut->player.spr, &GameBreakOut->spritesheetbat);
	GameBreakOut->player.spr->sxscale = GameBreakOut->spritescale.x;
	GameBreakOut->player.spr->syscale = GameBreakOut->spritescale.y;
	SDL_Point *TmpTz = CImage_ImageSize(GameBreakOut->spritesheetbat);
	GameBreakOut->player.tz = *TmpTz;
	free(TmpTz);
	GameBreakOut->player.tz.x = (int)(GameBreakOut->player.tz.x * GameBreakOut->spritescale.x);
	GameBreakOut->player.tz.y = (int)(GameBreakOut->player.tz.y * GameBreakOut->spritescale.y);
	GameBreakOut->player.pos.x = (float)(GameBreakOut->GameBase->screenright - GameBreakOut->GameBase->screenleft-80) / 2;
	GameBreakOut->player.pos.y = (float)GameBreakOut->GameBase->screenbottom - 20*yscale - (GameBreakOut->player.tz.y / 2);
	GameBreakOut->GameBase->HealthPoints = 5;
	GameBreakOut->player.spr->x  = GameBreakOut->player.pos.x;
	GameBreakOut->player.spr->y  = GameBreakOut->player.pos.y;
	GameBreakOut->player.alive = true;
}

void CGameBreakOut_updateplayer(CGameBreakOut* GameBreakOut)
{
	CSprites_SetSpriteVisibility(GameBreakOut->player.spr, GameBreakOut->player.alive);
	if (GameBreakOut->player.alive)
	{
		float speedmultiplier = 1;

		if (GameBreakOut->apressed)
			speedmultiplier = 2;

		if (GameBreakOut->leftpressed)
		{
			if (GameBreakOut->player.pos.x - GameBreakOut->player.tz.x / 2 - (CGameBreakOut_playerspeed * speedmultiplier) > GameBreakOut->GameBase->screenleft)
				GameBreakOut->player.pos.x -= CGameBreakOut_playerspeed * speedmultiplier;
			else
				GameBreakOut->player.pos.x = (float)(GameBreakOut->GameBase->screenleft + GameBreakOut->player.tz.x / 2.0);
		}

		if (GameBreakOut->rightpressed)
		{
			if ( GameBreakOut->player.pos.x + GameBreakOut->player.tz.x / 2 + (CGameBreakOut_playerspeed * speedmultiplier) < GameBreakOut->GameBase->screenright)
				GameBreakOut->player.pos.x += CGameBreakOut_playerspeed * speedmultiplier;
			else
				GameBreakOut->player.pos.x = (float)(GameBreakOut->GameBase->screenright - GameBreakOut->player.tz.x / 2.0);
		}

		GameBreakOut->player.spr->x = (float)((int)(GameBreakOut->player.pos.x));
		GameBreakOut->player.spr->y = (float)((int)(GameBreakOut->player.pos.y));
	}
	else
	{
		if (GameBreakOut->player.freeze > 0)
			GameBreakOut->player.freeze -= 1;
		else
			GameBreakOut->player.alive = true;
	}
}


//ball ----------------------------------------------------------------------------------------------------------------

void CGameBreakOut_destroyball(CGameBreakOut* GameBreakOut)
{
	if (GameBreakOut->ball.alive)
	{
		CSprites_RemoveSprite(GameBreakOut->ball.spr);
		GameBreakOut->ball.alive = false;
	}
}

void CGameBreakOut_createball(CGameBreakOut* GameBreakOut)
{
	GameBreakOut->ball.spr = CSprites_CreateSprite();
	CSprites_SetSpriteImage(GameBreakOut->ball.spr, &GameBreakOut->spritesheetball);
	GameBreakOut->ball.spr->sxscale = xscale;
	GameBreakOut->ball.spr->syscale = yscale;
	SDL_Point *tmpTz = CImage_ImageSize(GameBreakOut->spritesheetball);
	GameBreakOut->ball.tz = *tmpTz;
	free(tmpTz);
	GameBreakOut->ball.tz.x = (int)(GameBreakOut->ball.tz.x * xscale);
	GameBreakOut->ball.tz.y = (int)(GameBreakOut->ball.tz.y * yscale);
	
	CSprites_SetSpriteCollisionShape(GameBreakOut->ball.spr, SHAPE_BOX, 4/xscale, 4/yscale, 0, 0, 0);
	GameBreakOut->ball.pos.x = (float)((GameBreakOut->GameBase->screenright - GameBreakOut->GameBase->screenleft-80) / 2) + 250*xscale;
	GameBreakOut->ball.pos.y = (float)GameBreakOut->GameBase->screenbottom - 250*yscale - 20*yscale;
	GameBreakOut->ball.vel.x = -0.5;
	GameBreakOut->ball.vel.y = 0.5;
	GameBreakOut->curballspeed = CGameBreakOut_ballspeed;
	GameBreakOut->ball.alive = true;
	GameBreakOut->ball.spr->x = GameBreakOut->ball.pos.x;
	GameBreakOut->ball.spr->y = GameBreakOut->ball.pos.y;
}

void CGameBreakOut_updateball(CGameBreakOut* GameBreakOut)
{
	if (GameBreakOut->ball.alive)
	{
		if (GameBreakOut->ball.freeze > 0)
			GameBreakOut->ball.freeze -= 1;
		else
		{
			float steps = GameBreakOut->curballspeed / (CGameBreakOut_ballvelsegments + 1);

			for (int j = 1; j <=CGameBreakOut_ballvelsegments + 1; j++)
			{
				GameBreakOut->ball.pos.x += (steps * GameBreakOut->ball.vel.x);
				GameBreakOut->ball.pos.y += (steps * GameBreakOut->ball.vel.y);

				if (GameBreakOut->ball.pos.x < GameBreakOut->GameBase->screenleft)
				{
					GameBreakOut->ball.vel.x *= -1;
					GameBreakOut->ball.pos.x = (float)(GameBreakOut->GameBase->screenleft);
				}

				if (GameBreakOut->ball.pos.x > GameBreakOut->GameBase->screenright)
				{
					GameBreakOut->ball.vel.x *= -1;
					GameBreakOut->ball.pos.x = (float)(GameBreakOut->GameBase->screenright);
				}

				if (GameBreakOut->ball.pos.y < GameBreakOut->GameBase->screentop)
				{
					GameBreakOut->ball.pos.y = (float)(GameBreakOut->GameBase->screentop);
					GameBreakOut->ball.vel.y *= -1;
				}

				GameBreakOut->ball.spr->x = GameBreakOut->ball.pos.x;
				GameBreakOut->ball.spr->y = GameBreakOut->ball.pos.y;

				if (GameBreakOut->ball.pos.y >= GameBreakOut->GameBase->screenbottom)
				{
					CGameBreakOut_destroyball(GameBreakOut);
					CGameBreakOut_createball(GameBreakOut);
					GameBreakOut->ball.freeze = 15;
					if (GameMode == GMGame)
					{
						if(CGameBreakOut_candie)
							GameBreakOut->GameBase->HealthPoints -= 1;
					}
					else
						CGame_AddToScore(-100);
					CAudio_PlaySound(GameBreakOut->SfxDie, 0);
					if (GameBreakOut->GameBase->HealthPoints > 0)
					{
						SubGameState = SGReadyGo;
						SubStateTime = getCurrentTimeMilliseconds() + 500;
					}
				}

				for (int k = 0; k < CGameBreakOut_numblocks; k++)
				{
					if (GameBreakOut->blocks[k].alive && (GameBreakOut->blocks[k].state != CGameBreakOut_blockstatedeath))
					{
						if (CSprites_DetectSpriteCollision(GameBreakOut->ball.spr, GameBreakOut->blocks[k].spr))
						{
							//seen this in wireframe issue 11 not sure what it actually
							//calculates but seems to work more or less ok
							float dx = (GameBreakOut->ball.pos.x - GameBreakOut->blocks[k].pos.x) / GameBreakOut->blocks[k].tz.x;
							float dy = (GameBreakOut->ball.pos.y - GameBreakOut->blocks[k].pos.y) / GameBreakOut->blocks[k].tz.y;
							if (fabs(dx) > fabs(dy))
								GameBreakOut->ball.vel.x = fabs(GameBreakOut->ball.vel.x) * dx / fabs(dx);
							else
								GameBreakOut->ball.vel.y = fabs(GameBreakOut->ball.vel.y) * dy / fabs(dy);

							CGame_AddToScore(20);
							//inc CGameBreakOut_ballspeed
							GameBreakOut->curballspeed += CGameBreakOut_ballspeedinc;
							CAudio_PlaySound(GameBreakOut->SfxBrick, 0);
							GameBreakOut->blocks[k].state = CGameBreakOut_blockstatedeath;
							CSprites_SetSpriteDepth(GameBreakOut->blocks[k].spr, 5);
							setTweenInfo(GameBreakOut->tweens[k][CGameBreakOut_tweenblockdeath], CGameBreakOut_tweenblockdeath, 1, funcsmoothstep, 1, true, 60/CGameBreakOut_NumLogicFrames);
						}
					}
				}

				if (GameBreakOut->player.alive)
				{
					if (CSprites_DetectSpriteCollision(GameBreakOut->ball.spr, GameBreakOut->player.spr))
					{
						//touched top part of bat
						if (GameBreakOut->ball.pos.y < GameBreakOut->player.pos.y + GameBreakOut->player.tz.y / 3)
						{
							//set ball to top part - 1 so it can't callide again
							GameBreakOut->ball.pos.y = GameBreakOut->player.pos.y - GameBreakOut->player.tz.y / 2 - 1;
							GameBreakOut->ball.spr->x = GameBreakOut->ball.pos.x;
							GameBreakOut->ball.spr->y = GameBreakOut->ball.pos.y;

							//inverrt y velocity
							GameBreakOut->ball.vel.y = -GameBreakOut->ball.vel.y;
							//touch far right of bat
							if (GameBreakOut->ball.pos.x >= GameBreakOut->player.pos.x + ((GameBreakOut->player.tz.x / 2) * 5 / 7))
							{
								//and bal is moving to the left
								if (GameBreakOut->ball.vel.x < 0)
								{
									//reverse x velocity
									GameBreakOut->ball.vel.x = -GameBreakOut->ball.vel.x;
									//add some randomness
									float rnd = (rand() % 100) / 1150.0;
									if (rand() % 2 == 0)
										rnd *= -1;

									GameBreakOut->ball.vel.x += rnd;
								}
							}
							else
							{
								//touched far left of bat
								if (GameBreakOut->ball.pos.x <= GameBreakOut->player.pos.x - ((GameBreakOut->player.tz.x / 2) * 5 / 7))
								{
									//and ball moving to the right
									if (GameBreakOut->ball.vel.x > 0)
									{
										//reverse x velocity
										GameBreakOut->ball.vel.x = -GameBreakOut->ball.vel.x;
										//add some randomness
										float rnd = (rand() % 100) / 1150.0;
										if (rand() % 2 == 0)
											rnd *= -1;

										GameBreakOut->ball.vel.x += rnd;
									}
								}
							}
						}
						else
						{
							//bottom parts = loss of ball
							// ball is on the right
							if (GameBreakOut->ball.pos.x > GameBreakOut->player.pos.x)
							{
								//ball is moving towards bat to left
								if (GameBreakOut->ball.vel.x < 0)
									//reverse x velocity
									GameBreakOut->ball.vel.x = -GameBreakOut->ball.vel.x;
							}
							else
							{
								//ball is on the left and moving to the right
								if (GameBreakOut->ball.vel.x > 0)
									//reverse x velocity
									GameBreakOut->ball.vel.x = -GameBreakOut->ball.vel.x;
							}
						}

						//increase CGameBreakOut_ballspeed
						GameBreakOut->curballspeed += CGameBreakOut_ballspeedinc;

						//just a safety
						while (CSprites_DetectSpriteCollision(GameBreakOut->ball.spr, GameBreakOut->player.spr))
						{
							GameBreakOut->ball.pos.x += (steps * GameBreakOut->ball.vel.x);
							GameBreakOut->ball.pos.y += (steps * GameBreakOut->ball.vel.y);
							GameBreakOut->ball.spr->x = GameBreakOut->ball.pos.x;
							GameBreakOut->ball.spr->y = GameBreakOut->ball.pos.y;
						}

						CAudio_PlaySound(GameBreakOut->SfxBat, 0);
					}
				}
			}
		}
	}
}

//background ----------------------------------------------------------------------------------------------------------------

void CGameBreakOut_DrawBackground(CGameBreakOut* GameBreakOut)
{
	if(GameBreakOut->background > -1)
		CImage_DrawImage(GameBreakOut->background, 0, NULL, NULL);
	
}
//init - deinit ----------------------------------------------------------------------------------------------------------------

void CGameBreakOut_LoadSound(CGameBreakOut* GameBreakOut)
{
	GameBreakOut->SfxDie = CAudio_LoadSound("common/die");
	GameBreakOut->SfxSucces = CAudio_LoadSound("common/succes");
	GameBreakOut->SfxBat = CAudio_LoadSound("breakout/bat");
	GameBreakOut->SfxBrick = CAudio_LoadSound("breakout/brick");
	GameBreakOut->MusMusic = CAudio_LoadMusic("breakout/music");
}

void CGameBreakOut_UnLoadSound(CGameBreakOut* GameBreakOut)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GameBreakOut->MusMusic);
	CAudio_UnLoadSound(GameBreakOut->SfxSucces);
	CAudio_UnLoadSound(GameBreakOut->SfxDie);
	CAudio_UnLoadSound(GameBreakOut->SfxBrick);
	CAudio_UnLoadSound(GameBreakOut->SfxBat);
}

void CGameBreakOut_UnloadGraphics(CGameBreakOut* GameBreakOut)
{
	CImage_UnLoadImage(GameBreakOut->spritesheetblocks);
	CImage_UnLoadImage(GameBreakOut->spritesheetbat);
	CImage_UnLoadImage(GameBreakOut->spritesheetball);
	CImage_UnLoadImage(GameBreakOut->background);
}

void CGameBreakOut_LoadGraphics(CGameBreakOut* GameBreakOut)
{
	GameBreakOut->spritesheetblocks = CImage_LoadImage("breakout/blocks.png"); 
	GameBreakOut->spritesheetbat = CImage_LoadImage("breakout/paddle.png");
	GameBreakOut->spritesheetball = CImage_LoadImage("breakout/ball.png");
	GameBreakOut->background = CImage_LoadImage("breakout/background.png");
}

void CGameBreakOut_init(CGameBreakOut* GameBreakOut)
{
	CGameBreakOut_LoadGraphics(GameBreakOut);
	CGameBreakOut_createblocks(GameBreakOut, false);
	CGameBreakOut_createplayer(GameBreakOut);
	CGameBreakOut_createball(GameBreakOut);

	CGameBreakOut_LoadSound(GameBreakOut);
	CurrentGameMusicID = GameBreakOut->MusMusic;
	CAudio_PlayMusic(GameBreakOut->MusMusic, -1);
}

void CGameBreakOut_deinit(CGameBreakOut* GameBreakOut)
{
	CGameBreakOut_destroyplayer(GameBreakOut);
	CGameBreakOut_destroyallblocks(GameBreakOut);
	CGameBreakOut_destroyball(GameBreakOut);
	CGameBreakOut_UnLoadSound(GameBreakOut);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
	CGameBreakOut_UnloadGraphics(GameBreakOut);
}

//Update ----------------------------------------------------------------------------------------------------------------

void CGameBreakOut_UpdateObjects(CGameBreakOut* GameBreakOut, bool IsGameState)
{
	CGameBreakOut_updateblocks(GameBreakOut);
	if (IsGameState)
	{
		CGameBreakOut_updateplayer(GameBreakOut);
		CGameBreakOut_updateball(GameBreakOut);
	}
}

void CGameBreakOut_UpdateLogic(CGameBreakOut* GameBreakOut)
{
	CGameBase_UpdateLogic(GameBreakOut->GameBase);
	
	GameBreakOut->rightpressed = gamepad_right() > 0;
	GameBreakOut->leftpressed = gamepad_left() > 0;
	GameBreakOut->apressed = gamepad_button_a() > 0;

	if(CGameBreakOut_NumLogicFrames > 1)
		if (get_frame_counter() % 2 == 1)
			return;

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
	{
		return;
	}

	CGameBreakOut_UpdateObjects(GameBreakOut, SubGameState == SGGame);
	if(SubGameState == SGGame)
		CSprites_UpdateSprites();

}

void CGameBreakOut_Draw(CGameBreakOut* GameBreakOut)
{
	if(CGameBreakOut_NumLogicFrames > 1)
		if (get_frame_counter() % 2 == 0)
			return;

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameBreakOut_DrawBackground(GameBreakOut);
	CSprites_DrawSprites();
	CGameBase_DrawScoreBar(GameBreakOut->GameBase);
	CGameBase_DrawSubstateText(GameBreakOut->GameBase);
}

CGameBreakOut* Create_CGameBreakOut()
{
	CSprites_SetSpriteMax(CGameBreakOut_numblocks + 2);
	CGameBreakOut* GameBreakOut = (CGameBreakOut*) malloc(sizeof(CGameBreakOut));
	GameBreakOut->GameBase = Create_CGameBase(GSBreakout, false);
	GameBreakOut->MusMusic = -1;
	GameBreakOut->SfxSucces = -1;
	GameBreakOut->SfxDie = -1;
	GameBreakOut->SfxBrick = -1;
	GameBreakOut->SfxBat = -1;
	GameBreakOut->GameBase->screenleft = 0;
	GameBreakOut->GameBase->screenright = ScreenWidth;
	GameBreakOut->GameBase->screentop = ScoreBarHeight;
	GameBreakOut->GameBase->screenbottom = ScreenHeight;

	GameBreakOut->background = -1;
	GameBreakOut->spritesheetblocks = 0;
	GameBreakOut->spritesheetbat = 0;
	GameBreakOut->spritesheetball = 0;


	GameBreakOut->curballspeed = 0.0;
	GameBreakOut->pattern = 0;

	GameBreakOut->spritescale.x = 2.5*xscale;
	GameBreakOut->spritescale.y = 2.5*yscale;
	GameBreakOut->blockspritecale.x = 1.0*xscale;
	GameBreakOut->blockspritecale.y = 2.0*yscale;

	GameBreakOut->uppressed = false;
	GameBreakOut->downpressed = false;
	GameBreakOut->leftpressed = false;
	GameBreakOut->rightpressed = false;

	GameBreakOut->BlockTzCache = NULL;
	GameBreakOut->blocksAlive = 0;
	for (int i= 0; i < CGameBreakOut_numblocks; i++)
	{
		Initialize_CSpriteObject(&GameBreakOut->blocks[i]);
		GameBreakOut->tweens[i][0] = (CTweenInfo*) malloc(sizeof(CTweenInfo));
		GameBreakOut->tweens[i][1] = (CTweenInfo*) malloc(sizeof(CTweenInfo));
	
		initialize_CTweenInfo(GameBreakOut->tweens[i][0]);
		initialize_CTweenInfo(GameBreakOut->tweens[i][1]);
	}
	
	Initialize_CSpriteObject(&GameBreakOut->player);
	Initialize_CSpriteObject(&GameBreakOut->ball);

	return GameBreakOut;
}

void Destroy_CGameBreakOut(CGameBreakOut* GameBreakOut)
{
	if(GameBreakOut->BlockTzCache)
		free(GameBreakOut->BlockTzCache);
	for (int i= 0; i < CGameBreakOut_numblocks; i++)
	{
		free(GameBreakOut->tweens[i][0]);
		free(GameBreakOut->tweens[i][1]);
	}
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GameBreakOut->GameBase);
	free(GameBreakOut);
	GameBreakOut = NULL;
}


#endif