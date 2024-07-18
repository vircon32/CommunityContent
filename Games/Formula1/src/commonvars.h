#ifndef commonvars_h
#define commonvars_h

#include "texture.h"

#define gsGame 0
#define gsIntro 1
#define gsGameIntro 2
#define gsGameOver 3

#define gsInitDiff 50

#define gsInitGame (gsInitDiff + gsGame)
#define gsInitIntro (gsInitDiff + gsIntro)
#define gsInitGameIntro (gsInitDiff + gsGameIntro)
#define gsInitGameOver (gsInitDiff + gsGameOver)

int gameState;
int frames;
Texture* Player, Enemy, Background, introFont, lcdFont;
bool[3][3] EnemyStates;
bool[3] PlayerStates;
int HitPosition, LivesLost;
int Teller, FlashesDelay, Flashes, DelayExtra, Delay, Score;
bool CanMove, CrashSoundPlayed;
#endif