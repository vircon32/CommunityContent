#ifndef CSTAGESELECTSELECTOR_H
#define CSTAGESELECTSELECTOR_H

#include "misc.h"
#include "../sound.h"
#include "../commonvars.h"


struct CStageSelectSelector
{
	int X,Y;
 	Texture* Image;
};




CStageSelectSelector* CStageSelectSelector_Create()
{
	CStageSelectSelector* Result = (CStageSelectSelector*) malloc(sizeof(CStageSelectSelector));
	Result->Image= loadImageAtPath("graphics/select");
    Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CStageSelectSelector_Draw(CStageSelectSelector* selector)
{
	drawTextureZoomed(selector->Image, 0, ScreenXOffset + XOffsetStageSelect + (selector->X * 82) *xscale + 52*xscale, YOffsetStageSelect + selector->Y * 15*yscale - 3*yscale);
}

void CStageSelectSelector_MoveDown(CStageSelectSelector* selector)
{
	if (selector->Y < 11)
	{
		selector->Y++;
		playMenuSound();
	}
}

void CStageSelectSelector_MoveLeft(CStageSelectSelector* selector)
{
	if (selector->X > 0)
	{
		selector->X--;
		playMenuSound();
	}
}

void CStageSelectSelector_MoveRight(CStageSelectSelector* selector)
{
	if (selector->X < 2)
	{
		selector->X++;
		playMenuSound();
	}
}

void CStageSelectSelector_MoveUp(CStageSelectSelector* selector)
{
	if ( selector->Y > 0)
	{
		selector->Y--;
		playMenuSound();
	}
}

int CStageSelectSelector_GetSelection(CStageSelectSelector* selector)
{
	return  selector->X + selector->Y * 3;
}

void CStageSelectSelector_destroy(CStageSelectSelector* selector)
{
	freeTexture(selector->Image);
	free(selector);
}


#endif