#ifndef CMAINMENU_H
#define CMAINMENU_H

#include "texture.h"
#include "caudio.h"
#include "common.h"

struct CMainMenu
{
    int Selection; //Holds what we currently selected in the main menu, 1 = new game, 2= credits, 3 = quit
};

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CMainMenu* CMainMenu_Create()
{
    CMainMenu* Result = (CMainMenu*) malloc(sizeof(CMainMenu));
    Result->Selection = 1;
    return Result;
}

// destructor
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
    free(MainMenu);
    MainMenu = NULL;
}

// return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu) 
{
    return MainMenu->Selection;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 4)
        MainMenu->Selection = 1;
    CAudio_PlaySound(Sounds[SND_MENU],0);
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 3;
    CAudio_PlaySound(Sounds[SND_MENU],0);
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu)
{
    drawTexture(IMGTitleScreen,0, 0, 0);
    if (MainMenu->Selection == 1)
    {
        drawTexture(IMGPlay2,0,(WINDOW_WIDTH - IMGPlay2->width) / 2,83*SCALE);
    }
    else
    {
        drawTexture(IMGPlay1,0,(WINDOW_WIDTH - IMGPlay1->width) / 2,83*SCALE);
    }

    if (MainMenu->Selection == 2)
    {
        drawTexture(IMGHighScores2,0,(WINDOW_WIDTH - IMGHighScores2->width) / 2,120 *SCALE);
    }
    else
    {
       drawTexture(IMGHighScores1,0,(WINDOW_WIDTH - IMGHighScores1->width) / 2,120 *SCALE);
    }


    if (MainMenu->Selection == 3)
    {
        drawTexture(IMGCredits2,0,(WINDOW_WIDTH - IMGCredits2->width) / 2,157 *SCALE);
    }
    else
    {
        drawTexture(IMGCredits1,0,(WINDOW_WIDTH - IMGCredits1->width) / 2,157 *SCALE);
    }
}

#endif