#ifndef levelselect_h
#define levelselect_h

#include "time.h"
#include "input.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "savestate.h"
#include "sound.h"
#include "level.h"


void updateBackgroundLevelSelect() 
{
	clear_screen(backgroundColor);
    //LEVEL:
    printMessage(maxBoardBgWidth, 0, "LEVEL:");
    
    //[LEVEL NR] 2 ints
    printNumber(maxBoardBgWidth + 4, 1, selectedLevel, 2);
    
    //B:BACK
    printMessage(maxBoardBgWidth, 6, "b:");
    printMessage(maxBoardBgWidth, 7, "BACK");
    
    //A:PLAY
    printMessage(maxBoardBgWidth, 4, "a:");
    printMessage(maxBoardBgWidth, 5, "PLAY");
    
    //Locked & Unlocked keywoard
    int tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);
    if(!tmpUnlocked)
    {
        printMessage(maxBoardBgWidth, 2, "LOCKED");
    }
    else
    {
        if(tmpUnlocked)
        {
            printMessage(maxBoardBgWidth, 2, "OPEN");
        }
    }
    
    drawLevel();
}

void initLevelSelect()
{
    setBlockTilesAsBackground();
    SelectMusic(musTitle);
    updateBackgroundLevelSelect();
    needRedraw = 0;
}

void doLeft()
{
    if (difficulty == diffRandom)
    {
        playMenuSelectSound();
        randomSeedGame = get_date() + get_frame_counter();
        initLevel(randomSeedGame);
        needRedraw = 1;
    }
    else
    {
        if (selectedLevel > 1)
        {
            playMenuSelectSound();
            selectedLevel--;
            initLevel(randomSeedGame);
            needRedraw = 1;
        }
    }
}

void doRight()
{
    if (difficulty == diffRandom)
    {
        playMenuSelectSound();
        //need new seed based on time
        randomSeedGame = get_date() + get_frame_counter();
        initLevel(randomSeedGame);
        needRedraw = 1;
    }
    else
    {
        if (selectedLevel < maxLevel)
        {
            playMenuSelectSound();
            selectedLevel++;
            initLevel(randomSeedGame);
            needRedraw = 1;
        }
    }
}

void levelSelect()
{
    int tmpUnlocked;
    tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);
    
    if (gameState == gsInitLevelSelect)
    {
        initLevelSelect();
        gameState -= gsInitDiff;
    }
       
    if (gamepad_button_b() == 1)
    {
        playMenuBackSound();
        gameState = gsInitTitle;
    }
    if (gamepad_button_a() == 1)
    {
        if(tmpUnlocked)
        {
            gameState = gsInitGame;
            playMenuAcknowlege();
        }
        else
        {
            playErrorSound();
        }
    }
    if (gamepad_left() == 1)
    {
        doLeft();
    }
    if (gamepad_right() == 1)
    {
        doRight();
    }
    
    if (needRedraw)
    {
        updateBackgroundLevelSelect();
    }
}


#endif