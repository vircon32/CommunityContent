#include "video.h"
#include "commonvars.h"
#include "intro.h"
#include "sound.h"
#include "game.h"
#include "savestate.h"

void preloadImages()
{
    Background = newTexture(0,1,640,360);
	introFont =  newTexture(1,41,24,984);
    lcdFont = newTexture(2, 41,12, 492);
    Enemy = newTexture(3,1,54,54);
	Player = newTexture(4,1,54,54);
}
    

void unLoadImages()
{
	freeTexture(introFont);
	freeTexture(lcdFont);
	freeTexture(Player);
	freeTexture(Enemy);
	freeTexture(Background);
}

void resetGlobals()
{
	frames = 0;
	for (int X = 0; X < 3; X++)
		for (int Y = 0; Y < 3; Y++)
			EnemyStates[X][Y] = false;
	for (int X = 0; X < 3; X++)
		PlayerStates[X] = false;
	PlayerStates[1] = false;
}

// game initialization
void setupGame()
{  
    resetGlobals();
	gameState = gsInitIntro;
    preloadImages();    
    initSaveState();    
    initSound();
    setSoundOn(1);
}

void terminateGame()
{
	unLoadImages();
	deInitSound();
}

// main update function
void main()
{
	setupGame();
    while(true)
	{
		//gamestate handling   
		switch (gameState)
		{
			case gsInitIntro:
			case gsIntro:
				intro();
				break;
			case gsInitGame:
			case gsGame:
				game();
				break;
			case gsInitGameIntro:
			case gsGameIntro:
				gameIntro();
				break;
			case gsInitGameOver:
			case gsGameOver:
				gameOver();
				break;
			default:
				break;
		}
		end_frame();
	}
	terminateGame();
}
