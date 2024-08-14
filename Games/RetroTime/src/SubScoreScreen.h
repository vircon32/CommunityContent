#ifndef SUBSCORESCREEN_H
#define SUBSCORESCREEN_H

#include "string.h"
#include "CGame.h"
#include "games/CGameBase.h"
#include "Common.h"
#include "SubScoreScreen.h"
#include "Vec2F.h"
#include "games/CGameBlockStacker.h"
#include "games/CGameFastEddy.h"
#include "games/CGameFrog.h"
#include "games/CGameBreakOut.h"
#include "games/CGameInvaders.h"
#include "games/CGamePang.h"
#include "games/CGameRamIt.h"
#include "games/CGameSnake.h"
#include "SDL_HelperTypes.h"
#include "GamesShare.h"

bool wasnewhighscorecarousel;
bool wasnewhighscoregame;
int prevretrocarouselscore;
int view = 0;

void DeInitSubScoreScreen()
{
}

void InitSubScoreScreen()
{
	SubGameState = SGFrame;
	SubStateCounter = 0;
	view = 0;
	wasnewhighscorecarousel = false;
	wasnewhighscoregame = false;
	prevretrocarouselscore = RetroCarouselScore;
	if (GameMode == GMRetroCarousel)
		RetroCarouselScore += Scores[Game][GameMode];

	if (RetroCarouselScore > RetroCarouselHighScore)
	{
		RetroCarouselHighScore = RetroCarouselScore;
		wasnewhighscorecarousel = true;
	}

	if (Scores[Game][GameMode] > HighScores[Game][GameMode])
	{
		HighScores[Game][GameMode] = Scores[Game][GameMode];
		wasnewhighscoregame = true;
	}

	//savehighscoresoptions()
	CAudio_PlaySound(SfxScore, 0);
}

bool SubScoreScreen()
{
	bool result = false;
	if (GameState == GSSubScoreInit)
	{
		InitSubScoreScreen();
		GameState -= initDiff;
	}

	switch (ActiveGameGameStateId)
	{
	case GSSnake:
		CGameSnake_Draw(GameSnake);
		break;
	case GSRamIt:
		CGameRamIt_Draw(GameRamIt);
		break;
	case GSPang:
		CGamePang_Draw(GamePang);
		break;
	case GSSpaceInvaders:
		CGameInvaders_Draw(GameInvaders);
		break;
	case GSEddy:
		CGameFastEddy_Draw(GameFastEddy);
		break;
	case GSBreakout:
		CGameBreakOut_Draw(GameBreakOut);
		break;
	case GSFrog:
		CGameFrog_Draw(GameFrog);
		break;
	case GSTetris:
		CGameBlockStacker_Draw(GameBlockStacker);
		break;
	}

	if (SubGameState == SGFrame)
	{
		if (SubStateCounter < 7.6 *yscale)
			SubStateCounter += 0.1;
		else
		{
			SubGameState = SGCalcScore;
			SubStateCounter =  7.6 *yscale;
		}
	}

	SDL_Point pos = { ScreenWidth / 2, ScreenHeight / 2 };
	Vec2F Scale = { 2.5 * xscale * SubStateCounter / (7.6*yscale) , SubStateCounter};
	CImage_DrawImageFuze(GFXFrameID, 0, true, pos.x, pos.y, 0, Scale.x, Scale.y, 1.0, 1.0, 1.0, 1.0);
	int[1000] TextTmp;
	int[10] Nr;
	int* PTextTmp;

	SDL_Point *MedalTz = CImage_ImageSize(GFXMedal);
	Vec2F MedalScale = { 50.0 / MedalTz->y * xscale, 50.0 / MedalTz->y * yscale };
	free(MedalTz);
	if (SubGameState == SGCalcScore)
	{
		if ((Game == Games - 1) && (GameMode == GMRetroCarousel))
		{
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Final Results");
			int Texw = CFont_TextWidth("Roboto-Regular", (int)(80.0 * yscale), TextTmp);
			CFont_WriteText("Roboto-Regular", (int)(80.0 * yscale), TextTmp, (int)((ScreenWidth - Texw) / 2.0), (int)(50.0 * yscale), color_white);
			
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "-------------------------");
			Texw = CFont_TextWidth("Roboto-Regular", (int)(80.0 * yscale), TextTmp);
			CFont_WriteText("Roboto-Regular", (int)(80.0 * yscale), TextTmp, (int)((ScreenWidth - Texw) / 2.0), (int)(85.0 * yscale), color_white);
		}
		else
		{
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Results");
			int Texw = CFont_TextWidth("Roboto-Regular", (int)(80.0 * yscale), TextTmp);
			CFont_WriteText("Roboto-Regular", (int)(80.0 * yscale), TextTmp, (int)((ScreenWidth - Texw) / 2.0), (int)(50.0 * yscale), color_white);
			
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "----------------");
			Texw = CFont_TextWidth("Roboto-Regular", (int)(80.0 * yscale), TextTmp);
			CFont_WriteText("Roboto-Regular", (int)(80.0 * yscale), TextTmp, (int)((ScreenWidth - Texw) / 2.0), (int)(85.0 * yscale), color_white);
		}


		PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Game: ");
		PTextTmp = faststrcat(PTextTmp, GSGames[Game].name);
		CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(180.0 * yscale), color_white);
		
		PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Game Mode: ");
		PTextTmp = faststrcat(PTextTmp, GMModes[GameMode].name);
		CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(225.0 * yscale), color_white);
		
		if (GameMode == GMRetroCarousel)
		{
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Previous Rounds Score: ");
			itoa(prevretrocarouselscore, Nr, 10);
			PTextTmp = faststrcat(PTextTmp, Nr);
			CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(285.0 * yscale), color_white);
			
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Game Score: ");
			itoa(Scores[Game][GameMode], Nr, 10);
			PTextTmp = faststrcat(PTextTmp, Nr);
			CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(330.0 * yscale), color_white);
			

			if (Game < Games - 1)
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "New Total Rounds Score: ");
				itoa(RetroCarouselScore, Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
			}
			else
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Final Total Rounds Score: ");
				itoa(RetroCarouselScore, Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
			}
			CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(375.0 * yscale), color_white);

			if (wasnewhighscoregame)
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "New Game High Score: ");
				itoa(HighScores[Game][GameMode], Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(425.0 * yscale), color_white);
				
				SDL_Point pos = { (int)(120.0 * xscale),(int)(425.0 * yscale) };
				CImage_DrawImageFuze(GFXMedal,0, false, pos.x, pos.y, 0, MedalScale.x, MedalScale.y, 1.0, 1.0, 1.0, 1.0);
			}
			else
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Game High Score: ");
				itoa(HighScores[Game][GameMode], Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(425.0 * yscale), color_white);
			}

			if (wasnewhighscorecarousel)
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "New All Rounds High Score: ");
				itoa(RetroCarouselHighScore, Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(470.0 * yscale), color_white);
				
				SDL_Point pos = { (int)(120.0 * xscale),(int)(470.0 * yscale) };
				CImage_DrawImageFuze(GFXMedal, 0, false, pos.x,pos.y, 0, MedalScale.x,MedalScale.y, 1.0, 1.0, 1.0, 1.0);
			}
			else
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "All Rounds High Score: ");
				itoa(RetroCarouselHighScore, Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(470.0 * yscale), color_white);
			}

			if (Game < Games - 1)
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Press (A) for next game: ");
				PTextTmp = faststrcat(PTextTmp, GSGames[Game + 1].name);
			}
			else
			{
				PTextTmp = TextTmp; 
				*PTextTmp = 0; 
				PTextTmp = faststrcat(PTextTmp, "Press (A) for titlescreen");
			}

			int Texw = CFont_TextWidth("Roboto-Regular", (int)(34.0 * yscale), TextTmp);
			CFont_WriteText("Roboto-Regular", (int)(34.0 * yscale), TextTmp, (int)((ScreenWidth - Texw) / 2.0), (int)(630.0 * yscale), color_white);			
		}
		else
		{
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Game Score: ");
			itoa(Scores[Game][GameMode], Nr, 10);
			PTextTmp = faststrcat(PTextTmp, Nr);
			CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(285.0 * yscale), color_white);
			
			if (wasnewhighscoregame)
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "New Game High Score: ");
				itoa(HighScores[Game][GameMode], Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(330.0 * yscale), color_white);
				

				SDL_Point pos = { (int)(120.0 * xscale),(int)(330.0 * yscale) };
				CImage_DrawImageFuze(GFXMedal,0, false, pos.x, pos.y, 0, MedalScale.x,MedalScale.y, 1.0, 1.0, 1.0, 1.0);
			}
			else
			{
				PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Game High Score: ");
				itoa(HighScores[Game][GameMode], Nr, 10);
				PTextTmp = faststrcat(PTextTmp, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), TextTmp, (int)(150.0 * xscale), (int)(330.0 * yscale), color_white);
			}
			PTextTmp = TextTmp; *PTextTmp = 0; PTextTmp = faststrcat(PTextTmp, "Press (A) for titlescreen");
			int Texw = CFont_TextWidth("Roboto-Regular", (int)(34.0 * yscale), TextTmp);
			CFont_WriteText("Roboto-Regular", (int)(34.0 * yscale), TextTmp, (int)((ScreenWidth - Texw) / 2.0), (int)(630.0 * yscale), color_white);
		}
	
	}


	if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1) || (gamepad_button_start() == 1))
	{
		CAudio_PlaySound(SfxSelect, 0);

		GameState = GSTitleScreenInit;
		if(GameMode == GMRetroCarousel)
		{
			if (Game < Games - 1)
			{
				Game += 1;
				GameState = GSGames[Game].state;
			}			
		}

		if (GameState == GSTitleScreenInit)
			CGame_SaveHighScoresSettings();
		
		result = true;
	}
	return result;
}

#endif