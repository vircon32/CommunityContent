#ifndef COMMONVARS_H
#define COMMONVARS_H

#include "memcard.h"
#include "texture.h"
#include "libs/TextFonts/textfont.h"

#define DEBUG 0

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240
#define FRAMERATE 30

#define xscale (480.0 / (float)WINDOW_WIDTH)
#define yscale (360.0 / (float)WINDOW_HEIGHT)
#define fpsscale (60.0 / (float)FRAMERATE)

#define ScreenXOffset ((480 - WINDOW_WIDTH) >> 1)

#define GSTitleScreen 1 
#define GSOldManSpeaking 2 
#define GSPasswordEntry 3 
#define GSOptions 4 
#define GSCredits 5 
#define GSIntro 6 
#define GSQuit 7
#define GSGame 8 
#define GSStageClear 9 
#define GSNextStage 10 
#define GSStageSelect 11

#define GSInitDiff 50

#define GSTitleScreenInit (GSTitleScreen + GSInitDiff)
#define GSOldManSpeakingInit (GSOldManSpeaking + GSInitDiff) 
#define GSPasswordEntryInit (GSPasswordEntry + GSInitDiff)
#define GSOptionsInit (GSOptions + GSInitDiff)
#define GSCreditsInit (GSCredits + GSInitDiff)
#define GSIntroInit (GSIntro + GSInitDiff)
#define GSGameInit (GSGame + GSInitDiff)
#define GSStageClearInit (GSStageClear + GSInitDiff)
#define GSNextStageInit (GSNextStage + GSInitDiff)
#define GSStageSelectInit (GSStageSelect + GSInitDiff)

#define BlockCount 13
#define BorderCount 7
#define BlockWidth 12 * xscale
#define BlockHeight 12 * yscale
#define XOffsetGame 40 * xscale
#define YOffsetGame 34 * yscale
#define XOffsetPassword 50 * xscale
#define YOffsetPassword 75 * yscale
#define XOffsetStageSelect 50 * xscale
#define YOffsetStageSelect 38 * yscale
#define Cols 20
#define Rows 16
#define MinPlayAreaX XOffsetGame
#define MinPlayAreaY YOffsetGame
#define MaxPlayAreaX (XOffsetGame + BlockWidth * Cols)
#define MaxPlayAreaY (YOffsetGame + BlockHeight * Rows)
#define LetterRows 4
#define LetterCols 7


//audio
int*[36] LevelPasswords = {"DAVY","DISK","TREE","SEAL",
						   "OPEN","LION","WINE","GROW",
						   "FOOD","DUEL","MEAT","FLEE",
						   "DUST","LOST","HELP","MILK",
						   "SAFE","DULL","SAVE","BEER",
						   "BILL","BLOW","BIKE","VENT",
						   "ROOM","HOOD","MOOD","FEAR",
						   "REEF","POLE","BEEF","SONG",
						   "HOPE","BLUE","MAIL","MONK"};
int[4][7] Letters = {{'A','B','C','D','E','F','G'},
					 {'H','I','J','K','L','M','N'},
					 {'O','P','Q','R','S','T','U'},
					 {'V','W','X','Y','Z','0','0'}};

int GameMoveCoolDown, PasswordEntryCoolDown;

//common stuff
Texture* Background = NULL;
Texture* Border;
textfont* Mini2X, Ash;

//Game Stuff
int GameState = GSIntroInit;
int Level;

bool NeedGameReset = false;
int StartTime,EndTime;

//Puzzle Game Stuff
Texture* BlockImage, BlockActiveImage;
Texture*[BorderCount] BorderImages;
int[2][Cols][Rows] PlayField;
bool BlockActive;

//stage Clear Stuff
Texture* RoomBackground = NULL;
Texture* StageClearKader = NULL;

//Next Stage Stuff
Texture* Bridge = NULL;

embedded int[Cols*Rows*36] levels = "assets\\levels\\levels.dat"; 

game_signature GameSignature;

#endif