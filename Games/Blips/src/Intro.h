#ifndef INTRO_H
#define INTRO_H

#include "Texture.h"
#include "CInput.h"
#include "time.h"
#include "misc.h"
#include "Common.h"
#include "defines.h"
#include "GameFuncs.h"

void Intro()
{
    CInput *Input = CInput_Create(10);
    int Time=0;
    int IntroScreenNr = 1;
    Time = get_frame_counter();
    while (GameState == GSIntro)
    {
        CInput_Update(Input);
		//BUT_A BUT_B  BUT_X BUT_Y
        if(Input->JoystickHeld[BUT_A] || Input->JoystickHeld[BUT_B] || Input->JoystickHeld[BUT_X] || Input->JoystickHeld[BUT_Y] || Input->JoystickHeld[BUT_START])
        {
            GameState=GSTitleScreen;
        }

        switch(IntroScreenNr)
        {
            case 1 :
                drawTexture(IMGIntro1,0 ,0, 0);
                break;
            case 2 :
				drawTexture(IMGIntro2,0 ,0, 0);
                break;
            case 3 :
				drawTexture(IMGIntro3,0 ,0, 0);
                break;
        }
        end_frame();
        
        if(Time + (60 * 3.5) < get_frame_counter())
        {
            IntroScreenNr++;
            if(IntroScreenNr > 3)
                GameState = GSTitleScreen;
            Time = get_frame_counter();
        }

    }
}

#endif