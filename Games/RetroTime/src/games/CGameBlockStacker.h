#ifndef CGAMEBLOCKSTACKER_H
#define CGAMEBLOCKSTACKER_H

#include "CGameBase.h"
#include "../Common.h"
#include "../SDL_HelperTypes.h"
#include "BlockStackerBlocks.h"
#include "../CGame.h"
#include "../Vec2F.h"
#include "../SDL_HelperTypes.h"
#include "../libs/DrawPrimitives/draw_primitives.h"

#define CGameBlockStacker_numcols 12
#define CGameBlockStacker_numrows 18
#define CGameBlockStacker_blocksize ((ScreenHeight - ScoreBarHeight) / CGameBlockStacker_numrows)
#define CGameBlockStacker_ticksidle 2
#define CGameBlockStacker_ticksinputidle 4
#define CGameBlockStacker_totalelements (CGameBlockStacker_numcols * CGameBlockStacker_numrows)


struct CGameBlockStacker {
	CGameBase *GameBase;
	int background;
	int[CGameBlockStacker_totalelements] playfield;
	int currpiece, rotation,speed, speedcount, piececount, lineclear, plrx, plry;
	bool rotateblock, dropblock;
	int MusMusic, SfxDie, SfxLineClear, SfxDrop, SfxRotate;
};

CGameBlockStacker* Create_CGameBlockStacker()
{
	CSprites_SetSpriteMax(0);
	CGameBlockStacker* BlockStacker = (CGameBlockStacker*) malloc(sizeof(CGameBlockStacker));
	BlockStacker->GameBase = Create_CGameBase(GSTetris, true);

	BlockStacker->MusMusic = -1;
	BlockStacker->SfxDie = -1;
	BlockStacker->SfxLineClear = -1;
	BlockStacker->SfxDrop = -1;
	BlockStacker->SfxRotate = -1;
	BlockStacker->GameBase->playfieldwidth = CGameBlockStacker_numcols * CGameBlockStacker_blocksize;
	BlockStacker->GameBase->playfieldheight = CGameBlockStacker_numrows * CGameBlockStacker_blocksize;
	BlockStacker->GameBase->screenleft = (ScreenWidth - BlockStacker->GameBase->playfieldwidth) / 2;
	BlockStacker->GameBase->screenright = BlockStacker->GameBase->screenleft + BlockStacker->GameBase->playfieldwidth;
	BlockStacker->GameBase->screentop = ScoreBarHeight+ (ScreenHeight - BlockStacker->GameBase->playfieldheight -2*CGameBlockStacker_blocksize) / 2;
	BlockStacker->GameBase->screenbottom = BlockStacker->GameBase->screentop + BlockStacker->GameBase->playfieldheight;

	return BlockStacker;
}

void Destroy_CGameBlockStacker(CGameBlockStacker* BlockStacker)
{
	CSprites_SetSpriteMax(0);
	Destroy_CGameBase(BlockStacker->GameBase);
	free(BlockStacker);
	BlockStacker = NULL;
}

//helper funcs ----------------------------------------------------------------------------------------------------------------

bool CGameBlockStacker_piecefits(CGameBlockStacker* BlockStacker, int tetrimo, int rotation, int posx, int posy)
{
	bool result = true;
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			int piece = y * 4 + x;
			int field = (posy + y) * CGameBlockStacker_numcols + posx + x;

			if ((posx + x >= 0) && (posx + x < CGameBlockStacker_numcols) &&
				(posy + y >= 0) && (posy + y < CGameBlockStacker_numrows) &&
				(tstetrimos[tetrimo][rotation % 4][piece] && (BlockStacker->playfield[field] != -1)))
			{
				result = false;
				break;
			}
		}
		if (!result)
			break;
	}
	return result;
}

//player ----------------------------------------------------------------------------------------------------------------

void CGameBlockStacker_updateplayer(CGameBlockStacker* BlockStacker)
{
	if (gamepad_left() > 0)
		if (CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation, BlockStacker->plrx - 1, BlockStacker->plry))
			BlockStacker->plrx -= 1;

	if (gamepad_right() > 0)
		if (CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation, BlockStacker->plrx + 1, BlockStacker->plry))
			BlockStacker->plrx += 1;

	if (gamepad_down() > 0)
		if (CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation, BlockStacker->plrx, BlockStacker->plry + 1))
			BlockStacker->plry += 1;

	if (gamepad_button_a() > 0)
	{
		if (BlockStacker->rotateblock && CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation +1, BlockStacker->plrx, BlockStacker->plry))
		{
			CAudio_PlaySound(BlockStacker->SfxRotate, 0);
			BlockStacker->rotation += 1;
			BlockStacker->rotateblock = false;
		}
	}
	else
		BlockStacker->rotateblock = true;

	if (gamepad_button_x() > 0)
	{
		if (BlockStacker->dropblock)
		{
			while (CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation, BlockStacker->plrx, BlockStacker->plry +1))
				BlockStacker->plry += 1;
			BlockStacker->dropblock = false;
			BlockStacker->speedcount = 10000;
		}
	}
	else
		BlockStacker->dropblock = true;
}

//playfield ----------------------------------------------------------------------------------------------------------------

void CGameBlockStacker_createplayfield(CGameBlockStacker* BlockStacker)
{
	for(int y = 0; y < CGameBlockStacker_numrows; y++)
		for(int x = 0; x < CGameBlockStacker_numcols; x++)
			if ((x == 0) || (x == CGameBlockStacker_numcols -1) || (y == CGameBlockStacker_numrows -1))
				BlockStacker->playfield[y*CGameBlockStacker_numcols +x] = -2;
			else
				BlockStacker->playfield[y*CGameBlockStacker_numcols +x] = -1;
}

void CGameBlockStacker_updateplayfield(CGameBlockStacker* BlockStacker, bool force)
{

	if (BlockStacker->lineclear > -1)
	{
		BlockStacker->lineclear -= 1;

		if (BlockStacker->lineclear == 0)
		{
			int y = CGameBlockStacker_numrows -2;
			while(y > 0)
			{
				if(BlockStacker->playfield[y * CGameBlockStacker_numcols + 1] == -3)
				{
					int y2 = y;
					//set all rows equal to row above
					while (y2 > 0)
					{
						for(int x = 1; x < CGameBlockStacker_numcols -1; x++)
							BlockStacker->playfield[y2 * CGameBlockStacker_numcols + x] = BlockStacker->playfield[(y2 -1) * CGameBlockStacker_numcols + x];
						y2 -= 1;
					}
					//clear top row
					for(int x = 1; x < CGameBlockStacker_numcols -1; x++)
						BlockStacker->playfield[x] = -1;
					y += 1;
				}
				y -=1;
			}
		}
	}
	else
	{
		BlockStacker->speedcount += 1;

		if (BlockStacker->speedcount % CGameBlockStacker_ticksinputidle == 0)
			CGameBlockStacker_updateplayer(BlockStacker);

		if (force || (BlockStacker->speedcount >= BlockStacker->speed*CGameBlockStacker_ticksidle))
		{
			BlockStacker->speedcount = 0;
			BlockStacker->piececount += 1;
			//level increase
			if (BlockStacker->piececount % 40 == 0)
				if (BlockStacker->speed >= 5)
				{
					BlockStacker->speed -= 1;
					BlockStacker->GameBase->level += 1;
				}

			//can we move the piece down ?
			if (CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation, BlockStacker->plrx, BlockStacker->plry +1))
				BlockStacker->plry += 1;
			else
			{
				if(!force)
					CAudio_PlaySound(BlockStacker->SfxDrop, 0);


				//lock it in place
				for(int x = 0; x < 4; x++)
					for(int y = 0; y < 4; y++)
					{
						int piece = y * 4 + x;
						if (tstetrimos[BlockStacker->currpiece][BlockStacker->rotation % 4][piece])
							BlockStacker->playfield[(BlockStacker->plry + y) * CGameBlockStacker_numcols + BlockStacker->plrx + x] = BlockStacker->currpiece;
					}

				//check for lines
				int numlines = 0;
				bool linedone = true;
				for(int y = 0; y < 4; y++)
				{
					if (BlockStacker->plry + y < CGameBlockStacker_numrows -1)
					{
						linedone = true;
						for(int x = 1; x < CGameBlockStacker_numcols -1; x++)
							linedone = linedone && (BlockStacker->playfield[(BlockStacker->plry + y) * CGameBlockStacker_numcols + x] > -1);

						if (linedone)
						{
							numlines += 1;
							for(int x = 1; x < CGameBlockStacker_numcols -1; x++)
								BlockStacker->playfield[(BlockStacker->plry + y) * CGameBlockStacker_numcols + x] = -3;
						}
					}
				}
				CGame_AddToScore(7);

				if (numlines > 0)
				{
					CGame_AddToScore((1 << numlines) * 20);
					BlockStacker->lineclear = 30;
					CAudio_PlaySound(BlockStacker->SfxLineClear, 0);
				}

				BlockStacker->plrx = CGameBlockStacker_numcols / 2 -2;
				BlockStacker->plry = 0;
				BlockStacker->rotation = 0;
				BlockStacker->currpiece = rand() % 7;

				if (!CGameBlockStacker_piecefits(BlockStacker, BlockStacker->currpiece, BlockStacker->rotation, BlockStacker->plrx, BlockStacker->plry))
				{
					CAudio_PlaySound(BlockStacker->SfxDie, 0);
					if(GameMode == GMGame)
					{
						BlockStacker->GameBase->HealthPoints -= 1;
						if (BlockStacker->GameBase->HealthPoints > 0)
						{
							CGameBlockStacker_createplayfield(BlockStacker);
							SubGameState = SGReadyGo;
							SubStateTime = getCurrentTimeMilliseconds() + 500;
						}
					}
					else
					{
						CGame_AddToScore(-250);
						CGameBlockStacker_createplayfield(BlockStacker);
						SubGameState = SGReadyGo;
						SubStateTime = getCurrentTimeMilliseconds() + 500;
					}
				}
			}
		}
	}
}

void CGameBlockStacker_drawplayfieldcell(CGameBlockStacker* BlockStacker, int x, int y, int piece)
{
	int color = color_white;

	if (piece != -1)
	{
		if(piece == 0)
			color = make_color_rgba(0x65, 0x65, 0xFF, 0xFF);

		if (piece == 1)
			color = make_color_rgba(0xFF, 0xFF, 0x65, 0xFF);

		if (piece == 2)
			color = make_color_rgba(0x30, 0xFF, 0x65, 0xFF);

		if (piece == 3)
			color = make_color_rgba(0xFF, 0x65, 0x65, 0xFF);

		if (piece == 4)
			color = make_color_rgba(0xA0, 0x40, 0xF0, 0xFF);

		if (piece == 5)
			color = make_color_rgba(0xA5, 0x3A, 0x3A, 0xFF);

		if (piece == 6)
			color = make_color_rgba(0xFF, 0x65, 0xFF, 0xFF);

		if (piece == -2)
			color = color_gray;

		if (piece == -3)
			color = color_white;

		SDL_Rect r = {BlockStacker->GameBase->screenleft + x * CGameBlockStacker_blocksize, BlockStacker->GameBase->screentop + y * CGameBlockStacker_blocksize, BlockStacker->GameBase->screenleft + x * CGameBlockStacker_blocksize +CGameBlockStacker_blocksize, BlockStacker->GameBase->screentop + y * CGameBlockStacker_blocksize + CGameBlockStacker_blocksize};
		set_multiply_color(color_black);
		draw_filled_rectangle(r.x, r.y, r.w, r.h);

		r.x = BlockStacker->GameBase->screenleft +1 + x * CGameBlockStacker_blocksize;
		r.y = BlockStacker->GameBase->screentop +1 + y * CGameBlockStacker_blocksize;
		r.w = CGameBlockStacker_blocksize-2;
		r.h = CGameBlockStacker_blocksize-2;
		set_multiply_color(color);
		draw_filled_rectangle(r.x, r.y, r.x +  r.w, r.y + r.h);
		set_multiply_color(color_white);
	}
}

void CGameBlockStacker_drawplayfield(CGameBlockStacker* BlockStacker)
{
	for(int x = 0; x < CGameBlockStacker_numcols; x++)
		for(int y = 0; y < CGameBlockStacker_numrows; y++)
		{
			int piece = BlockStacker->playfield[y * CGameBlockStacker_numcols + x];
			CGameBlockStacker_drawplayfieldcell(BlockStacker,x,y, piece);
		}

	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
		{
			int piece = y * 4 + x;
			if(tstetrimos[BlockStacker->currpiece][BlockStacker->rotation % 4][piece])
				CGameBlockStacker_drawplayfieldcell(BlockStacker,BlockStacker->plrx + x, BlockStacker->plry + y, BlockStacker->currpiece);

		}
}

//Drawing ----------------------------------------------------------------------------------------------------------------

void CGameBlockStacker_DrawBackground(CGameBlockStacker* BlockStacker)
{
	CImage_DrawImage(BlockStacker->background,0, NULL, NULL);
}

//init - deinit ----------------------------------------------------------------------------------------------------------------


void CGameBlockStacker_LoadGraphics(CGameBlockStacker* BlockStacker)
{
	BlockStacker->background = CImage_LoadImage("blockstacker/background.png");
}

void CGameBlockStacker_UnloadGraphics(CGameBlockStacker* BlockStacker)
{
	CImage_UnLoadImage(BlockStacker->background);
}

void CGameBlockStacker_LoadSound(CGameBlockStacker* BlockStacker)
{
	BlockStacker->SfxLineClear = CAudio_LoadSound("blockstacker/lineclear");
	BlockStacker->SfxDrop = CAudio_LoadSound("blockstacker/drop");
	BlockStacker->SfxRotate = CAudio_LoadSound("blockstacker/rotate");
	BlockStacker->MusMusic = CAudio_LoadMusic("blockstacker/music");
	BlockStacker->SfxDie = CAudio_LoadSound("common/die");
}

void CGameBlockStacker_UnLoadSound(CGameBlockStacker* BlockStacker)
{
	CAudio_StopMusic();
	CAudio_UnLoadMusic(BlockStacker->MusMusic);
	CAudio_UnLoadSound(BlockStacker->SfxLineClear);
	CAudio_UnLoadSound(BlockStacker->SfxDrop);
	CAudio_UnLoadSound(BlockStacker->SfxRotate);
	CAudio_UnLoadSound(BlockStacker->SfxDie);
}

void CGameBlockStacker_deinit(CGameBlockStacker* BlockStacker)
{
	CGameBlockStacker_UnLoadSound(BlockStacker);
	SubStateCounter = 0;
	SubGameState = SGNone;
	CurrentGameMusicID = -1;
	CGameBlockStacker_UnloadGraphics(BlockStacker);
}

void CGameBlockStacker_init(CGameBlockStacker* BlockStacker)
{
	CGameBlockStacker_LoadGraphics(BlockStacker);
	CGameBlockStacker_LoadSound(BlockStacker);
	CurrentGameMusicID = BlockStacker->MusMusic;
	CAudio_PlayMusic(BlockStacker->MusMusic, -1);
	BlockStacker->GameBase->HealthPoints = 1;
	BlockStacker->currpiece = rand() % 7;
	BlockStacker->rotation = 0;
	BlockStacker->plrx = CGameBlockStacker_numcols / 2 -2;
	BlockStacker->plry = 0;
	BlockStacker->speed = 20;
	BlockStacker->speedcount = 0;
	BlockStacker->piececount = 0;
	BlockStacker->rotateblock = true;
	BlockStacker->dropblock = true;
	BlockStacker->GameBase->level = 1;
	BlockStacker->lineclear = 0;
	CGameBlockStacker_createplayfield(BlockStacker);
}


//Update ----------------------------------------------------------------------------------------------------------------

void CGameBlockStacker_UpdateObjects(CGameBlockStacker* BlockStacker, bool IsGameState)
{
	if(IsGameState)
		CGameBlockStacker_updateplayfield(BlockStacker,false);
}

void CGameBlockStacker_UpdateLogic(CGameBlockStacker* BlockStacker)
{
	CGameBase_UpdateLogic(BlockStacker->GameBase);
	
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameBlockStacker_UpdateObjects(BlockStacker, SubGameState == SGGame);
	if(SubGameState == SGGame)
		CSprites_UpdateSprites();
}


bool CGameBlockStacker_DrawObjects(CGameBlockStacker* BlockStacker)
{
	CGameBlockStacker_drawplayfield(BlockStacker);
	//don't call drawsprites
	return false;
}

void CGameBlockStacker_Draw(CGameBlockStacker* BlockStacker)
{
	if ((GameState == GSTitleScreenInit) || (SubGameState == SGPauseMenu) || (SubGameState == SGFrame) || (SubGameState == SGGameHelp))
		return;

	CGameBlockStacker_DrawBackground(BlockStacker);
	if (CGameBlockStacker_DrawObjects(BlockStacker))
		CSprites_DrawSprites();
	CGameBase_DrawScoreBar(BlockStacker->GameBase);
	CGameBase_DrawSubstateText(BlockStacker->GameBase);
}

#endif