#ifndef CSTAGEBLOCK_H
#define CSTAGEBLOCK_H

#include "misc.h"
#include "../texture.h"
#include "../commonvars.h"

struct CStageBlock
{
 	bool Hidden;
 	float X,Y,Yi;
	int Width,Height;
 	Texture* Image;
};

CStageBlock* CStageBlock_Create()
{
	CStageBlock* Result = (CStageBlock*) malloc(sizeof(CStageBlock));
	Result->Image=NULL;
 	return Result;
}

void CStageBlock_Load(CStageBlock* stageBlock, int BlockNr)
{
	int[50] ChrFileName;
	int[10] Nr;
	strcpy(ChrFileName, "graphics/stageblock");
	itoa(BlockNr, Nr, 10);
	strcat(ChrFileName, Nr);
	stageBlock->Image = loadImageAtPath(ChrFileName);
	stageBlock->Hidden = false;
	stageBlock->Yi = 3.0*yscale/fpsscale;
	stageBlock->X = (160.0 - stageBlock->Image->width / 2)*xscale;
	stageBlock->Y = (-stageBlock->Image->height)*yscale;
	stageBlock->Width = stageBlock->Image->width*xscale;
	stageBlock->Height = stageBlock->Image->height*yscale;
}

void CStageBlock_Draw(CStageBlock* stageBlock)
{
	if (!stageBlock->Hidden)
	{
		drawTextureZoomed(stageBlock->Image, 0, ScreenXOffset + (int)stageBlock->X, (int)stageBlock->Y);
	}
}

void CStageBlock_Move(CStageBlock* stageBlock)
{
	if (!stageBlock->Hidden)
		stageBlock->Y = stageBlock->Y + stageBlock->Yi;
}

int CStageBlock_GetY(CStageBlock* stageBlock)
{
	return stageBlock->Y;
}

int CStageBlock_GetHeight(CStageBlock* stageBlock)
{
	return stageBlock->Height;
}

void CStageBlock_destroy(CStageBlock* stageBlock)
{
	if(!stageBlock)
		return;
	if (stageBlock->Image != NULL)
	{
		freeTexture(stageBlock->Image);
	}
	free(stageBlock);
}


#endif