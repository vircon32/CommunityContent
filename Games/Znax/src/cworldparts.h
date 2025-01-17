#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include "texture.h"
#include "caudio.h"
#include "common.h"
#include "defines.h"
#include "utilfuncs.h"

struct CBlock
{
    int Color,AnimCounter,AnimBase,AnimDelay,AnimDelayCounter,AnimPhases,AnimPhase,PlayFieldX,PlayFieldY;
    bool bNeedToKill,bSelected;
};

struct CWorldParts
{
    CBlock*[NrOfCols][NrOfRows]Items;
    SPoint[4] Selects;
    int NumSelected,SelectedColor;
    int Time;
    bool NeedToKillBlocks,NeedToAddBlocks;
};

CWorldParts *World;

CBlock* CBlock_Create(int PlayFieldXin,int PlayFieldYin,int ColorIn)
{
    CBlock* Result = (CBlock *) malloc(sizeof(CBlock));
    Result->AnimBase = 0;
    Result->AnimPhase = 0;
    Result->AnimCounter = 0;
    Result->AnimDelayCounter = 0;
    Result->AnimPhases = 1;
    Result->AnimDelay = 2;
    Result->PlayFieldX = PlayFieldXin;
    Result->PlayFieldY = PlayFieldYin;
    Result->Color = ColorIn;
    Result->bNeedToKill = false;
    Result->bSelected = false;
    return Result;
}

void CBlock_Select(CBlock* Block)
{
    Block->AnimPhase = 0;
    Block->AnimBase = 0;
    Block->AnimCounter = 0;
    Block->AnimPhases = 6;
    Block->bSelected = true;
}

void CBlock_DeSelect(CBlock* Block)
{
    Block->AnimPhase = 0;
    Block->AnimBase = 0;
    Block->AnimCounter = 0;
    Block->AnimPhases = 1;
    Block->bSelected=false;
}

void CBlock_Kill(CBlock* Block)
{
    Block->AnimPhase = 6;
    Block->AnimBase = 6;
    Block->AnimCounter = 0;
    Block->AnimPhases = 1;
    Block->bNeedToKill = true;
}

void CBlock_Draw(CBlock* Block)
{
    switch(Block->Color)
    {
        case 0:
            drawTexture(IMGBlocks1, Block->AnimPhase, Block->PlayFieldX * TileWidth+5, Block->PlayFieldY * TileHeight+5);
            break;
        case 1:
            drawTexture(IMGBlocks2, Block->AnimPhase, Block->PlayFieldX * TileWidth+5, Block->PlayFieldY * TileHeight+5);
            break;
        case 2:
            drawTexture(IMGBlocks3, Block->AnimPhase, Block->PlayFieldX * TileWidth+5, Block->PlayFieldY * TileHeight+5);
            break;
        case 3:
            drawTexture(IMGBlocks4, Block->AnimPhase, Block->PlayFieldX * TileWidth+5, Block->PlayFieldY * TileHeight+5);
            break;
        case 4:
            drawTexture(IMGBlocks5, Block->AnimPhase, Block->PlayFieldX * TileWidth+5, Block->PlayFieldY * TileHeight+5);
            break;
        default:
            break;
    }

    Block->AnimPhase = Block->AnimBase + Block->AnimCounter;
    if(Block->AnimPhase != Block->AnimBase + Block->AnimPhases - 1)
    {
        Block->AnimDelayCounter++;
        if (Block->AnimDelayCounter >= Block->AnimDelay)
        {
            Block->AnimDelayCounter = 0;
            Block->AnimCounter++;
            if (Block->AnimCounter == Block->AnimPhases)
                Block->AnimCounter = 0;
        }
    }
}

void CBlock_Destroy(CBlock* Block)
{
    free(Block);
    Block = NULL;
}

CWorldParts* CWorldParts_Create()
{
    CWorldParts* Result = (CWorldParts*) malloc(sizeof(CWorldParts));
    int X,Y;
    Result->NeedToKillBlocks = false;
    Result->NeedToAddBlocks = false;
    Result->NumSelected = 0;
    Result->SelectedColor = -1;
    Result->Time = 0;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            Result->Items[X][Y] = NULL;
    return Result;
}

void CWorldParts_KillBlocks(CWorldParts* WorldParts)
{
    int X,Y,Teller=0,StartX=NrOfCols,StartY=NrOfRows,EndX=-1,EndY=-1;
    for(Teller=0;Teller<WorldParts->NumSelected;Teller++)
    {
        if(WorldParts->Selects[Teller].X > EndX)
            EndX = WorldParts->Selects[Teller].X;
        if(WorldParts->Selects[Teller].X < StartX)
            StartX = WorldParts->Selects[Teller].X;
        if(WorldParts->Selects[Teller].Y > EndY)
            EndY = WorldParts->Selects[Teller].Y;
        if(WorldParts->Selects[Teller].Y < StartY)
            StartY = WorldParts->Selects[Teller].Y;
    }
    for(Y = StartY;Y<=EndY;Y++)
        for(X=StartX;X<=EndX;X++)
            CBlock_Kill(WorldParts->Items[X][Y]);
}

int CWorldParts_MovesLeft(CWorldParts* WorldParts)
{
    int count = 0;
            
    // Iterate over all possible pairs of top-left and bottom-right corners
    for (int x1 = 0; x1 < NrOfRows; x1++)
    {
      for (int y1 = 0; y1 < NrOfCols; y1++)
      {
        for (int x2 = x1 + 1; x2 < NrOfCols; x2++)
        {
          for (int y2 = y1 + 1; y2 < NrOfCols; y2++)
          {
            // Check if the corners are the same
            if ((WorldParts->Items[x1][y1]->Color == WorldParts->Items[x1][y2]->Color) &&
                (WorldParts->Items[x1][y1]->Color == WorldParts->Items[x2][y1]->Color) &&
                (WorldParts->Items[x1][y1]->Color == WorldParts->Items[x2][y2]->Color) &&
                //no lines
                (x2 - x1 > 0) && (y2 - y1 > 0)) 
            {
                count++;
            }
          }
        }
      }
    }

    return count;
}

void CWorldParts_AddBlocks(CWorldParts* WorldParts)
{
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            if(WorldParts->Items[X][Y]->bNeedToKill)
            {
                CBlock_Destroy(WorldParts->Items[X][Y]);
                WorldParts->Items[X][Y] = CBlock_Create(X,Y,rand()%NrOfBlockColors);
            }
     movesLeft = CWorldParts_MovesLeft(WorldParts);
}

void CWorldParts_NewGame(CWorldParts* WorldParts)
{
    int X,Y;
    //make sure inital state got at least 10 rectangles to find
    movesLeft = 0;
    while(movesLeft < 10) 
    {
      for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
        {
            if (WorldParts->Items[X][Y])
                CBlock_Destroy(WorldParts->Items[X][Y]);
            WorldParts->Items[X][Y] = CBlock_Create(X,Y,rand()%NrOfBlockColors);
        }
        movesLeft = CWorldParts_MovesLeft(WorldParts);
    }
    WorldParts->NeedToKillBlocks = false;
    WorldParts->NeedToAddBlocks = false;
    WorldParts->NumSelected = 0;
    WorldParts->SelectedColor = -1;
}

void CWorldParts_Destroy(CWorldParts* WorldParts)
{
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            if(WorldParts->Items[X][Y])
                CBlock_Destroy(WorldParts->Items[X][Y]);
}

void CWorldParts_Draw(CWorldParts* WorldParts)
{
    if(WorldParts->NeedToKillBlocks && (WorldParts->Time < getCurrentTimeMilliseconds()))
    {
        CWorldParts_KillBlocks(WorldParts);
        WorldParts->NeedToKillBlocks = false;
        WorldParts->NeedToAddBlocks = true;
        WorldParts->Time = getCurrentTimeMilliseconds() + 350;
        CAudio_PlaySound(Sounds[SND_DELETE],0);
    }

    if (WorldParts->NeedToAddBlocks && (WorldParts->Time < getCurrentTimeMilliseconds()))
    {
        CWorldParts_AddBlocks(WorldParts);
        WorldParts->NeedToAddBlocks = false;
        WorldParts->NumSelected = 0;
    }

    drawTexture(IMGBackground,0,0,0);
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            CBlock_Draw(WorldParts->Items[X][Y]);
}

void CWorldParts_DeSelect(CWorldParts* WorldParts, bool PlaySound)
{
    if(PlaySound)
        CAudio_PlaySound(Sounds[SND_ERROR],0);
    int Teller = 0;
    for(Teller = 0;Teller<WorldParts->NumSelected;Teller++)
        CBlock_DeSelect(WorldParts->Items[WorldParts->Selects[Teller].X][WorldParts->Selects[Teller].Y]);
    WorldParts->NumSelected = 0;
    WorldParts->SelectedColor = -1;
}

int CWorldParts_Select(CWorldParts* WorldParts, int PlayFieldX,int PlayFieldY)
{

    int Score = 0,NumEqualY=0,NumEqualX = 0,Teller1=0,Teller2=0,StartX=NrOfCols,StartY=NrOfRows,EndX=-1,EndY=-1;;
    if(!WorldParts->NeedToKillBlocks && !WorldParts->NeedToAddBlocks)
    {
        if(!WorldParts->Items[PlayFieldX][PlayFieldY]->bSelected)
        {

            if (WorldParts->NumSelected == 0)
            {
                CBlock_Select(WorldParts->Items[PlayFieldX][PlayFieldY]);
                WorldParts->SelectedColor = WorldParts->Items[PlayFieldX][PlayFieldY]->Color;
                WorldParts->Selects[WorldParts->NumSelected].X = PlayFieldX;
                WorldParts->Selects[WorldParts->NumSelected].Y = PlayFieldY;
                WorldParts->NumSelected++;
                CAudio_PlaySound(Sounds[SND_BLOCKSELECT],0);

            }
            else
            {
                if(WorldParts->Items[PlayFieldX][PlayFieldY]->Color == WorldParts->SelectedColor)
                {
                    CBlock_Select(WorldParts->Items[PlayFieldX][PlayFieldY]);
                    WorldParts->Selects[WorldParts->NumSelected].X = PlayFieldX;
                    WorldParts->Selects[WorldParts->NumSelected].Y = PlayFieldY;
                    WorldParts->NumSelected++;
                    if(WorldParts->NumSelected > 2)
                    {
                        for(Teller1=0;Teller1 < WorldParts->NumSelected;Teller1++)
                        {
                            for(Teller2=0;Teller2<WorldParts->NumSelected;Teller2++)
                            if(Teller1 != Teller2)
                            {
                                if(WorldParts->Selects[Teller1].X == WorldParts->Selects[Teller2].X)
                                    NumEqualX++;
                                if(WorldParts->Selects[Teller1].Y == WorldParts->Selects[Teller2].Y)
                                    NumEqualY++;
                            }
                        }
                        if((NumEqualX > 4) || (NumEqualY > 4))
                            CWorldParts_DeSelect(WorldParts, true);
                    }


                    if(WorldParts->NumSelected == 3)
                        if (!(((NumEqualX == 2) && (NumEqualY == 2)) ))
                            CWorldParts_DeSelect(WorldParts, true);

                    if(WorldParts->NumSelected == 4)
                    {
                        if((NumEqualX == 4) && (NumEqualY == 4))
                        {
                            for(Teller1=0;Teller1<WorldParts->NumSelected;Teller1++)
                            {
                                if(WorldParts->Selects[Teller1].X > EndX)
                                    EndX = WorldParts->Selects[Teller1].X;
                                if(WorldParts->Selects[Teller1].X < StartX)
                                    StartX = WorldParts->Selects[Teller1].X;
                                if(WorldParts->Selects[Teller1].Y > EndY)
                                    EndY = WorldParts->Selects[Teller1].Y;
                                if(WorldParts->Selects[Teller1].Y < StartY)
                                    StartY = WorldParts->Selects[Teller1].Y;
                            }
                            Score = (EndY-StartY+1) * (EndX-StartX +1) * 100;
                            WorldParts->NeedToKillBlocks = true;
                            WorldParts->Time = getCurrentTimeMilliseconds() + 350;
                        }
                        else
                            CWorldParts_DeSelect(WorldParts, true);
                    }

                    if(((WorldParts->NumSelected <= 4) && (WorldParts->NumSelected > 0)) )
                        CAudio_PlaySound(Sounds[SND_BLOCKSELECT],0);
                }
                else
                    CWorldParts_DeSelect(WorldParts, true);
            }

        }
        else
            CWorldParts_DeSelect(WorldParts, true);
    }
    return Score;
}

#endif