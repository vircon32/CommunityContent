#ifndef game_h
#define game_h

#include "time.h"
#include "misc.h"
#include "input.h"
#include "texture.h"
#include "savestate.h"
#include "printfuncs.h"

void DrawGame(void)
{
	int X, Y;
	for (X = 0; X < 3; X++)
		for (Y = 0; Y < 3; Y++)
			if (EnemyStates[X][Y])
			{
				drawTexture(Enemy,0, 210 + (X * 87), 55 + (Y * 71));
			}

	for (X = 0; X < 3; X++)
	{
		if (PlayerStates[X])
		{
			drawTexture(Player,0, 210 + (X * 87), 55+213);
		}
	}
}

void MoveEnemy(void)
{
	int X, Y;
	for (X = 0; X < 3; X++)
		for (Y = 2; Y >= 1; Y--)
			EnemyStates[X][Y] = EnemyStates[X][Y - 1];
	for (X = 0; X < 3; X++)
		EnemyStates[X][0] = false;
	for (X = 0; X <= 1; X++)
		EnemyStates[rand() % 3][0] = true;
}

void MoveLeft(void)
{
	int X;
	for (X = 0; X < 2; X++)
	{
		if (PlayerStates[X + 1])
		{
			PlayerStates[X] = true;
			PlayerStates[X + 1] = false;
		}
	}
}

void MoveRight(void)
{
	int X;
	for (X = 2; X >= 1; X--)
	{
		if (PlayerStates[X - 1])
		{
			PlayerStates[X] = true;
			PlayerStates[X - 1] = false;
		}
	}
}

bool IsCollided(void)
{
	int X;
	bool Temp;
	Temp = false;
	for (X = 0; X < 3; X++)
		if (PlayerStates[X] && EnemyStates[X][2])
		{
			Temp = true;
			HitPosition = X;
		}
	return Temp;
}

void HitFlash(void)
{
	PlayerStates[HitPosition] = !PlayerStates[HitPosition];
	EnemyStates[HitPosition][2] = !EnemyStates[HitPosition][2];
}

void InitialiseStates(void)
{
	int X, Y;
	for (X = 0; X < 3; X++)
		for (Y = 0; Y < 3; Y++)
			EnemyStates[X][Y] = false;
	for (X = 0; X < 3; X++)
		PlayerStates[X] = false;
	PlayerStates[1] = true;
}

void initGame(void)
{
	srand(get_time());
	Teller = 25;
	FlashesDelay = 14;
	Flashes = 0;
	CanMove = true;
	Score = 0;
	Delay = 60;
	DelayExtra = 60;
	LivesLost = 0;
	CrashSoundPlayed = false;
	InitialiseStates();
	playStartSound();
}


void game(void)
{
	int X;
    if (gameState == gsInitGame)
    {
        initGame();
        gameState -= gsInitDiff;
    }
    
    if (gamepad_right() == 1)
    {
		if (CanMove)
			MoveRight();
    }

    if (gamepad_left() == 1)
    {
		if (CanMove)
			MoveLeft();
    }

	drawTexture(Background,0, 0, 0);
	printNumber(lcdFont, 31, 3, -3, 2, 12, Score, 6);
	printNumber(lcdFont, 23, 3, 7, 2, 12, getHiScore(), 6);
	if (LivesLost >= 1)
	{
		for (X = 0; X < LivesLost; X++)
			printMessage(lcdFont, 17 + X, 3,0,3, 12,  "X");
	}
	if(DelayExtra > 0)
	{
		DelayExtra--;
		return;
	}
	Teller++;
	if (Teller >= Delay)
	{
		if (!IsCollided() && CanMove)
		{
			Teller = 0;
			for (X = 0; X < 3; X++)
				if (EnemyStates[X][2])
				{
					Score += 10;
					if (Score > getHiScore())
						setHiScore(Score);
					if ((Score % 100 == 0) && (Delay > 16))
						Delay--;
				}
			MoveEnemy();
			playTickSound();
		}
		else
		{
			if (!CrashSoundPlayed)
			{
				playCrashSound();
				CrashSoundPlayed = true;
			}
			CanMove = false;
			FlashesDelay++;
			if (FlashesDelay == 15)
			{
				Flashes++;
				HitFlash();
				FlashesDelay = 0;
				if (Flashes == 6)
				{
					Flashes = 0;
					CanMove = true;
					Teller = 0;
					CrashSoundPlayed = false;
					EnemyStates[HitPosition][2] = false;
					LivesLost++;
					FlashesDelay = 14;
					if (LivesLost == 3)
						gameState = gsInitGameOver;
				}
			}
		}
	}
	DrawGame();
}

void initGameOver(void)
{
	playGameOverSound();
}

void gameOver(void)
{
	if (gameState == gsInitGameOver)
	{
		initGameOver();
		gameState -= gsInitDiff;
	}

	if ((gamepad_right() == 1) ||
		(gamepad_left() == 1) ||
		(gamepad_button_a() == 1) ||
		(gamepad_button_b() == 1))
	{
		gameState = gsInitGame;
	}


	drawTexture(Background, 0,0, 0);
	printNumber(lcdFont, 31, 3, -3, 2, 12, Score, 6);
	printNumber(lcdFont, 23, 3, 7, 2, 12, getHiScore(), 6);
	if (LivesLost >= 1)
	{
		for (int X = 0; X < LivesLost; X++)
			printMessage(lcdFont, 17 + X, 3,0,3, 12,  "X");
		
	}
	DrawGame();	
}

void FlashIntro(void)
{
	int X, Y;
	for (X = 0; X < 3; X++)
		for (Y = 0; Y < 3; Y++)
			EnemyStates[X][Y] = !EnemyStates[X][Y];
	for (X = 0; X < 3; X++)
		PlayerStates[X] = !PlayerStates[X];
}


void gameIntroInit(void)
{
	LivesLost = 0;
	FlashesDelay = 0;
	Score = 0;
}

void gameIntro(void)
{
	if (gameState == gsInitGameIntro)
	{
		gameIntroInit();
		gameState -= gsInitDiff;
	}


	if ((gamepad_right() == 1) ||
		(gamepad_left() == 1) ||
		(gamepad_button_a() == 1) ||
		(gamepad_button_b() == 1))
	{
		gameState = gsInitGame;
	}

	drawTexture(Background, 0, 0, 0);
	FlashesDelay++;
	if (FlashesDelay == 25)
	{
		FlashesDelay = 0;
		FlashIntro();
		if (PlayerStates[0])
		{
			LivesLost = 3;
			Score = 888888;
		}
		else
		{
			LivesLost = 0;
			Score = 0;
		}
	}
	if (Score > 0)
	{
		printNumber(lcdFont, 31, 3, -3, 2, 12, Score, 6);
		printNumber(lcdFont, 23, 3, 7, 2, 12, Score, 6);
	}
	if (LivesLost >= 1)
	{
		for (int X = 0; X < LivesLost; X++)
			printMessage(lcdFont, 17 + X, 3,0,3, 12, "X");
	}
	DrawGame();		
}



#endif