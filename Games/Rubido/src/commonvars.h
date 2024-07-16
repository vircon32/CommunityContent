#ifndef COMMONVARS_H
#define COMMONVARS_H

#include "memcard.h"
#include "texture.h"

// The diffrent difficultys
#define VeryEasy 0
#define Easy 1
#define Hard 2
#define VeryHard 3

// The diffrent gameStates possible in the game
#define GSQuit 0
#define GSGame 1 
#define GSTitleScreen 2
#define GSDifficultySelect 3 
#define GSCredits 4

#define GSInitDiff 50

#define GSGameInit (GSGame + GSInitDiff)
#define GSTitleScreenInit (GSTitleScreen + GSInitDiff)
#define GSDifficultySelectInit (GSDifficultySelect + GSInitDiff)
#define GSCreditsInit (GSCredits + GSInitDiff)

//game defines
#define NrOfRows 9
#define NrOfCols 9
#define TileWidth 36
#define TileHeight 36
#define IDPeg 1
#define XOffSet 95
#define YOffSet 16

//game
bool PrintFormShown = false;
int Difficulty = VeryEasy;
int Moves = 0;
int[4] BestPegsLeft;
int iMovesLeft;
int iPegsLeft;

//main
game_signature	GameSignature;
Texture *IMGCredits;
Texture *IMGPeg;
Texture *IMGBackground;
Texture *IMGEasyInfo;
Texture *IMGVeryEasyInfo;
Texture *IMGHardInfo;
Texture *IMGVeryHardInfo;

int GameState = GSTitleScreenInit; // the game state
#endif