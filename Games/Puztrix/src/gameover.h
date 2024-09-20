#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "string.h"
#include "input.h"
#include "main.h"
#include "gameover.h"
#include "gamefuncs.h"

void GameOverInit()
{
	CAudio_PlaySound(Sounds[SND_GameOver],0);
    WasNewHighScore = AddHighScore(Score, WorldParts->LevelNumber);
}

void GameOver()
{
    if(GameState == GSGameOverInit)
	{
		GameOverInit();
		GameState = GSGameOver;
	}
	
	if (GameState == GSGameOver )
    {
		if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1))
		{
			CAudio_PlaySound(Sounds[SND_Select],0);
			if(WasNewHighScore)
				GameState=GSHighScoresInit;
			else
				GameState=GSTitleScreenInit;
        }
		drawTextureZoomed(IMGGameOver, 0, 0, 0);
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
    }
}

#endif