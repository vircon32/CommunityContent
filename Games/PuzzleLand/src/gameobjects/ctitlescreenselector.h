#ifndef CTITLESCREENSELECTOR_H
#define CTITLESCREENSELECTOR_H

#include "misc.h"
#include "input.h"
#include "../sound.h"
#include "../commonvars.h"

struct CTitleScreenSelector
{
	int X,Selection;
	Texture *Image;
};


CTitleScreenSelector* CTitleScreenSelector_Create()
{
	CTitleScreenSelector* Result = (CTitleScreenSelector*) malloc(sizeof(CTitleScreenSelector));
	Result->Image=loadImageAtPath("graphics/titleselector");
    Result->Selection = 1;
	return Result;
}

void CTitleScreenSelector_MoveUp(CTitleScreenSelector* selector)
{

	if (selector->Selection > 1)
	{
		selector->Selection--;
		playMenuSound();
	}

}

void CTitleScreenSelector_MoveDown(CTitleScreenSelector* selector)
{
	if (selector->Selection < 4)
	{
		selector->Selection++;
		playMenuSound();
	}

}

void CTitleScreenSelector_Draw(CTitleScreenSelector* selector)
{
	int y = 0;
	switch (selector->Selection)
	{
		case 1 : y = 66*yscale;
				 break;
		case 2 : y = 100*yscale;
				 break;
		case 3 : y = 136*yscale;
				 break;
		case 4 : y = 175*yscale;
				 break;
	}
	drawTextureZoomed(selector->Image, 0, ScreenXOffset + 71*xscale, y);
}

void CTitleScreenSelector_destroy(CTitleScreenSelector* selector)
{
	freeTexture(selector->Image);
	free(selector);
}



#endif