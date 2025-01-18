#ifndef STATETIMEOVER_H
#define STATETIMEOVER_H

#include "input.h"
#include "texture.h"
#include "cworldparts.h"
#include "gamefuncs.h"
#include "common.h"
#include "state_gethighscorename.h"
#include "utilfuncs.h"

void TimeOver()
{
    end_frame();
    int[21] Name;
    int Teller1,Teller2;
    int Time2 = getCurrentTimeMilliseconds() + 1250;
    int Counter=0;
    memset(&Name[0], 0, 21 * sizeof(int));
    CWorldParts_DeSelect(World, false);

    while (GameState == GSTimeOver)
    {
        if(gamepad_button_b() == 1)
		    GameState = GSTitleScreen;

		CWorldParts_Draw(World);
		switch(Counter)
		{
		    case 0 :
                drawTexture(IMGTimeOver, 0, ((NrOfCols * TileWidth+10) - IMGTimeOver->width) / 2, (WINDOW_HEIGHT - IMGTimeOver->height) / 2);
                break;
		}
        drawStatusBar();
        end_frame();
        if (Time2 < getCurrentTimeMilliseconds())
        {
            GameState = GSShowHighScores;
        }

    }
    for(Teller1 =0;Teller1<10;Teller1++)
        if(HighScores[GameType][Teller1].PScore < Score)
        {
            GetHighScoreName(Name,Teller1,Score);
            for(Teller2=8;Teller2>=Teller1;Teller2--)
                HighScores[GameType][Teller2+1] = HighScores[GameType][Teller2];
            if((strcmp(Name," ") == 0))
                strcpy(HighScores[GameType][Teller1].PName, "player");
            else
                strcpy(HighScores[GameType][Teller1].PName, Name);
            HighScores[GameType][Teller1].PScore = Score;
            SaveHighScores();
            break;
        }
}


#endif