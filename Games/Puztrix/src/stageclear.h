#ifndef STAGECLEAR_H
#define STAGECLEAR_H

#include "input.h"
#include "string.h"
#include "caudio.h"
#include "main.h"
#include "gamefuncs.h"

void StageClearInit()
{
    CAudio_PlaySound(Sounds[SND_Win],0);
	ScoreStatus = 0;
	RetryScore=Retries*1000;
    ClearScore=((WorldParts->LevelNumber / 10) + 1)*1000;
    MoveScore=MaxMoves*500;
    TotalScore=RetryScore+ClearScore+MoveScore;
	Movement = MNone;
}

void StageClear()
{

	if(GameState == GSStageClearInit)
	{
		StageClearInit();
		GameState = GSStageClear;
	}
	bool playBackSound = true;
    if (GameState == GSStageClear)
    {
		
		drawTextureZoomed(IMGLevelDone, 0, 0, 0);
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

		strcpy(Text,"Clear Bonus: ");
		itoa((WorldParts->LevelNumber / 10) + 1, Nr, 10);
		strcat(Text, Nr);
		strcat(Text, "x1000 = ");
		itoa(ClearScore, Nr, 10);
		strcat(Text, Nr);
		strcat(Text,"\nRetry Bonus: ");
		itoa(Retries, Nr, 10);
		strcat(Text, Nr);
		strcat(Text,"x1000 = ");
		itoa(RetryScore, Nr, 10);
		strcat(Text, Nr);
		strcat(Text,"\nMoves Bonus:");
		itoa(MaxMoves, Nr, 10);
		strcat(Text, Nr);
		strcat(Text,"x500  = ");
		itoa(MoveScore, Nr, 10);
		strcat(Text, Nr);
        drawTextColor(font, Text, 182*xscale, 65*yscale, ColorSelection);


		strcpy(Text,"Total Bonus: ");
		itoa(TotalScore, Nr, 10);
		strcat(Text, Nr);
        drawTextColor(BigFont, Text, 182*xscale, 140*yscale, ColorSelection);

		strcpy(Text,"Score: ");
		itoa(Score, Nr, 10);
		strcat(Text, Nr);
        drawTextColor(BigFont, Text, 182*xscale, 170*yscale, ColorSelection);

		DrawArrows();

		if(gamepad_button_b() == 1)
		{
			GameState = GSTitleScreenInit;
			playBackSound = false;
		}

		if ((gamepad_button_a() == 1))
		{
			ScoreStatus++;
			if(ScoreStatus ==3)
			{
				if(WorldParts->LevelNumber + 1 <= LevelCount)
				{
					CWorldParts_IncLevel(WorldParts);
					GameState=GSGameInit;
				}
				else
				{
					GameState = GSLevelpackDoneInit;
				}
			}
        }
        if(ScoreStatus == 1)
        {
            if(TotalScore > 0)
            {
                Score+=100;
                TotalScore -=100;
                if(TotalScore % 300 == 0)
                    CAudio_PlaySound(Sounds[SND_Score],0);
            }
            else
                ScoreStatus++;
        }

        if(ScoreStatus == 2)
        {
             Score+=TotalScore;
             TotalScore = 0;
        }
    }
	if(playBackSound && (GameState != GSStageClear) && (GameState != GSStageClearInit))
    	CAudio_PlaySound(Sounds[SND_WinExit],0);
}

#endif