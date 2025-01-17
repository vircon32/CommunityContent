#ifndef STATEINTRO_H
#define STATEINTRO_H

#include "input.h"
#include "texture.h"
#include "gamefuncs.h"
#include "common.h"
#include "input.h"
#include "utilfuncs.h"

void Intro()
{
    int Time=0;
    int IntroScreenNr = 1;
    Time = getCurrentTimeMilliseconds();
    while (GameState == GSIntro)
    {
        if((gamepad_button_a() > 0) || (gamepad_button_b() > 0) || (gamepad_button_start() > 0) ||
            (gamepad_button_x() > 0) || (gamepad_button_y() > 0))
            GameState = GSTitleScreen;
    
        switch(IntroScreenNr)
        {
            case 1 :
                drawTexture(IMGIntro1, 0, 0, 0);
                break;
            case 2 :
                drawTexture(IMGIntro2, 0, 0, 0);
                break;
            case 3 :
                drawTexture(IMGIntro3, 0, 0, 0);
                break;
        }
        end_frame();

        if(Time + 3700 < getCurrentTimeMilliseconds())
        {
            IntroScreenNr++;
            if(IntroScreenNr > 3)
                GameState = GSTitleScreen;
            Time = getCurrentTimeMilliseconds();
        }

    }
    CAudio_PlayMusic(Music[0], -1);
    CAudio_PlaySound(Sounds[SND_WELCOME],0);
}


#endif