#ifndef MAIN_H
#define MAIN_H

#include "memcard.h"
#include "defines.h"
#include "caudio.h"
#include "cworldparts.h"
#include "texture.h"
#include "libs/TextFonts/textfont.h"

struct HighScore{
	int Score;
	int Level;
};

struct SPoint{
    int X;
    int Y;
};

Texture *IMGBackgroundLevelEditor=NULL,IMGBackground=NULL,IMGBlocks=NULL,IMGFloor = NULL,IMGLevelDone=NULL, IMGArrows1=NULL, IMGArrows2=NULL,IMGGameOver=NULL,IMGLevelpackDone=NULL,IMGTitleScreen=NULL,IMGGrid=NULL;
textfont* font,BigFont,BigFont2;
//SDL_Color TextColor;
int ScoreStatus = 0, RetryScore=0, ClearScore=0, MoveScore=0, TotalScore=0;
bool KeyPressed = false;
int Movement = MNone;
CWorldParts* WorldParts;
int GameState = GSTitleScreenInit;
int MaxMoves=0,Retries=5;
int Music;
int[NrOfSounds] Sounds;
int Score=0;
HighScore[MaxHighScores] HighScores;
bool WasNewHighScore = false;
int skin = 1;
int ColorSelection, ColorNoSelection;
game_signature GameSignature;
int titleSelection = 0;
int optionSelection = 0;
#endif
