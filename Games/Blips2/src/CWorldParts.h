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
	CWorldPart*[NrOfRows * NrOfCols * 2] MoveAbleItems;
	CWorldPart* Player,Player1,Player2;
	int MinX, MinY, MaxX, MaxY;
	int ActivePlayer;
	int ItemCount, MoveAbleItemCount, ActivePlayerFlicker;
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

	// if ((WorldPart->Type == IDBox) || (WorldPart->Type == IDBox1) || (WorldPart->Type == IDBox2) || (WorldPart->Type == IDPlayer) || (WorldPart->Type == IDPlayer2) ||
	// (WorldPart->Type == IDBoxWall) || (WorldPart->Type == IDBoxBomb))
	// if (WorldParts->MoveAbleItemCount < NrOfRows * NrOfCols * 2)
	// {
	// 	WorldParts->MoveAbleItems[WorldParts->MoveAbleItemCount++] = WorldPart;
	// }

	if (WorldPart->Type == IDPlayer)
	{
		WorldParts->Player1 = WorldPart;
		WorldParts->Player = WorldParts->Player1;
		WorldParts->ActivePlayer = IDPlayer;
	}

	if (WorldPart->Type == IDPlayer2)
	{
		WorldParts->Player2 = WorldPart;
		WorldParts->Player = WorldParts->Player2;
		WorldParts->ActivePlayer = IDPlayer2;
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
		case IDPlayer2:
			Result->Image=IMGPlayer2;
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
			Result->AnimPhase = 0;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimPhases = 1;
			Result->Z = ZBox;
			break;
		case IDBox1:
			Result->Image = IMGBox;
			Result->AnimPhase = 2;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimPhases = 1;
			Result->Z = ZBox;
			break;
		case IDBox2:
			Result->Image = IMGBox;
			Result->AnimPhase = 3;
			Result->AnimPhases = 1;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimPhases = 1;
			Result->Z = ZBox;
			break;
		case IDBoxWall:
			Result->Image = IMGBox;
			Result->AnimPhase = 1;
			Result->AnimPhases = 1;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimPhases = 1;
			Result->Z = ZBox;
			break;
		case IDBoxBomb:
			Result->Image = IMGBox;
			Result->AnimPhase = 4;
			Result->AnimPhases = 1;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimPhases = 1;
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
			Result->AnimPhase = 0;
			break;
		case IDWallBreakable:
			Result->Image = IMGWall;
			Result->Z = ZWall;
			Result->AnimPhase = 1;
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
    if(WorldPart->Type == IDPlayer || WorldPart->Type == IDPlayer2)
	{
		if (WorldPart->ParentList)
		{
			for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
			{
				if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
					continue;

				if((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY))
				{
					if(WorldPart->ParentList->Items[Teller]->Type == IDBomb)
					{
						//kill needs to come first, Add sorts the lists skewing indexing
						CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
						WorldPart->IsDeath = true;
						CWorldPart_Hide(WorldPart);
						CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX,WorldPart->PlayFieldY, IDExplosion));
						break;
					}

					if(WorldPart->ParentList->Items[Teller]->Type == IDDiamond)
					{
						CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
						CAudio_PlaySound(Sounds[SND_COLLECT],0);
					}

				}
			}
		}
	}

	if (WorldPart->Type == IDBox || WorldPart->Type == IDBox1 || WorldPart->Type == IDBox2 || WorldPart->Type == IDBoxBomb || WorldPart->Type == IDBoxWall)
	{
		if (WorldPart->Type == IDBox)
			WorldPart->AnimPhase = 0;
		else if (WorldPart->Type == IDBox1)
			WorldPart->AnimPhase = 2;
		else if (WorldPart->Type == IDBox2)
			WorldPart->AnimPhase = 3;
		else if (WorldPart->Type == IDBoxWall)
			WorldPart->AnimPhase = 1;
		else if (WorldPart->Type == IDBoxBomb)
			WorldPart->AnimPhase = 4;
		if (WorldPart->ParentList)
		{
			for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
			{
				if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
					continue;

				if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY) &&
					(WorldPart->ParentList->Items[Teller]->Type == IDBomb))
				{
					//kill needs to come first, Add sorts the lists skewing indexing
					CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
					CWorldPart_Kill(WorldPart);
					CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX, WorldPart->PlayFieldY, IDExplosion));
					break;
				}

				if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY) &&
					(WorldPart->ParentList->Items[Teller]->Type == IDBoxWall) && (WorldPart->Type == IDBoxWall) &&
					(WorldPart->ParentList->Items[Teller] != WorldPart))
				{
					//kill needs to come first, Add sorts the lists skewing indexing
					CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
					CWorldPart_Kill(WorldPart);
					CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX, WorldPart->PlayFieldY, IDExplosion));
					CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX, WorldPart->PlayFieldY, IDWall));			
					break;
				}

				if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY) &&
					(WorldPart->ParentList->Items[Teller]->Type != IDWall) && (WorldPart->ParentList->Items[Teller]->Type != IDDiamond) && 
					(WorldPart->ParentList->Items[Teller]->Type != IDFloor) &&
					(WorldPart->Type == IDBoxBomb) && (WorldPart != WorldPart->ParentList->Items[Teller]))
				{
					//kill needs to come first, Add sorts the lists skewing indexing
					if ((WorldPart->ParentList->Items[Teller]->Type == IDPlayer) || (WorldPart->ParentList->Items[Teller]->Type == IDPlayer2))
					{
						WorldPart->ParentList->Items[Teller]->IsDeath = true;
						CWorldPart_Hide(WorldPart->ParentList->Items[Teller]);
					}
					else
						CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
					CWorldPart_Kill(WorldPart);
					CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX, WorldPart->PlayFieldY, IDExplosion));					
					break;
				}

				if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY) &&
					(WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) && (WorldPart != WorldPart->ParentList->Items[Teller]))
				{
					//kill needs to come first, Add sorts the lists skewing indexing					
					CWorldPart_Kill(WorldPart->ParentList->Items[Teller]);
					CWorldPart_Kill(WorldPart);
					CWorldParts_Add(WorldPart->ParentList, CWorldPart_Create(WorldPart->PlayFieldX, WorldPart->PlayFieldY, IDExplosion));
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
		case IDPlayer2:
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
	if(WorldPart->Type == IDPlayer || WorldPart->Type == IDPlayer2)
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
					for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;

						if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
						{
							if (WorldPart->ParentList->Items[Teller]->Type == IDWall || WorldPart->ParentList->Items[Teller]->Type == IDWallBreakable || 
								WorldPart->ParentList->Items[Teller]->Type == IDPlayer || WorldPart->ParentList->Items[Teller]->Type == IDPlayer2 || 
								WorldPart->ParentList->Items[Teller]->Type == IDBox2)
							{
								Result = false;
								break;
							}
							if (WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox1 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb)
							{
								if (WorldPart->PlayFieldX > PlayFieldXin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin - 1, PlayFieldYin);
								}
								if (WorldPart->PlayFieldX < PlayFieldXin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin + 1, PlayFieldYin);
								}
								if (WorldPart->PlayFieldY > PlayFieldYin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin, PlayFieldYin - 1);
								}
								if (WorldPart->PlayFieldY < PlayFieldYin)
								{
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller], PlayFieldXin, PlayFieldYin + 1);
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
		case IDPlayer2:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;

						if((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
						{
							if(WorldPart->ParentList->Items[Teller]->Type == IDWall || WorldPart->ParentList->Items[Teller]->Type == IDWallBreakable ||
								WorldPart->ParentList->Items[Teller]->Type == IDPlayer || WorldPart->ParentList->Items[Teller]->Type == IDPlayer2 || 
								WorldPart->ParentList->Items[Teller]->Type == IDBox1)
							{
								Result = false;
								break;
							}
							if(WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox2 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb)
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
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;

						if((WorldPart->ParentList->Items[Teller]->Type == IDWall) || (WorldPart->ParentList->Items[Teller]->Type == IDWallBreakable) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDBox) ||(WorldPart->ParentList->Items[Teller]->Type == IDDiamond) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDPlayer) || (WorldPart->ParentList->Items[Teller]->Type == IDPlayer2) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDBox1) || (WorldPart->ParentList->Items[Teller]->Type == IDBox2) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDBoxWall))
							if((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								Result = false;
								break;
							}
					}
				}
			}
			else
				Result = false;
			break;
		}

		case IDBoxBomb:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;
						
						if ((WorldPart->ParentList->Items[Teller]->Type == IDWall) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDDiamond) )
							if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								Result = false;
								break;
							}
					}
				}
			}
			else
				Result = false;
			break;
		}

		case IDBoxWall:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;

						if ((WorldPart->ParentList->Items[Teller]->Type == IDWall) || (WorldPart->ParentList->Items[Teller]->Type == IDWallBreakable) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDDiamond) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDPlayer) || (WorldPart->ParentList->Items[Teller]->Type == IDPlayer2) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDBox1) || (WorldPart->ParentList->Items[Teller]->Type == IDBox2))
							if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								Result = false;
								break;
							}
					}
				}
			}
			else
				Result = false;
			break;
		}
		
		case IDBox1:
		{
			if (WorldPart->ParentList->ActivePlayer != IDPlayer)
				return false;
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;

						if ((WorldPart->ParentList->Items[Teller]->Type == IDWall) || (WorldPart->ParentList->Items[Teller]->Type == IDWallBreakable) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDDiamond) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDPlayer) ||	(WorldPart->ParentList->Items[Teller]->Type == IDPlayer2) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDBox1) || (WorldPart->ParentList->Items[Teller]->Type == IDBox2) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDBoxWall))
							if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								Result = false;
								break;
							}
					}
				}
			}
			else
				Result = false;
			break;
		}

		case IDBox2:
		{
			if (WorldPart->ParentList->ActivePlayer != IDPlayer2)
				return false;
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
					{
						if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
							continue;

						if ((WorldPart->ParentList->Items[Teller]->Type == IDWall) || (WorldPart->ParentList->Items[Teller]->Type == IDWallBreakable) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDDiamond) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDPlayer) ||	(WorldPart->ParentList->Items[Teller]->Type == IDPlayer2) || 
							(WorldPart->ParentList->Items[Teller]->Type == IDBox1) || (WorldPart->ParentList->Items[Teller]->Type == IDBox2) ||
							(WorldPart->ParentList->Items[Teller]->Type == IDBoxWall))
							if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
							{
								Result = false;
								break;
							}
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
 	if(WorldPart->Type == IDPlayer)
	{
		if(!WorldPart->IsMoving && !WorldPart->PNeedToKill && !WorldPart->BHide)
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
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox1 || 
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
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
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox1 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
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
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox1 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
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
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox1 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
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
				CAudio_PlaySound(Sounds[SND_MOVE],0);
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
	else if (WorldPart->Type == IDPlayer2)
	{
		if (!WorldPart->IsMoving && !WorldPart->PNeedToKill && !WorldPart->BHide)
		{
			if (CWorldPart_CanMoveTo(WorldPart, PlayFieldXin, PlayFieldYin) || BackWards)
			{
				WorldPart->PlayFieldX = PlayFieldXin;
				WorldPart->PlayFieldY = PlayFieldYin;
				if (WorldPart->X < WorldPart->PlayFieldX * TileWidth)
				{
					WorldPart->Xi = WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
						{
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if ((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox2 || 
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
								((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX + 1, WorldPart->PlayFieldY, false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 4;

				}
				if (WorldPart->X > WorldPart->PlayFieldX * TileWidth)
				{
					WorldPart->Xi = -WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
						{
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if ((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox2 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
								((WorldPart->PlayFieldX == WorldPart->ParentList->Items[Teller]->PlayFieldX) &&
									(WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX - 1, WorldPart->PlayFieldY, false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 0;
				}
				if (WorldPart->Y > WorldPart->PlayFieldY * TileHeight)
				{
					WorldPart->Yi = -WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
						{
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if ((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox2 || 
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
								((WorldPart->PlayFieldY == WorldPart->ParentList->Items[Teller]->PlayFieldY) &&
									(WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX, WorldPart->PlayFieldY - 1, false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 8;
				}
				if (WorldPart->Y < WorldPart->PlayFieldY * TileHeight)
				{
					WorldPart->Yi = WorldPart->MoveSpeed;
					if (WorldPart->ParentList)
					{
						for (Teller = 0; Teller < WorldPart->ParentList->ItemCount; Teller++)
						{
							if (WorldPart->ParentList->Items[Teller]->PNeedToKill || WorldPart->ParentList->Items[Teller]->BHide)
								continue;

							if ((WorldPart->ParentList->Items[Teller]->Type == IDBox || WorldPart->ParentList->Items[Teller]->Type == IDBox2 ||
								WorldPart->ParentList->Items[Teller]->Type == IDBoxWall || WorldPart->ParentList->Items[Teller]->Type == IDBoxBomb) &&
								((WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY) &&
									(WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX)))
							{
								CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX, WorldPart->PlayFieldY + 1, false);
								break;
							}
						}
					}
					WorldPart->AnimBase = 12;
				}
				WorldPart->IsMoving = true;
				CAudio_PlaySound(Sounds[SND_MOVE],0);
			}
			else
			{
				if (PlayFieldXin > WorldPart->PlayFieldX)
				{
					WorldPart->AnimBase = 4;
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
	// if (!WorldPart->FirstArriveEventFired)
	// {
	// 	CWorldPart_Event_ArrivedOnNewSpot(WorldPart);
	// 	WorldPart->FirstArriveEventFired=true;
	// }
	if (WorldPart->IsMoving && !WorldPart->PNeedToKill && !WorldPart->BHide)
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
	if (Result)
	{
		Result->ItemCount = 0;
		Result->MoveAbleItemCount = 0;
		Result->DisableSorting = false;
		Result->Player = NULL;
		Result->Player1 = NULL;
		Result->Player2 = NULL;
		Result->ActivePlayer = IDPlayer;
		Result->ActivePlayerFlicker = 0;
		Result->ViewPort = CViewPort_Create(0, 0, 19, 11, 0, 0, NrOfCols - 1, NrOfRows - 1);
	}
	return Result;
}

void CWorldParts_CenterVPOnPlayer(CWorldParts* WorldParts)
{
    int PlayerX=-1,PlayerY=-1;
	if(WorldParts->Player)
	{
		PlayerX = WorldParts->Player->PlayFieldX;
       	PlayerY = WorldParts->Player->PlayFieldY;
	}
    CViewPort_SetViewPort(WorldParts->ViewPort, PlayerX-10, PlayerY-6,PlayerX+10, PlayerY+6);
}


void CWorldParts_SwitchPlayers(CWorldParts* WorldParts)
{
	if (!WorldParts->Player2)
		return;

	if (WorldParts->ActivePlayer == IDPlayer)
	{
		WorldParts->ActivePlayer = IDPlayer2;
		WorldParts->Player = WorldParts->Player2;
	}
	else
	{
		WorldParts->ActivePlayer = IDPlayer;
		WorldParts->Player = WorldParts->Player1;
	}
	WorldParts->ActivePlayerFlicker = 18;
	CWorldParts_CenterVPOnPlayer(WorldParts);
}

void CWorldParts_LimitVPLevel(CWorldParts* WorldParts)
{
    CViewPort_SetVPLimit(WorldParts->ViewPort, WorldParts->MinX,WorldParts->MinY,WorldParts->MaxX,WorldParts->MaxY);
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
	WorldParts->MoveAbleItemCount = 0;
	WorldParts->ActivePlayer = -1;
	WorldParts->Player1 = NULL;
	WorldParts->Player2 = NULL;
}
void CWorldParts_Remove(CWorldParts* WorldParts, int PlayFieldXin,int PlayFieldYin)
{
	int Teller1,Teller2;
	for (Teller1=0;Teller1<WorldParts->ItemCount;Teller1++)
	{
		// if ((Teller1 < WorldParts->MoveAbleItemCount) && (WorldParts->MoveAbleItems[Teller1]->PlayFieldX == PlayFieldXin) && (WorldParts->MoveAbleItems[Teller1]->PlayFieldY == PlayFieldYin))
		// {
		// 	for (Teller2 = Teller1; Teller2 < WorldParts->MoveAbleItemCount - 1; Teller2++)
		// 		WorldParts->MoveAbleItems[Teller2] = WorldParts->MoveAbleItems[Teller2 + 1];
		// 	WorldParts->MoveAbleItemCount--;
		// }

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
		// if ((Teller1 < WorldParts->MoveAbleItemCount) && (WorldParts->MoveAbleItems[Teller1]->PlayFieldX == PlayFieldXin) && (WorldParts->MoveAbleItems[Teller1]->PlayFieldY == PlayFieldYin) && (WorldParts->MoveAbleItems[Teller1]->Type == Type))
		// {
		// 	for (Teller2 = Teller1; Teller2 < WorldParts->MoveAbleItemCount - 1; Teller2++)
		// 		WorldParts->MoveAbleItems[Teller2] = WorldParts->MoveAbleItems[Teller2 + 1];
		// 	WorldParts->MoveAbleItemCount--;
		// }

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


void CWorldParts_Load(CWorldParts* WorldParts, int LevelPackNr, int Level)
{
	//end frame before loading and after loading 
	//to not hang the current frame / cpu
	end_frame();
	int X,Y,Type;
	CWorldParts_RemoveAll(WorldParts);
	WorldParts->DisableSorting = true;
	WorldParts->MinX = NrOfCols;
	WorldParts->MinY = NrOfRows;
	WorldParts->MaxX = -1;
	WorldParts->MaxY = -1;
	for(int z = 0; z < 50*50*2; z+=3)
	{
		Type = Levels[LevelPackNr][Level][z];
		X = Levels[LevelPackNr][Level][z+1];
		Y = Levels[LevelPackNr][Level][z+2];
		//will always happen at the end of the real data in the level
		if ((Type == 0) && ((X == 0) && (Y ==0)))
			break;
		if (X < WorldParts->MinX)
			WorldParts->MinX = X;
		if (Y < WorldParts->MinY)
			WorldParts->MinY = Y;
		if (X > WorldParts->MaxX)
			WorldParts->MaxX = X;
		if (Y > WorldParts->MaxY)
            WorldParts->MaxY = Y;
		CWorldParts_Add(WorldParts, CWorldPart_Create(X,Y,Type));
		
	}
	WorldParts->DisableSorting = false;
	if (WorldParts->Player1 && WorldParts->Player2)
	{
		WorldParts->Player = WorldParts->Player1;
		WorldParts->ActivePlayer = IDPlayer;
	}
	CWorldParts_Sort(WorldParts);
	CWorldParts_LimitVPLevel(WorldParts);
	CWorldParts_CenterVPOnPlayer(WorldParts);
	end_frame();
}

void CWorldParts_Move(CWorldParts* WorldParts)
{
	int Teller;
	// for (Teller=0;Teller<WorldParts->MoveAbleItemCount;Teller++)
	// {
	// 	if(WorldParts->MoveAbleItems[Teller]->IsMoving)
	// 		//other items are not moveable and have no effect
	// 		CWorldPart_Move(WorldParts->MoveAbleItems[Teller]);
	// }

	WorldParts->MoveAbleItemCount = 0;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		if(WorldParts->Items[Teller]->IsMoving)
		{
			//other items are not moveable and have no effect
			if (!WorldParts->Items[Teller]->PNeedToKill && !WorldParts->Items[Teller]->BHide)
			{
				CWorldPart_Move(WorldParts->Items[Teller]);
				if (!WorldParts->Items[Teller]->PNeedToKill && !WorldParts->Items[Teller]->BHide)
					WorldParts->MoveAbleItems[WorldParts->MoveAbleItemCount++] = WorldParts->Items[Teller];
			}
		}
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
                    if (WorldParts->ActivePlayerFlicker > 0)
					{
						if (WorldParts->Items[Teller]->Type == WorldParts->ActivePlayer)
						{
							if (WorldParts->ActivePlayerFlicker % 3 == 0)
								CWorldPart_Draw(WorldParts->Items[Teller]);
						}
						else
							CWorldPart_Draw(WorldParts->Items[Teller]);

					}
					else
						CWorldPart_Draw(WorldParts->Items[Teller]);
				}
	}
	//redraw movableitems so they are always on top
	for (Teller=0;Teller<WorldParts->MoveAbleItemCount;Teller++)
	{
		CWorldPart_Draw(WorldParts->MoveAbleItems[Teller]);
	}

	if (WorldParts->ActivePlayerFlicker > 0)
		WorldParts->ActivePlayerFlicker--;
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