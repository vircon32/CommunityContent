#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CInput.h"
#include "fonts/font_13.h"
#include "fonts/font1_25.h"
#include "fonts/font2_30.h"
#include "CAudio.h"

#define levelLocksSavePosition 100

void UnLoadGraphics()
{
    freeTexture(IMGGrid);
    freeTexture(IMGWall);
	freeTexture(IMGBackground);
	freeTexture(IMGFloor);
	freeTexture(IMGPlayer);
	freeTexture(IMGBox);
	freeTexture(IMGEmpty);
	freeTexture(IMGDiamond);
	freeTexture(IMGBomb);
	freeTexture(IMGTitleScreen);
	freeTexture(IMGIntro1);
	freeTexture(IMGIntro2);
	freeTexture(IMGIntro3);
	freeTexture(IMGExplosion);
}


void LoadSounds()
{
	CAudio_Init();
	CAudio_SetSoundEnabled(true);
	CAudio_SetMusicEnabled(true);
	Music = CAudio_LoadMusic("title");		
	Sounds[SND_MENU] = CAudio_LoadSound("menu");
	Sounds[SND_SELECT] = CAudio_LoadSound("select");
	Sounds[SND_ERROR] = CAudio_LoadSound("error");
	Sounds[SND_STAGEEND] = CAudio_LoadSound("stageend");
	Sounds[SND_EXPLODE] = CAudio_LoadSound("explode");
	Sounds[SND_COLLECT] = CAudio_LoadSound("collect");
	Sounds[SND_BACK] = CAudio_LoadSound("menuback");
}

void UnloadSounds()
{
	CAudio_UnloadSounds();
	CAudio_UnloadMusics();
	CAudio_DeInit();
}

void FindLevels()
{
	InstalledLevels = 0;
	if(strcmp(LevelPackName, "Bips") == 0)
		InstalledLevels = 26;
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

void loadFonts()
{
	setupFontfont_13();
	setupFontfont1_25();
	setupFontfont2_30();
	font = &Fontfont_13;
	BigFont = &Fontfont2_30;
	MonoFont = &Fontfont1_25;
}

void SaveUnlockData()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			card_write_data(&UnlockedLevels, levelLocksSavePosition, sizeof (UnlockedLevels));
		}
}

void LoadUnlockData()
{
	UnlockedLevels = 1;
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&UnlockedLevels, levelLocksSavePosition, sizeof (UnlockedLevels));			
		}
}

bool AskQuestion(int *Msg)
{
	bool Result = false;
	CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		end_frame();
	set_multiply_color(MenuBoxColor);
	draw_filled_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	set_multiply_color(MenuBoxBorderColor);
	draw_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	draw_rectangle(61*UI_WIDTH_SCALE,81*UI_HEIGHT_SCALE,259*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE);
	set_multiply_color(color_white);
	WriteText(font,Msg,65*UI_WIDTH_SCALE,83*UI_HEIGHT_SCALE,MenuTextColor);
	end_frame();
	{
		//BUT_A BUT_X
		while (!( Input->JoystickHeld[BUT_A] ||  Input->JoystickHeld[BUT_X] || Input->JoystickHeld[BUT_START]))
		{
		    CInput_Update(Input);
			end_frame();
		}
		//BUT_A
		if (Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_START])
			Result = true;

	}
	//only return if no inputs are left
	while(CInput_HasInput(Input))
		end_frame();
	CInput_Destroy(Input);
	return Result;
}

void PrintForm(int *msg)
{
    CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		end_frame();
	set_multiply_color(MenuBoxColor);
	draw_filled_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	set_multiply_color(MenuBoxBorderColor);
	draw_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	draw_rectangle(61*UI_WIDTH_SCALE,81*UI_HEIGHT_SCALE,259*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE);
	set_multiply_color(color_white);
	WriteText(font,msg,65*UI_WIDTH_SCALE,83*UI_HEIGHT_SCALE,MenuTextColor);
    end_frame();
	//BUT_A
    while (!( Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_START]))
    {
        CInput_Update(Input);
        end_frame();
    }
	//only return if no inputs are left
	while(CInput_HasInput(Input))
		end_frame();
	CInput_Destroy(Input);
}

void SearchForLevelPacks()
{
	InstalledLevelPacksCount = 1;
	strcpy(&InstalledLevelPacks[0][0], "Bips");
	SelectedLevelPack=0;
	if (InstalledLevelPacksCount > 0)
	{
	 	strcpy(LevelPackName ,InstalledLevelPacks[SelectedLevelPack]);
	}
}

void LoadGraphics()
{
    IMGBackground = newTextureHorz(0,0,1,0,0,640,360,1.0,1.0);
	IMGGrid = newTextureHorz(0,1,1,0,360,640,360,1.0,1.0);
	IMGFloor = newTextureHorz(0,2,1,128,720,32,32,1.0,1.0);
	IMGWall = newTextureHorz(0,3,1,160,720,32,32,1.0,1.0);
	IMGBomb = newTextureHorz(0,4,1,0,720,32,32,1.0,1.0);
	IMGDiamond = newTextureHorz(0,5,1,64,720,32,32,1.0,1.0);
	IMGBox = newTextureHorz(0,6,1,32,720,32,32,1.0,1.0);
	IMGEmpty = newTextureHorz(0,7,1,96,720,32,32,1.0,1.0);
	IMGPlayer = newTextureHorz(0,8,16,0,752,16*32,32,1.0,1.0);
	IMGExplosion = newTextureHorz(0,40,8,192,720,8*32,32,1.0,1.0);
    IMGIntro1 = newTextureHorz(1,1,1,0,0,640,360,1.0,1.0);
	IMGIntro2 = newTextureHorz(1,2,1,0,360,640,360,1.0,1.0);
	IMGIntro3 = newTextureHorz(2,1,1,0,0,640,360,1.0,1.0);
	IMGTitleScreen = newTextureHorz(2,2,1,0,360,640,360,1.0,1.0);
}


#endif