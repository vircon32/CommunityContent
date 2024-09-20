#ifndef CFAIRY_H
#define CFAIRY_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"

struct CFairy
{
  	bool Hidden;
 	int X,Y,Width,Height,Delay,AnimPhase,AnimDelay;
 	Texture* Image;
} ;

CFairy* CFairy_Create(int XIn, int YIn,int AnimDelayIn)
{
	CFairy* Result = (CFairy*) malloc(sizeof(CFairy));
	Result->Image = loadImageAtPath("graphics/ryf-fairy");
	Result->X = XIn;
	Result->Y = YIn;
	Result->Width = 27;
	Result->Height = 33;
	Result->AnimPhase = 0;
	Result->Delay = 0;
	Result->Hidden = false;
	Result->AnimDelay = AnimDelayIn;
	return Result;
}

void CFairy_Draw(CFairy* Fairy)
{
	if (!Fairy->Hidden)
	{
		drawTextureZoomed(Fairy->Image, Fairy->AnimPhase, ScreenXOffset + Fairy->X, Fairy->Y);
		Fairy->Delay++;
		if (Fairy->Delay >= Fairy->AnimDelay)
		{
			Fairy->AnimPhase++;
			Fairy->Delay = 0;
			if (Fairy->AnimPhase == 2)
				Fairy->AnimPhase = 0;
		}
	}
}

int CFairy_GetX(CFairy* Fairy)
{
	return Fairy->X;
}

void CFairy_Destroy(CFairy* Fairy)
{
	freeTexture(Fairy->Image);
	free(Fairy);
}


#endif