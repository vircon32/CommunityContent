#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "video.h"
#include "Texture.h"
#include "Titlescreen.h"
#include "Common.h"
#include "GameFuncs.h"
#include "CInput.h"
#include "Debugspeed.h"

void TitleScreen()
{
    CInput *Input = CInput_Create(InputDelay);
	CInput_WaitNoInput(Input);
	int Teller, Selection = 1;
	int[300] Tekst;
	SelectedMusic = 0;
	if(MusicCount > 0)
		if (! CAudio_IsMusicPlaying())
			CAudio_PlayMusic(Music[SelectedMusic],-1);

	
	CLevelPackFile_loadFile(LevelPackFile,SelectedLevelPack, NrOfCols, NrOfRows, true);	
	while (GameState == GSTitleScreen)
	{
		drawTexture(IMGTitleScreen,0,0,0);

        CInput_Update(Input);
					
		if (CInput_Ready(Input) && (Input->JoystickHeld[0][(BUT_LEFT)]))
		{
			if(Selection==2)
				if (InstalledLevelPacksCount > 0)
				{
					SelectedLevelPack--;
					if(SelectedLevelPack < 0)
						SelectedLevelPack = InstalledLevelPacksCount - 1;
					strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);									
					CLevelPackFile_loadFile(LevelPackFile, SelectedLevelPack, NrOfCols, NrOfRows, true);									
					CAudio_PlaySound(Sounds[SND_MENU],0);
					SaveSettings();
				}
			CInput_Delay(Input);
		}

		if (CInput_Ready(Input) && (Input->JoystickHeld[0][(BUT_RIGHT)]))
		{
			if (Selection==2)
				if (InstalledLevelPacksCount > 0)
				{
					SelectedLevelPack++;
					if(SelectedLevelPack > InstalledLevelPacksCount-1)
						SelectedLevelPack = 0;
					strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
					CLevelPackFile_loadFile(LevelPackFile, SelectedLevelPack, NrOfCols, NrOfRows, true);
					CAudio_PlaySound(Sounds[SND_MENU],0);
					SaveSettings();
				}
			CInput_Delay(Input);
		}

		if (CInput_Ready(Input) && (Input->JoystickHeld[0][(BUT_UP)]))
		{
			if (Selection > 1)
			{
				Selection--;
				CAudio_PlaySound(Sounds[SND_MENU],0);
			}
			CInput_Delay(Input);
		}

		if (CInput_Ready(Input) && (Input->JoystickHeld[0][(BUT_DOWN)]))
		{
			if (Selection < 3)
			{
				Selection++;
				CAudio_PlaySound(Sounds[SND_MENU],0);
			}
			CInput_Delay(Input);
		}

		if (CInput_Ready(Input) && (Input->JoystickHeld[0][(BUT_A)]))
		{
			switch(Selection)
			{
				case 1:
					if (InstalledLevelPacksCount >0)
					{
						drawTexture(IMGTitleScreen,0,0,0);
						printTitleInfo();
						set_multiply_color(MenuBoxColor);
						draw_filled_rectangle(50*UI_WIDTH_SCALE,70*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,170*UI_HEIGHT_SCALE);
						set_multiply_color(MenuBoxBorderColor);
						draw_rectangle(50*UI_WIDTH_SCALE,70*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,170*UI_HEIGHT_SCALE);		
						draw_rectangle(51*UI_WIDTH_SCALE,71.5*UI_HEIGHT_SCALE,269*UI_WIDTH_SCALE,169*UI_HEIGHT_SCALE);
						set_multiply_color(color_white);
						strcpy(Tekst,"Loading Selected LevelPack:\n");
						strcat(Tekst,LevelPackName);
						WriteText(RobotoSmall,Tekst,80*UI_WIDTH_SCALE,87*UI_HEIGHT_SCALE,MenuTextColor);
						CAudio_PlaySound(Sounds[SND_SELECT],0);
						CLevelPackFile_loadFile(LevelPackFile,SelectedLevelPack, NrOfCols, NrOfRows, false);								
						FindLevels();
						if(InstalledLevels > 0)
						{										
							LoadUnlockData();
							SelectedLevel=UnlockedLevels;
							GameState=GSStageSelect;
						}
						else
						{							
							drawTexture(IMGTitleScreen,0,0,0);
							strcpy(Tekst,"There are no levels found in levelpack\n");
							strcat(Tekst, LevelPackName);
							strcat(Tekst, "\n\nPlease create a level for this level pack\nfirst!");
							PrintForm(Tekst);
							CInput_Reset(Input);
						}
					}
					break;
				case 2:
					if (InstalledLevelPacksCount > 0)
					{
						SelectedLevelPack++;
						if(SelectedLevelPack > InstalledLevelPacksCount-1)
							SelectedLevelPack = 0;
						strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
						CLevelPackFile_loadFile(LevelPackFile, SelectedLevelPack, NrOfCols, NrOfRows, true);
						CAudio_PlaySound(Sounds[SND_MENU],0);
						SaveSettings();
					}
					break;
				case 3:
					GameState=GSCredits;
					CAudio_PlaySound(Sounds[SND_SELECT],0);
					break;
			}
			CInput_Delay(Input);
		}
		if(GameState == GSTitleScreen)
		{
			printTitleInfo();

			set_multiply_color(MenuBoxColor);
			draw_filled_rectangle(50*UI_WIDTH_SCALE,70*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,170*UI_HEIGHT_SCALE);
			set_multiply_color(MenuBoxBorderColor);
			draw_rectangle(50*UI_WIDTH_SCALE,70*UI_HEIGHT_SCALE,270*UI_WIDTH_SCALE,170*UI_HEIGHT_SCALE);		
			draw_rectangle(51*UI_WIDTH_SCALE,71.5*UI_HEIGHT_SCALE,269*UI_WIDTH_SCALE,169*UI_HEIGHT_SCALE);
			set_multiply_color(color_white);
			strcpy(Tekst,"Play Selected LevelPack\n<");
			strcat(Tekst,LevelPackName);
			strcat(Tekst,">\nCredits");
			WriteText(RobotoSmall,Tekst,80*UI_WIDTH_SCALE,87*UI_HEIGHT_SCALE,MenuTextColor);
			if (Selection > 1)
			{
				strcpy(Tekst,"\n");
				for(Teller=2;Teller<Selection;Teller++)
					strcat(Tekst,"\n");
				strcat(Tekst,">>");
			}
			else
				strcpy(Tekst,">>");
			WriteText(RobotoSmall,Tekst,55*UI_WIDTH_SCALE,87*UI_HEIGHT_SCALE,MenuTextColor);
			end_frame();
		}
	}
	CInput_Destroy(Input);
}


#endif