#ifndef STAGESELECT_H
#define STAGESELECT_H

#include "Defines.h"
#include "string.h"
#include "Texture.h"
#include "StageSelect.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CInput.h"
#include "debugspeed.h"


void StageSelect()
{
    CInput *Input = CInput_Create(InputDelay);
	CInput_WaitNoInput(Input);
	int[400] Tekst;
	int[10] Nr;
	SelectedMusic = 0;
	if(MusicCount > 0)
		if (! CAudio_IsMusicPlaying())
			CAudio_PlayMusic(Music[SelectedMusic],-1);

	if (SelectedLevel > 0)
	{
		CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);	
	}
	else
		CWorldParts_RemoveAll(WorldParts);

	while (GameState == GSStageSelect)
	{
#ifdef DEBUG
		StartDebugSpeed(2);
#endif
		drawTexture(IMGBackground,0,0,0);
		if (SelectedLevel > 0)
		{
			//CWorldParts_Move(WorldParts);
			CWorldParts_Draw(WorldParts);
			if((InstalledLevels > 0))
			{
				set_multiply_color(MenuBoxColor);
				draw_filled_rectangle(0,ORIG_WINDOW_HEIGHT- 13*UI_HEIGHT_SCALE,320*UI_WIDTH_SCALE,ORIG_WINDOW_HEIGHT);
				set_multiply_color(MenuBoxBorderColor);
				draw_rectangle(0,ORIG_WINDOW_HEIGHT- 13*UI_HEIGHT_SCALE,320*UI_WIDTH_SCALE,ORIG_WINDOW_HEIGHT);
				set_multiply_color(color_white);
				if(WorldParts->isLevelPackFileLevel)
				{
					if ((strlen(LevelPackFile->LevelsMeta[SelectedLevel-1].title) > 0) || (strlen(LevelPackFile->LevelsMeta[SelectedLevel-1].author) > 0))
					{
						if(strlen(LevelPackFile->LevelsMeta[SelectedLevel-1].author) > 0)
						{
							strcpy(Tekst, LevelPackFile->LevelsMeta[SelectedLevel-1].title);
							strcat(Tekst, " by ");
							strcat(Tekst,LevelPackFile->LevelsMeta[SelectedLevel-1].author);
						}
						else
						{
							strcpy(Tekst, LevelPackFile->LevelsMeta[SelectedLevel-1].title);
							strcat(Tekst, " by ");
							strcat(Tekst,LevelPackFile->author);
						}
						int w;
						w = textfont_get_line_width(font, Tekst);
						WriteText(font,Tekst,(ORIG_WINDOW_WIDTH - w) / 2,ORIG_WINDOW_HEIGHT- 12*UI_HEIGHT_SCALE,MenuTextColor);
					}					
				}
			}
		}
		set_multiply_color(MenuBoxColor);
		draw_filled_rectangle(0,0,320*UI_WIDTH_SCALE,13*UI_HEIGHT_SCALE);
		set_multiply_color(MenuBoxBorderColor);
		draw_rectangle(0,-1,320*UI_WIDTH_SCALE,13*UI_HEIGHT_SCALE);
		set_multiply_color(color_white);
		strcpy(Tekst,"Level Pack: ");
		strcat(Tekst, LevelPackName);
		strcat(Tekst," Level:");
		itoa(SelectedLevel, Nr, 10);
		strcat(Tekst, Nr);
		strcat(Tekst, "/");
		itoa(InstalledLevels, Nr, 10);
		strcat(Tekst, Nr);
		if(SelectedLevel <= UnlockedLevels)
		{
			strcat(Tekst, " - (A) Play Level");
		}
		else
		{
			strcat(Tekst, " - Level is locked!");
		}
		
		WriteText(font,Tekst,2*UI_WIDTH_SCALE,1*UI_HEIGHT_SCALE,MenuTextColor);

        CInput_Update(Input);


		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_B)]))
		{
			GameState= GSTitleScreen;
			CAudio_PlaySound(Sounds[SND_BACK],0);
			CWorldParts_RemoveAll(WorldParts);
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_A)]))
		{
			CAudio_PlaySound(Sounds[SND_SELECT],0);
			if (SelectedLevel <= UnlockedLevels)
				GameState = GSGame;
			else
			{
				strcpy(Tekst,"This Level Hasn't been unlocked yet!\nDo you want to play the last unlocked\nlevel ");
				itoa(UnlockedLevels, Nr, 10);
				strcat(Tekst, Nr);
				strcat(Tekst, "/");
				itoa(InstalledLevels, Nr, 10);
				strcat(Tekst, Nr);
				strcat(Tekst,"\n\nPress (A) to Play (X) to Cancel");
				if	(AskQuestion(Tekst))
				{									
					SelectedLevel = UnlockedLevels;
					CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);
					GameState = GSGame;
				}
				CInput_Reset(Input);
			}
			CInput_Delay(Input);
		}
		
		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_L)]))
		{
			if(SelectedLevel != 1)
			{								
				CAudio_PlaySound(Sounds[SND_MENU],0);
				
				SelectedLevel -= 5;	
				if (SelectedLevel < 1)
					SelectedLevel = 1;
				CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);
			}
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_R)]))
		{
			if(SelectedLevel != InstalledLevels)
			{
				CAudio_PlaySound(Sounds[SND_MENU],0);
				
				SelectedLevel +=5;
				if (SelectedLevel > InstalledLevels)
					SelectedLevel = InstalledLevels;
				CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);
			}
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_LEFT)]))
		{
			if(SelectedLevel != 1)
			{
				CAudio_PlaySound(Sounds[SND_MENU],0);
				
				SelectedLevel--;
				if (SelectedLevel < 1)
					SelectedLevel = 1;
				CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);
			}
			CInput_Delay(Input);
		}

		if ( CInput_Ready(Input) &&  (Input->JoystickHeld[0][(BUT_RIGHT)]))
		{
			if(SelectedLevel != InstalledLevels)
			{
				SelectedLevel++;
				CAudio_PlaySound(Sounds[SND_MENU],0);
				if (SelectedLevel > InstalledLevels)
					SelectedLevel = InstalledLevels;
				
				CWorldParts_LoadFromLevelPackFile(WorldParts,LevelPackFile, SelectedLevel, true);
			}
			CInput_Delay(Input);
		}
#ifdef DEBUG
		StopDebugSpeed(2);
		int[500] Debug;
		int[100] Nr;
		itoa(MemoryUsed(), Nr, 10);
		strcpy(Debug, "RAM: ");
		strcat(Debug, Nr);
		itoa(WorldParts->ItemCount, Nr, 10);
		strcat(Debug, "\nITEMS: ");
		strcat(Debug, Nr);
		set_multiply_color(make_color_rgb(255,0,255));
		print_at(0,10,Debug);
		printDebugSpeed(1, 0,60,"LVL LOAD ", 1.0);
		printDebugSpeed(2, 0,80,"FRAME S ", 1.0);
		printDebugSpeed(5, 0,120,"PACK LOAD ", 1.0);
        set_multiply_color(color_white);
#endif
		end_frame();

	}
	CInput_Destroy(Input);
}


#endif