#ifndef CHAND_H
#define CHAND_H


#include "misc.h"
#include "../helperfuncs.h"
#include "../texture.h"
#include "../commonvars.h"


struct CHand
{
 	int X,Y,MoveCoolDown;
 	bool Hidden;
 	Texture* Image;
};

CHand* CHand_Create()
{
	CHand* Result = (CHand*) malloc(sizeof(CHand));
	Result->Image = loadImageAtPath("graphics/hand");
	Result->Hidden = false;
	Result->X = 0;
	Result->Y = 0;
	Result->MoveCoolDown = 0;
	return Result;
}

void CHand_Draw(CHand* Hand)
{
	if (!Hand->Hidden)
	{
		drawTextureZoomed(Hand->Image, 0, ScreenXOffset + MinPlayAreaX + Hand->X * BlockWidth, MinPlayAreaY + Hand->Y * BlockHeight);
	}
}

void CHand_Move(CHand* Hand)
{
	if (Hand->MoveCoolDown > 0)
		Hand->MoveCoolDown--;
	if ((!Hand->Hidden) && (Hand->MoveCoolDown == 0))
	{
		if (gamepad_up() > 0)
		{
			if (Hand->Y - 1 >= 0)
			{
				Hand->Y = Hand->Y - 1;
				Hand->MoveCoolDown = 3*fpsscale;
			}
		}
		else if (gamepad_down() > 0)
		{
			if (Hand->Y + 1 < Rows)
			{
				Hand->Y = Hand->Y + 1;
				Hand->MoveCoolDown = 3*fpsscale;
			}
		}
		
		if (gamepad_left() > 0)
		{
			if (Hand->X - 1 >= 0)
			{
				Hand->X = Hand->X - 1;
				Hand->MoveCoolDown = 3*fpsscale;
			}
		}
		else if (gamepad_right() > 0)
		{
			if (Hand->X + 1 < Cols)
			{
				Hand->X = Hand->X + 1;
				Hand->MoveCoolDown = 3*fpsscale;
			}
		}
	}
}

void CHand_SetPosition(CHand* Hand, int XIn,int YIn)
{
	Hand->X = XIn;
	Hand->Y = YIn;
}

int CHand_GetPlayFieldX(CHand* Hand)
{
	return Hand->X;
}

int CHand_GetPlayFieldY(CHand* Hand)
{
	return Hand->Y;
}

void CHand_Hide(CHand* Hand)
{
	Hand->Hidden = true;
}

void CHand_Show(CHand* Hand)
{
	Hand->Hidden = false;
}

void CHand_Destroy(CHand* Hand)
{
	freeTexture(Hand->Image);
	free(Hand);
}

#endif