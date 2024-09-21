#ifndef game_h
#define game_h

#include "time.h"
#include "input.h"
#include "video.h"
#include "level.h"
#include "commonvars.h"
#include "helperfuncs.h"
#include "sound.h"
#include "printfuncs.h"
#include "cursor.h"
#include "savestate.h"

void updateBackgroundGame()
{
    //background
	clear_screen(backgroundColor);
        
    //LEVEL:
    printMessage(maxBoardBgWidth, 0, "LEVEL:");
        
    //[LEVEL NR] 2 ints
    printNumber(maxBoardBgWidth + 4, 1, selectedLevel, 2);
        
        
    //MOVES:
    printMessage(maxBoardBgWidth, 2, "MOVES:");

    printNumber(maxBoardBgWidth + 1, 3, moves, 5); 
        
    //A:XXXXXX (XXXXXX="ROTATE" or XXXXXX="SLIDE " or XXXXXX="ROSLID")
    if(gameMode == gmRotate)
    {
        printMessage(maxBoardBgWidth, 4, "a:");
        printMessage(maxBoardBgWidth, 5, "ROTATE");
    }
    else
    {
        if(gameMode == gmSlide)
        {
            printMessage(maxBoardBgWidth, 4, "a:");
            printMessage(maxBoardBgWidth, 5, "SLIDE");
        }
        else
        {
            if(gameMode == gmRotateSlide)
            {
                printMessage(maxBoardBgWidth, 4, "a:");
                printMessage(maxBoardBgWidth, 5, "ROSLID");
            }
        }
    }

    //B:BACK
    printMessage(maxBoardBgWidth, 6, "b:");
    printMessage(maxBoardBgWidth, 7, "BACK");

    drawLevel();
        
    if (paused)
    {
        printMessage(0, (maxBoardBgHeight >> 1) - 3, "[**************]");
        printMessage(0, (maxBoardBgHeight >> 1) - 2, "|PLEASE CONFIRM+");
        printMessage(0, (maxBoardBgHeight >> 1) - 1, "|              +");
        printMessage(0, (maxBoardBgHeight >> 1) + 0, "|   a PLAY     +");
        printMessage(0, (maxBoardBgHeight >> 1) + 1, "|   b TO QUIT  +");
        printMessage(0, (maxBoardBgHeight >> 1) + 2, "<##############>");
    }

    if (levelDoneBit && (fpsStep == 0))
    {
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) - 3, "[************]");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) - 2, "| LEVEL DONE +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) - 1, "|            +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) + 0, "| a CONTINUE +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) + 1, "| b SOLUTION +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) + 2, "<############>");        
    }

    if ((!paused) && (!levelDoneBit))
        drawCursors();
}

void initGame()
{
    SelectMusic(musGame);
    //set background tiles
    setBlockTilesAsBackground();
    //set sprite for selector / cursor
    initCursors();
    setCursorPos(0, boardX + selectionX, boardY + selectionY);
    showCursors();
    levelDoneBit = 0;
    paused = 0;
    fpsStep = 0;
    updateBackgroundGame();
}

void doPause()
{
    paused = 1;
    setMusicOn(0);
    setSoundOn(0);
    hideCursors();
    needRedraw = 1;
}

void doUnPause()
{
    paused = 0;
    //music could have been disabled by menu options during pause screen so we use the savestate value
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    setCursorPos(0, boardX + selectionX, boardY + selectionY);
    showCursors();
    playMenuAcknowlege();
    needRedraw = 1;
}

void game()
{
    int needRedraw = updateCursorFrame();
    if (gameState == gsInitGame)
    {
        initGame();
        gameState -= gsInitDiff;
    }
    
    if (fpsStep > 0)
    {
        fpsStep--;
        if (fpsStep == 0)
        {
            needRedraw = 1;
        }
    }
    
	if (gamepad_down() == 1)
	{
		if(!levelDone && !paused)
		{
			playGameMoveSound();
			//if not touching border on bottom
			if (selectionY + 1 < boardHeight + posAdd)
			{
				selectionY += 1;
				needRedraw = 1;
			}
			else
			//set to border on top
			{
				selectionY = -posAdd;
				needRedraw = 1;
			}
			setCursorPos(0, boardX + selectionX, boardY + selectionY);
		}
	} 
	if (gamepad_up() == 1)
	{
		if (!levelDone && !paused)
		{
			//if not touching border on top
			playGameMoveSound();
			if (selectionY -1 >= -posAdd)
			{
				selectionY -= 1;
				needRedraw = 1;
			}
			else
			//set to border on bottom
			{
				selectionY = boardHeight -1 +posAdd;
				needRedraw = 1;
			}
			setCursorPos(0, boardX + selectionX, boardY + selectionY);
		}
	}
	if (gamepad_right() == 1)
	{
		if (!levelDone && !paused)
		{
			playGameMoveSound();
			//if not touching border on right
			if(selectionX + 1 < boardWidth + posAdd)
			{
				selectionX += 1;
				needRedraw = 1;
			}
			else
			//set to border on left
			{
				selectionX = -posAdd;
				needRedraw = 1;
			}
			setCursorPos(0, boardX + selectionX, boardY + selectionY);
		}
	}

	if (gamepad_left() == 1)
	{
		if(!levelDone && !paused)
		{
			playGameMoveSound();
			//if not touching border on left
			if( selectionX -1 >= -posAdd)
			{
				selectionX -= 1;
				needRedraw = 1;
			}
			//set to border on right
			else
			{
				selectionX = boardWidth -1 + posAdd;
				needRedraw = 1;
			}
			setCursorPos(0, boardX + selectionX, boardY + selectionY);
		}
	}

	if (gamepad_button_a() == 1)
	{
		if(paused)
		{
			doUnPause();            
		}
		else
		{
			if(!levelDone)
			{
				if ((selectionX > -1) && (selectionX < boardWidth) &&
					(selectionY > -1) && (selectionY < boardHeight))
				{   
					if (gameMode != gmSlide)
					{
						rotateBlock((int)selectionX + ((int)selectionY * boardWidth));
						moves++;
						playGameAction();
						needRedraw = 1;
					}
					else
					{
						playErrorSound();
					}
				}
				else
				{
					if ((selectionX > -1) && (selectionX < boardWidth))
					{
						if (selectionY == -1)
						{
							moveBlockDown((int)selectionX + ((int)(selectionY+1) * boardWidth));
							moves++;
							playGameAction();
							needRedraw = 1;
						}
						else
						{
							if (selectionY == boardHeight)
							{
								moveBlockUp((int)selectionX + ((int)(selectionY-1) * boardWidth));
								moves++;
								playGameAction();
								needRedraw = 1;
							}
						}
					}
					else
					{
						if ((selectionY > -1) && (selectionY < boardHeight))    
						{
							if (selectionX == -1)
							{
								moveBlockRight((int)(selectionX + 1) + ((int)selectionY * boardWidth));
								moves++;
								playGameAction();
								needRedraw = 1;
							}
							else
							{
								if (selectionX == boardWidth)
								{
									moveBlockLeft( (int)(selectionX - 1) + ((int)selectionY * boardWidth));
									moves++;
									playGameAction();
									needRedraw = 1;
								}
							}
						}
						else
						{
							playErrorSound();
						}
					}
				}
				updateConnected();
				levelDone = isLevelDone();
				if(levelDone)
				{
					fpsStep = 11; //to display solution for brief moment
					SelectMusic(musLevelClear);
					//hide cursor it's only sprite we use
					hideCursors();                    
					levelDoneBit = 1; 
					needRedraw = 1;
				}
			}
			else 
			{
				levelDoneBit = 0;
				//could have been enabled / disabled using menu's so need to replay as it's blocked from renabling
				//during pause leveldonebit = 1
				setMusicOn(isMusicOnSaveState());
				setSoundOn(isSoundOnSaveState());
				//goto next level
				if (difficulty == diffRandom)
				{
					//ned new seed based on time
					randomSeedGame = get_date() + get_frame_counter();
					initLevel(randomSeedGame);
					SelectMusic(musGame);
					//show cursor again (it's actually to early but i'm not fixing that)
					setCursorPos(0, boardX + selectionX, boardY + selectionY);
					showCursors();
					needRedraw = 1;
				}
				else
				{   
					//goto next level if any
					if (selectedLevel < maxLevel)
					{
						selectedLevel++;
						unlockLevel(gameMode, difficulty, selectedLevel-1);
						initLevel(randomSeedGame);
						SelectMusic(musGame);
						//show cursor again (it's actually to early but i'm not fixing that)
						setCursorPos(0, boardX + selectionX, boardY + selectionY);
						showCursors();
						needRedraw = 1;
					}
					else //Goto some congrats screen
					{
						gameState = gsInitLevelsCleared;                         
					}
				}
			}
		}
	}


	if (gamepad_button_b() > 0)
	{
		if (gamepad_button_b() > 1)
		{
			if (levelDone)
			{
				fpsStep = 1;
				needRedraw = 1;
			}
		}

		if (gamepad_button_b() == 1)
		{
			if (!levelDone)
			{
				if (!paused)
				{
					playMenuBackSound();
					doPause();
					needRedraw = 1;
				}
				else
				{
					//need to reanble early 
					setSoundOn(isSoundOnSaveState());
					hideCursors();
					playMenuBackSound();
					gameState = gsInitLevelSelect;
					doUnPause();
					//unpause sets cursor visible !
					hideCursors();
					//need to reset the level to initial state when going back to level selector
					//could not find a better way unfortunatly
					//also we do not want to reset the randomseed used for random level generating
					//or a new level would have been created when going back we only want the level
					//with random to change when pressing left and right in the level selector
					//this way it stays consistent with the normal levels
					//and the player can replay the level if he wants to
					initLevel(randomSeedGame);
				}
			}
		}
	}

    if (needRedraw)
    {
        updateBackgroundGame();
    }
}


#endif