#ifndef STATECREDITS_H
#define STATECREDITS_H

#include "input.h"
#include "texture.h"
#include "gamefuncs.h"
#include "common.h"

void Credits()
{
    end_frame();
    while (GameState == GSCredits)
    {
        if((gamepad_button_x() == 1) || (gamepad_button_y() == 1) || (gamepad_button_a() == 1) || (gamepad_button_start() == 1) || (gamepad_button_b() == 1))
        {
            GameState = GSTitleScreen;
        }

        drawTexture(IMGTitleScreen, 0, 0, 0);
        drawTexture(IMGCredits, 0, 163, 114);
        end_frame();
    }
}


#endif