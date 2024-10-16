#ifndef CREDITS_H
#define CREDITS_H

#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "CInput.h"
#include "Common.h"
#include "GameFuncs.h"

void Credits()
{
	CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		sleep(1);
	//hardcode for now
	int *LevelPackCreator = (int*) malloc(sizeof(int)* 21);
	strcpy(LevelPackCreator, "Bryant Brownell");
	int *Tekst = (int*) malloc(sizeof(int)* 500);
	strcpy(Tekst,"Blips was created by\nWillems Davy - Willems Soft 2008-2024.\nhttps://joyrider3774.itch.io\n\nLevelpack ");
	strcat(Tekst, LevelPackName);
	strcat(Tekst," was created\nby ");
	strcat(Tekst, LevelPackCreator);
	strcat(Tekst, ".");
	while (GameState == GSCredits)
	{
		drawTexture(IMGTitleScreen,0,0,0);

		CInput_Update(Input);

		//BUT_X BUT_Y BUT_A BUT_B
		if(Input->JoystickHeld[BUT_X] || Input->JoystickHeld[BUT_Y] || Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_B]|| Input->JoystickHeld[BUT_START])
        {
            GameState=GSTitleScreen;
			CAudio_PlaySound(Sounds[SND_BACK],0);
        }

		set_multiply_color(MenuBoxColor);
		draw_filled_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
		set_multiply_color(MenuBoxBorderColor);
		draw_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,160*UI_HEIGHT_SCALE);
		draw_rectangle(61*UI_WIDTH_SCALE,81*UI_HEIGHT_SCALE,259*UI_WIDTH_SCALE,159*UI_HEIGHT_SCALE);
		set_multiply_color(color_white);
		WriteText(font,Tekst,65*UI_WIDTH_SCALE,82*UI_HEIGHT_SCALE,MenuTextColor);
        end_frame();
	}
	free(Tekst);
	free(LevelPackCreator);
	CInput_Destroy(Input);
}

#endif