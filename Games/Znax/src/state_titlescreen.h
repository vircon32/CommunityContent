#ifndef STATETITLESCREEN_H
#define STATETITLESCREEN_H

#include "input.h"
#include "texture.h"
#include "gamefuncs.h"
#include "common.h"
#include "cmainmenu.h"


void TitleScreen()
{
    end_frame();
    CMainMenu *Menu = CMainMenu_Create();
    while (GameState == GSTitleScreen)
    {         
        if(gamepad_up() == 1)
            CMainMenu_PreviousItem(Menu);
        if(gamepad_down() == 1)
            CMainMenu_NextItem(Menu);
        if((gamepad_button_x() == 1) || (gamepad_button_y() == 1) || (gamepad_button_a() == 1) || (gamepad_button_start() == 1))
        {
            if(CMainMenu_GetSelection(Menu) != 4)
            {
                CAudio_PlaySound(Sounds[SND_SELECT],0);
                switch(CMainMenu_GetSelection(Menu))
                {
                    case 1:
                        GameState = GSGameTypeMenu;
                        break;
                    case 2:
                        //so that it shows both gameplay modes
                        GameType = Fixed;
                        GameState = GSShowHighScores;
                        break;
                    case 3:
                        GameState = GSCredits;
                        break;
                }
                break;
            }
        }
        CMainMenu_Draw(Menu);
        end_frame();
    }
    CMainMenu_Destroy(Menu);
}


#endif