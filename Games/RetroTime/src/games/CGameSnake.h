#ifndef CGAMESNAKE_H
#define CGAMESNAKE_H

#include "CGameBase.h"
#include "../Common.h"
#include "../SDL_HelperTypes.h"
#include "../CGame.h"
#include "../libs/DrawPrimitives/draw_primitives.h"

//floor(35 * yscale)
#define CGameSnake_snakesize 18
#define CGameSnake_rows (int)((ScreenHeight / CGameSnake_snakesize) -4)
#define CGameSnake_cols (int)((ScreenWidth / CGameSnake_snakesize) -3)
#define CGameSnake_updateticks 8 
//rows*cols
#define CGameSnake_totalcells (CGameSnake_rows * CGameSnake_cols)

struct CGameSnake {

	CGameBase *GameBase;
	int snakeheadcolor;
	int snakebodycolor;
	int snakefoodcolor;

	int background;

	bool movedone;
	int snakelength;
	int ticks;
	SDL_Point head;
	SDL_Point[CGameSnake_totalcells] body;
	SDL_Point dir;
	SDL_Point food;
	int playerdeathtime;
	int playerdeath;
	int MusMusic, SfxFood, SfxDie;
};

CGameSnake* Create_CGameSnake()
{
	CSprites_SetSpriteMax(0);
	CGameSnake* GameSnake = (CGameSnake*) malloc(sizeof(CGameSnake));
	GameSnake->GameBase = Create_CGameBase(GSSnake, false);
	GameSnake->MusMusic = -1;
	GameSnake->SfxFood = -1;
	GameSnake->SfxDie = -1;
	GameSnake->playerdeathtime = 0;
	GameSnake->GameBase->playfieldwidth = (CGameSnake_cols) * CGameSnake_snakesize;
	GameSnake->GameBase->playfieldheight = (CGameSnake_rows) * CGameSnake_snakesize;
	GameSnake->GameBase->screenleft = (ScreenWidth - GameSnake->GameBase->playfieldwidth) / 2;
	GameSnake->GameBase->screenright = GameSnake->GameBase->screenleft + GameSnake->GameBase->playfieldwidth;
	GameSnake->GameBase->screentop = (ScreenHeight - GameSnake->GameBase->playfieldheight + ScoreBarHeight) / 2;
	GameSnake->GameBase->screenbottom = GameSnake->GameBase->screentop + GameSnake->GameBase->playfieldheight;
	GameSnake->snakeheadcolor = color_red;

	GameSnake->snakebodycolor = color_white;

	GameSnake->snakefoodcolor = color_green;

	return GameSnake;
}

void Destroy_CGameSnake(CGameSnake* GameSnake)
{
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(GameSnake->GameBase);
	free(GameSnake);
	GameSnake = NULL;
}

//GameSnake->food ----------------------------------------------------------------------------------------------------------------

void CGameSnake_createfood(CGameSnake* GameSnake)
{
	srand(getCurrentTimeMilliseconds());
	bool bok = false;
	while (!bok)
	{
		GameSnake->food.x = GameSnake->GameBase->screenleft + (int)((rand() % CGameSnake_cols) * CGameSnake_snakesize);
		GameSnake->food.y = GameSnake->GameBase->screentop + (int)((rand() % CGameSnake_rows) * CGameSnake_snakesize);
		bok = !((GameSnake->food.x == GameSnake->head.x) && (GameSnake->food.y == GameSnake->head.y));
		for (int i = 0; i < GameSnake->snakelength; i++)
		{
			bok = bok && !((GameSnake->food.x == GameSnake->body[i].x) && (GameSnake->food.y == GameSnake->body[i].y));
			if (!bok)
				break;
		}
	}
}

void CGameSnake_drawfood(CGameSnake* GameSnake)
{
	SDL_Rect r = {GameSnake->food.x, GameSnake->food.y, CGameSnake_snakesize, CGameSnake_snakesize};
	set_multiply_color(GameSnake->snakefoodcolor);
	draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);
	set_multiply_color(color_white);
}

void CGameSnake_updatefood(CGameSnake* GameSnake)
{
	if ((GameSnake->head.x == GameSnake->food.x) && (GameSnake->head.y == GameSnake->food.y))
	{
		CAudio_PlaySound(GameSnake->SfxFood, 0);
		GameSnake->snakelength += 1;
		CGameSnake_createfood(GameSnake);
		CGame_AddToScore(GameSnake->snakelength*2);
	}
}

//snake ----------------------------------------------------------------------------------------------------------------

void CGameSnake_createsnake(CGameSnake* GameSnake)
{
	GameSnake->playerdeath = false;
	GameSnake->playerdeathtime = 0;
	GameSnake->snakelength = 0;
	GameSnake->head.x = GameSnake->GameBase->screenleft + ((int)(floor(CGameSnake_cols / 2))) * CGameSnake_snakesize;
	GameSnake->head.y = GameSnake->GameBase->screentop + ((int)(floor(CGameSnake_rows / 2))) * CGameSnake_snakesize;
	GameSnake->dir.x = 1;
	GameSnake->dir.y = 0;
	GameSnake->ticks = 0;
}

void CGameSnake_drawsnake(CGameSnake* GameSnake)
{
	SDL_Rect r;
	set_multiply_color(GameSnake->snakebodycolor);
	for (int i = 0; i < GameSnake->snakelength; i++)
	{
		r.x = GameSnake->body[i].x;
		r.y = GameSnake->body[i].y;
		r.w = CGameSnake_snakesize;
		r.h = CGameSnake_snakesize;
		draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);
	}
	set_multiply_color(GameSnake->snakeheadcolor);
	r.x = GameSnake->head.x;
	r.y = GameSnake->head.y;
	r.w = CGameSnake_snakesize;
	r.h = CGameSnake_snakesize;
	draw_filled_rectangle(r.x, r.y, r.x + r.w, r.y + r.h);
	set_multiply_color(color_white);
}

void CGameSnake_updatesnake(CGameSnake* GameSnake)
{
	if (gamepad_left() > 0)
	{
		if(GameSnake->movedone && GameSnake->dir.x == 0)
		{
			GameSnake->movedone = false;
			GameSnake->dir.x = -1;
			GameSnake->dir.y = 0;
		}
	}
	else
	{
		if (gamepad_right() > 0)
		{
			if(GameSnake->movedone && GameSnake->dir.x == 0)
			{
				GameSnake->movedone = false;
				GameSnake->dir.x = 1;
				GameSnake->dir.y = 0;
			}
		}
		else
		{
			if (gamepad_up() > 0)
			{
				if(GameSnake->movedone && GameSnake->dir.y == 0)
				{
					GameSnake->movedone = false;
					GameSnake->dir.x = 0;
					GameSnake->dir.y = -1;
				}
			}
			else
			{
				if (gamepad_down() > 0)
				{
					if(GameSnake->movedone && GameSnake->dir.y == 0)
					{
						GameSnake->movedone = false;
						GameSnake->dir.x = 0;
						GameSnake->dir.y = 1;
					}
				}
			}
		}
	}

	GameSnake->ticks += 1;

	if(GameSnake->ticks >= CGameSnake_updateticks)
	{
		GameSnake->movedone = true;
		GameSnake->ticks = 0;
		int i = GameSnake->snakelength;
		while (i >= 1)
		{
			GameSnake->body[i] = GameSnake->body[i-1];
			i -= 1;
		}
		GameSnake->body[0] = GameSnake->head;
		GameSnake->head.x += GameSnake->dir.x * CGameSnake_snakesize;
		GameSnake->head.y += GameSnake->dir.y * CGameSnake_snakesize;
		if ((GameSnake->head.x < GameSnake->GameBase->screenleft) || (GameSnake->head.x >= GameSnake->GameBase->screenright) ||
			(GameSnake->head.y < GameSnake->GameBase->screentop) || (GameSnake->head.y >= GameSnake->GameBase->screenbottom))
		{
			if(!GameSnake->playerdeath)
			{
				GameSnake->playerdeath = true;
				CAudio_PlaySound(GameSnake->SfxDie, 0);
				if (!(GameMode == GMGame))
					CGame_AddToScore(-50);
				GameSnake->playerdeathtime = getCurrentTimeMilliseconds() + 500;
			}
		}

		for (int i = 0; i < GameSnake->snakelength; i++)
			if ((GameSnake->head.x == GameSnake->body[i].x) && (GameSnake->head.y == GameSnake->body[i].y))
			{
				if(!GameSnake->playerdeath)
				{
					GameSnake->playerdeath = true;
					GameSnake->playerdeathtime = getCurrentTimeMilliseconds() + 500;
				}
			}
	}
}

//background ----------------------------------------------------------------------------------------------------------------

void CGameSnake_DrawBackground(CGameSnake* GameSnake)
{
	CImage_DrawImage(GameSnake->background, 0, NULL, NULL);
}

//init - deinit ----------------------------------------------------------------------------------------------------------------

void CGameSnake_LoadSound(CGameSnake* GameSnake)
{
	GameSnake->SfxFood = CAudio_LoadSound("snakey/food");
	GameSnake->SfxDie = CAudio_LoadSound("common/die");
	GameSnake->MusMusic = CAudio_LoadMusic("snakey/music");
}

void CGameSnake_UnLoadSound(CGameSnake* GameSnake)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(GameSnake->MusMusic);
	CAudio_UnLoadSound(GameSnake->SfxFood);
	CAudio_UnLoadSound(GameSnake->SfxDie);
}

void CGameSnake_UnloadGraphics(CGameSnake* GameSnake)
{
	CImage_UnLoadImage(GameSnake->background);
}

void CGameSnake_LoadGraphics(CGameSnake* GameSnake)
{
	GameSnake->background = CImage_LoadImage( "snakey/background.png");
}

void CGameSnake_init(CGameSnake* GameSnake)
{
	CGameSnake_LoadGraphics(GameSnake);
	CGameSnake_createsnake(GameSnake);
	CGameSnake_createfood(GameSnake);

	GameSnake->movedone = true;
	GameSnake->GameBase->HealthPoints = 2;
	CGameSnake_LoadSound(GameSnake);
	CurrentGameMusicID = GameSnake->MusMusic;
	CAudio_PlayMusic(GameSnake->MusMusic, -1);
}

void CGameSnake_deinit(CGameSnake* GameSnake)
{
	CGameSnake_UnLoadSound(GameSnake);
	CGameSnake_UnloadGraphics(GameSnake);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
}

//Update ----------------------------------------------------------------------------------------------------------------

void CGameSnake_UpdateObjects(CGameSnake* GameSnake, bool IsGameState)
{
	if (IsGameState && ! GameSnake->playerdeath)
	{
		CGameSnake_updatesnake(GameSnake);
		CGameSnake_updatefood(GameSnake);
	}
	else
		if (IsGameState)
		{
			if (GameSnake->GameBase->HealthPoints > 1)
			{
				if (GameSnake->playerdeathtime < getCurrentTimeMilliseconds())
				{
					CGameSnake_createsnake(GameSnake);
					CGameSnake_createfood(GameSnake);
					if (GameMode == GMGame)
						GameSnake->GameBase->HealthPoints -= 1;
					SubGameState = SGReadyGo;
					SubStateTime = getCurrentTimeMilliseconds() + 500;
				}
			}
			else
				if(GameMode == GMGame)
					if (GameSnake->GameBase->HealthPoints > 0)
						GameSnake->GameBase->HealthPoints -= 1;
		}
}

void CGameSnake_UpdateLogic(CGameSnake* GameSnake)
{
	CGameBase_UpdateLogic(GameSnake->GameBase);

	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameSnake_UpdateObjects(GameSnake, SubGameState == SGGame);
	if(SubGameState == SGGame)
		CSprites_UpdateSprites();
}


bool CGameSnake_DrawObjects(CGameSnake* GameSnake)
{
	CGameSnake_drawfood(GameSnake);
	CGameSnake_drawsnake(GameSnake);
	//don't call drawsprites in base object
	return false;
}

void CGameSnake_Draw(CGameSnake* GameSnake)
{
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameSnake_DrawBackground(GameSnake);
	if (CGameSnake_DrawObjects(GameSnake))
		CSprites_DrawSprites();
	CGameBase_DrawScoreBar(GameSnake->GameBase);
	CGameBase_DrawSubstateText(GameSnake->GameBase);
}

#endif