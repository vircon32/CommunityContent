
#include "input.h"
#include "time.h"
#include "main.h"
#include "cworldparts.h"
#include "debugspeed.h"
#include "gamefuncs.h"
#include "stageclear.h"
#include "levelpackdone.h"
#include "credits.h"
#include "titlescreen.h"
#include "gameover.h"
#include "game.h"
#include "highscore.h"
#include "options.h"
#include "texture.h"
#include "fonts/bigfont2_14.h"
#include "fonts/bigfont_14.h"
#include "fonts/font_14.h"

void resetGlobals()
{
	IMGBackgroundLevelEditor = NULL;
	IMGBackground = NULL;
	IMGBlocks = NULL;
	IMGFloor = NULL;
	IMGLevelDone = NULL;
	IMGArrows1 = NULL;
	IMGArrows2 = NULL;
	IMGGameOver = NULL;
	IMGLevelpackDone = NULL;
	IMGTitleScreen = NULL;
	IMGGrid = NULL;
	font = NULL;
	BigFont = NULL;
	BigFont2 = NULL;
	ScoreStatus = 0;
	RetryScore=0;
	ClearScore=0;
	MoveScore=0;
	TotalScore=0;
	KeyPressed = false;
	Movement = MNone;
	WorldParts = NULL;
	GameState = GSTitleScreenInit;
	MaxMoves=0;
	Retries=5;
	Music = -1;
	Score=0;
	WasNewHighScore = false;
	titleSelection = 0;
	optionSelection = 0;
}

void setupGame()
{
	memset( &GameSignature, 0, sizeof( game_signature ) );
    strcpy( GameSignature, "Puztrix_V1" );
	resetGlobals();
	CAudio_Init();
	setupFontbigfont_14();
	setupFontbigfont2_14();
	setupFontfont_14();	
	font = &Fontfont_14;
	BigFont = &Fontbigfont_14;
	BigFont2 = &Fontbigfont2_14; 
	LoadSounds();
    LoadGraphics();	
	WorldParts = CWorldParts_Create();
    CWorldParts_AssignImage(WorldParts, IMGBlocks);
	LoadSettings();
    Retries = 5;
    Score = 0;
	CAudio_SetVolumeMusic(64);
	CAudio_SetVolumeSound(128);
	CAudio_PlayMusic(Music, -1);
}

void TerminateGame()
{
    SaveSettings();
    UnLoadGraphics();
	UnloadSounds();
    UnloadMusic();
	CWorldParts_RemoveAll(WorldParts);
	CWorldParts_Destroy(WorldParts);
}



void main()
{
	setupGame();
	while(true)
	{
		if(gamepad_button_r() == 1)
			NextSkin();
		switch(GameState)
		{
			case GSTitleScreenInit:
			case GSTitleScreen:
				TitleScreen();
				break;
			case GSLevelpackDoneInit:
			case GSLevelpackDone:
				LevelpackDone();
				break;
			case GSGameInit:
			case GSGame:
				if(get_frame_counter() % 2 == 0)
					Game_Logic();
				else
					Game_Draw();
				break;
			case GSStageClearInit:
			case GSStageClear:
				StageClear();
				break;
			case GSGameOverInit:
			case GSGameOver:
				GameOver();
				break;
			case GSCreditsInit:
			case GSCredits:
				Credits();
				break;
			case GSHighScoresInit:
			case GSHighScores:
				ShowHighScores();
				break;
			case GSOptionsInit:
			case GSOptions:
				Options();
				break;
			default :
				break;
		}
		if(DEBUG)
		{
			int[100] DebugText;
			int[10] DebugTmpNr;
			strcpy(DebugText, "MEM USE: ");		
			itoa(MemoryUsed(), DebugTmpNr, 10);
			strcat(DebugText, DebugTmpNr);
			set_multiply_color(make_color_rgb(255,0,255));
			print_at(0,bios_character_height, DebugText);
			set_multiply_color(color_white);
		}
		end_frame();

	}
	TerminateGame();
}


