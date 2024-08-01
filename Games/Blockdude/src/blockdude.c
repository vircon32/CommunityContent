#include "time.h"
#include "string.h"
#include "commonvars.h"
#include "sound.h"
#include "gamefuncs.h"
#include "savestate.h"
#include "stageselectstate.h"
#include "titlescreenstate.h"
#include "gamestate.h"
#include "stageselectstate.h"
#include "introstate.h"
#include "levels.h"
#include "debugspeed.h"

CWorldParts* WorldParts;

void resetGlobals()
{
	GameState = GSIntroInit;
	SelectedLevel = 0;
	NeedRedraw = 1;
	AskingQuestionID = -1;
	titleStep = tsMainMenu;
	titleSelection = 0;
	Option = opMusicSound;
	CurrentLevelPackIndex = 0;
	FoundLevelPacks = 0;
	AskingQuestion = false;
	FreeView = false;
	NeedToReloadGraphics = false;
	IntroScreenNr = 1;
	framecounter = 0;
}

// game initialization
void setupGame(void)
{  
	setupLevels();
	resetGlobals();
    GameState = GSIntroInit;
    FindLevelPacks();
	initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    LoadGraphics();
    LoadFonts();
	
    WorldParts = CWorldParts_Create();	
}

void terminateGame(void)
{
	deInitSound();
	deInitMusic();
	UnLoadGraphics();
	CWorldParts_deinit(WorldParts);	
}



// main update function
void main()
{
	initDebugSpeed();
	setupGame();
	while(true)
	{
		if(gamepad_button_l() == 1)
			ResetAllDebugSpeedMaxValues();
		StartDebugSpeed(0);
		//gamestate handling   
		switch (GameState)
		{
			case GSIntro:
			case GSIntroInit:
			 	Intro();
			 	break;
			case GSTitleScreen:
			case GSTitleScreenInit:
			 	TitleScreen();
			 	break;
			case GSStageSelect:
			case GSStageSelectInit:
			 	StageSelect(WorldParts);
			 	break;
			case GSGame:
			case GSGameInit:
			 	Game(WorldParts);
			 	break;
			default:
				break;
		}
		StopDebugSpeed(0);

		printDebugSpeed(0, 10, 40, "F:");
		printDebugSpeed(1, 10, 60, "D:");
		printDebugSpeed(2, 10, 80, "L:");

		
		end_frame();

	}
	terminateGame();
}
