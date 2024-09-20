#ifndef commonvars_h
#define commonvars_h

#include "texture.h"
#include "memcard.h"

#define maxBoardWidth 10
#define maxBoardHeight 8

#define maxBoardBgWidth 10
#define maxBoardBgHeight 8

#define maxBoardSize 80

#define gsGame 0
#define gsTitle 1
#define gsLevelSelect 2
#define gsLevelsCleared 3
#define gsHelpRotate 4
#define gsHelpRotate2 5
#define gsHelpRotate3 6
#define gsHelpRotateSlide 7
#define gsHelpRotateSlide2 8
#define gsHelpRotateSlide3 9
#define gsHelpRotateSlide4 10
#define gsHelpSlide 11
#define gsHelpSlide2 12
#define gsHelpSlide3 13
#define gsIntro 14

#define gsInitDiff 50

#define gsInitGame (gsInitDiff + gsGame)
#define gsInitTitle (gsInitDiff + gsTitle)
#define gsInitLevelSelect (gsInitDiff + gsLevelSelect)
#define gsInitLevelsCleared (gsInitDiff + gsLevelsCleared)
#define gsInitHelpRotate (gsInitDiff + gsHelpRotate)
#define gsInitHelpRotate2 (gsInitDiff + gsHelpRotate2)
#define gsInitHelpRotate3 (gsInitDiff + gsHelpRotate3)
#define gsInitHelpRotateSlide (gsInitDiff + gsHelpRotateSlide)
#define gsInitHelpRotateSlide2 (gsInitDiff + gsHelpRotateSlide2)
#define gsInitHelpRotateSlide3 (gsInitDiff + gsHelpRotateSlide3)
#define gsInitHelpRotateSlide4 (gsInitDiff + gsHelpRotateSlide4)
#define gsInitHelpSlide (gsInitDiff + gsHelpSlide)
#define gsInitHelpSlide2 (gsInitDiff + gsHelpSlide2)
#define gsInitHelpSlide3 (gsInitDiff + gsHelpSlide3)
#define gsInitIntro (gsInitDiff + gsIntro)

#define diffVeryEasy 0
#define diffEasy 1
#define diffNormal 2
#define diffHard 3
#define diffVeryHard 4
#define diffRandom 5
#define diffCount 6

#define gmRotate 0
#define gmSlide 1
#define gmRotateSlide 2
#define gmCount 3

#define mmStartGame 0
#define mmHelp 1
#define mmOptions 2
#define mmCredits 3
#define mmCount 4

#define opMusic 0
#define opSound 1
#define opText 2
#define opMainSkin 3
#define opCount 4

#define tsMainMenu 0
#define tsGameMode 1
#define tsDifficulty 2
#define tsOptions 3
#define tsCredits 4

#define levelCount 25
#define arrowDown 122
#define arrowUp 120
#define arrowLeft 123
#define arrowRight 121
#define leftMenu 118
#define emptyFloor 49

#define maxSkins 2
#define maxMainSkins 4

#define OLDSCREENWIDTH 400
#define OLDSCREENHEIGHT 240

#define SCREENWIDTH 600
#define SCREENHEIGHT 360

#define xscale ((float)SCREENWIDTH / (float)OLDSCREENWIDTH)
#define yscale ((float)SCREENHEIGHT / (float)OLDSCREENHEIGHT)

#define tileSize (24 * xscale)

#define FRAMERATE 15
#define FRAMESCALE (60/FRAMERATE)

//original graphcis were 8x8 for a screen resolution of 128x64 (arduboy) i scaled the graphics by 3
//so we have some space left and can use a drawoffset to center everything on the screen
#define xoffset (((int)(OLDSCREENWIDTH* xscale - 384* xscale)) >> 1) + 20
#define yoffset (((int)(OLDSCREENHEIGHT* yscale - 192* yscale)) >> 1)

int startPos, maxLevel, selectedLevel, boardX, boardY, difficulty,
    gameState, boardWidth, boardHeight, boardSize, levelDone, titleStep, gameMode, posAdd,
    mainMenu, option, needRedraw, paused, levelDoneBit, fpsStep;
int backgroundColor;

int selectionX, selectionY;
int moves;
int randomSeedGame;
int[maxBoardSize] level;
Texture* titlescreenMap = NULL, congratsMap = NULL, blockTiles = NULL, blockTiles2 = NULL, selectorTiles = NULL, congratsScreenTiles = NULL;
game_signature GameSignature;

#endif