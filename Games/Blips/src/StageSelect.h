#ifndef STAGESELECT_H
#define STAGESELECT_H

#include "time.h"
#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "CInput.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CWorldParts.h"

void StageSelect()
{
	int[300] Tekst;
    CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		sleep(1);
	if (SelectedLevel > 0)
	{
		CWorldParts_Load(WorldParts, SelectedLevel-1);
	}
	else
		CWorldParts_RemoveAll(WorldParts);

	while (GameState == GSStageSelect)
	{
        if(GlobalSoundEnabled)           
		drawTexture(IMGBackground,0,0,0);
		CWorldParts_Draw(WorldParts);
		set_multiply_color(MenuBoxColor);
		draw_filled_rectangle(0,0,ORIG_WINDOW_WIDTH-1,13*UI_HEIGHT_SCALE);
		set_multiply_color(MenuBoxBorderColor);
		draw_rectangle(0,-1,ORIG_WINDOW_WIDTH-1,13*UI_HEIGHT_SCALE);
		set_multiply_color(color_white);
		
		strcpy(Tekst,"Level Pack: ");
		strcat(Tekst,LevelPackName);
		strcat(Tekst," Level:");
		int[10] tmpText;
		itoa(SelectedLevel,tmpText,10);
		strcat(Tekst, tmpText);
		strcat(Tekst, "/");
		itoa(InstalledLevels,tmpText,10);
		strcat(Tekst, tmpText);
		if(SelectedLevel <= UnlockedLevels)
		{	
			strcat(Tekst," - (A) Play Level");
		}
		else
		{
			strcat(Tekst," - Level is locked!");
		}
		WriteText(font,Tekst,2,0,MenuTextColor);
		CInput_Update(Input);

		//BUT_SELECT
        if(Input->JoystickHeld[BUT_B])
        {
            GameState= GSTitleScreen;
			CAudio_PlaySound(Sounds[SND_BACK],0);
        }
		
		//BUT_A
        if(CInput_Ready(Input) && (Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_START]))
        {
            CAudio_PlaySound(Sounds[SND_SELECT],0);
			if (SelectedLevel <= UnlockedLevels)
				GameState = GSGame;
			else
			{
				strcpy(Tekst,"This Level Hasn't been unlocked yet!\nDo you want to play the last unlocked\nlevel ");
				itoa(UnlockedLevels, tmpText, 10);
				strcat(Tekst, tmpText);
				strcat(Tekst,"/");
				itoa(InstalledLevels, tmpText, 10);
				strcat(Tekst, tmpText);
				strcat(Tekst,"\n\nPress (A) to Play (X) to Cancel");
				if	(AskQuestion(Tekst))
				{
					SelectedLevel = UnlockedLevels;
					CWorldParts_Load(WorldParts, SelectedLevel-1);
					GameState = GSGame;
				}
				CInput_Reset(Input);
			}
            CInput_Delay(Input);
        }

		//BUT_L
        if (CInput_Ready(Input) && (Input->JoystickHeld[BUT_L]))
        {
			if(SelectedLevel != 1)
			{	
				SelectedLevel -= 5;
				if (SelectedLevel < 1)
					SelectedLevel = 1;
				CAudio_PlaySound(Sounds[SND_SELECT],0);
				CWorldParts_Load(WorldParts, SelectedLevel-1);
				CInput_Delay(Input);
			}
        }
		//BUT_R
        if (CInput_Ready(Input) && ( Input->JoystickHeld[BUT_R]))
        {
			if(SelectedLevel != InstalledLevels)
			{
				SelectedLevel +=5;
				if (SelectedLevel > InstalledLevels)
					SelectedLevel = InstalledLevels;
				CAudio_PlaySound(Sounds[SND_SELECT],0);
				CWorldParts_Load(WorldParts, SelectedLevel-1);
				CInput_Delay(Input);
			}
        }
		//BUT_LEFT
        if (CInput_Ready(Input) && (Input->JoystickHeld[BUT_LEFT]))
        {
			if(SelectedLevel != 1)
			{
				SelectedLevel--;
				if (SelectedLevel < 1)
					SelectedLevel = 1;
				CAudio_PlaySound(Sounds[SND_SELECT],0);
				CWorldParts_Load(WorldParts, SelectedLevel-1);
				CInput_Delay(Input);
			}
        }
		//BUT_RIGHT
        if (CInput_Ready(Input) && ( Input->JoystickHeld[BUT_RIGHT]))
        {
			if(SelectedLevel != InstalledLevels)
			{
				SelectedLevel++;
				if (SelectedLevel > InstalledLevels)
					SelectedLevel = InstalledLevels;
				CAudio_PlaySound(Sounds[SND_SELECT],0);
				CWorldParts_Load(WorldParts, SelectedLevel-1);
				CInput_Delay(Input);
			}
        }
		end_frame();
	}
	CInput_Destroy(Input);
}


#endif