#include "input.h"
#include "time.h"
#include "texture.h"
#include "commonvars.h"
#include "titlescreen.h"
#include "game.h"
#include "helpscreens.h"
#include "levelscleared.h"
#include "intro.h"
#include "levelselect.h"
#include "sound.h"
#include "savestate.h"
#include "helperfuncs.h"

// game initialization
void setupGame()
{  
	memset( &GameSignature, 0, sizeof( game_signature ) );
    	strcpy( GameSignature, "Waternet_V1" );
    option = 0;
    needRedraw = 0;
    levelDoneBit = 0;
    paused = 0;
    difficulty = diffNormal;
    selectedLevel = 1;
    mainMenu = mmStartGame;
    gameState = gsInitIntro;
    titleStep = tsMainMenu;
    gameMode = gmRotate;
    initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
	setMainSkin(mainSkinSaveState());
    setBlockTilesAsBackground();
}

void terminateGame()
{
	unloadImages();
	deInitSound();
	deInitMusic();
}

// main update function
void main()
{
	setupGame();

	while (true)
	{
		if(gamepad_button_r() == 1)
		{
			needRedraw = 1;
			nextMainSkin();
		}
		//gamestate handling   
		switch (gameState)
		{
			case gsInitTitle:
			case gsTitle:
				titleScreen();
				break;
			case gsInitLevelSelect:
			case gsLevelSelect:
				levelSelect();
				break;
			case gsInitGame:
			case gsGame:
				game();
				break;
			case gsInitLevelsCleared:
			case gsLevelsCleared:
				levelsCleared();
				break;
			case gsInitHelpSlide:
			case gsHelpSlide:
				helpSlide();
				break;
			case gsInitHelpSlide2:
			case gsHelpSlide2:
				helpSlide2();
				break;
			case gsInitHelpSlide3:
			case gsHelpSlide3:
				helpSlide3();
				break;
			case gsHelpRotateSlide:
			case gsInitHelpRotateSlide:
				helpRotateSlide();
				break;
			case gsInitHelpRotateSlide2:
			case gsHelpRotateSlide2:
				helpRotateSlide2();
				break;
			case gsInitHelpRotateSlide3:
			case gsHelpRotateSlide3:
				helpRotateSlide3();
				break;
			case gsInitHelpRotateSlide4:
			case gsHelpRotateSlide4:
				helpRotateSlide4();
				break;
			case gsInitHelpRotate:
			case gsHelpRotate:
				helpRotate();
				break;
			case gsInitHelpRotate2:
			case gsHelpRotate2:
				helpRotate2();
				break;
			case gsInitHelpRotate3:
			case gsHelpRotate3:
				helpRotate3();
				break;
			case gsInitIntro:
			case gsIntro:
				intro();
				break;
		}
		end_frame();
	}
	terminateGame();
}
