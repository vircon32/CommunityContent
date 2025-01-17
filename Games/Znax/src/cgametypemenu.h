#ifndef CGAMETYPEMENU_H
#define CGAMETYPEMENU_H

#include "texture.h"
#include "common.h"
#include "defines.h"
#include "cgametypemenu.h"

struct CGameTypeMenu
{
    int Selection; //Holds what we currently selected in the main menu, 1 = new game, 2= credits, 3 = quit
};

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CGameTypeMenu* CGameTypeMenu_Create()
{
    CGameTypeMenu* Result = (CGameTypeMenu*) malloc(sizeof(CGameTypeMenu));
    Result->Selection = Fixed;
    return Result;
}

// return the current selection
int CGameTypeMenu_GetSelection(CGameTypeMenu* GameTypeMenu) 
{
    return GameTypeMenu->Selection;
}

// Destructor will free the surface images
void CGameTypeMenu_Destroy(CGameTypeMenu* GameTypeMenu)
{
    free(GameTypeMenu);
    GameTypeMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void CGameTypeMenu_NextItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection++;
    if (GameTypeMenu->Selection == 2)
        GameTypeMenu->Selection = 0;
    CAudio_PlaySound(Sounds[SND_MENU],0);
}

// decrease the selection if it goes to low set it to the last selection
void CGameTypeMenu_PreviousItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection--;
    if (GameTypeMenu->Selection == -1)
        GameTypeMenu->Selection = 1;
    CAudio_PlaySound(Sounds[SND_MENU],0);
}

// Draw the main menu
void CGameTypeMenu_Draw(CGameTypeMenu* GameTypeMenu)
{
    // draw the title screen background
    drawTexture(IMGTitleScreen,0,0,0);
    drawTexture(IMGSelectGame,0,(WINDOW_WIDTH - IMGSelectGame->width) / 2, 77*SCALE);

    if (GameTypeMenu->Selection == Fixed)
    {
        drawTexture(IMGFixedTimer2,0,(WINDOW_WIDTH - IMGFixedTimer2->width) / 2, 114*SCALE);
    }
    else
    {
        drawTexture(IMGFixedTimer1,0,(WINDOW_WIDTH - IMGFixedTimer1->width) / 2, 114*SCALE);
    }

    if (GameTypeMenu->Selection == Relative)
    {
        drawTexture(IMGRelativeTimer2,0,(WINDOW_WIDTH - IMGRelativeTimer2->width) / 2, 151*SCALE);
    }
    else
    {
        drawTexture(IMGRelativeTimer1,0,(WINDOW_WIDTH - IMGRelativeTimer1->width) / 2, 151*SCALE);
    }
}


#endif