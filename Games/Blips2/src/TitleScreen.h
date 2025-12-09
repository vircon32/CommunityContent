#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "CInput.h"
#include "Common.h"
#include "GameFuncs.h"

void TitleScreen()
{
	int Teller, Selection = 1;
	CInput *Input = CInput_Create(InputDelay);
	while(CInput_HasInput(Input))
		sleep(1);
	int *Tekst = (int*) malloc(sizeof(int)* 300);
	memset(Tekst, 0, sizeof(int)* 300);
	if(!CAudio_IsMusicPlaying())
		CAudio_PlayMusic(Music, -1);
	while (GameState == GSTitleScreen)
	{
		CInput_Update(Input);
		drawTexture(IMGTitleScreen,0,0,0);
		//BUT_LEFT
        if (CInput_Ready(Input) && ( Input->JoystickHeld[BUT_LEFT]))
        {
            if(Selection==2)
                if (InstalledLevelPacksCount > 0)
                {
                    CAudio_PlaySound(Sounds[SND_MENU],0);
                    SelectedLevelPack--;
                    if(SelectedLevelPack < 0)
                        SelectedLevelPack = InstalledLevelPacksCount - 1;                   
                    strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
                    SaveSettingsData();                    
                }
            CInput_Delay(Input);
        }
		//BUT_RIGHT
        if (CInput_Ready(Input) && (Input->JoystickHeld[BUT_RIGHT]))
        {
            if (Selection==2)
                if (InstalledLevelPacksCount > 0)
                {
                    CAudio_PlaySound(Sounds[SND_MENU],0);
                    SelectedLevelPack++;
                    if(SelectedLevelPack >= InstalledLevelPacksCount)
                        SelectedLevelPack = 0;
                    strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
                    SaveSettingsData(); 
                }
            CInput_Delay(Input);
        }
		//BUT_DOWN 
        if(CInput_Ready(Input) && (Input->JoystickHeld[BUT_DOWN]))
        {
            if (Selection < 4)
            {
                Selection++;
                CAudio_PlaySound(Sounds[SND_MENU],0);
            }

            CInput_Delay(Input);
        }
		//BUT_UP
        if(CInput_Ready(Input) && (Input->JoystickHeld[BUT_UP]))
        {
            if (Selection > 1)
            {
                Selection--;
                CAudio_PlaySound(Sounds[SND_MENU],0);
            }
            CInput_Delay(Input);
        }
		//BUT_A
        if(CInput_Ready(Input) && (Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_START]))
        {
            switch(Selection)
            {
                case 1:
                    if (InstalledLevelPacksCount >0)
                    {
                        FindLevels();
                        if(InstalledLevels > 0)
                        {
                            LoadUnlockData();
                            SelectedLevel=UnlockedLevels;
                            GameState=GSStageSelect;
                            CAudio_PlaySound(Sounds[SND_SELECT],0);
                        }
                        else
                        {
                            CAudio_PlaySound(Sounds[SND_SELECT],0);
                            drawTexture(IMGTitleScreen,0,0,0);
                            strcpy(Tekst,"There are no levels found in levelpack\n");
							strcat(Tekst,LevelPackName);
							strcat(Tekst,"\n\nPlease create a level for this level pack\nfirst!");
                            PrintForm(Tekst);
                            CInput_Reset(Input);
                        }
                    }
                    break;
                case 2:
                    if (InstalledLevelPacksCount > 0)
                    {
                        CAudio_PlaySound(Sounds[SND_MENU],0);
                        SelectedLevelPack++;
                        if(SelectedLevelPack >= InstalledLevelPacksCount)
                            SelectedLevelPack = 0;
                        strcpy(LevelPackName,InstalledLevelPacks[SelectedLevelPack]);
                        SaveSettingsData(); 
                    }
                    break;
                case 3:
                    GameState=GSInstructions;
                    CAudio_PlaySound(Sounds[SND_SELECT],0);
                    break;
                case 4:
                    GameState=GSCredits;
                    CAudio_PlaySound(Sounds[SND_SELECT],0);
                    break;
            }
            CInput_Delay(Input);
        }
		set_multiply_color(MenuBoxColor);
		draw_filled_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,170*UI_HEIGHT_SCALE);
		set_multiply_color(MenuBoxBorderColor);
		draw_rectangle(60*UI_WIDTH_SCALE,80*UI_HEIGHT_SCALE,260*UI_WIDTH_SCALE,170*UI_HEIGHT_SCALE);
		draw_rectangle(62*UI_WIDTH_SCALE,82*UI_HEIGHT_SCALE,258*UI_WIDTH_SCALE,168*UI_HEIGHT_SCALE);
		set_multiply_color(color_white);
		strcpy(Tekst,"Play Selected LevelPack\n<");
		strcat(Tekst,LevelPackName);
		strcat(Tekst,">\nInstructions\nCredits");
		BigFont->line_separation = 10;
		WriteText(BigFont,Tekst,90*UI_WIDTH_SCALE,90*UI_HEIGHT_SCALE,MenuTextColor);
		if (Selection > 1)
		{
			strcpy(Tekst,"\n");
			for(Teller=2;Teller<Selection;Teller++)
				strcat(Tekst,"\n");
			strcat(Tekst, ">>");
		}
		else
			strcpy(Tekst,">>");
		WriteText(BigFont,Tekst,65*UI_WIDTH_SCALE,90*UI_HEIGHT_SCALE,MenuTextColor);
		BigFont->line_separation = 2;
		end_frame();
	}
	free(Tekst);
	CInput_Destroy(Input);
}


#endif