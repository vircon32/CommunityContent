#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "string.h"
#include "input.h"
#include "Common.h"
#include "TitleScreen.h"
#include "Vec2F.h"
#include "SDL_HelperTypes.h"
#include "libs/TextFonts/textfont.h"
#include "CAudio.h"
#include "TitleScreenBackground.h"

int SelectedMenu = 0;
int CurrentMainMenu = -1;
int SelMenu = 0;
int SelOptions = 0;
int FrameScaleTicks = 15;
float FrameEndXScale = 1.5;
float FrameEndYScale = 7.4;
float FrameXi = 0.0;
float FrameYi = 0.0;

float FrameXScaleHelp = 2.4;
float FrameYScaleHelp = 7.6;
float FrameXScaleMain = 1.4;
float FrameYScaleMain = 7.6;
float FrameXScaleCredits = 2.5;
float FrameYScaleCredits = 7.6;
float FrameXScaleOptions = 1.4;
float FrameYScaleOptions = 7.6;
float FrameXScaleSelectGame = 2.5;
float FrameYScaleSelectGame = 7.6;
float FrameXScaleSelectGameMode = 2.4;
float FrameYScaleSelectGameMode = 7.6;
float FrameXScaleScores = 2.1;
float FrameYScaleScores = 7.6;
float FrameXScale = 0.0;
float FrameYScale = 0.0;

int menutextsize = (int)(60.0*yscale);
int menuspacing = (int)(90.0*yscale);

void ResetGlobalsTitleScreen()
{
	SelectedMenu = 0;
	CurrentMainMenu = -1;
	SelMenu = 0;
	SelOptions = 0;	
}

void SetFrameScaleValues(float frameEndXScale, float frameEndYScale, int ticks)
{
	FrameEndXScale = frameEndXScale;
	FrameEndYScale = frameEndYScale;

	FrameXi = (FrameEndXScale - FrameXScale) / ticks;
	FrameYi = (FrameEndYScale - FrameYScale) / ticks;
}

void InitTitleScreen()
{
	CAudio_PlayMusic(MusMenu, -1);
	CGame_StartCrossFade(GameState, SGNone, 0);
	CGame_CreateRandomBackground();
	SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
}

void TitleScreenAdjustFrameScaleValues()
{
	if(FrameXi < 0)
	{
		if (FrameXScale > FrameEndXScale)
			FrameXScale += FrameXi;
		else
		{
			FrameXScale = FrameEndXScale;
			FrameXi = 0;
		}
	}

	if(FrameXi > 0)
	{
		if (FrameXScale < FrameEndXScale)
			FrameXScale += FrameXi;
		else
		{
			FrameXScale = FrameEndXScale;
			FrameXi = 0;
		}
	}

	if(FrameYi < 0)
	{
		if (FrameYScale > FrameEndYScale)
			FrameYScale += FrameYi;
		else
		{
			FrameYScale = FrameEndYScale;
			FrameYi = 0;
		}
	}

	if(FrameYi > 0)
	{
		if (FrameYScale < FrameEndYScale)
			FrameYScale += FrameYi;
		else
		{
			FrameYScale = FrameEndYScale;
			FrameYi = 0;
		}
	}
}

void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		InitTitleScreen();
		GameState -= initDiff;
	}

	CGame_DrawTitleBackground((gamepad_button_l() > 0) && (gamepad_button_r() > 0) && (CurrentMainMenu == -1));

	SDL_Point FramePos = {ScreenWidth / 2, ScreenHeight / 2};
	//Vec2F FrameScale = {2.5 * xscale, 7.6 *yscale};
	Vec2F FrameScale = {FrameXScale * xscale, FrameYScale *yscale};
	CImage_DrawImageFuze(GFXFrameID, 0, true, FramePos.x , FramePos.y, 0, FrameScale.x, FrameScale.y, 1.0, 1.0, 1.0, 0.90);
	CImage_DrawImageFuze(GFXOuterFrameID, 0, true, FramePos.x , FramePos.y, 0, FrameScale.x, FrameScale.y, 1.0, 1.0, 1.0, 1.0);
	
	TitleScreenAdjustFrameScaleValues();
	

	int color = color_white;
	int[1000] Text;
	int[10] Nr;
	int* PText;
	switch (CurrentMainMenu)
	{
		case MMOptions:
		{
			int selectedmenu = 0;

			selectedmenu = OMOptionMenus[SelOptions].menu;
			PText = Text; *PText = 0; PText = faststrcat(PText, "Options");
			CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(525.0*xscale), (int)(50.0*yscale), color);
			int menu;

			for(int i = 0; i < OptionMenus; i++)
			{
				menu = OMOptionMenus[i].menu;
				if (menu == selectedmenu)
					color = color_white;
				else
					color = color_gray;

				switch(menu)
				{
					case OMSoundVol:
						PText = Text; *PText = 0; PText = faststrcat(PText, OMOptionMenus[menu].name);
						itoa((int)(CAudio_GetVolumeSound()*100/128), Nr, 10);
						PText = faststrcat(PText, Nr);
						PText = faststrcat(PText, "%");
						CFont_WriteText("Roboto-Regular", menutextsize, Text, (int)(330.0*xscale), (int)(185.0*yscale + i * menuspacing), color);
						break;
					case OMMusicVol:
						PText = Text; *PText = 0; PText = faststrcat(PText, OMOptionMenus[menu].name);
						itoa((int)(CAudio_GetVolumeMusic()*100/128), Nr, 10);
						PText = faststrcat(PText, Nr);
						PText = faststrcat(PText, "%");
						CFont_WriteText("Roboto-Regular", menutextsize, Text, (int)(330.0*xscale), (int)(185.0*yscale + i * menuspacing), color);
						break;
					default:
						CFont_WriteText("Roboto-Regular", menutextsize, OMOptionMenus[menu].name, (int) (330.0*xscale),	(int)(185.0*yscale + i * menuspacing), color);
						break;
				}
			}
			color = color_white;
			PText = Text; *PText = 0; PText = faststrcat(PText, "Use dpad to switch between options.\n(A) to select and (B) for back");
			CFont_WriteText("Roboto-Regular", (int)(34.0*yscale), Text, (int)(350.0*xscale), (int)(570.0*yscale), color);
			
			if (gamepad_down() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);
				SelOptions += 1;
				if (SelOptions == OptionMenus)
					SelOptions = 0;
			}

			if (gamepad_up() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);

				SelOptions -= 1;
				if( SelOptions == -1)
					SelOptions = OptionMenus - 1;
			}

			if (gamepad_left() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);
				bool wasplaying;
				switch (selectedmenu)
				{
					case OMSoundVol:
						CAudio_DecVolumeSound();
						break;

					case OMMusicVol:
						wasplaying = CAudio_IsMusicPlaying();
						CAudio_DecVolumeMusic();
						if (!wasplaying)
							CAudio_PlayMusic(MusMenu, -1);
						break;

				}
			}

			if (gamepad_right() == 1)
			{
				CAudio_PlaySound(SfxSelect, 0);
				bool wasplaying;
				switch (selectedmenu)
				{
					case OMSoundVol:
						CAudio_IncVolumeSound();
						break;

					case OMMusicVol:
						wasplaying = CAudio_IsMusicPlaying();
						CAudio_IncVolumeMusic();
						if (!wasplaying)
							CAudio_PlayMusic(MusMenu, -1);
						break;
				}
			}


			if (gamepad_button_b() == 1)
			{
				CAudio_PlaySound(SfxBack, 0);
				CGame_StartFade();
				CurrentMainMenu = -1;
				CGame_SaveHighScoresSettings();
				SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
			}

			if ((gamepad_button_start() == 1) || (gamepad_button_a() == 1))
			{
				CAudio_PlaySound(SfxSelect, 0);
				bool wasplaying;
				switch(selectedmenu)
				{
					case OMBack:
						CurrentMainMenu = -1;
						CGame_StartFade();
						CGame_SaveHighScoresSettings();
						SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
						break;
					case OMResetHighScores:
						CGame_ResetHighScores();
						CGame_SaveHighScoresSettings();
						break;
					case OMSoundVol:
						CAudio_IncVolumeSound();
						break;
					case OMMusicVol:
						wasplaying = CAudio_IsMusicPlaying();
						CAudio_IncVolumeMusic();
						if(!wasplaying)
							CAudio_PlayMusic(MusMenu, -1);
						break;
				}
			}
			break;
		}


		case MMHelp:
		{
			if((FrameXi == 0.0) && (FrameYi == 0.0))
			{
				PText = Text; *PText = 0; PText = faststrcat(PText,"Help");
				CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(560.0*xscale), (int)(50.0*yscale), color);
				

				PText = Text; *PText = 0; PText = faststrcat(PText, "Retro time is a collection of retro games, each playable in different\n"
					"game modes.\n"
					"\n"
					"You can control players in games with the dpad. Extra actions are\n"
					"available, using (A), depending on the game.\n"
					"\n"
					"During gameplay you can access the pause menu, by pressing\n"
					"(B) button. Pressing it again will resume gameplay.\n"
					"\n"
					"There are 3 game modes: Retro Carousel, Time Attack and\n"
					"Lives mode.");
				int tw = CFont_TextWidth("Roboto-Regular", (int)(38.0*yscale), Text);
				CFont_WriteText("Roboto-Regular", (int)(38.0*yscale), Text, (int)((ScreenWidth-tw)/2.0),(int)(140.0*yscale), color);

				if ((gamepad_button_a() == 1) || (gamepad_button_start() == 1) || (gamepad_button_b() == 1))
				{
					SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
					CAudio_PlaySound(SfxBack, 0);
					CGame_StartFade();
					CurrentMainMenu = -1;
				}
			}
			break;
		}
		case MMCredits:
		{
			if((FrameXi == 0.0) && (FrameYi == 0.0))
			{
				PText = Text; *PText = 0; PText = faststrcat(PText, "Credits");
				CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(500.0*xscale),(int)(50.0*yscale), color);

				PText = Text; *PText = 0; PText = faststrcat(PText,
				"Block Stacker code is heavily inspired on this video from one lone\n"
				"coder (javidx9) with my own adaptations: https://youtu.be/8OK8_tHeCIA\n"

				"Snakey code is based on an edureka article (by Wajiha Urooj) about making\n"
				"python snake: https://www.edureka.co/blog/snake-game-with-pygame\n"

				"Brick Breaker ball / block collision uses a detection seen in wireframe\n"
				"magazine nr 11: https://wireframe.raspberrypi.org\n"

				"Toady water and grass background tiles have been created by me,\n"
				"Willems Davy aka joyrider3774 feel free to use them. Music is\n"
				"created, payed and owned by me using Strofe: https://www.strofe.com\n"

				"All other assets (including sound) come from either payed or free\n"
				"asset packs. For a complete list check the github or itch.io page:\n"
				"https://github.com/joyrider3774/retrotime_vircon32 or\n"
				"https://joyrider3774.itch.io/retrotime_vircon32_version\n");

				int tw = CFont_TextWidth("Roboto-Regular", (int)(34.0*yscale), Text);
				CFont_WriteText("Roboto-Regular", (int)(34.0*yscale), Text, (int)((ScreenWidth - tw) / 2.0), (int)(140.0*yscale), color);			

				if ((gamepad_button_a() == 1) || (gamepad_button_start() == 1) || (gamepad_button_b() == 1))
				{
					CAudio_PlaySound(SfxBack, 0);
					CGame_StartFade();
					CurrentMainMenu = -1;
					SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
				}
			}
			break;
		}
		case MMHighScores:
		{
			if((FrameXi == 0.0) && (FrameYi == 0.0))
			{
				PText = Text; *PText = 0; PText = faststrcat(PText,"High Scores");
				CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(400.0*xscale), (int)(50.0*yscale), color);
				

				PText = Text; *PText = 0; PText = faststrcat(PText, "Retro Carousel Total highscore: ");
				itoa(RetroCarouselHighScore, Nr, 10);
				PText = faststrcat(PText, Nr);
				CFont_WriteText("Roboto-Regular", (int)(50.0*yscale), Text,(int)(150.0*xscale),(int)(195.0*yscale), color);
				
				CFont_WriteText("Roboto-Regular", (int)(50.0*yscale), GSGames[Game].name,(int)(150.0*xscale),(int)(290.0*yscale), color);

				CImage_DrawImageFuze(GFXPrevewID, Game, false, (int)(150.0*xscale), (int)(355.0*yscale), 0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

				for(int mode = 0; mode < Modes; mode++)
				{
					PText = Text; *PText = 0; PText = faststrcat(PText, GMModes[mode].name);
					PText = faststrcat(PText,": ");
					itoa(HighScores[Game][mode], Nr, 10);
					PText = faststrcat(PText, Nr);
					CFont_WriteText("Roboto-Regular", (int)(50.0*yscale), Text, (int)(500.0*xscale), (int)((350 + mode * 46)*yscale), color);				
				}

				PText = Text; *PText = 0; PText = faststrcat(PText, "Use dpad or (A) to switch between games. (B) for back");
				CFont_WriteText("Roboto-Regular", (int)(34.0*yscale), Text, (int)(200.0*xscale),(int)(630.0*yscale), color);
				
				if (gamepad_button_b() == 1)
				{
					CAudio_PlaySound(SfxBack, 0);
					CGame_StartFade();
					CurrentMainMenu = -1;
					SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
				}

				if ((gamepad_button_a() == 1) || (gamepad_button_start() == 1) || (gamepad_right() == 1))
				{
					CAudio_PlaySound(SfxSelect, 0);

					Game += 1;
					if (Game == Games)
						Game = 0;
				}

				if (gamepad_left() == 1)
				{
					CAudio_PlaySound(SfxSelect, 0);

					Game -= 1;
					if (Game == -1)
						Game = Games - 1;
				}
			}
			break;
		}
		case MMSelectGame:
		{
			if((FrameXi == 0.0) && (FrameYi == 0.0))
			{
				int gamestate = GSGames[Game].state;
				PText = Text; *PText = 0; PText = faststrcat(PText, "Select Game");
				CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(465.0*xscale), (int)(50.0*yscale), color);
				

				PText = Text; *PText = 0; PText = faststrcat(PText, GSGames[Game].name);
				CFont_WriteText("Roboto-Regular", (int)(50.0*yscale), Text, (int)(50.0*xscale), (int)(165.0*yscale), color);
				
				CImage_DrawImageFuze(GFXPrevewID, Game, false, (int)(50.0*xscale), (int)(230.0*yscale), 0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

				PText = Text; *PText = 0; PText = faststrcat(PText, GMModes[GameMode].name);
				PText = faststrcat(PText, " High Score: ");
				itoa(HighScores[Game][GameMode], Nr, 10);
				PText = faststrcat(PText, Nr);

				CFont_WriteText("Roboto-Regular", (int)(40.0*yscale), Text, (int)(400.0*xscale), (int)(170.0*yscale), color);
				
				CFont_WriteText("Roboto-Regular", (int)(28.0*yscale), GSGames[Game].description, (int)(400.0*xscale), (int)(230.0*yscale), color);

				PText = Text; *PText = 0; PText = faststrcat(PText, "Use dpad to switch between games. (A) to select and (B) for back");
				CFont_WriteText("Roboto-Regular", (int)(34.0*yscale), Text, (int)(90.0*xscale), (int)(630.0*yscale), color);
				
				if (gamepad_button_b() == 1)
				{
					CAudio_PlaySound(SfxBack, 0);
					CurrentMainMenu = MMSelectGameMode;
					CGame_StartFade();
					SetFrameScaleValues(FrameXScaleSelectGameMode, FrameYScaleSelectGameMode, FrameScaleTicks);
				}

				if ((gamepad_button_start() == 1) || (gamepad_button_a() == 1))
				{
					CAudio_PlaySound(SfxConfirm, 0);
					CGame_StartFade();
					GameState = gamestate;
					CGame_ResetScores();
					CurrentMainMenu = -1;
					FrameXScale = 2.5;
					FrameYScale = 7.6;
					//CInput_ResetButtons();
				}

				if (gamepad_left() == 1)
				{
					CAudio_PlaySound(SfxSelect, 0);

					Game -= 1;
					if (Game == -1)
						Game = Games - 1;
				}
				if (gamepad_right() == 1)
				{
					CAudio_PlaySound(SfxSelect, 0);

					Game += 1;
					if (Game == Games)
						Game = 0;
				}
			}
			break;
		}
		case MMSelectGameMode:
		{
			if((FrameXi == 0.0) && (FrameYi == 0.0))
			{
				PText = Text; *PText = 0; PText = faststrcat(PText, "Select Game Mode");
				CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(285.0*xscale), (int)(50.0*yscale), color);
				
				int ModeIterator;
				for(int i = 0; i < Modes; i++)
				{
					ModeIterator = GMModes[i].mode;
					if (ModeIterator == GameMode)
						color = color_white;
					else
						color = color_gray;

					CFont_WriteText("Roboto-Regular", menutextsize, GMModes[i].name, (int)(470.0*xscale), (int)(135.0*yscale + i * menuspacing), color);
				}
				color = color_white;

				CFont_WriteText("Roboto-Regular", (int)(40.0*yscale), GMModes[GameMode].description,(int)(90.0*xscale),(int)(400.0*yscale), color);

				PText = Text; *PText = 0; PText = faststrcat(PText, "Use dpad to switch between game modes. (A) to select and (B) for back");
				CFont_WriteText("Roboto-Regular", (int)(34.0*yscale), Text, (int)(90.0*xscale), (int)(630.0*yscale), color);
				
				if (gamepad_down() == 1)
				{
					CAudio_PlaySound(SfxSelect, 0);
					GameMode += 1;
					if (GameMode == Modes)
						GameMode = 0;
				}

				if (gamepad_up() == 1)
				{
					CAudio_PlaySound(SfxSelect, 0);

					GameMode -= 1;
					if (GameMode == -1)
						GameMode = Modes - 1;
				}

				if (gamepad_button_b() == 1)
				{
					CAudio_PlaySound(SfxBack, 0);
					CurrentMainMenu = -1;
					CGame_StartFade();
					SetFrameScaleValues(FrameXScaleMain, FrameYScaleMain, FrameScaleTicks);
				}

				if ((gamepad_button_start() == 1) || gamepad_button_a() == 1)
				{
					CAudio_PlaySound(SfxConfirm, 0);

					if (GameMode == GMRetroCarousel)
					{
						Game = 0;
						CGame_ResetScores();
						CurrentMainMenu = -1;
						GameState = GSGames[Game].state;
						FrameXScale = 2.5;
						FrameYScale = 7.6;
					}
					else
					{
						SetFrameScaleValues(FrameXScaleSelectGame, FrameYScaleSelectGame, FrameScaleTicks);
						CurrentMainMenu = MMSelectGame;
					}
					CGame_StartFade();
				}
			}
			break;
		}
		default:
		{
			if((FrameXi == 0.0) && (FrameYi == 0.0))
			{
				SelMenu = MMMainMenus[SelectedMenu].menu;

				PText = Text; *PText = 0; PText = faststrcat(PText, "Retro Time");
				CFont_WriteText("Roboto-Regular", (int)(80.0*yscale), Text, (int)(465.0*xscale), (int)(50.0*yscale), color);
				
				int MenuIterator;
				for (int i = 0; i < MainMenus; i++)
				{
					MenuIterator = MMMainMenus[i].menu;
					if (MenuIterator == SelMenu)
						color = color_white;
					else
						color = color_gray;
					CFont_WriteText("Roboto-Regular", menutextsize, MMMainMenus[i].name, (int)(500.0*xscale), (int)(180.0*yscale + i * menuspacing), color);
				}
				color = color_white;

				if (gamepad_down() == 1)
				{
					CAudio_PlaySound(SfxSelect, 0);
					SelectedMenu += 1;
					if (SelectedMenu == MainMenus)
						SelectedMenu = 0;
				}

				if (gamepad_up() == 1)

				{
					CAudio_PlaySound(SfxSelect, 0);

					SelectedMenu -= 1;
					if(SelectedMenu == -1)
						SelectedMenu = MainMenus - 1;
				}

				if ((gamepad_button_start() == 1) || (gamepad_button_a() == 1))
				{
					CGame_StartFade();
					CurrentMainMenu = SelMenu;
					CAudio_PlaySound(SfxConfirm, 0);
					switch(SelMenu)
					{
						case MMStart:
							CurrentMainMenu = MMSelectGameMode;
							SetFrameScaleValues(FrameXScaleSelectGameMode, FrameYScaleSelectGameMode, FrameScaleTicks);
							break;
						case MMCredits:
							SetFrameScaleValues(FrameXScaleCredits, FrameYScaleCredits, FrameScaleTicks);
							break;
						case MMHelp:
							SetFrameScaleValues(FrameXScaleHelp, FrameYScaleHelp, FrameScaleTicks);
							break;
						case MMHighScores:
							SetFrameScaleValues(FrameXScaleScores, FrameYScaleScores, FrameScaleTicks);
							break;
						case MMOptions:
							SetFrameScaleValues(FrameXScaleOptions, FrameYScaleOptions, FrameScaleTicks);
							break;
					}
				}
			}
		}
	}
}

#endif