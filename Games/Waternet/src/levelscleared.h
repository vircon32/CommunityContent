#ifndef levels_cleared_h
#define levels_cleared_h

#include "input.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "sound.h"
#include "level.h"

void initLevelsCleared()
{
    set_bkg_data(congratsScreenTiles);
    
	clear_screen(backgroundColor);
    
	set_bkg_tiles(0, 0, congratsMap);
    SelectMusic(musAllLevelsClear);
}

void levelsCleared() 
{
    if (gameState == gsInitLevelsCleared)
    {
        initLevelsCleared();
        gameState -= gsInitDiff;
    }
    
    if (difficulty == diffVeryEasy)
    {
        printCongratsScreen(0, 3, "VERY EASY LEVELS");
    }
    if (difficulty == diffEasy)
    {
        printCongratsScreen(3, 3, "EASY LEVELS");
    }
    if (difficulty == diffNormal)
    {
        printCongratsScreen(2, 3, "NORMAL LEVELS");
    }
    if (difficulty == diffHard)
    {
        printCongratsScreen(3, 3, "HARD LEVELS");
    }
    if (difficulty == diffVeryHard)
    {
        printCongratsScreen(0, 3, "VERY HARD LEVELS");
    }


     if ((gamepad_button_a() == 1) || (gamepad_button_b() == 1))
     {
         playMenuAcknowlege();
         titleStep = tsMainMenu;
         gameState = gsInitTitle;
     }
} 

#endif