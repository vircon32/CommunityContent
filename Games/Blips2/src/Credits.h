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
	int *Tekst1 = (int*) malloc(sizeof(int)* 500);
	int *Tekst2 = (int*) malloc(sizeof(int)* 500);
	int *Tekst3 = (int*) malloc(sizeof(int)* 500);
	strcpy(Tekst1,"Blips was created by Willems Davy (2008-2025).\nhttps://joyrider3774.itch.io");
	strcpy(Tekst2,"Original games by Bryant Brownell.\nbryant.brownell@gmail.com");
	strcpy(Tekst3,"Levelpack ");
	strcat(Tekst3, LevelPackName);
	strcat(Tekst3," was created\nby ");
	strcat(Tekst3, LevelPackCreator);
	strcat(Tekst3, ".");
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
		draw_rectangle(62*UI_WIDTH_SCALE,82*UI_HEIGHT_SCALE,258*UI_WIDTH_SCALE,158*UI_HEIGHT_SCALE);
		set_multiply_color(color_white);
		WriteText(font,Tekst1,65*UI_WIDTH_SCALE,82*UI_HEIGHT_SCALE,MenuTextColor);
		WriteText(font,Tekst2,65*UI_WIDTH_SCALE,107*UI_HEIGHT_SCALE,MenuTextColor);
		WriteText(font,Tekst3,65*UI_WIDTH_SCALE,132*UI_HEIGHT_SCALE,MenuTextColor);
        end_frame();
	}
	free(Tekst1);
	free(Tekst2);
	free(Tekst3);
	free(LevelPackCreator);
	CInput_Destroy(Input);
}

#endif