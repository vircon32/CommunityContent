#ifndef COPTIONSSELECTOR_H
#define COPTIONSSELECTOR_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"
#include "../sound.h"

struct COptionsSelector
{
 	Texture* Image;
 	int Selection;
};

COptionsSelector* COptionsSelector_Create()
{
	COptionsSelector* Result = (COptionsSelector *) malloc(sizeof(COptionsSelector));
	Result->Image = loadImageAtPath("graphics/optionsselect");
	Result->Selection = 1;
	return Result;
}

void COptionsSelector_Draw(COptionsSelector* Selector)
{
	int y;
	switch(Selector->Selection)
	{
		case 1 :
			y = 65*yscale;
			break;
		case 2 :
			y = 95*yscale;
			break;
		case 3 :
			y = 125*yscale;
			break;
	}
	drawTextureZoomed(Selector->Image, 0, ScreenXOffset + 75*xscale, y);
}

int COptionsSelector_GetSelection(COptionsSelector* Selector)
{
	return Selector->Selection;
}

void COptionsSelector_MoveDown(COptionsSelector* Selector)
{
	if (Selector->Selection < 2)
	{
		Selector->Selection++;
		playMenuSound();
	}
}

void COptionsSelector_MoveUp(COptionsSelector* Selector)
{
	if (Selector->Selection > 1)
	{
		Selector->Selection--;
		playMenuSound();
	}
}

void COptionsSelector_Destroy(COptionsSelector* Selector)
{
	freeTexture(Selector->Image);
	free(Selector);
}


#endif