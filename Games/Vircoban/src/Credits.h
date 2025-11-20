#ifndef CREDITS_H
#define CREDITS_H

#include "Texture.h"
#include "Credits.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CInput.h"

void Credits()
{
    CInput *Input = CInput_Create(InputDelay);
	int[1000] Tekst;
	if(InstalledLevelPacksCount > 0)
	{
		strcpy(Tekst,"Vircoban was created by\nWillems Davy - Willems Soft 2006-2025.\nHttps://joyrider3774.itch.io\n\nLevelpack ");
		strcat(Tekst,LevelPackName);
		strcat(Tekst," was created\nby ");
		strcat(Tekst,LevelPackFile->author);
		strcat(Tekst,".");
	}
	drawTexture(IMGTitleScreen,0,0,0);

	set_multiply_color(MenuBoxColor);
	draw_filled_rectangle(50*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	set_multiply_color(MenuBoxBorderColor);
	draw_rectangle(50*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
	draw_rectangle(51*UI_WIDTH_SCALE,81.5*UI_HEIGHT_SCALE,269*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE);
	set_multiply_color(color_white);
	WriteText(font,Tekst,55*UI_WIDTH_SCALE,85*UI_HEIGHT_SCALE,MenuTextColor);
	printTitleInfo();
	end_frame();

	CInput_WaitNoInput(Input);		
	while (GameState == GSCredits)
	{
		CInput_Update(Input);
		if (CInput_Ready(Input) && ((Input->JoystickHeld[0][BUT_A] || Input->JoystickHeld[0][(BUT_X)] || Input->JoystickHeld[0][(BUT_Y)] || Input->JoystickHeld[0][(BUT_B)] || Input->JoystickHeld[0][(BUT_START)] )))
        {
			CAudio_PlaySound(Sounds[SND_BACK],0);
		    GameState = GSTitleScreen;
		}
		end_frame();
	}
	CInput_Destroy(Input);
}


#endif