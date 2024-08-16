#ifndef TITLESCREEN_H
#define TITLESCREEN_H


#include "input.h"
#include "string.h"
#include "main.h"
#include "titlescreen.h"
#include "gamefuncs.h"
#include "cworldparts.h"


void TitleScreenInit()
{
    Score=0;
}

void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState = GSTitleScreen;
	}
    
    if (GameState == GSTitleScreen)
    {
		if(gamepad_up() == 1)
		{
			CAudio_PlaySound( Sounds[SND_LevelEditorSelect], 0);
			titleSelection--;
			if (titleSelection < 0)
				titleSelection = 3;
		}

		if(gamepad_down() == 1)
		{
			CAudio_PlaySound( Sounds[SND_LevelEditorSelect], 0);
			titleSelection++;
			if (titleSelection > 3)
				titleSelection = 0;
		}

		if(gamepad_button_a() == 1)
		{
			CAudio_PlaySound( Sounds[SND_Select], 0);
			switch(titleSelection)
			{
				case 0:
					CWorldParts_SetLevel(WorldParts,1);
					Retries = 5;
					Score = 0;
					GameState=GSGameInit;
					break;
				case 1:
					GameState = GSHighScoresInit;
					break;
				case 2:
					GameState = GSOptionsInit;
					break;
				case 3:
					GameState = GSCreditsInit;
					break;
				default:
					break;
			}
			
        }
	
		drawTextureZoomed(IMGTitleScreen, 0, 0, 0);

		int LeftX = 145 * xscale;
		int color;
		
		if(titleSelection == 0)
			color = ColorSelection;
		else
			color = ColorNoSelection;
		drawTextColor(BigFont2, "Play", LeftX, 62*yscale, color);

		if(titleSelection == 1)
			color = ColorSelection;
		else
			color = ColorNoSelection;
		drawTextColor(BigFont2, "High Scores", LeftX, 94*yscale, color);

		if(titleSelection == 2)
			color = ColorSelection;
		else
			color = ColorNoSelection;
		drawTextColor(BigFont2, "Options", LeftX, 126*yscale, color);

		if(titleSelection == 3)
			color = ColorSelection;
		else
			color = ColorNoSelection;
		drawTextColor(BigFont2, "Credits",  LeftX, 158*yscale, color);
    }
}


#endif