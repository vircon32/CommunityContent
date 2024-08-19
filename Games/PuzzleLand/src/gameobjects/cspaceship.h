#ifndef CSPACESHIP_H
#define CSPACESHIP_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"


struct CSpaceShip
{
 	int X,Y;
 	Texture* Image;
};

CSpaceShip* CSpaceShip_Create()
{
	CSpaceShip* Result = (CSpaceShip*) malloc(sizeof(CSpaceShip));
	Result->Image = loadImageAtPath("graphics/spaceship");
	Result->X=-53*xscale;
	Result->Y= 22*yscale;
	return Result;
}

void CSpaceShip_Draw(CSpaceShip* spaceShip)
{
	drawTextureZoomed(spaceShip->Image, 0, ScreenXOffset + spaceShip->X, spaceShip->Y);
}

void CSpaceShip_Move(CSpaceShip* spaceShip)
{
	if (spaceShip->X < 352*xscale)
		spaceShip->X = spaceShip->X + 3*xscale;
}

int CSpaceShip_GetX(CSpaceShip* spaceShip)
{
	return spaceShip->X;
}

void CSpaceShip_destroy(CSpaceShip* spaceShip)
{
	freeTexture(spaceShip->Image);
	free(spaceShip);
}


#endif