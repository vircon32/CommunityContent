#ifndef CGAMEBASE_H
#define CGAMEBASE_H

#include "input.h"
#include "../CAudio.h"
#include "../CGame.h"
#include "../Common.h"
#include "../CFont.h"
#include "../Vec2F.h"
#include "../SDL_HelperTypes.h"
#include "../libs/DrawPrimitives/draw_primitives.h"

struct CGameBase {
	int[500] SubStateText;
	bool UsesLevels;
	int level;
	int screenleft, screenright, screentop, screenbottom, playfieldwidth, playfieldheight, HealthPoints;
	int GameStateID;
};


int CGameBase_prevsubgamestate = -1;
float CGameBase_prevsubstatecounter = 0;
int CGameBase_selected = 0;
int CGameBase_selectedmenu = 0;
int CGameBase_maxmenus = 5;
int CGameBase_menutextsize = (int)(60.0 * yscale);
int CGameBase_menuspacing = (int)(85.0 * yscale);
bool CGameBase_readygoplayed = false;
bool CGameBase_IgnoreFirstFrame = false;

void CGameBase_PauseMenu(CGameBase* GameBase)
{
	if(CGameBase_IgnoreFirstFrame)
	{
		CGameBase_IgnoreFirstFrame = false;
		return;
	}

	if ((CGameBase_prevsubgamestate > -1) && ((SubGameState == SGFrame) || (SubGameState == SGPauseMenu) || (SubGameState == SGGameHelp)))
	{
		CGameBase_selectedmenu = GPGamePauseMenus[Game].menus[CGameBase_selected];

		SDL_Point FramePos = {ScreenWidth / 2, ScreenHeight / 2};
		Vec2F FrameScale = {2.5 * xscale, 7.6 *yscale};
		CImage_DrawImageFuze(GFXFrameID, 0, true, FramePos.x , FramePos.y, 0, FrameScale.x, FrameScale.y, 1.0, 1.0, 1.0, 1.0);
		
		int color = color_white;
		int[1000] Text;
		int[10] Nr;
		int* PText;
		if (SubGameState == SGPauseMenu)
		{

			PText = Text; *PText = 0; PText = faststrcat(PText, "Paused");
			CFont_WriteText("Roboto-Regular", (int)(80.0 * yscale), Text, (int)(510.0 * xscale), (int)(50.0 * yscale), color);
			int menu;

			for (int i = 0; i < CGameBase_maxmenus; i++)
			{
				menu = GPGamePauseMenus[Game].menus[i];
				if (menu == CGameBase_selectedmenu)
					color = color_white;
				else
					color = color_gray;

				switch (menu)
				{
					case PMSoundVol:
						PText = Text; *PText = 0; PText = faststrcat(PText, PMPauseMenus[menu].name);
						PText = faststrcat(PText, " ");
						itoa((int)(CAudio_GetVolumeSound() * 100.0 / 128.0), Nr, 10);
						PText = faststrcat(PText, Nr);
						PText = faststrcat(PText, " %"); 
						CFont_WriteText("Roboto-Regular", CGameBase_menutextsize, Text, (int)(300.0 * xscale), (int)(185.0 * yscale + i * CGameBase_menuspacing), color);
						break;
					case PMMusicVol:
						PText = Text; *PText = 0; PText = faststrcat(PText, PMPauseMenus[menu].name);
						PText = faststrcat(PText, " ");
						itoa((int)(CAudio_GetVolumeMusic() * 100.0 / 128.0), Nr, 10);
						PText = faststrcat(PText, Nr);
						PText = faststrcat(PText, " %"); 
						CFont_WriteText("Roboto-Regular", CGameBase_menutextsize, Text, (int)(300.0 * xscale), (int)(185.0 * yscale + i * CGameBase_menuspacing), color);
						break;
					default:
						CFont_WriteText("Roboto-Regular", CGameBase_menutextsize, PMPauseMenus[menu].name, (int)(300.0 * xscale),
							(int)(185.0 * yscale + i * CGameBase_menuspacing), color);
						break;
				}
			}

			color = color_white;
			PText = Text; *PText = 0; PText = faststrcat(PText, "Use dpad to switch between options. (A) to select and (B) for back");
			CFont_WriteText("Roboto-Regular", (int)(34.0 * yscale), Text, (int)(90.0 * xscale), (int)(630.0 * yscale), color);
		}

		if (SubGameState == SGGameHelp)
		{
			PText = Text; *PText = 0; PText = faststrcat(PText, "Game Help");
			CFont_WriteText("Roboto-Regular", (int)(80.0 * yscale), Text, (int)(485.0 * xscale), (int)(50.0 * yscale), color);
			
			PText = Text; *PText = 0; PText = faststrcat(PText, GSGames[Game].name);
			CFont_WriteText("Roboto-Regular", (int)(50.0 * yscale), Text, (int)(75.0 * xscale), (int)(150.0 * yscale), color);


			PText = Text; *PText = 0; PText = faststrcat(PText,GSGames[Game].name);
			PText = faststrcat(PText, " ");
			PText = faststrcat(PText, GMModes[GameMode].name);
			PText = faststrcat(PText," High Score: ");
			itoa(HighScores[Game][GameMode], Nr, 10);
			PText = faststrcat(PText, Nr);
			CFont_WriteText("Roboto-Regular", (int)(38.0 * yscale), Text, (int)(75.0 * xscale), (int)(210.0 * yscale), color);

			PText = Text; *PText = 0; PText = faststrcat(PText, GSGames[Game].description);
			CFont_WriteText("Roboto-Regular", (int)(38.0 * yscale), Text, (int)(75.0 * xscale), (int)(255.0 * yscale), color);
			
			PText = Text; *PText = 0; PText = faststrcat(PText, "Press (A) or (B) for back");
			CFont_WriteText("Roboto-Regular", (int)(34.0 * yscale), Text, (int)(485.0 * xscale),(int)(630.0 * yscale), color);
		}

		if (SubGameState == SGGameHelp)
		{
			if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1) || (gamepad_button_start() == 1))
			{
				CAudio_PlaySound(SfxBack, 0);
				SubGameState = SGPauseMenu;
				CGame_StartFade();
				return;
			}
		}

		if (SubGameState == SGPauseMenu)
		{
			if (gamepad_left() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);

				switch (CGameBase_selectedmenu)
				{
					case PMSoundVol:
					{
						CAudio_DecVolumeSound();
						CGame_SaveHighScoresSettings();
						break;
					}

					case PMMusicVol:
					{
						bool wasplaying = CAudio_IsMusicPlaying();
						CAudio_DecVolumeMusic();
						if (!wasplaying)
							CAudio_PlayMusic(CurrentGameMusicID, -1);
						CGame_SaveHighScoresSettings();
						break;
					}

				}
			}

			if (gamepad_right() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);
				switch (CGameBase_selectedmenu)
				{
					case PMSoundVol:
					{
						CAudio_IncVolumeSound();
						CGame_SaveHighScoresSettings();
						break;
					}

					case PMMusicVol:
					{
						bool wasplaying = CAudio_IsMusicPlaying();
						CAudio_IncVolumeMusic();
						if (!wasplaying)
							CAudio_PlayMusic(CurrentGameMusicID, -1);
						CGame_SaveHighScoresSettings();
						break;
					}
				}
			}

			if (gamepad_down() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);

				CGameBase_selected += 1;
				if (CGameBase_selected == CGameBase_maxmenus)
					CGameBase_selected = 0;
			}

			if (gamepad_up() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);

				CGameBase_selected -= 1;
				if (CGameBase_selected == -1)
					CGameBase_selected = CGameBase_maxmenus - 1;
			}

			if (gamepad_button_b() == 1)
			{
				CAudio_PlaySound(SfxConfirm, 0);
				SubGameState = CGameBase_prevsubgamestate;
				SubStateCounter = CGameBase_prevsubstatecounter;
				CGameBase_prevsubgamestate = -1;
				CGame_StartFade();
			}

			if ((gamepad_button_a() == 1) || (gamepad_button_start() == 1))
			{
				CAudio_PlaySound(SfxConfirm, 0);

				switch (CGameBase_selectedmenu)
				{
				case PMContinue:
				{
					SubGameState = CGameBase_prevsubgamestate;
					SubStateCounter = CGameBase_prevsubstatecounter;
					CGameBase_prevsubgamestate = -1;
					CGame_StartFade();
					break;
				}

				case PMQuit:
				{
					CGameBase_prevsubgamestate = -1;
					CGame_StartCrossFade(GSTitleScreenInit, SGNone, 3);
					break;
				}

				case PMSoundVol:
				{
					CAudio_IncVolumeSound();
					CGame_SaveHighScoresSettings();
					break;
				}

				case PMMusicVol:
				{
					bool wasplaying = CAudio_IsMusicPlaying();
					CAudio_IncVolumeMusic();
					if (!wasplaying)
						CAudio_PlayMusic(CurrentGameMusicID, -1);
					CGame_SaveHighScoresSettings();
					break;
				}

				case PMGameHelp:
				{
					SubGameState = SGGameHelp;
					CGameBase_IgnoreFirstFrame = true;
					CGame_StartFade();
					break;
				}
				}

			}
		}
	}
}

void CGameBase_DrawScoreBar(CGameBase* GameBase)
{
	int[1000] Text;
	int[1000] TmpText;
	int[20] Nr;
	int* PText = Text;
	int* PTmpText = TmpText;
	*PText = 0;
	set_multiply_color(make_color_rgba(0,0,0,128));
	draw_filled_rectangle(0, 0, ScreenWidth, ScoreBarHeight);
	set_multiply_color(color_white);

	if(GameBase->UsesLevels)
	{
		PTmpText = TmpText; *PTmpText = 0; PTmpText = faststrcat(PTmpText, "Lev:");
		itoa(GameBase->level, Nr, 10);
		PTmpText = faststrcat(PTmpText, Nr);
		PTmpText = faststrcat(PTmpText, " ");
		PText = faststrcat(PText, TmpText);
	}

	if (GameMode == GMGame)
	{
		PTmpText = TmpText; *PTmpText = 0; PTmpText = faststrcat(PTmpText, "Lives:");
		itoa(GameBase->HealthPoints, Nr, 10);
		PTmpText = faststrcat(PTmpText, Nr);
		PTmpText = faststrcat(PTmpText, " Score:");
		itoa(Scores[Game][GameMode], Nr, 10);
		PTmpText = faststrcat(PTmpText, Nr);
		PTmpText = faststrcat(PTmpText, " High:");
		itoa(HighScores[Game][GameMode], Nr, 10);
		PTmpText = faststrcat(PTmpText, Nr);
		PTmpText = faststrcat(PTmpText, " ");
		PText = faststrcat(PText, TmpText);
	}
	else
	{
		if(GameMode == GMRetroCarousel)
		{
			PTmpText = TmpText; *PTmpText = 0; PTmpText = faststrcat(PTmpText,"Tmr:");
			ftoa(floor(Timer),Nr);
			PTmpText = faststrcat(PTmpText, Nr);
			PTmpText = faststrcat(PTmpText," Tot Score:");
			itoa(RetroCarouselScore, Nr, 10);
			PTmpText = faststrcat(PTmpText, Nr);
			PTmpText = faststrcat(PTmpText, " Score:");
			itoa(Scores[Game][GameMode], Nr, 10);
			PTmpText = faststrcat(PTmpText, Nr);
			PTmpText = faststrcat(PTmpText, " Prev Tot high:");
			itoa(RetroCarouselHighScore, Nr, 10);
			PTmpText = faststrcat(PTmpText, Nr);
			PTmpText = faststrcat(PTmpText, " Prev High:");
			itoa(HighScores[Game][GameMode], Nr, 10);
			PTmpText = faststrcat(PTmpText, Nr);
			PText = faststrcat(PText, TmpText);
		}
		else
		{
			PTmpText = TmpText; *PTmpText = 0; PTmpText = faststrcat(PTmpText,"Tmr:");
			ftoa(floor(Timer),Nr);
			PTmpText = faststrcat(PTmpText, Nr);
			PTmpText = faststrcat(PTmpText, " Score:");
			itoa(Scores[Game][GameMode], Nr, 10);
			PTmpText = faststrcat(PTmpText, Nr);
			PTmpText = faststrcat(PTmpText, " Prev High:");
			itoa(HighScores[Game][GameMode], Nr, 10);
			PTmpText = faststrcat(PTmpText, Nr);
			PText = faststrcat(PText, TmpText);
		}
			
	}
	CFont_WriteText("Roboto-Regular", 17, Text, 0, 0, color_white);
}

void CGameBase_DrawSubstateText(CGameBase* GameBase)
{
	int w = CFont_TextWidth("Roboto-Regular", 40, GameBase->SubStateText);
	CFont_WriteText("Roboto-Regular", 40, GameBase->SubStateText, (int)(-1.0 + GameBase->screenleft + ((GameBase->screenright - GameBase->screenleft) / 2.0) - w / 2.0),
		(int)(-1.0 + GameBase->screentop + ((GameBase->screenbottom - GameBase->screentop) / 2.0) - 110.0 * xscale), color_black);
	CFont_WriteText("Roboto-Regular", 40, GameBase->SubStateText, (int)(-1.0 + GameBase->screenleft + ((GameBase->screenright - GameBase->screenleft) / 2.0) - w / 2.0),
		(int)(1.0 + GameBase->screentop + ((GameBase->screenbottom - GameBase->screentop) / 2.0) - 110.0 * xscale), color_black);
	CFont_WriteText("Roboto-Regular", 40, GameBase->SubStateText, (int)(1.0 + GameBase->screenleft + ((GameBase->screenright - GameBase->screenleft) / 2.0) - w / 2.0),
		(int)(-1.0 + GameBase->screentop + ((GameBase->screenbottom - GameBase->screentop) / 2.0) - 110.0 * xscale), color_black);
	CFont_WriteText("Roboto-Regular", 40, GameBase->SubStateText, (int)(1.0 + GameBase->screenleft + ((GameBase->screenright - GameBase->screenleft) / 2.0) - w / 2.0),
		(int)(1.0 + GameBase->screentop + ((GameBase->screenbottom - GameBase->screentop) / 2.0) - 110.0 * xscale), color_black);
	CFont_WriteText("Roboto-Regular", 40, GameBase->SubStateText, (int)(GameBase->screenleft + ((GameBase->screenright - GameBase->screenleft) / 2.0) - w / 2.0),
		(int)(GameBase->screentop + ((GameBase->screenbottom - GameBase->screentop) / 2.0) - 110.0 * xscale), color_white);
}

bool CGameBase_UpdateLogic(CGameBase* GameBase)
{
	bool result = false;
	//check for pause menu only when in game substate
	if ((CGameBase_prevsubgamestate == -1) && (SubGameState == SGGame) && ((gamepad_button_b() == 1) ||(gamepad_button_start() == 1)))
	{
		CAudio_PlaySound(SfxConfirm, 0);
		CGameBase_selected = 0;
		CGameBase_selectedmenu = 0;
		CGameBase_IgnoreFirstFrame = true;
		CGameBase_prevsubgamestate = SubGameState;
		CGameBase_prevsubstatecounter = SubStateCounter;
		SubGameState = SGPauseMenu;
		CGame_StartFade();
	}

	CGameBase_PauseMenu(GameBase);
	
	//we are in the pause menu
	if (CGameBase_prevsubgamestate > -1)
		return result;

	if (GameMode == GMGame)
	{
		if (SubGameState == SGGame)
		{
			if(GameBase->HealthPoints == 0)
			{
				SubGameState = SGTimeUp;
				SubStateTime = getCurrentTimeMilliseconds() + 750;
				SubStateCounter = 0;
			}
		}
	}

	GameBase->SubStateText[0] = 0;
	if (SubGameState != SGFadeIn)
	{
		if ((SubGameState == SGReadyGo)||
			(SubGameState == SGTimeUp))
		{
			if (SubStateTime > getCurrentTimeMilliseconds())
			{
				if (SubStateCounter >= 0)
				{
					int[10] Nr;
					itoa((int)SubStateCounter, Nr, 10);
					strcpy(GameBase->SubStateText, Nr);
					if(SubStateCounter == 2)
					{
						if (!CGameBase_readygoplayed)
						{
							CAudio_PlaySound(SfxReadyGo, 0);
							CGameBase_readygoplayed = true;
						}
					}

					if (SubStateCounter == 0)
					{
						CGameBase_readygoplayed = false;
						if (SubGameState == SGReadyGo)
						{
							strcpy(GameBase->SubStateText, "GO");
						}
						else
						{
							if (GameMode != GMGame)
							{
								strcpy(GameBase->SubStateText, "Time Up");
							}
							else
								strcpy(GameBase->SubStateText, "Game Over");

						}
					}
				}
			}
			else
			{
				if (SubStateCounter > 0)
				{
					if (SubStateCounter > 1)
						SubStateTime = getCurrentTimeMilliseconds() + 500;
					else
						SubStateTime = getCurrentTimeMilliseconds() + 250;
					SubStateCounter -= 1;
				}
				else
				{
					if (SubGameState == SGReadyGo)
					{
						result = true;
						SubGameState = SGGame;
					}
					else
					{
						GameState = GSSubScoreInit;
					}
				}
			}
		}
	}
	return result;
}

CGameBase* Create_CGameBase(int aGameStateID, bool aUsesLevels)
{
	CGameBase* result = (CGameBase*) malloc(sizeof(CGameBase));
	
	result->UsesLevels = aUsesLevels;
	result->GameStateID = aGameStateID;
	result->level = 0;
	result->HealthPoints = 0;
	result->SubStateText[0] = 0;
	result->playfieldheight = 0;
	result->playfieldwidth = 0;
	result->screenbottom = 0;
	result->screentop = 0;
	result->screenleft = 0;
	result->screenright = 0;
	return result;
}

void Destroy_CGameBase(CGameBase* GameBase)
{
	free(GameBase);
}


#endif