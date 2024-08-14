#ifndef CGAMERAMIT_H
#define CGAMERAMIT_H

#include "CGameBase.h"
#include "../libs/DrawPrimitives/draw_primitives.h"
#include "../Common.h"
#include "../SDL_HelperTypes.h"
#include "../CGame.h"
#include "../SDL_HelperTypes.h"


#define CGameRamIt_bulletsteps 6
#define CGameRamIt_playerrailwidth (10*xscale)
#define CGameRamIt_playerspeed (10*xscale)
#define CGameRamIt_bulletspeed (5*xscale)
#define CGameRamIt_numblocks 16
#define CGameRamIt_blocksegments 21
#define CGameRamIt_sides 2
#define CGameRamIt_blockspacing (int)(5*yscale)
#define CGameRamIt_ticksidle 35*2  
#define CGameRamIt_tickslevelmul 5

struct ramitblock
{
	int maxsegments;
	int segments;
	int color;
};

struct CGameRamIt {

	CGameBase *GameBase;

	int background;
	int SfxShoot, SfxHit, SfxDie, SfxSucces, MusMusic;
	int speed, speedcount, playerdx, playerdeath, riblocksize, riblocksizespacing, segmentwidth;
	int playerdeathtime;
	SDL_Point playerpos;
	SDL_Point bulletpos;
	SDL_Point bulletvel;
	bool bulletalive;
	ramitblock[CGameRamIt_sides][CGameRamIt_numblocks] playfield;
};


CGameRamIt* Create_CGameRamIt()
{
	CSprites_SetSpriteMax(0);
	CGameRamIt* GameRamIt = (CGameRamIt*) malloc(sizeof(CGameRamIt));
	GameRamIt->GameBase = Create_CGameBase(GSRamIt, true);
	GameRamIt->bulletalive = false;
	GameRamIt->speed = 0;
	GameRamIt->speedcount = 0;
	GameRamIt->SfxShoot = -1;
	GameRamIt->SfxHit = -1;
	GameRamIt->SfxDie = -1;
	GameRamIt->SfxSucces = -1;
	GameRamIt->MusMusic = -1;
	GameRamIt->riblocksize = (int)(((ScreenHeight - ScoreBarHeight) / (CGameRamIt_numblocks+1)) - 2 * CGameRamIt_blockspacing);
	GameRamIt->riblocksizespacing =(int)(GameRamIt->riblocksize + 2 * CGameRamIt_blockspacing);
	GameRamIt->GameBase->playfieldwidth = (ScreenWidth - 1 * GameRamIt->riblocksize);
	GameRamIt->segmentwidth = (int)(((GameRamIt->GameBase->playfieldwidth / 2) / CGameRamIt_blocksegments));
	GameRamIt->GameBase->playfieldheight = CGameRamIt_numblocks * GameRamIt->riblocksizespacing;
	GameRamIt->GameBase->screenleft = (ScreenWidth - GameRamIt->GameBase->playfieldwidth) / 2;
	GameRamIt->GameBase->screenright = GameRamIt->GameBase->screenleft + GameRamIt->GameBase->playfieldwidth;
	GameRamIt->GameBase->screentop =  (ScreenHeight - GameRamIt->GameBase->playfieldheight + ScoreBarHeight) / 2;
	GameRamIt->GameBase->screenbottom = GameRamIt->GameBase->screentop + GameRamIt->GameBase->playfieldheight;

	return GameRamIt;
}

void Destroy_CGameRamIt(CGameRamIt* GameRamIt) 
{
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GameRamIt->GameBase);
	free(GameRamIt);
	GameRamIt = NULL;
}

bool CGameRamIt_createbullet(CGameRamIt* GameRamIt)
{
	bool result = false;
	if (!GameRamIt->bulletalive)
	{
		GameRamIt->bulletalive = true;
		GameRamIt->bulletpos = GameRamIt->playerpos;
		GameRamIt->bulletvel.x = (int)(GameRamIt->playerdx * CGameRamIt_bulletspeed);
		GameRamIt->bulletvel.y = 0;
		result = true;
	}
	return result;
}

//BULLET ----------------------------------------------------------------------------------------------------------------

void CGameRamIt_updatebullet(CGameRamIt* GameRamIt)
{
	if (GameRamIt->bulletalive)
	{
		bool destroybullet = false;
		bool playaudiobullet = false;
		for(int steps = 0; steps < CGameRamIt_bulletsteps; steps++)
		{
			GameRamIt->bulletpos.x += GameRamIt->bulletvel.x;
			GameRamIt->bulletpos.y += GameRamIt->bulletvel.y;
			if (GameRamIt->bulletpos.x + GameRamIt->riblocksize / 2 < GameRamIt->GameBase->screenleft)
				destroybullet = true;
			if (GameRamIt->bulletpos.x - GameRamIt->riblocksize / 2 > GameRamIt->GameBase->screenright)
				destroybullet = true;

			for (int side = 0; side < CGameRamIt_sides; side++)
			{
				for (int block = 0; block < CGameRamIt_numblocks; block++)
				{
					if (GameRamIt->playfield[side][block].segments > 0)
					{
						if ((GameRamIt->bulletpos.y + GameRamIt->riblocksize / 6 >= GameRamIt->GameBase->screentop +
							block * GameRamIt->riblocksizespacing + CGameRamIt_blockspacing) &&
							(GameRamIt->bulletpos.y - GameRamIt->riblocksize / 6 <= GameRamIt->GameBase->screentop +
							block * GameRamIt->riblocksizespacing + CGameRamIt_blockspacing + GameRamIt->riblocksize))
						{
							if (side == 0)
							{
								if ((GameRamIt->bulletpos.x - GameRamIt->riblocksize / 2) <= GameRamIt->GameBase->screenleft +
									GameRamIt->playfield[side][block].segments * GameRamIt->segmentwidth)
								{
									GameRamIt->playfield[side][block].segments -= 1;
									if (GameRamIt->playfield[side][block].segments == 0)
										CGame_AddToScore((GameRamIt->GameBase->level + 1) * 2*GameRamIt->playfield[side][block].maxsegments);

									playaudiobullet = true;
									destroybullet = true;
								}
							}
							else
							{
								if ((GameRamIt->bulletpos.x - GameRamIt->riblocksize / 2) >= GameRamIt->GameBase->screenright -
									GameRamIt->playfield[side][block].segments * GameRamIt->segmentwidth)
								{
									GameRamIt->playfield[side][block].segments -= 1;
									if (GameRamIt->playfield[side][block].segments == 0)
										CGame_AddToScore((GameRamIt->GameBase->level + 2) * 2 * GameRamIt->playfield[side][block].maxsegments);

									playaudiobullet = true;
									destroybullet = true;
								}
							}
						}
					}
				}
			}

			if(destroybullet)
			{
				if (playaudiobullet)
					CAudio_PlaySound(GameRamIt->SfxHit, 0);
				GameRamIt->bulletalive = false;
				break;
			}
		}
	}
}

void CGameRamIt_drawbullet(CGameRamIt* GameRamIt)
{
	if (GameRamIt->bulletalive)
	{
		SDL_Rect r = {GameRamIt->bulletpos.x - GameRamIt->riblocksize / 2, GameRamIt->bulletpos.y - GameRamIt->riblocksize / 6, GameRamIt->riblocksize, GameRamIt->riblocksize / 3};
		draw_filled_rectangle(r.x, r.y,r.x + r.w, r.y + r.h);
	}
}

//PLAYER ----------------------------------------------------------------------------------------------------------------

void CGameRamIt_createplayer(CGameRamIt* GameRamIt)
{
	GameRamIt->playerpos.x = GameRamIt->GameBase->screenleft + (GameRamIt->GameBase->screenright - GameRamIt->GameBase->screenleft) / 2;
	GameRamIt->playerpos.y = GameRamIt->GameBase->screentop + (GameRamIt->GameBase->screenbottom - GameRamIt->GameBase->screentop) / 2;
	GameRamIt->playerdx = 1;
}

void CGameRamIt_drawplayer(CGameRamIt* GameRamIt)
{
	SDL_Rect r;
	r.x = (int)(GameRamIt->GameBase->screenleft + (GameRamIt->GameBase->screenright - GameRamIt->GameBase->screenleft -CGameRamIt_playerrailwidth) / 2);
	r.y = GameRamIt->GameBase->screentop;
	r.w = (int)CGameRamIt_playerrailwidth;
	r.h = GameRamIt->GameBase->screenbottom - GameRamIt->GameBase->screentop;
	set_multiply_color(color_lightgray);
	draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);

	set_multiply_color(color_white);
	r.x = GameRamIt->playerpos.x - GameRamIt->riblocksize / 2;
	r.y = GameRamIt->playerpos.y - GameRamIt->riblocksize / 2;
	r.w = GameRamIt->riblocksize;
	r.h = GameRamIt->riblocksize;
	draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);

	if (GameRamIt->playerdx == 1)
	{
		r.x = GameRamIt->playerpos.x + GameRamIt->riblocksize / 2;
		r.y = GameRamIt->playerpos.y - GameRamIt->riblocksize / 4;
		r.w = GameRamIt->riblocksize / 2;
		r.h = GameRamIt->riblocksize / 2;
	}
	else
	{
		r.x = GameRamIt->playerpos.x - GameRamIt->riblocksize;
		r.y = GameRamIt->playerpos.y - GameRamIt->riblocksize / 4;
		r.w = GameRamIt->riblocksize / 2;
		r.h = GameRamIt->riblocksize / 2;
	}
	set_multiply_color(color_red);
	draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);
	set_multiply_color(color_white);
}

void CGameRamIt_updateplayer(CGameRamIt* GameRamIt)
{
	if (gamepad_left() > 0)
		GameRamIt->playerdx = -1;

	if (gamepad_right() > 0)
		GameRamIt->playerdx = 1;

	if (gamepad_down() > 0)
	{
		if (GameRamIt->playerpos.y + GameRamIt->riblocksize / 2 + CGameRamIt_playerspeed < GameRamIt->GameBase->screenbottom)
			GameRamIt->playerpos.y += (int)CGameRamIt_playerspeed;
		else
			GameRamIt->playerpos.y = GameRamIt->GameBase->screenbottom - GameRamIt->riblocksize / 2;
	}

	if (gamepad_up() > 0)
	{
		if (GameRamIt->playerpos.y - GameRamIt->riblocksize / 2 - CGameRamIt_playerspeed > GameRamIt->GameBase->screentop)
			GameRamIt->playerpos.y -= (int)CGameRamIt_playerspeed;
		else
			GameRamIt->playerpos.y = GameRamIt->GameBase->screentop + GameRamIt->riblocksize / 2;
	}

	if (gamepad_button_a() == 1)
		if (CGameRamIt_createbullet(GameRamIt))
		{
			CAudio_PlaySound(GameRamIt->SfxShoot, 0);
		}
}

//playfield ----------------------------------------------------------------------------------------------------------------

void CGameRamIt_createplayfield(CGameRamIt* GameRamIt)
{
	int prevpiece = -1;
	int piece = -1;
	int color = color_white;
	for (int side = 0 ; side < CGameRamIt_sides; side++)
	{
		for (int block = 0; block < CGameRamIt_numblocks; block++)
		{
			while(prevpiece == piece)
				piece = rand() % 17;

			prevpiece = piece;

			if (piece == 0)
				color = make_color_rgba(0x65, 0x65, 0xFF, 0xFF);

			if (piece == 1)
				color = make_color_rgba(0xFF, 0xFF, 0x65, 0xFF);

			if (piece == 2)
				color = make_color_rgba(0x65, 0xFF, 0x65, 0xFF);

			if (piece == 3)
				color = make_color_rgba(0x65, 0x65, 0xFF, 0xFF);

			if (piece == 4)
				color = make_color_rgba(0xA0, 0x20, 0xF0, 0xFF);

			if (piece == 5)
				color = make_color_rgba(0xA5, 0x2A, 0x2A, 0xFF);

			if (piece == 6)
				color = make_color_rgba(0xFF, 0x65, 0xFF, 0xFF);

			if (piece == 7)
				color = make_color_rgba(0xFF, 0xFF, 0xFF, 0xFF);

			if (piece == 8)
				color = make_color_rgba(0x9B, 0x9B, 0x9B, 0xFF);

			if (piece == 9)
				color = make_color_rgba(0xDD, 0xE4, 0xC4, 0xFF);

			if (piece == 10)
				color = make_color_rgba(0xED, 0x70, 0x24, 0xFF);

			if (piece == 11)
				color = make_color_rgba(0xCC, 0xCC, 0xFF, 0xFF);

			if (piece == 12)
				color = make_color_rgba(0xBF, 0xDD, 0x65, 0xFF);

			if (piece == 13)
				color = make_color_rgba(0x65, 0x80, 0x80, 0xFF);

			if (piece == 14)
				color = make_color_rgba(0x65, 0xFF, 0xFF, 0xFF);

			if (piece == 15)
				color = make_color_rgba(0x8A, 0x9A, 0x5B, 0xFF);

			if (piece == 16)
				color = make_color_rgba(0xD9, 0x96, 0x7A, 0xFF);

			GameRamIt->playfield[side][block].color = color;
			GameRamIt->playfield[side][block].segments = 2;
			GameRamIt->playfield[side][block].maxsegments = 2;
		}
	}
}

void CGameRamIt_updateplayfield(CGameRamIt* GameRamIt, bool force)
{
	GameRamIt->speedcount += 1;

	if (force || (GameRamIt->speedcount >= GameRamIt->speed - ((GameRamIt->GameBase->level-1) * CGameRamIt_tickslevelmul)))
	{
		GameRamIt->speedcount = 0;
		int stageclear = true;
		int numalive = 0;
		int side;
		int block;
		for (side = 0; side < CGameRamIt_sides; side++)
			for(block = 0; block < CGameRamIt_numblocks; block++)
				if (GameRamIt->playfield[side][block].segments != 0)
				{
					stageclear = false;
					numalive += 1;
				}

		if (stageclear)
		{
			CAudio_PlaySound(GameRamIt->SfxSucces, 0);
			CGameRamIt_createplayfield(GameRamIt);
			GameRamIt->GameBase->level += 1;
			CGame_AddToScore((GameRamIt->GameBase->level-1) * 100);
		}

		if (!stageclear)
		{
			int r = 1;
			if (numalive <= 5)
				r = rand() % 2;

			if (r == 1)
			{
				side = rand() % CGameRamIt_sides;
				block = rand() % CGameRamIt_numblocks;
				while (GameRamIt->playfield[side][block].segments == 0)
				{
					side = rand() % CGameRamIt_sides;
					block = rand() % CGameRamIt_numblocks;
				}
				GameRamIt->playfield[side][block].segments += 2;
				if (GameRamIt->playfield[side][block].segments > CGameRamIt_blocksegments)
					GameRamIt->playfield[side][block].segments = CGameRamIt_blocksegments;

				if (GameRamIt->playfield[side][block].segments > GameRamIt->playfield[side][block].maxsegments)
					GameRamIt->playfield[side][block].maxsegments = GameRamIt->playfield[side][block].segments;

				//death
				for (side = 0; side < CGameRamIt_sides; side++)
					for (block = 0; block < CGameRamIt_numblocks; block++)
						if (GameRamIt->playfield[side][block].segments == CGameRamIt_blocksegments)
						{
							GameRamIt->playerdeathtime = getCurrentTimeMilliseconds() + 500;
							GameRamIt->playerdeath = true;
							CAudio_PlaySound(GameRamIt->SfxDie, 0);
							break;
						}
			}
		}
	}
}

void CGameRamIt_drawplayfield(CGameRamIt* GameRamIt)
{
	for (int side = 0; side < CGameRamIt_sides; side++)
		for (int block = 0; block < CGameRamIt_numblocks; block++)
		{
			SDL_Rect r;
			if (side == 0)
			{
				r.x = GameRamIt->GameBase->screenleft;
				r.y = (int)(GameRamIt->GameBase->screentop + block * GameRamIt->riblocksizespacing + CGameRamIt_blockspacing);
				r.w = GameRamIt->playfield[side][block].segments * GameRamIt->segmentwidth;
				r.h =GameRamIt->riblocksize;
			}
			else
			{
				r.x = GameRamIt->GameBase->screenright - GameRamIt->playfield[side][block].segments * GameRamIt->segmentwidth;
				r.y = (int)(GameRamIt->GameBase->screentop + block * GameRamIt->riblocksizespacing + CGameRamIt_blockspacing);
				r.w = GameRamIt->playfield[side][block].segments * GameRamIt->segmentwidth;
				r.h = GameRamIt->riblocksize;
			}
			set_multiply_color(GameRamIt->playfield[side][block].color);
			draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);
			set_multiply_color(color_white);
		}
}

//background ----------------------------------------------------------------------------------------------------------------

void CGameRamIt_DrawBackground(CGameRamIt* GameRamIt)
{
	CImage_DrawImage( GameRamIt->background, 0, NULL, NULL);
	
}

//init - deinit ----------------------------------------------------------------------------------------------------------------

void CGameRamIt_LoadSound(CGameRamIt* GameRamIt)
{
	GameRamIt->SfxShoot = CAudio_LoadSound("ramit/shoot");
	GameRamIt->SfxHit = CAudio_LoadSound("ramit/hit");
	GameRamIt->SfxDie = CAudio_LoadSound("common/die");
	GameRamIt->SfxSucces = CAudio_LoadSound("common/succes");
	GameRamIt->MusMusic = CAudio_LoadMusic("ramit/music");
}

void CGameRamIt_UnLoadSound(CGameRamIt* GameRamIt)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GameRamIt->MusMusic);
	CAudio_UnLoadSound(GameRamIt->SfxShoot);
	CAudio_UnLoadSound(GameRamIt->SfxHit);
	CAudio_UnLoadSound(GameRamIt->SfxDie);
	CAudio_UnLoadSound(GameRamIt->SfxSucces);
}

void CGameRamIt_UnloadGraphics(CGameRamIt* GameRamIt)
{
	CImage_UnLoadImage(GameRamIt->background);
}

void CGameRamIt_LoadGraphics(CGameRamIt* GameRamIt)
{
	GameRamIt->background = CImage_LoadImage( "ramit/background.png");
}

void CGameRamIt_init(CGameRamIt* GameRamIt)
{
	CGameRamIt_LoadGraphics(GameRamIt);
	GameRamIt->bulletalive = false;
	GameRamIt->speed = CGameRamIt_ticksidle;
	GameRamIt->GameBase->level = 1;
	GameRamIt->playerdeath = false;
	GameRamIt->playerdeathtime = 0;
	CGameRamIt_createplayer(GameRamIt);
	CGameRamIt_createplayfield(GameRamIt);
	GameRamIt->GameBase->HealthPoints = 3;
	CGameRamIt_LoadSound(GameRamIt);
	CurrentGameMusicID = GameRamIt->MusMusic;
	CAudio_PlayMusic(GameRamIt->MusMusic, -1);
}

void CGameRamIt_deinit(CGameRamIt* GameRamIt)
{
	CGameRamIt_UnloadGraphics(GameRamIt);
	CGameRamIt_UnLoadSound(GameRamIt);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
}


//Update ----------------------------------------------------------------------------------------------------------------

void CGameRamIt_UpdateObjects(CGameRamIt* GameRamIt, bool IsGameState)
{
	if (IsGameState)
	{
		if (!GameRamIt->playerdeath)
		{
			CGameRamIt_updateplayer(GameRamIt);
			CGameRamIt_updateplayfield(GameRamIt, false);
			CGameRamIt_updatebullet(GameRamIt);
		}
		//don't handle death state immediatly after updating
		//otherwise it won't draw the last state hence the else
		else
		{
			if (GameRamIt->GameBase->HealthPoints > 1)
			{
				if (GameRamIt->playerdeathtime < getCurrentTimeMilliseconds())
				{
					if (GameMode == GMGame)
						GameRamIt->GameBase->HealthPoints -= 1;

					CGameRamIt_createplayfield(GameRamIt);
					GameRamIt->playerdeath = false;	
					SubGameState = SGReadyGo;
					SubStateTime = getCurrentTimeMilliseconds() + 500;
				}
			}
			else
				if (GameMode == GMGame)
					if (GameRamIt->GameBase->HealthPoints > 0)
						GameRamIt->GameBase->HealthPoints -= 1;
		}
	}
}

void CGameRamIt_UpdateLogic(CGameRamIt* GameRamIt)
{
	CGameBase_UpdateLogic(GameRamIt->GameBase);

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameRamIt_UpdateObjects(GameRamIt, SubGameState == SGGame);
	if(SubGameState == SGGame)
		CSprites_UpdateSprites();
}

bool CGameRamIt_DrawObjects(CGameRamIt* GameRamIt)
{
	CGameRamIt_drawbullet(GameRamIt);
	CGameRamIt_drawplayer(GameRamIt);
	CGameRamIt_drawplayfield(GameRamIt);
	//don't call drawsprites
	return false;
}


void CGameRamIt_Draw(CGameRamIt* GameRamIt)
{
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameRamIt_DrawBackground(GameRamIt);
	if (CGameRamIt_DrawObjects(GameRamIt))
		CSprites_DrawSprites();
	CGameBase_DrawScoreBar(GameRamIt->GameBase);
	CGameBase_DrawSubstateText(GameRamIt->GameBase);
}

#endif