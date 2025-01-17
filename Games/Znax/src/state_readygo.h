#ifndef STATEREADYGO_H
#define STATEREADYGO_H

#include "input.h"
#include "texture.h"
#include "cworldparts.h"
#include "gamefuncs.h"
#include "common.h"
#include "utilfuncs.h"

void ReadyGo()
{
    end_frame();
    CWorldParts_NewGame(World);
    Score = 0;
    int Time2 = getCurrentTimeMilliseconds();
    int Counter=0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    while (GameState == GSReadyGo)
    {
        if(gamepad_button_b() == 1)
		    GameState = GSTitleScreen;

		CWorldParts_Draw(World);
		switch(Counter)
		{
		    case 1 :
                drawTexture(IMGReady, 0, ((NrOfCols * TileWidth+10) - IMGReady->width) / 2, (WINDOW_HEIGHT - IMGReady->height) / 2);
                break;
            case 2 :
                drawTexture(IMGGo, 0, ((NrOfCols * TileWidth+10) - IMGGo->width) / 2, (WINDOW_HEIGHT - IMGGo->height) / 2);
                break;
            case 3 :
                GameState = GSGame;
                break;
		}
        drawStatusBar();
        end_frame();
        if (Time2 < getCurrentTimeMilliseconds())
        {
            Counter++;
            if(Counter == 1)
                CAudio_PlaySound(Sounds[SND_READYGO],0);
            if (Counter == 2)
            {
                Time2 = getCurrentTimeMilliseconds() + 400;
            }
            else
                Time2 = getCurrentTimeMilliseconds() + 900;
        }

    }
}


#endif