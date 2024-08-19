#ifndef CCLOUD_H
#define CCLOUD_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"

#define Big 0 
#define Small 1

struct CCloud
{
 	float X,Xi;
 	int Y,Width,Height;
 	Texture* Image;
} ;


CCloud* CCloud_Create(int XIn,int YIn,float XiIn,int Style)
{
	CCloud* Result = (CCloud*)malloc(sizeof(CCloud));
	if (Style == Big)
	{
		Result->Image = loadImageAtPath("graphics/ryf-cloud");
		Result->Width = 60*xscale;
		Result->Height = 28*yscale;
	}
	else
	{
		Result->Image = loadImageAtPath("graphics/ryf-smallcloud");
		Result->Width=30*xscale;
		Result->Height=14*yscale;
	 }
	Result->X = (float)XIn;
	Result->Y = YIn;
	Result->Xi = XiIn;
	return Result;
}

void CCloud_Draw(CCloud* Cloud)
{
	drawTextureZoomed(Cloud->Image, 0, ScreenXOffset + (int)Cloud->X, Cloud->Y);
}

void CCloud_Move(CCloud* Cloud)
{
	if ((Cloud->X > -Cloud->Width) && (Cloud->X < WINDOW_WIDTH*xscale))
		Cloud->X = Cloud->X + Cloud->Xi;
	else
		if (Cloud->X <= -Cloud->Width)
			Cloud->X = 319*xscale;
		else
			Cloud->X = -Cloud->Width + 1.0;
}


void CCloud_Destroy(CCloud* Cloud)
{
	freeTexture(Cloud->Image);
	free(Cloud);
}


#endif