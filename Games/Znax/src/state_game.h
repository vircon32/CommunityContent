#ifndef STATEGAME_H
#define STATEGAME_H

#include "input.h"
#include "texture.h"
#include "cworldparts.h"
#include "gamefuncs.h"
#include "common.h"
#include "cselector.h"
#include "utilfuncs.h"

void Game()
{
    end_frame();
    int Time = getCurrentTimeMilliseconds();
    int ScoreTimer = 0;
    CSelector* Selector = CSelector_Create(NrOfCols / 2, NrOfRows / 2);
    int TextColor = make_color_rgba(255,255,255,255);
    int AddToScore = 0;
    int[500] Text;
    int[20] Nr;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    while (GameState == GSGame)
    {
        if(gamepad_left() % 10 == 1)
            CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);

        if(gamepad_right() % 10 == 1)
            CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);

        if(gamepad_up() % 10 == 1)
            CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);

        if(gamepad_down() % 10 == 1)
            CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);

        if(gamepad_button_b() == 1)
            GameState = GSTitleScreen;

        if((gamepad_button_a() == 1) || (gamepad_button_x() == 1) || (gamepad_button_y() == 1))
        {
            AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
            if(AddToScore != 0)
            {
                ScoreTimer = getCurrentTimeMilliseconds() + 700;
            }
        }
		CWorldParts_Draw(World);
        CSelector_Draw(Selector);
        drawStatusBar();
        if(AddToScore !=0)
        {
            if(ScoreTimer > getCurrentTimeMilliseconds())
            {
                strcpy(Text, "+");
                itoa(AddToScore, Nr, 10);
                strcat(Text, Nr);
                WriteText(font,Text,345*SCALE,115*SCALE,TextColor);
                if(GameType == Relative)
                {
                    strcpy(Text, "+");
                    itoa(floor(AddToScore / 400.0), Nr, 10);
                    strcat(Text, Nr);
                    WriteText(font,Text,345*SCALE,50*SCALE,TextColor);
                }
            }
            else
            {
                ScoreTimer = 0;
                Score +=AddToScore;
                if (GameType == Relative)
                    Timer += floor(AddToScore / 400.0);
                AddToScore = 0;
            }
        }
        
        end_frame();
        if (Time +1000 < getCurrentTimeMilliseconds())
        {
            Timer-= 1;
            switch (Timer)
            {
                case 60:
                    CAudio_PlaySound(Sounds[SND_1MINUTE],0);
                    break;
                case 3 :
                    CAudio_PlaySound(Sounds[SND_3],0);
                    break;
                case 2 :
                    CAudio_PlaySound(Sounds[SND_2],0);
                    break;
                case 1 :
                    CAudio_PlaySound(Sounds[SND_1],0);
                    break;
                case 0 :
                    if(ScoreTimer != 0)
                    {
                        Score += AddToScore;
                        if(GameType == Relative)
                            Timer += AddToScore / 200;
                    }
                    if(Timer == 0)
                    {
                        CAudio_PlaySound(Sounds[SND_TIMEOVER],0);
                        GameState = GSTimeOver;
                    }
                    break;
            }
            Time = getCurrentTimeMilliseconds();
        }

    }
    CSelector_Destroy(Selector);
}


#endif