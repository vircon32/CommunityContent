#ifndef COMMON_H
#define COMMON_H

#include "libs/TextFonts/textfont.h"
#include "memcard.h"
#include "texture.h"
#include "caudio.h"
#include "defines.h"
#include "memcard.h"

Texture *IMGBackground=NULL,IMGBlocks1=NULL,IMGBlocks2=NULL,IMGBlocks3=NULL,IMGBlocks4=NULL,IMGBlocks5=NULL,IMGCursor=NULL,IMGReady=NULL,IMGGo=NULL,IMGTimeOver=NULL,IMGIntro1=NULL,IMGIntro2=NULL,IMGIntro3=NULL,
        IMGTitleScreen=NULL,IMGPlay1=NULL,IMGPlay2=NULL,IMGHighScores1=NULL,IMGHighScores2=NULL,IMGCredits1=NULL,IMGCredits2=NULL,
        IMGCredits=NULL,IMGSelectGame=NULL,IMGFixedTimer1=NULL,IMGFixedTimer2=NULL,IMGRelativeTimer1=NULL,IMGRelativeTimer2=NULL,IMGHighScores;



int [NrOfSounds] Sounds;
int [MaxMusicFiles] Music;

game_signature GameSignature;
textfont* font,BigFont,MonoFont;
int Timer;
int movesLeft;
int GameState = GSIntro;
int MusicCount=0,Score=0;
int GameType = Fixed;
SHighScore[2][10] HighScores;

#endif