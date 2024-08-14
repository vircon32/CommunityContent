#ifndef COMMON_H
#define COMMON_H

#include "string.h"
#include "memcard.h"
#include "CAudio.h"

#define debugInfoStats false
#define debugShowCollisionShapes false

#define epsilion 0.0001

#define ScreenWidth 640
#define ScreenHeight 360
#define xscale (ScreenWidth / 1280.0)
#define yscale (ScreenHeight / 720.0)

#define ScoreBarHeight (int)(40*yscale)

//GameStates
#define initDiff 50

#define GSIntro 1
#define GSGame 2
#define GSTitleScreen 3
#define GSRamIt 4
#define GSSubScore 5
#define GSSpaceInvaders 6
#define GSBreakout 7
#define GSFrog 8
#define GSSnake 9
#define GSPang 10
#define GSTetris 11
#define GSEddy 12

#define GSIntroInit GSIntro + initDiff
#define GSGameInit GSGame + initDiff
#define GSTitleScreenInit GSTitleScreen + initDiff
#define GSRamItInit GSRamIt + initDiff
#define GSSubScoreInit GSSubScore + initDiff

#define GSSpaceInvadersInit GSSpaceInvaders + initDiff
#define GSBreakoutInit GSBreakout + initDiff
#define GSFrogInit GSFrog + initDiff
#define GSSnakeInit GSSnake + initDiff
#define GSPangInit GSPang + initDiff
#define GSTetrisInit GSTetris + initDiff
#define GSEddyInit GSEddy + initDiff

//SubGameStates
#define SGNone 0
#define SGReadyGo 1
#define SGGame 2
#define SGTimeUp 3
#define SGFrame 4
#define SGCalcScore 5
#define SGFadeIn 6
#define SGPauseMenu 7
#define SGGameHelp 8

//GameModes
#define Modes 3
#define GMRetroCarousel 0
#define GMGame 1
#define GMTimeAttack 2

#define Games 8

//PAUSEMENUS
#define PMNone -1
#define PMContinue 0
#define PMQuit 1
#define PMMusicVol 2
#define PMSoundVol 3
#define PMGameHelp 4


#define PauseMenus 10

//main menus
#define MMStart 0
#define MMHighScores 1
#define MMHelp 2
#define MMOptions 3
#define MMCredits 4
//Sub Main Menus
#define MMSelectGameMode 5
#define MMSelectGame 6
//6 because only fist 5 are real main menu
#define MainMenus 5

//options menu
#define OMMusicVol 0
#define OMSoundVol 1
#define OMResetHighScores 2
#define OMBack 3
#define OptionMenus 4

struct ModeDesc {
	int mode;
	int* name;
	int* description;
};


struct GameDesc {
	int state;
	int* name;
	int* description;
	int* shortdescription;
};


struct PauseMenuDesc {
	int menu;
	int* name;
};


struct GPGamePauseMenusDesc {
	int game;
	int[5] menus;
};


struct MainMenusDesc {
	int menu;
	int* name;
};


struct OptionMenusDesc {
	int menu;
	int* name;
};


//Modes
ModeDesc[Modes] GMModes = {
	{
		GMRetroCarousel,
		"Retro Carousel",
		"In Retro Carousel mode you will play all games for 2 minutes\n"
		"after each other. You can not die by losing lives. Points will\n"
		"be deducted from the score when dying. The aim is to get the\n"
		"highest score, accumulated over all the games"
	},
	{
		GMGame,
		"Lives Mode",
		"In Lives mode you play a single game and start with a fixed\n"
		"amount of lives. Dying will lose you one live. The game is\n"
		"over if the lives reaches 0. The aim of the game is to get\n"
		"the highest score possible without dying."
	},
	{
		GMTimeAttack,
		"Time Attack",
		"In Time Attack mode you play a single game for 5 minutes.\n"
		"You can not die by losing lives. Points will be deducted\n"
		"from the score when dying. The aim is to get the highest\n"
		"score during these 5 minutes of playing."
	}
};

//GameDescriptions
GameDesc[Games] GSGames = {
	{
		GSSpaceInvadersInit,//GSSpaceInvaders,
		"Invaders",
		"Invaders is a game based on Space Invaders. Rows of enemies\n"
		"are closing in you. You have to shoot them down before they\n"
		"reach your mining asteroids. Shooting down enemies gains\n"
		"points, shooting down all enemies gains extra points\n"
		"You can move with dpad and shoot with (A).\n"
		"If enemies reach your mining asteroids you will lose a life.\n"
		"Avoid being shot or you will also lose a life.",
		"a game based on Space Invaders (Arcade)"
	},
	{
		GSBreakoutInit, //gsbreakout,
		"Brick Breaker",
		"Brick Breaker is a game based on Breakout. Rows of blocks\n"
		"have to be destroyed by touching them with the ball.\n"
		"You control the paddle at the bottom of the screen with\n"
		"the dpad. Keeping (A) pressed speeds up the paddle.\n"
		"You have to let the ball bounce of your paddle to\n"
		"send it back in the playfield. Destroying blocks gains points.\n"
		"Fail to bounce back the ball and you lose a life",
		"a game based on Breakout (Arcade)"

	},
	{
		GSFrogInit,//gsfrog,
		"Toady",
		"Toady is a game based on Frogger. You control the robot\n"
		"by the dpad and you have to keep moving up.\n"
		"Each time you move up to a place you had not reached yet,\n"
		"you will gain points. Avoid getting hit by traffic, don't\n"
		"fall into water, don't exceed the edges of the playfield\n"
		"or you will lose a life. Collect different fruits to gain\n"
		"extra score.",
		"a game based on Frogger (Arcade)"
	},
	{
		GSSnakeInit,//gssnake,
		"Snakey",
		"Snakey is a game based on well snake. You control a snake's\n"
		"head (red block) by the dpad. The snake\n"
		"can move in four directions and wants food (green blocks).\n"
		"Each time you eat food the snake's body will grow. Eat\n"
		"food to gain points, the longer your snake is to more\n"
		"points you will gain. Touching the snake's body or going\n"
		"outside the playfield will lose you a life.",
		"a game based on Snake (Nokia 3310)",
	},
	{
		GSPangInit,//gspang,
		"Bubble Buster",
		"Bubble Buster is a game based on Pang. You control a player\n"
		"that needs to pop bubbles. You can control the player using the\n"
		"dpad and shoot at bubbles using (A) button. If you hit a\n"
		"bubble it will split up into smaller bubbles and you gain points. Get\n"
		"hit by a bubble and you will lose a life, making you temporary\n"
		"invincible but you can not shoot during this time. Clearing all\n"
		"bubbles gives you extra points.",
		"a game based on Pang (Arcade)",
	},
	{
		GSTetrisInit,
		"Block Stacker",
		"Block Stacker is a game of tetris. You control the blocks\n"
		"with the dpad. You need to stack them in such a manner that\n"
		"they form complete rows. Once this is done that row will be\n"
		"removed. Speed increases gradually and having no place at\n"
		"the top to place a block will lose you a life. You can rotate\n"
		"blocks using (A) and quick drop them using (X).",
		"a game based on Tetris"
	},
	{
		GSRamItInit,
		"Color Invasion",
		"Color Invasion is a game based on Ram-It. You control the\n"
		"cannon with the dpad. You need to shoot the invading\n"
		"colored bars completely of the screen using (A). Points\n"
		"are awarded when the colored bar is completely of the\n"
		"screen, the closer a bar had gotten to the cannon the more\n"
		"points you will gain. You also gain extra points for clearing\n"
		"all bars from the screen. When a colored bar reaches the\n"
		"cannon rail you will lose a life.",
		"a game based on Ram-It (Atari 2600)"
	},
	{
		GSEddyInit,//gseddy,
		"Faster Dave",
		"Faster Dave is a game based on Fast Eddie. You control Dave with\n"
		"dpad. You need to avoid or jump over enemies with the (A)\n"
		"button while collecting the magic balls. When you collect 9\n"
		"balls the end level key is reachable. You are safe on ladders. Points\n"
		"are received for collecting magic balls and getting the end level\n"
		"key. Collecting the 10th magic ball is not required. When you touch\n"
		"an enemy you will a lose life. Every 5 levels, level layout changes.",
		"a game based on Fast Eddie (Atari 2600)"
	}
};

//PauseMenus
//order must equal order from pmvalues !!!
PauseMenuDesc[PauseMenus] PMPauseMenus =
{
	{PMContinue,	"Continue"},
	{PMQuit,		"Quit"},
	{PMMusicVol,	"Music Volume: "},
	{PMSoundVol,	"Sound Volume: "},
	{PMGameHelp,	"Game Help"},
};

//GamePauseMenus
GPGamePauseMenusDesc[Games] GPGamePauseMenus = {
	{GSSpaceInvaders,	{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSBreakout,		{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSFrog,			{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSSnake,			{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSPang,			{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSTetris,			{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSRamIt,			{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}},
	{GSEddy,			{PMContinue, PMGameHelp, PMMusicVol, PMSoundVol, PMQuit}}
};

//MainMenus
MainMenusDesc[MainMenus] MMMainMenus =
{
	{MMStart,				"Start Game"},
	{MMHighScores,	"High Scores"},
	{MMOptions,				"Options"},
	{MMHelp,				"Help"},
	{MMCredits,				"Credits"},
};

//OptionsMenus
OptionMenusDesc[OptionMenus] OMOptionMenus =
{
	{OMMusicVol,		"Music Volume: "},
	{OMSoundVol,		"Sound Volume: "},
	{OMResetHighScores, "Reset Highscores"},
	{OMBack,			"Back"},
};

int TimerTicks;

int NextSubState, NextSubStateTimeAdd;
float NextSubStateCounter;

int ActiveGameGameStateId;

int RetroCarouselHighScore, RetroCarouselScore;
int[Games][Modes] HighScores;
int[Games][Modes] Scores;

int GameState, SubGameState, GameMode, Game;
float SubStateCounter;
int MusMenu;
int SfxConfirm, SfxBack, SfxSelect, SfxScore, SfxOne, SfxTwo, SfxThree, SfxTimeOver, SfxReadyGo, SfxOneMinute;
float Timer;
int SubStateTime;
int GFXFrameID, GFXOuterFrameID, GFXMedal, GFXPrevewID, GFXPreviewID2;
int CurrentGameMusicID;

game_signature GameSignature;
#define HighScoresSavePosition 100
#define SoundVolumeSavePosition (sizeof(game_signature))
#define MusicVolumeSavePosition (SoundVolumeSavePosition + sizeof(int))

float getCurrentTimeMilliseconds()
{
	return get_frame_counter() * 1000.0/60.0;
}

//this one does not change subgamestate to SGFadeIn it is needed for the ingame pause menu's
//or main menu (basically it allows fading while keeping the subgamestate
void CGame_StartFade()
{
}

//mainly used to fade when going from one gamestate to another gamestate
void CGame_StartCrossFade(int SetGameState, int SetNextSubState, float SetNextSubStateCounter)
{
	GameState = SetGameState;
	SubGameState = SetNextSubState;
	SubStateCounter = (float)SetNextSubStateCounter;
	SubStateTime = getCurrentTimeMilliseconds() + NextSubStateTimeAdd + 500;
	return;
}

void CGame_ResetHighScores()
{
	for(int x = 0; x < Games; x++)
		for(int y = 0; y < Modes; y++)
			HighScores[x][y] = 0;
	RetroCarouselHighScore = 0;
}

void CGame_ResetScores()
{
	for(int x = 0; x < Games; x++)
		for(int y = 0; y < Modes; y++)
			Scores[x][y] = 0;
	RetroCarouselScore = 0;
}

void CGame_AddToScore(int Value)
{
	int AScore = Value;
	if (AScore < 0)
		if (GameMode == GMGame)
			AScore = 0;

	Scores[Game][GameMode] += AScore;
	if (Scores[Game][GameMode] < 0)
		Scores[Game][GameMode] = 0;
}

void CGame_LoadHighScoresSettings()
{
	int VolumeMusic = 128, VolumeSound = 128;
	CGame_ResetHighScores();
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&VolumeMusic, MusicVolumeSavePosition, sizeof(sizeof (int)));
			card_read_data(&VolumeSound, SoundVolumeSavePosition, sizeof(sizeof (int)));
			card_read_data(&RetroCarouselHighScore, HighScoresSavePosition  , sizeof(sizeof (RetroCarouselHighScore)));
			for (int i = 0; i < Games; i++)
				for (int j = 0; j < Modes; j++)
				card_read_data(&HighScores[i][j], HighScoresSavePosition  + sizeof(RetroCarouselHighScore) +  (i * sizeof(HighScores[i][j]) * Modes + j) , sizeof(HighScores[i][j]));
		}
	CAudio_SetVolumeMusic(VolumeMusic);
	CAudio_SetVolumeSound(VolumeSound);
}

void CGame_SaveHighScoresSettings()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			int VolumeMusic = CAudio_GetVolumeMusic();
			int VolumeSound = CAudio_GetVolumeSound();
			card_write_data(&VolumeMusic, MusicVolumeSavePosition, sizeof(sizeof (VolumeMusic)));
			card_write_data(&VolumeSound, SoundVolumeSavePosition, sizeof(sizeof (VolumeSound)));
			card_write_data(&RetroCarouselHighScore, HighScoresSavePosition  , sizeof(sizeof (RetroCarouselHighScore)));
			for (int i = 0; i < Games; i++)
				for (int j = 0; j < Modes; j++)
				card_write_data(&HighScores[i][j], HighScoresSavePosition  + sizeof(RetroCarouselHighScore) +  (i * sizeof(HighScores[i][j]) * Modes + j) , sizeof (HighScores[i][j]));
		}
}

int* faststrcat( int* dest, int* src )
{
     while (*dest) dest++;
     while (*dest++ = *src++);
     return --dest;
}

#endif