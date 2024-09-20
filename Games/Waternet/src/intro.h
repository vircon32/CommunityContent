#ifndef intro_h
#define intro_h

#include "input.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "intro.h"

#define FRAMEDELAY 10 * FRAMESCALE

int frames = 0;
int ay;

void initIntro()
{
	frames = 0;
    setBlockTilesAsBackground();
    ay = SCREENHEIGHT;
}

void intro()
{
    if (gameState == gsInitIntro)
    {
        initIntro();
        gameState -= gsInitDiff;
    }
    
    frames++;
	clear_screen(backgroundColor);
    if (frames < FRAMEDELAY)
    {
        printMessage((16-12) >> 1, 4, "WILLEMS DAVY");
    }
    else
    {
        if (frames < FRAMEDELAY *2)
        {
            printMessage((16-8) >> 1, 4, "PRESENTS");
        }
        else
        {
            set_bkg_tiles(0, ay, titlescreenMap);
            if(ay > 0)
            {
                ay -= 10/FRAMESCALE;
            }
            else
            {
                gameState = gsInitTitle;
            }
        }
    }
        
    if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1))
    {            
        gameState = gsInitTitle;
    }
}


#endif