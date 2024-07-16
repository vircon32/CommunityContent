#ifndef CMAINMENU_H
#define CMAINMENU_H

#include "misc.h"
#include "string.h"
#include "sound.h"
#include "texture.h"
#include "commonvars.h"

struct CMainMenu {
    //Holds what we currently selected in the main menu, 1 = new game, 2= credits
	int Selection; 
	// the textures
    Texture *IMGCredits1;
	Texture *IMGCredits2;
	Texture *IMGNewGame1;
	Texture *IMGNewGame2;
	Texture *IMGTitle; 
};


CMainMenu* CMainMenu_Create()
{
	CMainMenu* Result = malloc(sizeof(CMainMenu));
    Result->Selection = 1;

	//define the textures
	Result->IMGTitle = newTexture(6, 1, 640, 360);
	Result->IMGNewGame1 = newTexture(8, 1, 267, 64);
	Result->IMGNewGame2 = newTexture(9, 1, 267, 64);
	Result->IMGCredits1 = newTexture(10, 1, 188, 48);
	Result->IMGCredits2 = newTexture(11, 1, 188, 48);
	
	return Result;
}

 // return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu)
{
	return MainMenu->Selection;
}

// Destructor
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
    free(MainMenu);
	MainMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 3)
        MainMenu->Selection = 1;
    playSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 2;
    playSelectSound();
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu)
{
    // draw the title screen background
    drawTexture(MainMenu->IMGTitle, 0, 0, 0);
	
    // if selection = newgame draw the purple new game image in the middle of the screen
    if (MainMenu->Selection == 1)
    {
        drawTexture(MainMenu->IMGNewGame1, 0, screen_width - MainMenu->IMGNewGame1->width >> 1, (screen_height >> 1) - 65);
    }
    else
    // draw the blue one
    {
        drawTexture(MainMenu->IMGNewGame2, 0, screen_width - MainMenu->IMGNewGame2->width >> 1, (screen_height >> 1) - 65);
    }

    if (MainMenu->Selection == 2) // = credits draw purple
    {
        drawTexture(MainMenu->IMGCredits1, 0, screen_width - MainMenu->IMGCredits1->width >> 1, (screen_height >> 1) + 35);
    }
    else // blue
    {
        drawTexture(MainMenu->IMGCredits2, 0, screen_width - MainMenu->IMGCredits2->width >> 1, (screen_height >> 1) + 35);
    }
}

#endif