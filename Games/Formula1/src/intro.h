#ifndef intro_h
#define intro_h

#define FRAMEDELAY 60

#include "video.h"
#include "input.h"
#include "commonvars.h"
#include "printfuncs.h"

void initIntro(void)
{

}

void intro(void)
{
    if (gameState == gsInitIntro)
    {
        initIntro();
        gameState -= gsInitDiff;
    }
    
    frames++;
    clear_screen(color_black);
    if (frames < FRAMEDELAY)
    {
        printMessage(introFont, (27 - 12) >> 1, 6,0,0, 24, "WILLEMS DAVY");
    }
    else
    {
        if (frames < FRAMEDELAY *2)
        {
            printMessage(introFont, (27-8) >> 1, 6,0,0, 24, "PRESENTS");
        }
		else
		{
			if (frames < FRAMEDELAY *5)
			{
				printMessage(introFont, (27-9) >> 1, 3,0,0, 24, "THANKS TO");
				printMessage(introFont, (27-14) >> 1, 5,0,0, 24, "LUCA ANTIGNANO");
				printMessage(introFont, (27-19) >> 1, 7,0,0, 24, "FOR THE SOUND FILES");
				printMessage(introFont, (27-21) >> 1, 9,0,0, 24, "WWW.MADRIGALDESIGN.IT");
			}
			else
			{
				gameState = gsInitGameIntro;
			}
		}
    }
        
    if ((gamepad_button_a() == 1) ||
        (gamepad_button_b() == 1))
    {            
        gameState = gsInitGameIntro;
    }
}


#endif