#ifndef LEVELPACKDONE_h
#define LEVELPACKDONE_h

#include "input.h"
#include "string.h"
#include "main.h"
#include "levelpackdone.h"
#include "gamefuncs.h"

void LevelpackDoneInit()
{
	WasNewHighScore = AddHighScore(Score, WorldParts->LevelNumber);
}

void LevelpackDone()
{
    if (GameState == GSLevelpackDoneInit)
	{
		LevelpackDoneInit();
		GameState = GSLevelpackDone;
	}
   
    if (GameState == GSLevelpackDone)
    {

		drawTextureZoomed(IMGLevelpackDone, 0, 0, 0);
		
		int[100] Text;
		int[10] Nr;
		strcpy(Text,"Score: ");
		itoa(Score, Nr, 10);
		strcat(Text, Nr);
		strcat(Text,"\nLevel Number: ");
		itoa(WorldParts->LevelNumber, Nr, 10);
		strcat(Text, Nr);
		strcat(Text,"\nMoves Left: ");
		itoa(MaxMoves, Nr , 10);
		strcat(Text, Nr);
		strcat(Text,"\nRetry: ");
		itoa(Retries, Nr, 10);
		strcat(Text, Nr);
        drawTextColor(font, Text, 21*xscale, 50*yscale, ColorSelection);

		DrawArrows();
		
		if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1))
		{
			CAudio_PlaySound(Sounds[SND_Select],0);
            if(WasNewHighScore)
				GameState=GSHighScoresInit;
			else
				GameState=GSTitleScreenInit;
        }
    }
}


#endif