#ifndef STATEGAMETYPEMENU_H
#define STATEGAMETYPEMENU_H

#include "input.h"
#include "texture.h"
#include "cgametypemenu.h"
#include "gamefuncs.h"
#include "common.h"

void GameTypeMenu()
{
    end_frame();
    CGameTypeMenu *Menu = CGameTypeMenu_Create();
    while (GameState == GSGameTypeMenu)
    {
        if(gamepad_up() == 1)
            CGameTypeMenu_NextItem(Menu);
    
    
        if(gamepad_down() == 1)
            CGameTypeMenu_PreviousItem(Menu);
        
        if((gamepad_button_x() == 1) || (gamepad_button_y() == 1) || (gamepad_button_a() == 1) || (gamepad_button_start() == 1))
        {
            CAudio_PlaySound(Sounds[SND_SELECT],0);
            switch(CGameTypeMenu_GetSelection(Menu))
            {
                case Fixed:
                    GameType = Fixed;
                    break;
                case Relative:
                    GameType = Relative;
                    break;
            }
            GameState = GSReadyGo;
        }
        
        if(gamepad_button_b() == 1)
            GameState = GSTitleScreen;

        CGameTypeMenu_Draw(Menu);
        end_frame();
    }
    CGameTypeMenu_Destroy(Menu);
}



#endif