#include "CGame.h"
#include "video.h"
#include "Vec2F.h"
#include "CImage.h"
#include "CSprites.h"
#include "debugspeed.h"

#define BENCHMARKSCALESPRITES 1
#define BENCHMARKROTATEDSPRITES 0
#define BENCHMARKSTARTSPRITESAMOUNT 1
#define BENCHMARKANIMATEDSPRITES 0
#define BENCHMARKENABLED 0

int BenchMarkGFX;
int BenchMarkTotalAmount = 0;
int BenchMarkNeedMaxReset = 0;

void benchMarkAddSprite(int amount)
{
	if (BenchMarkTotalAmount + amount >= 0)
		BenchMarkTotalAmount += amount;
	CSprites_SetSpriteMax(BenchMarkTotalAmount);
	
	for (int i = 0; i < amount; i ++)
	{
		CSprite* sprite = CSprites_CreateSprite();
		Vec2F pos = {rand()%screen_width,rand()%screen_height};
		Vec2F scale = {-2, 2 };
		CSprites_SetSpriteImageTiles(sprite,&BenchMarkGFX,6,3);
		SDL_Point* tz = CSprites_TileSize(sprite);
		if (BENCHMARKANIMATEDSPRITES)
			CSprites_SetSpriteAnimation(sprite, 6, 10, 6);
		else
			CSprites_SetSpriteAnimation(sprite, 6, 6, 0);
		CSprites_SetSpriteDepth(sprite, 0);
		scale.x = CGameFrog_playerspeed / tz->x;
		scale.y = CGameFrog_playerspeed / tz->y;
		free(tz);
		CSprites_SetSpriteLocation(sprite,&pos);
		if(BENCHMARKSCALESPRITES)
			CSprites_SetSpriteScale(sprite, &scale);
		sprite->xspeed = -2 + rand() % 5;
		sprite->yspeed = -2 + rand() % 5;
		if(BENCHMARKROTATEDSPRITES)
			CSprites_SetSpriteRotationSpeed(sprite, (rand()%20)/5);
	}
	BenchMarkNeedMaxReset = 2;
}

void benchmarkMain()
{
		StartDebugSpeed(2);
		clear_screen(color_black);
		CSprites_UpdateSprites();
		for(int i = 0; i < BenchMarkTotalAmount; i++)
		{
			if((CSprites_Sprites[i]->x > screen_width) || (CSprites_Sprites[i]->x < 0))
				CSprites_Sprites[i]->xspeed = CSprites_Sprites[i]->xspeed * -1;
			if((CSprites_Sprites[i]->y > screen_height) || (CSprites_Sprites[i]->y < 0))
				CSprites_Sprites[i]->yspeed = CSprites_Sprites[i]->yspeed * -1;
		}
		CSprites_DrawSprites();		
		if(gamepad_button_a() == 1)
		{
			benchMarkAddSprite(1);
		}

		if(gamepad_button_b() == 1)
		{
			benchMarkAddSprite(25);
		}
	
		if(gamepad_button_y() == 1)
		{
			benchMarkAddSprite(-1);
		}

		if(gamepad_button_x() == 1)
		{
			benchMarkAddSprite(-25);
		}

		if(gamepad_button_l() == 1)
				ResetAllDebugSpeedMaxValues();
		int[100] Text;
		int[10] Nr;
		int* PText;
		itoa(BenchMarkTotalAmount, Nr, 10);
		PText = Text; *PText = 0; PText = faststrcat(PText, Nr);
		PText = faststrcat(PText, " sprites ");
		StopDebugSpeed(2);
		printDebugSpeed(2,0,20,Text, 1);
		if(BenchMarkNeedMaxReset > 0)
		{
			BenchMarkNeedMaxReset--;
			ResetDebugSpeedMaxValue(2);
		}
		
		end_frame();
}

void main()
{
	if(BENCHMARKENABLED)
	{
		srand(0);
		CImage_Init();
		CSprites_Init();
		CSprites_SetSpriteMax(1000);
		BenchMarkGFX = CImage_LoadImage("frog/watergrass.png");		
		benchMarkAddSprite(BENCHMARKSTARTSPRITESAMOUNT);
	}
	else
	{
		CGame_Init();
	}
	while(true)
	{
		if(BENCHMARKENABLED)
		{
			benchmarkMain();
		}
		else
		{	
			StartDebugSpeed(0);
			if(gamepad_button_l() == 1)
				ResetAllDebugSpeedMaxValues();

			CGame_MainLoop();
			StopDebugSpeed(0);
			printDebugSpeed(0, 0,180, "FRA ", 1);
			printDebugSpeed(4, 0,180 + bios_character_height*2, "INI ", 1);
			printDebugSpeed(5, 0,180 + bios_character_height*4, "LGC ", 1);
			printDebugSpeed(6, 0,180+ bios_character_height*6, "DRW ", 1);
			end_frame();
		}
	}
	CGame_DeInit();
}