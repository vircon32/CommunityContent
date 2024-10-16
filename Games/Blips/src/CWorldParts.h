#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H


#include "Texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "defines.h"
#include "Common.h"
#include "CViewPort.h"
#include "Levels.h"
#include "CAudio.h"

struct CWorldParts;

struct CWorldPart
{
	int MoveDelayCounter;
	bool FirstArriveEventFired,PNeedToKill;
	int Type,MoveSpeed,MoveDelay,Xi,Yi,X,Y,AnimPhase,PlayFieldX,PlayFieldY,Z,Group;
	bool BHide;
	int AnimBase,AnimCounter,AnimDelay,AnimDelayCounter,AnimPhases;
	Texture * Image;

	CWorldParts *ParentList;
	bool IsMoving;
	bool Selected;
	bool IsDeath;
};



struct CWorldParts 
{
	CViewPort *ViewPort;
	CWorldPart*[NrOfRows*NrOfCols*2] Items;
	int ItemCount;	
	bool DisableSorting;	
};

CWorldParts *WorldParts;

void CWorldParts_Sort(CWorldParts* WorldParts)
{
	int Teller1,Teller2,Index;
	CWorldPart *Part;
	if (!WorldParts->DisableSorting)
	{
		for (Teller1 = 1; Teller1 <WorldParts->ItemCount;Teller1++)
		{
			Index = WorldParts->Items[Teller1]->Z;
			Part = WorldParts->Items[Teller1];
			Teller2 = Teller1;
			while ((Teller2 > 0) && (WorldParts->Items[Teller2-1]->Z > Index))
			{
				WorldParts->Items[Teller2] = WorldParts->Items[Teller2 - 1];
				Teller2--;
			}
			WorldParts->Items[Teller2] = Part;
		}
	}

}

void CWorldParts_Add(CWorldParts* WorldParts, CWorldPart *WorldPart)
{
	if( WorldParts->ItemCount < NrOfRows*NrOfCols*2 )
	{
		WorldPart->ParentList = WorldParts;
		WorldParts->Items[WorldParts->ItemCount] = WorldPart;
		WorldParts->ItemCount++;
		CWorldParts_Sort(WorldParts);
	}
}

CWorldPart* CWorldPart_Create( int PlayFieldXin, int PlayFieldYin,  int TypeId)
{
	CWorldPart* Result = (CWorldPart* ) malloc(sizeof(CWorldPart));
	Result->PlayFieldX=PlayFieldXin;
	Result->PlayFieldY=PlayFieldYin;
	Result->Xi=0;
	Result->Yi=0;
	Result->X=PlayFieldXin*TileWidth;
	Result->Y=PlayFieldYin*TileHeight;
	Result->Type=TypeId;
	Result->MoveDelay=0;
	Result->MoveDelayCounter=0;
	Result->IsMoving = false;
	Result->MoveSpeed=0;
	Result->Image = NULL;
	Result->ParentList = NULL;
	Result->AnimPhase=0;
	Result->Selected = false;
	Result->FirstArriveEventFired = false;
	Result->Z=0;
	Result->Group=0;
	Result->PNeedToKill = false;
	Result->BHide = false;
	Result->AnimBase = 0;
	Result->IsDeath=false;
	switch(TypeId)
	{
		case IDPlayer:
			Result->Image=IMGPlayer;
			Result->AnimBase=4;
			Result->AnimPhase=4;
			Result->AnimPhases=4;
			Result->AnimCounter = 0;
			Result->AnimDelay = 12;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimDelayCounter =0;
			Result->Z = ZPlayer;			
			break;
		case IDBox:
			Result->Image = IMGBox;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->Z = ZBox;
			break;
		case IDDiamond:
			Result->Image = IMGDiamond;
			Result->Z = ZDiamond;
			break;
		case IDBomb:
			Result->Image = IMGBomb;
			Result->Z = ZBomb;
			break;
		case IDFloor:
			Result->Image = IMGFloor;
			Result->Z = ZFloor;
			break;
		case IDWall:
			Result->Image = IMGWall;
			Result->Z = ZWall;
			break;
		case IDEmpty:
			Result->Image = IMGEmpty;
			break;
		case IDExplosion:
      		CAudio_PlaySound(Sounds[SND_EXPLODE],0);
			

			Result->Image = IMGExplosion;
			Result->Z = ZExplosion;
			Result->AnimPhase=0;
			Result->AnimPhases=8;
			Result->AnimCounter = 1;
			Result->AnimDelay = 2;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 4;
			Result->AnimDelayCounter =0;
			break;
	}
	return(Result);
}

void CWorldPart_Hide(CWorldPart* WorldPart) 
{
	WorldPart->BHide = true;
}

void CWorldPart_Kill(CWorldPart* WorldPart)
{
	WorldPart->PNeedToKill = true;
}

bool CWorldPart_NeedToKill(CWorldPart* WorldPart) 
{
	return WorldPart->PNeedToKill;
}

int CWorldPart_GetGroup(CWorldPart* WorldPart) 
{
	return WorldPart->Group;
}

int CWorldPart_GetType(CWorldPart* WorldPart) 
{
	return WorldPart->Type;
}

int CWorldPart_GetX(CWorldPart* WorldPart) 
{
	return WorldPart->X;
}

int CWorldPart_GetY(CWorldPart* WorldPart) 
{
	return WorldPart->Y;
}

int CWorldPart_GetPlayFieldX(CWorldPart* WorldPart) 
{
	return WorldPart->PlayFieldX;
}

int CWorldPart_GetPlayFieldY(CWorldPart* WorldPart) 
{
	return WorldPart->PlayFieldY;
}

int CWorldPart_GetZ(CWorldPart* WorldPart) 
{
	return WorldPart->Z;
}

int CWorldPart_GetAnimPhase(CWorldPart* WorldPart) 
{
	return WorldPart->AnimPhase;
}

void CWorldPart_SetAnimPhase(CWorldPart* WorldPart, int AnimPhaseIn) 
{ 
	WorldPart->AnimPhase = AnimPhaseIn;
}

void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* WorldPart)
{
	int Teller=0;
    if(WorldPart->Type == IDPlayer)
	{
		if (WorldPart->ParentList)
		{
			for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
			{
				if((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY))
				{
					if((WorldPart->ParentList->Items[Teller]->Type == IDBomb))
					{
						CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX,WorldPart->PlayFieldY, IDExplosion));
						CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
						WorldPart->IsDeath = true;
						CWorldPart_Hide(WorldPart);
						break;
					}

					if((WorldPart->ParentList->Items[Teller]->Type == IDDiamond))
					{
						CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
						CAudio_PlaySound(Sounds[SND_COLLECT],0);
					}

				}
			}
		}
	}

	if (WorldPart->Type == IDBox)
	{
		WorldPart->AnimPhase = 0;
		if (WorldPart->ParentList)
		{
			for (Teller=0;Teller< WorldPart->ParentList->ItemCount;Teller++)
			{
			if((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY) &&
				(WorldPart->ParentList->Items[Teller]->Type == IDBomb))
				{
					CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX,WorldPart->PlayFieldY,IDExplosion));
					CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
					CWorldPart_Kill(WorldPart);
					break;
				}
			}
		}
	}	
}

void CWorldPart_Event_BeforeDraw(CWorldPart* WorldPart) 
{
	switch(WorldPart->Type)
	{
		case IDPlayer:
		{
			if (WorldPart->IsMoving)
			{
				WorldPart->AnimPhase = WorldPart->AnimBase + WorldPart->AnimCounter;
				WorldPart->AnimDelayCounter++;
				if (WorldPart->AnimDelayCounter == WorldPart->AnimDelay)
				{
					WorldPart->AnimDelayCounter = 0;
					WorldPart->AnimCounter++;
					if (WorldPart->AnimCounter == WorldPart->AnimPhases)
						WorldPart->AnimCounter = 0;
				}
			}
			break;
		}

		case IDExplosion:
		{
			WorldPart->AnimDelayCounter++;
			if (WorldPart->AnimDelayCounter == WorldPart->AnimDelay)
			{
				WorldPart->AnimDelayCounter = 0;
				WorldPart->AnimPhase++;
				if (WorldPart->AnimPhase == WorldPart->AnimPhases)
					CWorldPart_Kill(WorldPart);
			}
			break;
		}
		default:
			break;
	}
}

void CWorldPart_Event_Moving(CWorldPart* WorldPart, int ScreenPosX,int ScreenPosY) 
{
	if(WorldPart->Type == IDPlayer)
	{
		if((ScreenPosX > (WorldPart->ParentList->ViewPort->MaxScreenX) - ORIG_WINDOW_WIDTH/2) && (WorldPart->Xi > 0))
			CViewPort_Move(WorldPart->ParentList->ViewPort, WorldPart->Xi,WorldPart->Yi);
		if((ScreenPosX < (WorldPart->ParentList->ViewPort->MaxScreenX) - ORIG_WINDOW_WIDTH/2) && (WorldPart->Xi < 0))
			CViewPort_Move(WorldPart->ParentList->ViewPort, WorldPart->Xi,WorldPart->Yi);
		if((ScreenPosY > (WorldPart->ParentList->ViewPort->MaxScreenY) - ORIG_WINDOW_HEIGHT/2) && (WorldPart->Yi > 0))
			CViewPort_Move(WorldPart->ParentList->ViewPort, WorldPart->Xi,WorldPart->Yi);
		if((ScreenPosY < (WorldPart->ParentList->ViewPort->MaxScreenY) - ORIG_WINDOW_HEIGHT/2) && (WorldPart->Yi < 0))
			CViewPort_Move(WorldPart->ParentList->ViewPort, WorldPart->Xi,WorldPart->Yi);
	}
}

void CWorldPart_SetPosition(CWorldPart* WorldPart,  int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		WorldPart->PlayFieldX=PlayFieldXin;
		WorldPart->PlayFieldY=PlayFieldYin;
		WorldPart->X=PlayFieldXin*TileWidth;
		WorldPart->Y=PlayFieldYin*TileHeight;
	}
}

bool CWorldPart_CanMoveTo(CWorldPart* WorldPart,  int PlayFieldXin, int PlayFieldYin) 
{
	int Teller;
	bool Result = true;
	switch(WorldPart->Type)
	{
		case IDPlayer:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
					{
						if((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
						{
							if((WorldPart->ParentList->Items[Teller]->Type == IDWall))
							{
								Result = false;
								break;
							}
							if((WorldPart->ParentList->Items[Teller]->Type == IDBox))
							{
								if (WorldPart->PlayFieldX > PlayFieldXin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin-1,PlayFieldYin);
								}
								if (WorldPart->PlayFieldX < PlayFieldXin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin+1,PlayFieldYin);
								}
								if (WorldPart->PlayFieldY > PlayFieldYin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin,PlayFieldYin-1);
								}
								if (WorldPart->PlayFieldY < PlayFieldYin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin,PlayFieldYin+1);
								}
								break;
							}
						}
					}
				}
				else
					Result = false;
			}
			break;
		}

		case IDBox:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
						if((WorldPart->ParentList->Items[Teller]->Type == IDWall) || (WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDDiamond))
							if((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								Result = false;
								break;
							}
				}
			}
			else
				Result = false;
			break;
		}
		default:
			Result = false;
			break;
	}
	return Result;
}


void CWorldPart_MoveTo(CWorldPart* WorldPart,  int PlayFieldXin, int PlayFieldYin,bool BackWards)
{
	int Teller;
 	if(WorldPart->Type == IDPlayer )
	{
		if(!WorldPart->IsMoving)
		{
			if(CWorldPart_CanMoveTo(WorldPart, PlayFieldXin,PlayFieldYin) || BackWards)
			{
				WorldPart->PlayFieldX = PlayFieldXin;
				WorldPart->PlayFieldY = PlayFieldYin;
				if(WorldPart->X < WorldPart->PlayFieldX*TileWidth)
				{
					WorldPart->Xi = WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
						{
							if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && 
								((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX+1,WorldPart->PlayFieldY,false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 4;

				}
				if(WorldPart->X > WorldPart->PlayFieldX*TileWidth)
				{
					WorldPart->Xi = -WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
						{
							if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && 
							   ((WorldPart->PlayFieldX == WorldPart->ParentList->Items[Teller]->PlayFieldX )  && 
							    (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX-1,WorldPart->PlayFieldY,false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 0;
				}
				if(WorldPart->Y > WorldPart->PlayFieldY*TileHeight)
				{
					WorldPart->Yi = -WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
						{
							if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && 
							   ((WorldPart->PlayFieldY == WorldPart->ParentList->Items[Teller]->PlayFieldY)  && 
							    (WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX,WorldPart->PlayFieldY-1,false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 8;
				}
				if(WorldPart->Y < WorldPart->PlayFieldY*TileHeight)
				{
					WorldPart->Yi = WorldPart->MoveSpeed;
					if(WorldPart->ParentList)
					{
						for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
						{
							if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && 
							   ((WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)  && 
							    (WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX )))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX,WorldPart->PlayFieldY+1,false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 12;
				}
				WorldPart->IsMoving = true;
			}
			else
			{
				if (PlayFieldXin > WorldPart->PlayFieldX)
				{
					WorldPart->AnimBase= 4;
				}
				if (PlayFieldXin < WorldPart->PlayFieldX)
				{
					WorldPart->AnimBase = 0;
				}
				if (PlayFieldYin > WorldPart->PlayFieldY)
				{
					WorldPart->AnimBase = 12;
				}
				if (PlayFieldYin < WorldPart->PlayFieldY)
				{
					WorldPart->AnimBase = 8;
				}
				WorldPart->AnimPhase = WorldPart->AnimBase + WorldPart->AnimCounter;
				WorldPart->AnimDelayCounter++;
				if (WorldPart->AnimDelayCounter == WorldPart->AnimDelay)
				{
					WorldPart->AnimDelayCounter = 0;
					WorldPart->AnimCounter++;
					if (WorldPart->AnimCounter == WorldPart->AnimPhases)
						WorldPart->AnimCounter = 0;
				}
			}

		}
	}
	else
	{
		if(!WorldPart->IsMoving)
		{
			if((PlayFieldXin != WorldPart->PlayFieldX) || (PlayFieldYin != WorldPart->PlayFieldY))
				if(CWorldPart_CanMoveTo(WorldPart, PlayFieldXin,PlayFieldYin) || BackWards)
				{
					WorldPart->PlayFieldX = PlayFieldXin;
					WorldPart->PlayFieldY = PlayFieldYin;
					if(WorldPart->X < WorldPart->PlayFieldX*TileWidth)
						WorldPart->Xi = WorldPart->MoveSpeed;
					if(WorldPart->X > WorldPart->PlayFieldX*TileWidth)
						WorldPart->Xi = -WorldPart->MoveSpeed;
					if(WorldPart->Y > WorldPart->PlayFieldY*TileHeight)
						WorldPart->Yi = -WorldPart->MoveSpeed;
					if(WorldPart->Y < WorldPart->PlayFieldY*TileHeight)
						WorldPart->Yi = WorldPart->MoveSpeed;
					WorldPart->IsMoving = true;
				}
		}
	}
}


void CWorldPart_Move(CWorldPart* WorldPart)
{
	if (!WorldPart->FirstArriveEventFired)
	{
		CWorldPart_Event_ArrivedOnNewSpot(WorldPart);
		WorldPart->FirstArriveEventFired=true;
	}
	if (WorldPart->IsMoving)
	{
		if (WorldPart->MoveDelayCounter == WorldPart->MoveDelay)
		{
			WorldPart->X += WorldPart->Xi;
			WorldPart->Y += WorldPart->Yi;
			CWorldPart_Event_Moving(WorldPart, WorldPart->X,WorldPart->Y);
			if ((WorldPart->X == WorldPart->PlayFieldX * TileWidth) && (WorldPart->Y == WorldPart->PlayFieldY * TileHeight))
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

void CWorldPart_Draw(CWorldPart* WorldPart)
{
	if(!WorldPart->BHide)
	{
		if (WorldPart->Image)
		{
			CWorldPart_Event_BeforeDraw(WorldPart);
			int DstX, DstY;
			if(WorldPart->ParentList)
			{
				DstX = WorldPart->X- WorldPart->ParentList->ViewPort->MinScreenX;
				DstY = WorldPart->Y- WorldPart->ParentList->ViewPort->MinScreenY;
			}
			else
			{
				DstX = WorldPart->X;
				DstY = WorldPart->Y;
			}
			drawTexture(WorldPart->Image, WorldPart->AnimPhase,DstX,DstY);
		}
	}
}


void CWorldPart_Destroy(CWorldPart* WorldPart)
{
	free(WorldPart);
	WorldPart = NULL;
}

CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = (CWorldParts*) malloc(sizeof(CWorldParts));

	Result->ItemCount = 0;
	Result->DisableSorting = true;
	Result->ViewPort = CViewPort_Create(0,0,19,11,0,0,NrOfCols-1,NrOfRows-1);
	return Result;
}

void CWorldParts_CenterVPOnPlayer(CWorldParts* WorldParts)
{
    int Teller=0,PlayerX=-1,PlayerY=-1;
    for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
        if(WorldParts->Items[Teller]->Type == IDPlayer)
        {

            PlayerX = WorldParts->Items[Teller]->PlayFieldX;
            PlayerY = WorldParts->Items[Teller]->PlayFieldY;
            break;
        }
    CViewPort_SetViewPort(WorldParts->ViewPort, PlayerX-10, PlayerY-6,PlayerX+10, PlayerY+6);
}

void CWorldParts_LimitVPLevel(CWorldParts* WorldParts)
{
    int MinX = NrOfCols, MinY = NrOfRows, MaxX = -1, MaxY = -1, Teller = 0;
	for (Teller = 0;Teller<WorldParts->ItemCount;Teller++)
	{
		if (WorldParts->Items[Teller]->PlayFieldX < MinX)
			MinX = WorldParts->Items[Teller]->PlayFieldX;
		if (WorldParts->Items[Teller]->PlayFieldY < MinY)
			MinY = WorldParts->Items[Teller]->PlayFieldY;
		if (WorldParts->Items[Teller]->PlayFieldX > MaxX)
			MaxX = WorldParts->Items[Teller]->PlayFieldX;
		if (WorldParts->Items[Teller]->PlayFieldY > MaxY)
            MaxY = WorldParts->Items[Teller]->PlayFieldY;
    }
    CViewPort_SetVPLimit(WorldParts->ViewPort, MinX,MinY,MaxX,MaxY);
    CWorldParts_CenterVPOnPlayer(WorldParts);
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

void CWorldParts_Remove_Type(CWorldParts* WorldParts, int PlayFieldXin,int PlayFieldYin,int Type)
{
	int Teller1,Teller2;
	for (Teller1=0;Teller1<WorldParts->ItemCount;Teller1++)
	{
		if ((WorldParts->Items[Teller1]->PlayFieldX == PlayFieldXin) && (WorldParts->Items[Teller1]->PlayFieldY == PlayFieldYin) && (WorldParts->Items[Teller1]->Type == Type))
		{
			CWorldPart_Destroy(WorldParts->Items[Teller1]);
			for (Teller2=Teller1;Teller2<WorldParts->ItemCount-1;Teller2++)
				WorldParts->Items[Teller2] = WorldParts->Items[Teller2+1];
			WorldParts->ItemCount--;
			Teller1--;
		}
	}
}


void CWorldParts_Load(CWorldParts* WorldParts, int Level)
{
	int X,Y,Type;
	CWorldParts_RemoveAll(WorldParts);
	//WorldParts->DisableSorting=true;
	for(int z = 0; z < 50*50*2; z+=3)
	{
		Type = Levels[0][Level][z];
		X = Levels[0][Level][z+1];
		Y = Levels[0][Level][z+2];
		//will always happen at the end of the real data in the level
		if ((Type == 0) && ((X == 0) && (Y ==0)))
			break;
		CWorldParts_Add(WorldParts, CWorldPart_Create(X,Y,Type));
		
	}
	//WorldParts->DisableSorting=false;
	CWorldParts_Sort(WorldParts);
	CWorldParts_LimitVPLevel(WorldParts);
	CWorldParts_CenterVPOnPlayer(WorldParts);
}

void CWorldParts_Move(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		CWorldPart_Move(WorldParts->Items[Teller]);
	}
}

void CWorldParts_Draw(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
	    if(WorldParts->Items[Teller]->PNeedToKill)
	     {
	         CWorldParts_Remove_Type(WorldParts, WorldParts->Items[Teller]->PlayFieldX,WorldParts->Items[Teller]->PlayFieldY,WorldParts->Items[Teller]->Type);
	         //go back one item to prevent skips & segaults
	         Teller--;
	     }
	     else
            if((WorldParts->Items[Teller]->PlayFieldX >= WorldParts->ViewPort->VPMinX) && (WorldParts->Items[Teller]->PlayFieldX-1 <= WorldParts->ViewPort->VPMaxX) &&
                (WorldParts->Items[Teller]->PlayFieldY >= WorldParts->ViewPort->VPMinY) && (WorldParts->Items[Teller]->PlayFieldY-1 <= WorldParts->ViewPort->VPMaxY))
                {
                    CWorldPart_Draw(WorldParts->Items[Teller]);
				}
	}
}

void CWorldParts_Destroy(CWorldParts* WorldParts)
{
    CViewPort_Destroy(WorldParts->ViewPort);
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		CWorldPart_Destroy(WorldParts->Items[Teller]);
		WorldParts->Items[Teller] = NULL;
	}
}



#endif