#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

#include "Texture.h"
#include "memcard.h"
#include "libs/TextFonts/textfont.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "fonts/Roboto_Black_20.h"
#include "fonts/Roboto_Black_30.h"
#include "fonts/Roboto_Black_60.h"
#include "fonts/Roboto_Light_15.h"
#include "CAudio.h"
#include "Vircoban.h"
#include "Common.h"
#include "CInput.h"

#define levelLocksSavePosition 100

void setupFonts()
{
	setupFontRoboto_Black_20();
	setupFontRoboto_Black_30();
	setupFontRoboto_Black_60();
	setupFontRoboto_Light_15();
	
	
	font = &FontRoboto_Light_15;
	RobotoBig = &FontRoboto_Black_60;
	RobotoMedium = &FontRoboto_Black_30;
	RobotoSmall = &FontRoboto_Black_20;
}

void WriteText(textfont* font, int* text, int x, int y, int color)
{
	if(!font)
		return;

	if(*text == 0)
		return;

	set_multiply_color(color);
	textfont_print_from_left(font, x, y, text);
	set_multiply_color(color_white);
}



void LoadSettings()
{
	SelectedLevelPack = 0;
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&SelectedLevelPack, levelLocksSavePosition -1, sizeof (SelectedLevelPack));			
		}
	if((SelectedLevelPack < 0) || (SelectedLevelPack >= InstalledLevelPacksCount))
		SelectedLevelPack = 0;
	strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
}


void SaveSettings()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			card_write_data(&SelectedLevelPack, levelLocksSavePosition -1, sizeof (SelectedLevelPack));	
		}
}


void SearchForMusic()
{
	Music[0] = CAudio_LoadMusic("title");
	Music[1] = CAudio_LoadMusic("041415calmbgm");
	Music[2] = CAudio_LoadMusic("periwinkle");
	Music[3] = CAudio_LoadMusic("Puzzle Game 3");
	MusicCount = 4;
}


void SearchForLevelPacks()
{
	InstalledLevelPacksCount = MaxLevelPacks;
	strcpy(InstalledLevelPacks[0], "696.sok");
	strcpy(InstalledLevelPacks[1], "696 Part 2.sok");
	strcpy(InstalledLevelPacks[2], "Cosmonotes.sok");
	strcpy(InstalledLevelPacks[3], "Cosmopoly.sok");
	strcpy(InstalledLevelPacks[4], "Erim Sever Collection.sok");
	strcpy(InstalledLevelPacks[5], "GRIGoRusha 2001.sok");
	strcpy(InstalledLevelPacks[6], "GRIGoRusha 2002.sok");
	strcpy(InstalledLevelPacks[7], "GRIGoRusha Remodel Club.sok");
	strcpy(InstalledLevelPacks[8], "GRIGoRusha Special.sok");
	strcpy(InstalledLevelPacks[9], "GRIGoRusha Star.sok");
	strcpy(InstalledLevelPacks[10], "GRIGoRusha Sun.sok");
	strcpy(InstalledLevelPacks[11], "LOMA.sok");
	strcpy(InstalledLevelPacks[12], "Microcosmos.sok");
	strcpy(InstalledLevelPacks[13], "Minicosmos.sok");
	strcpy(InstalledLevelPacks[14], "Myriocosmos.sok");
	strcpy(InstalledLevelPacks[15], "Nabokosmos.sok");
	strcpy(InstalledLevelPacks[16], "Picokosmos.sok");
	strcpy(InstalledLevelPacks[17], "SokEvo.sok");
	strcpy(InstalledLevelPacks[18], "SokHard.sok");
	strcpy(InstalledLevelPacks[19], "SokWhole.sok");
	SelectedLevelPack=0;
	strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
}


bool AskQuestion(int *Msg)
{
	CAudio_PlaySound(Sounds[SND_SELECT],0);
	bool Result = false;
	CInput *Input = CInput_Create(InputDelay);
	set_multiply_color(MenuBoxColor);
	draw_filled_rectangle(50*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	set_multiply_color(MenuBoxBorderColor);
	draw_rectangle(50*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	draw_rectangle(51*UI_WIDTH_SCALE,81.5*UI_HEIGHT_SCALE,269*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE);
	set_multiply_color(color_white);
	WriteText(font,Msg,55*UI_WIDTH_SCALE,85*UI_HEIGHT_SCALE,MenuTextColor);
	end_frame();
	CInput_WaitNoInput(Input);
	{
		while (!( Input->JoystickHeld[0][(BUT_A)] || Input->JoystickHeld[0][(BUT_X)] || Input->JoystickHeld[0][(BUT_START)] ))
		{
		    CInput_Update(Input);			
			end_frame();
		}
		if (Input->JoystickHeld[0][(BUT_A)] || Input->JoystickHeld[0][(BUT_START)])
		{
			CAudio_PlaySound(Sounds[SND_SELECT],0);
			Result = true;
		}
		else
		{
			CAudio_PlaySound(Sounds[SND_BACK],0);
			Result = false;
		}

	}
	CInput_WaitNoInput(Input);
	CInput_Destroy(Input);
	return Result;
}

void PrintForm(int *msg)
{
	CAudio_PlaySound(Sounds[SND_SELECT],0);
    CInput *Input = CInput_Create(InputDelay);
	set_multiply_color(MenuBoxColor);
	draw_filled_rectangle(50*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	set_multiply_color(MenuBoxBorderColor);
	draw_rectangle(50*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	draw_rectangle(51*UI_WIDTH_SCALE,81.5*UI_HEIGHT_SCALE,269*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE);
	set_multiply_color(color_white);
	WriteText(font,msg,55*UI_WIDTH_SCALE,85*UI_HEIGHT_SCALE,MenuTextColor);
	end_frame();
	CInput_WaitNoInput(Input);
    while (!( Input->JoystickHeld[0][(BUT_A)] || Input->JoystickHeld[0][(BUT_START)]))
    {
        CInput_Update(Input);
        end_frame();
    }
	CAudio_PlaySound(Sounds[SND_SELECT],0);
	CInput_WaitNoInput(Input);
	CInput_Destroy(Input);
}

void SaveUnlockData()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			card_write_data(&UnlockedLevels, levelLocksSavePosition + SelectedLevelPack, sizeof (UnlockedLevels));			
		}
}

void LoadUnlockData()
{
	UnlockedLevels = 1;
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&UnlockedLevels, levelLocksSavePosition + SelectedLevelPack, sizeof (UnlockedLevels));			
		}
	if((UnlockedLevels < 1) || (UnlockedLevels > InstalledLevels))
		UnlockedLevels = 1;
}


void FindLevels()
{
	InstalledLevels= LevelPackFile->LevelCount;
}

void LoadGraphics()
{
	if(IMGBackground)
		freeTexture(IMGBackground);
	if(IMGFloor)
		freeTexture(IMGFloor);
	if(IMGPlayer)
		freeTexture(IMGPlayer);
	if(IMGBox)
		freeTexture(IMGBox);
	if(IMGSpot)
		freeTexture(IMGSpot);
	if(IMGEmpty)
		freeTexture(IMGEmpty);
	if(IMGWall)
		freeTexture(IMGWall);
	if(IMGTitleScreen)
		freeTexture(IMGTitleScreen);

	IMGBackground = newTextureHorz(0, 1, 1, 0, 0, 640, 360, 1.0, 1.0);
	IMGTitleScreen = newTextureHorz(0, 2, 1, 0, 360, 640, 360, 1.0, 1.0);
	IMGEmpty = newTextureHorz(0, 3, 1, 0, 720, 24, 24, 1.0, 1.0);
	IMGFloor = newTextureHorz(0, 4, 1, 24, 720, 24, 24, 1.0, 1.0);
	IMGSpot = newTextureHorz(0, 5, 1, 48, 720, 24, 24, 1.0, 1.0);
	IMGWall = newTextureHorz(0, 6, 1, 72, 720, 24, 24, 1.0, 1.0);
	IMGBox = newTextureHorz(0, 7, 2, 96, 720, 48, 24, 1.0, 1.0);
	IMGPlayer = newTextureHorz(0, 9, 16, 144, 720, 384, 24, 1.0, 1.0);
	isCustomnTitleScreen = false;
	MenuBoxColor = make_color_rgb(197,215,235);
	MenuBoxBorderColor = make_color_rgb(52,102,148);
	MenuTextColor = make_color_rgb(52,102,148);
}

void UnLoadGraphics()
{
	if(IMGBackground)
		freeTexture(IMGBackground);
	if(IMGFloor)
		freeTexture(IMGFloor);
	if(IMGPlayer)
		freeTexture(IMGPlayer);
	if(IMGBox)
		freeTexture(IMGBox);
	if(IMGSpot)
		freeTexture(IMGSpot);
	if(IMGEmpty)
		freeTexture(IMGEmpty);
	if(IMGWall)
		freeTexture(IMGWall);
	if(IMGTitleScreen)
		freeTexture(IMGTitleScreen);
}

void UnloadMusic()
{
	if (GlobalSoundEnabled)
	{
		CAudio_StopMusic();
		CAudio_UnloadMusics();
	}
}

void LoadSounds()
{
	if (GlobalSoundEnabled)
	{
		Sounds[SND_MENU] = CAudio_LoadSound("menu");
		Sounds[SND_SELECT] = CAudio_LoadSound("select");
		Sounds[SND_ERROR] = CAudio_LoadSound("error");
		Sounds[SND_STAGEEND] = CAudio_LoadSound("stageend");
		Sounds[SND_BACK] = CAudio_LoadSound("back");
		Sounds[SND_MOVE] = CAudio_LoadSound("move");
	}
}



void UnloadSounds()
{
	CAudio_StopSound();
	CAudio_UnloadSounds();
}

void printTitleInfo()
{
	int[250] Tekst;
	int w;
	if(LevelPackFile->Loaded)
	{
		strcpy(Tekst, "Vircoban");
		w = textfont_get_line_width(RobotoBig, Tekst);
		int TitleColor = make_color_rgb(174,198,234);
		WriteText(RobotoBig, Tekst, (ORIG_WINDOW_WIDTH - w) / 2, 10, TitleColor);

		if(strlen(LevelPackFile->author) > 0)
		{
			strcpy(Tekst, "Levels by ");
			strcat(Tekst, LevelPackFile->author);
			w = textfont_get_line_width(RobotoMedium, Tekst);
			WriteText(RobotoMedium, Tekst, (ORIG_WINDOW_WIDTH - w) / 2, 290, TitleColor);
		}
	}
}


#endif