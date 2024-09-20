#ifndef CPLAYER_H
#define CPLAYER_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"


#define Walking 0 
#define Waiting 1 
#define LookingUp 2 
#define EnterBuilding 3 
#define EnteredBuilding 4

struct CPlayer
{
 	int State;
 	Texture *Image,Shadow;
 	float X,Y,MinX,MaxX;
	int AnimPhase,AnimCounter,Delay,Width,Height;
};


//Player anims
int[6] AnimLeft= {12,11,10,9,8,7};
int[6] AnimRight = {1,2,3,4,5,6};
int[4] AnimEnterBuilding = {15,16,17,18};


CPlayer* CPlayer_Create(float Xin,float Yin,float MinXin, float MaxXin)
{
	CPlayer* Result = (CPlayer*) malloc(sizeof(CPlayer));
 	Result->Image = loadImageAtPath("graphics/ryf-player");
 	Result->Shadow = loadImageAtPath("graphics/ryf-shadow");
 	Result->Y = Yin;
	Result->X = Xin;
 	Result->Width = 23*xscale;
 	Result->Height = 28*yscale;
 	Result->AnimCounter = 0;
 	Result->Delay = 0;
 	Result->AnimPhase = 0;
 	Result->MaxX = MaxXin;
 	Result->MinX = MinXin;
 	Result->State = Waiting;
	return Result;
}

void CPlayer_Draw(CPlayer* Player)
{
	drawTextureZoomed(Player->Shadow,0, ScreenXOffset + (int)(Player->X + 1*xscale), (int)(Player->Y + 26*yscale));
	drawTextureZoomed(Player->Image, Player->AnimPhase, ScreenXOffset + (int)Player->X, (int)Player->Y);
}

int CPlayer_GetX(CPlayer* Player)
{
	return Player->X;
}

int CPlayer_GetY(CPlayer* Player)
{
	return Player->Y;
}

int CPlayer_GetWidth(CPlayer* Player)
{
	return Player->Width;
}

void CPlayer_Destroy(CPlayer* Player)
{
 	freeTexture(Player->Shadow);
 	freeTexture(Player->Image);
	free(Player);
}

void CPlayer_Move(CPlayer* Player)
{

	if ((Player->State == Walking) || (Player->State==Waiting))
	{
		if (gamepad_left() > 0)
		{
			if(Player->X - 1*xscale >= Player->MinX)
			{
				Player->X = Player->X -1*xscale;
				Player->AnimPhase = AnimLeft[Player->AnimCounter];
				Player->State = Walking;
			}
			else
				Player->State = Waiting;
		}
 		else
			if (gamepad_right() > 0)
			{
				if(Player->X + 1*xscale <= Player->MaxX)
				{
					Player->X = Player->X +1*xscale;
					Player->AnimPhase = AnimRight[Player->AnimCounter];
					Player->State = Walking;
				}
				else
					Player->State = Waiting;
			}
			else
				Player->State = Waiting;
	}
	if (Player->State == Walking)
	{
		if (Player->Delay > 0)
			Player->Delay--;
		if (Player->Delay <= 0)
		{
			Player->AnimCounter++;
			Player->Delay = 3*fpsscale;
		}
     	if (Player->AnimCounter > 5)
     		Player->AnimCounter = 0;
    }
  	if (Player->State == EnterBuilding)
  	{
  		Player->Delay--;
  		if(Player->Delay<=0)
  		{
  			Player->AnimCounter++;
  			Player->Y = Player->Y - 1*yscale;
  			Player->Delay = 3*fpsscale;
  		}
  		if (Player->AnimCounter > 3)
  		{
  			Player->AnimCounter = 0;
			if(Player->Y <=160*yscale)
				Player->State = EnteredBuilding;
		}
 		Player->AnimPhase = AnimEnterBuilding[Player->AnimCounter];
	}
	if (Player->State == Waiting)
	{
		if ((Player->AnimPhase != 0) && (Player->AnimPhase !=13))
		{
			if (Player->AnimPhase==14)
			{
				Player->AnimPhase = 0;
			}
			else
			{
				if (Player->AnimPhase < 7)
					Player->AnimPhase = 0;
				else
					Player->AnimPhase=13;
			}
		}
	}
 	if (Player->State ==LookingUp)
 		Player->AnimPhase = 14;
}

#endif