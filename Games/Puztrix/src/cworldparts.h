#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include "defines.h"
#include "texture.h"
#include "sdl_helpertypes.h"

embedded int[((NrOfRows*NrOfCols)+1)*MaxLevels] LevelPackData = "assets\\levels\\levels.dat";
int LevelCount = 80;

struct CWorldPart;
struct CWorldParts
{
 	Texture *TilesImage;
 	int LevelNumber;
 	CWorldPart*[NrOfRows*NrOfCols] Items;
 	int ItemCount;
 	int LevelMoves;
};

struct CWorldPart
{
    int MoveDelayCounter;
    bool FirstArriveEventFired;
 	int Type,MoveSpeedX,MoveSpeedY,MoveDelay,Xi,Yi,X,Y,PreviousPlayFieldX,PreviousPlayFieldY,AnimPhase,PlayFieldX,PlayFieldY,Z,Group;
 	bool BHistory;
 	Texture *Image;
	int loops;
    int AnimDelay;
    CWorldParts *ParentList;
 	bool IsMoving;
 	bool Selected;
 	bool Death,Remove;
};

CWorldPart* CWorldParts_GetItemFromPosPlayField(CWorldParts* WorldParts, int PlayFieldXin,int PlayFieldYin)
{
    int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
	    if((WorldParts->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldParts->Items[Teller]->PlayFieldY == PlayFieldYin) )
            return WorldParts->Items[Teller];
	}
	return NULL;
}

void CWorldPart_SetPosition(CWorldPart* WorldPart, int PlayFieldXin,int PlayFieldYin)
{
    if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
    {
        WorldPart->PlayFieldX=PlayFieldXin;
        WorldPart->PlayFieldY=PlayFieldYin;
        WorldPart->PreviousPlayFieldX = PlayFieldXin;
        WorldPart->PreviousPlayFieldY = PlayFieldYin;
        WorldPart->X=Xoffset+(PlayFieldXin*TileWidth);
        WorldPart->Y=Yoffset+(PlayFieldYin*TileHeight);
    }
}

bool CWorldPart_CanMoveTo(CWorldPart* WorldPart, int PlayFieldXin,int PlayFieldYin)
{
    CWorldPart *Box;
    int DiffX,DiffY;



    if ((PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols) || (PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows))
        return false;

    if (WorldPart->Type == 5)
        return false;

    DiffX = WorldPart->PlayFieldX - PlayFieldXin;
    DiffY = WorldPart->PlayFieldY - PlayFieldYin;



    Box = CWorldParts_GetItemFromPosPlayField(WorldPart->ParentList,PlayFieldXin,PlayFieldYin);
    if(Box == NULL)
        return true;
    else
        return CWorldPart_CanMoveTo(Box, Box->PlayFieldX-DiffX,Box->PlayFieldY-DiffY);
}

void CWorldPart_MoveTo(CWorldPart* WorldPart, int PlayFieldXin,int PlayFieldYin,bool BackWards)
{

        if((PlayFieldXin != WorldPart->PlayFieldX) || (PlayFieldYin != WorldPart->PlayFieldY))
            if(CWorldPart_CanMoveTo(WorldPart, PlayFieldXin,PlayFieldYin) || BackWards)
            {
                WorldPart->PreviousPlayFieldX = WorldPart->PlayFieldX;
                WorldPart->PreviousPlayFieldY = WorldPart->PlayFieldY;
                WorldPart->PlayFieldX = PlayFieldXin;
                WorldPart->PlayFieldY = PlayFieldYin;
                if(WorldPart->X < Xoffset+(WorldPart->PlayFieldX*TileWidth))
                    WorldPart->Xi = WorldPart->MoveSpeedX;
                if(WorldPart->X > Xoffset+(WorldPart->PlayFieldX*TileWidth))
                    WorldPart->Xi = -WorldPart->MoveSpeedX;
                if(WorldPart->Y > Yoffset+(WorldPart->PlayFieldY*TileHeight))
                    WorldPart->Yi = -WorldPart->MoveSpeedY;
                if(WorldPart->Y < Yoffset+(WorldPart->PlayFieldY*TileHeight))
                    WorldPart->Yi = WorldPart->MoveSpeedY;
                WorldPart->IsMoving = true;
            }

}

void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* WorldPart)
{
	CWorldPart_MoveTo(WorldPart, WorldPart->PlayFieldX +(WorldPart->PlayFieldX-WorldPart->PreviousPlayFieldX),WorldPart->PlayFieldY+ (WorldPart->PlayFieldY-WorldPart->PreviousPlayFieldY),false);
}

void CWorldPart_Move(CWorldPart* WorldPart)
{
    if (WorldPart->IsMoving)
    {
        if (WorldPart->MoveDelayCounter == WorldPart->MoveDelay)
        {
            WorldPart->X += WorldPart->Xi;
            WorldPart->Y += WorldPart->Yi;
            if ((WorldPart->X == Xoffset+(WorldPart->PlayFieldX * TileWidth)) && (WorldPart->Y == Yoffset+(WorldPart->PlayFieldY * TileHeight)))
            {
                WorldPart->IsMoving = false;
                WorldPart->Xi = 0;
                WorldPart->Yi = 0;
                CWorldPart_Event_ArrivedOnNewSpot(WorldPart);
            }
            WorldPart->MoveDelayCounter = -1;
        }
        WorldPart->MoveDelayCounter++;
    }
}

void CWorldPart_MoveDown(CWorldPart* WorldPart)
{
    if(CWorldPart_CanMoveTo(WorldPart, WorldPart->PlayFieldX,WorldPart->PlayFieldY+1))
        CWorldPart_MoveTo(WorldPart, WorldPart->PlayFieldX,WorldPart->PlayFieldY+1,false);
}

void CWorldPart_MoveUp(CWorldPart* WorldPart)
{
    if(CWorldPart_CanMoveTo(WorldPart,WorldPart->PlayFieldX,WorldPart->PlayFieldY-1))
        CWorldPart_MoveTo(WorldPart,WorldPart->PlayFieldX,WorldPart->PlayFieldY-1,false);
}


void CWorldPart_MoveLeft(CWorldPart* WorldPart)
{
    if(CWorldPart_CanMoveTo(WorldPart,WorldPart->PlayFieldX-1,WorldPart->PlayFieldY))
        CWorldPart_MoveTo(WorldPart,WorldPart->PlayFieldX-1,WorldPart->PlayFieldY,false);
}


void CWorldPart_MoveRight(CWorldPart* WorldPart)
{
    if(CWorldPart_CanMoveTo(WorldPart, WorldPart->PlayFieldX+1,WorldPart->PlayFieldY))
        CWorldPart_MoveTo(WorldPart, WorldPart->PlayFieldX+1,WorldPart->PlayFieldY,false);
}

void CWorldPart_Draw(CWorldPart* WorldPart)
{
    if(WorldPart->Death)
    {
        WorldPart->AnimDelay++;
        if(WorldPart->AnimDelay == 4)
        {
            WorldPart->AnimDelay = 0;
            WorldPart->AnimPhase++;
            if (WorldPart->AnimPhase == 2)
            {
                WorldPart->AnimPhase =0;
                WorldPart->loops++;
                if(WorldPart->loops == 5)
                {
                    WorldPart->AnimPhase = 1;
                    WorldPart->Remove = true;
                }
            }
        }
    }
    if (WorldPart->Image )
    {
		drawTextureZoomed(WorldPart->Image, ((WorldPart->Type-1)*2) + WorldPart->AnimPhase, WorldPart->X,  WorldPart->Y);
    }
}

void CWorldPart_Destroy(CWorldPart* WorldPart)
{
	free(WorldPart);
	WorldPart = NULL;
}

void CWorldPart_SetMovesSpeed(CWorldPart* WorldPart, int aMoveSpeedX ,int aMoveSpeedY)
{
    WorldPart->MoveSpeedX = aMoveSpeedX;
    WorldPart->MoveSpeedY = aMoveSpeedY;
}

CWorldPart* CWorldPart_Create(int PlayFieldXin,int PlayFieldYin,Texture *IMG,int ID)
{
	CWorldPart* Result = (CWorldPart*) malloc(sizeof(CWorldPart));
    Result->PlayFieldX=PlayFieldXin;
    Result->PlayFieldY=PlayFieldYin;
    Result->Xi=0;
    Result->Yi=0;
    Result->X=Xoffset+(PlayFieldXin*TileWidth);
    Result->Y=Yoffset+(PlayFieldYin*TileHeight);
    Result->MoveDelayCounter=0;
    Result->IsMoving = false;
    Result->ParentList = NULL;
    Result->Selected = false;
    Result->FirstArriveEventFired = false;
    Result->Z=0;
    Result->Group=0;
	Result->Image = IMG;
    Result->Type = ID;
    Result->MoveSpeedY = 4 * yscale;
    Result->MoveSpeedX = 4 * xscale;
    Result->MoveDelay = 0;
    Result->AnimDelay = 0;
    Result->AnimPhase = 0;
    Result->loops = 0;
    Result->Death = false;
    Result->Remove = false;
	return Result;
}



CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = (CWorldParts*) malloc(sizeof(CWorldParts));
    Result->ItemCount = 0;
    Result->LevelNumber = 0;
    Result->LevelMoves = 1;
	Result->TilesImage = NULL;
	return Result;
}


bool CWorldParts_CanMoveToRight(CWorldParts* WorldParts)
{
    int Teller;
    for(Teller=0;Teller<WorldParts->ItemCount;Teller++)
        if(WorldParts->Items[Teller]->Type != 5)
        if(CWorldPart_CanMoveTo(WorldParts->Items[Teller], WorldParts->Items[Teller]->PlayFieldX+1,WorldParts->Items[Teller]->PlayFieldY))
            return true;

    return false;
}

bool CWorldParts_CanMoveToUp(CWorldParts* WorldParts)
{
    int Teller;
    for(Teller=0;Teller<WorldParts->ItemCount;Teller++)
        if(CWorldPart_CanMoveTo(WorldParts->Items[Teller],WorldParts->Items[Teller]->PlayFieldX,WorldParts->Items[Teller]->PlayFieldY-1))
            return true;
    return false;
}

bool CWorldParts_CanMoveToDown(CWorldParts* WorldParts)
{
    int Teller;
    for(Teller=0;Teller<WorldParts->ItemCount;Teller++)
        if(CWorldPart_CanMoveTo(WorldParts->Items[Teller],WorldParts->Items[Teller]->PlayFieldX,WorldParts->Items[Teller]->PlayFieldY+1))
            return true;
    return false;
}

bool CWorldParts_CanMoveToLeft(CWorldParts* WorldParts)
{
    int Teller;
    for(Teller=0;Teller<WorldParts->ItemCount;Teller++)
        if(CWorldPart_CanMoveTo(WorldParts->Items[Teller],WorldParts->Items[Teller]->PlayFieldX-1,WorldParts->Items[Teller]->PlayFieldY))
            return true;
    return false;
}


void CWorldParts_AssignImage(CWorldParts* WorldParts, Texture *Image)
{
    int Teller;
    WorldParts->TilesImage = Image;
    for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
        WorldParts->Items[Teller]->Image = Image;
}

void CWorldParts_RemoveAll(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		CWorldPart_Destroy(WorldParts->Items[Teller]);
		WorldParts->Items[Teller] = NULL;
	}
	WorldParts->ItemCount=0;
}
void CWorldParts_Remove(CWorldParts* WorldParts, int PlayFieldXin,int PlayFieldYin)
{
	int Teller1,Teller2;
	for (Teller1=0;Teller1<WorldParts->ItemCount;Teller1++)
	{
		if ((WorldParts->Items[Teller1]->PlayFieldX == PlayFieldXin) && (WorldParts->Items[Teller1]->PlayFieldY == PlayFieldYin))
		{
			CWorldPart_Destroy(WorldParts->Items[Teller1]);
			for (Teller2=Teller1;Teller2<WorldParts->ItemCount-1;Teller2++)
				WorldParts->Items[Teller2] = WorldParts->Items[Teller2+1];
			WorldParts->ItemCount--;
			Teller1--;
		}
	}
}


void CWorldParts_Add(CWorldParts* WorldParts, CWorldPart *WorldPart)
{
	if( WorldParts->ItemCount < NrOfRows*NrOfCols )
	{
		WorldPart->ParentList = WorldParts;
		WorldParts->Items[WorldParts->ItemCount] = WorldPart;
		WorldParts->ItemCount++;
	}
}

bool CWorldParts_LoadLevel(CWorldParts* WorldParts)
{
    int x,y,type;
    if ((WorldParts->LevelNumber <= LevelCount) && (WorldParts->LevelNumber > 0))
    {
        CWorldParts_RemoveAll(WorldParts);
        WorldParts->LevelMoves = LevelPackData[((WorldParts->LevelNumber-1)*((NrOfCols*NrOfRows)+1))];
        for(y=0;y<NrOfRows;y++)
            for(x=0;x<NrOfCols;x++)
            {
                type = LevelPackData[((WorldParts->LevelNumber-1)*((NrOfCols*NrOfRows)+1))+(y*NrOfCols)+x+1];
                if(type !=0)
                    CWorldParts_Add(WorldParts, CWorldPart_Create(x,y,WorldParts->TilesImage,type));
            }
        return true;
    }
    return false;
}

bool CWorldParts_IsMoving(CWorldParts* WorldParts)
{
    int Teller;
    for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
        if(WorldParts->Items[Teller]->IsMoving)
            return true;
    return false;
}

void CWorldParts_SetLevel(CWorldParts* WorldParts, int aLevelNumber)
{
    if ((aLevelNumber > 0) && (aLevelNumber <= LevelCount))
    {
        WorldParts->LevelNumber = aLevelNumber;
        CWorldParts_LoadLevel(WorldParts);
    }
    else
    {
        CWorldParts_RemoveAll(WorldParts);
        WorldParts->LevelNumber = 0;
        WorldParts->LevelMoves = 0;
    }
}

void CWorldParts_IncLevel(CWorldParts* WorldParts)
{
    if(WorldParts->LevelNumber < LevelCount)
    {
        WorldParts->LevelNumber++;
        CWorldParts_LoadLevel(WorldParts);
    }
}

void CWorldParts_DecLevel(CWorldParts* WorldParts)
{
    if(WorldParts->LevelNumber > 1)
    {
        WorldParts->LevelNumber--;
        CWorldParts_LoadLevel(WorldParts);
    }
}


void CWorldParts_Move(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_Move(WorldParts->Items[Teller]);
}

void CWorldParts_MoveDown(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_MoveDown(WorldParts->Items[Teller]);
}

void CWorldParts_MoveLeft(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_MoveLeft(WorldParts->Items[Teller]);
}

void CWorldParts_MoveRight(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_MoveRight(WorldParts->Items[Teller]);
}

void CWorldParts_MoveUp(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_MoveUp(WorldParts->Items[Teller]);
}

void CWorldParts_Draw(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
	    if((WorldParts->Items[Teller]->PlayFieldX >= 0) && (WorldParts->Items[Teller]->PlayFieldX <= NrOfCols) &&
           (WorldParts->Items[Teller]->PlayFieldY >= 0) && (WorldParts->Items[Teller]->PlayFieldY <= NrOfRows))
           {
                CWorldPart_Draw(WorldParts->Items[Teller]);
           }
	}
}


void CWorldParts_Destroy(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		CWorldPart_Destroy(WorldParts->Items[Teller]);
		WorldParts->Items[Teller] = NULL;
	}
	free(WorldParts);
	WorldParts = NULL;
}


#endif
