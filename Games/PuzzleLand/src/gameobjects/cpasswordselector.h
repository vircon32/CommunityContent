#ifndef CPASSWORDSELECTOR_H
#define CPASSWORDSELECTOR_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"
#include "../sound.h"

struct CPasswordSelector
{
 	Texture* Image;
 	int X,Y;
} ;


CPasswordSelector* CPasswordSelector_Create()
{
	CPasswordSelector* Result = (CPasswordSelector*) malloc(sizeof(CPasswordSelector));
	Result->Image = loadImageAtPath("graphics/select");
	Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CPasswordSelector_Draw(CPasswordSelector* Selector)
{
	drawTextureZoomed(Selector->Image, 0, ScreenXOffset + XOffsetPassword + (3 * xscale) + Selector->X * (35 * xscale), YOffsetPassword + ((Selector->Y * 35) * yscale) - 5*yscale);
}

void CPasswordSelector_MoveDown(CPasswordSelector* Selector)
{
	if (Selector->Y < LetterRows - 2)
	{
		Selector->Y = Selector->Y + 1;
		playMenuSound();
	}
	else
		if ((Selector->Y == LetterRows -2) && (Selector->X < LetterCols -2))
		{
			Selector->Y = Selector->Y + 1;
			playMenuSound();
		}
}

void CPasswordSelector_MoveLeft(CPasswordSelector* Selector)
{
	if (Selector->X > 0)
	{
		Selector->X = Selector->X -1;
		playMenuSound();
	}
}

void CPasswordSelector_MoveRight(CPasswordSelector* Selector)
{
	if (Selector->Y < LetterRows -1)
		if (Selector->X < LetterCols -1)
		{
			Selector->X = Selector->X + 1;
			playMenuSound();
		}

	if (Selector->Y == LetterRows - 1)
		if (Selector->X < LetterCols -3)
		{
			Selector->X = Selector->X + 1;
			playMenuSound();
		}
}

void CPasswordSelector_MoveUp(CPasswordSelector* Selector)
{
	if (Selector->Y > 0)
	{
		Selector->Y = Selector->Y - 1;
		playMenuSound();
	}
}

int CPasswordSelector_GetX(CPasswordSelector* Selector)
{
	return Selector->X;
}

int CPasswordSelector_GetY(CPasswordSelector* Selector)
{
	return Selector->Y;
}

void CPasswordSelector_Destroy(CPasswordSelector* Selector)
{
	freeTexture(Selector->Image);
	free(Selector);
}


#endif