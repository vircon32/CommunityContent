#ifndef CREDITS_H
#define CREDITS_H


#include "input.h"
#include "string.h"
#include "credits.h"
#include "gamefuncs.h"
#include "main.h"

void CreditsInit()
{

}

void Credits()
{
	if (GameState == GSCreditsInit)
	{
		CreditsInit();
		GameState = GSCredits;
	}
    if (GameState == GSCredits)
    {
		
	    if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1))
		{
            GameState = GSTitleScreenInit;
        }
		drawTextureZoomed(IMGTitleScreen, 0, 0, 0);
        drawTextColor(font, "      Puztrix was created by\n Willems Davy - joyrider3774\n\n      Puztrix is a remake of\n      gravnic, part of puzznic\n    (Nintendo NES console)\n\n      Music was created by\n     radiance of iris - 1996\n Taken from the modarchive\n   Sounds created using sfxr",  108*xscale, 57*yscale, ColorSelection);
    }
}


#endif