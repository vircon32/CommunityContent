#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include "Common.h"
#include "Defines.h"
#include "GameFuncs.h"
#include "CLevelPackFile.h"
#include "Debugspeed.h"

struct CWorldPart;
struct CHistory;

struct SPrevPoint
{
	int X,Y;
};

struct CHistory
{
	SPrevPoint[MaxHistory] Items;
	CWorldPart *Part;
	int ItemCount;
};

struct CWorldParts;

struct CWorldPart
{
	int MoveDelayCounter;
	bool FirstArriveEventFired;
	int AnimCounter,AnimBase,AnimDelay,AnimDelayCounter,AnimPhases;
	int Type,MoveSpeed,MoveDelay,Xi,Yi,X,Y,AnimPhase,PlayFieldX,PlayFieldY,Z;
	bool BHistory;
	Texture * Image;
	CWorldParts *ParentList;
	bool IsMoving;
	CHistory *History;
	bool Selected;
};

struct CWorldParts
{
	bool[NrOfRows*NrOfCols] LevelWalls;
	bool[NrOfRows*NrOfCols] LevelSpots;
	bool DisableSorting;
	CWorldPart*[NrOfRows*NrOfCols*3] Items;
	CWorldPart *Player;
	int Pushes, Moves;
	bool isLevelPackFileLevel;
	int ItemCount;
};

CHistory* CHistory_Create(CWorldPart *Partin)
{
	CHistory* Result = (CHistory*)malloc(sizeof(CHistory));
	Result->ItemCount = 0;
	Result->Part = Partin;
	return Result;
}

void CHistory_Destroy(CHistory* History)
{
	if(History)
	{
		free(History);
		History = NULL;
	}
}

void CHistory_Add(CHistory* History, int X, int Y)
{
	SPrevPoint Temp;
	int Teller;
	Temp.X = X;
	Temp.Y = Y;
	if (History->ItemCount < MaxHistory)
	{
		History->Items[History->ItemCount] = Temp;
		History->ItemCount++;
	}
	else
	{
		for (Teller=0;Teller < History->ItemCount - 1 ;Teller++)
		{
			History->Items[Teller] = History->Items[Teller+1];
		}
		History->Items[History->ItemCount-1] = Temp;
	}
}

CWorldPart* CWorldPart_Create(int PlayFieldXin,int PlayFieldYin,bool CreateHistory, int aType)
{
	CWorldPart* Result = (CWorldPart*) malloc(sizeof(CWorldPart));
	Result->BHistory = CreateHistory;
	if (Result->BHistory)
		Result->History = CHistory_Create(Result);
	Result->PlayFieldX=PlayFieldXin;
	Result->PlayFieldY=PlayFieldYin;
	Result->Xi=0;
	Result->Yi=0;
	Result->X=PlayFieldXin*TileWidth;
	Result->Y=PlayFieldYin*TileHeight;
	Result->Type=aType;
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
	Result->AnimBase=0;
	Result->AnimPhases=0;
	Result->AnimCounter = 0;
	Result->AnimDelay = 0;
	Result->MoveSpeed = 0;

	switch(Result->Type)
	{
		case IDPlayer:
			Result->Image= IMGPlayer;
			Result->AnimBase=4;
			Result->AnimPhase=4;
			Result->AnimPhases=4;
			Result->AnimCounter = 1;
			Result->AnimDelay = 8;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->AnimDelayCounter =0;
			Result->Z = ZPlayer;
			break;
		case IDSpot:
			Result->Image = IMGSpot;
			Result->Z = ZSpot;
			break;
		case IDBox:
			Result->Image = IMGBox;
			Result->MoveDelay = 0;
			Result->MoveSpeed = 2;
			Result->Z = ZBox;
			break;
		case IDWall:
			Result->Image = IMGWall;
			Result->Z = ZWall;
			break;
		case IDFloor:
			Result->Image = IMGFloor;
			Result->Z = ZFloor;
			break;
		case IDEmpty:
			Result->Image = IMGEmpty;
			Result->Z = ZEmpty;
			break;
	}
	return Result;
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

bool CWorldPart_HasHistory(CWorldPart* WorldPart) 
{ 
	return WorldPart->BHistory;
}


void CWorldPart_SetAnimPhase(CWorldPart* WorldPart, int AnimPhaseIn) 
{
	WorldPart->AnimPhase = AnimPhaseIn;
}

void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* WorldPart) 
{
	if (WorldPart->Type == IDBox)
	{
		WorldPart->AnimPhase = 0;
		if (WorldPart->ParentList)
		{
			if(WorldPart->ParentList->LevelSpots[(WorldPart->PlayFieldY * NrOfCols) +  WorldPart->PlayFieldX])
				WorldPart->AnimPhase = 1;
			// for (int Teller=0;Teller< WorldPart->ParentList->ItemCount;Teller++)
			// {
			// 	if( WorldPart->ParentList->Items[Teller]->Type == IDSpot)
			// 	{
			// 		if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY))
			// 		{
			// 			WorldPart->AnimPhase = 1;
			// 			break;
			// 		}
			// 	}
			// }
		}
	}

	// no longer needed as level editor is gone
	// if(WorldPart->Type == IDSpot)
	// {
	// 	if (WorldPart->ParentList)
	// 	{
	// 		for (int Teller=0;Teller< WorldPart->ParentList->ItemCount;Teller++)
	// 		{
	// 			if( WorldPart->ParentList->Items[Teller]->Type == IDBox)
	// 			{
	// 				if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY))
	// 				{
	// 					WorldPart->ParentList->Items[Teller]->AnimPhase = 1;
	// 					break;
	// 				}
	// 			}
	// 		}
	// 	}
	// }
}

void CWorldPart_Event_BeforeDraw(CWorldPart* WorldPart) 
{
	if(WorldPart->Type == IDPlayer)
	{
		if (WorldPart->IsMoving)
		{
			WorldPart->AnimPhase = WorldPart->AnimBase + WorldPart->AnimCounter;
			WorldPart->AnimDelayCounter++;
			if (WorldPart->AnimDelayCounter == WorldPart->AnimDelay)
			{
				WorldPart->AnimDelayCounter = 0;
				WorldPart->AnimCounter++;
				if (WorldPart->AnimCounter >= WorldPart->AnimPhases)
					WorldPart->AnimCounter = 0;
			}
		}

	}
}

void CWorldPart_Event_LeaveCurrentSpot(CWorldPart* WorldPart) 
{
	if(WorldPart->Type == IDBox)
	{
		if (WorldPart->ParentList)
		{
			int Teller;
			for (Teller=0;Teller< WorldPart->ParentList->ItemCount;Teller++)
			{
				if( WorldPart->ParentList->Items[Teller]->Type == IDSpot)
				{
					if ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY))
					{
						WorldPart->AnimPhase = 1;
						break;
					}
				}
			}
		}
	}
}

void CWorldPart_SetPosition(CWorldPart* WorldPart, int PlayFieldXin,int PlayFieldYin)
{
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		WorldPart->PlayFieldX=PlayFieldXin;
		WorldPart->PlayFieldY=PlayFieldYin;
		WorldPart->X=PlayFieldXin*TileWidth;
		WorldPart->Y=PlayFieldYin*TileHeight;
		CWorldPart_Event_ArrivedOnNewSpot(WorldPart);
	}
}

bool CWorldPart_CanMoveTo(CWorldPart* WorldPart, int PlayFieldXin,int PlayFieldYin) 
{
	bool Result = true;
	int Teller;
	if(WorldPart->Type == IDBox)
	{
		if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
		{
			if (WorldPart->ParentList)
			{
				for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
					if((WorldPart->ParentList->Items[Teller]->Type == IDWall) || (WorldPart->ParentList->Items[Teller]->Type == IDBox))
						if((WorldPart->ParentList->Items[Teller]->PlayFieldX == PlayFieldXin) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == PlayFieldYin))
						{
							Result = false;
							break;
						}
			}
		}
		else
			Result = false;
		return Result;

	}
	else
	{
		if(WorldPart->Type == IDPlayer)
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (WorldPart->ParentList)
				{
					for (Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
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
									Result = CWorldPart_CanMoveTo(WorldPart->ParentList->Items[Teller],PlayFieldXin,PlayFieldYin+1);
								}
								break;
							}

						}
				}
			}
			else
				Result = false;
			return Result;

		}
		else
			return false;
	}
}


void CWorldPart_MoveTo(CWorldPart* WorldPart, int PlayFieldXin,int PlayFieldYin,bool BackWards)
{
	if(WorldPart->Type== IDPlayer)
	{
		int Teller;
		if(!WorldPart->IsMoving)
		{
			if(CWorldPart_CanMoveTo(WorldPart, PlayFieldXin,PlayFieldYin) || BackWards)
			{
				if(WorldPart->ParentList)
				{
					if(BackWards)
						WorldPart->ParentList->Moves--;
					else
						WorldPart->ParentList->Moves++;
				}
				WorldPart->AnimPhases = 4;
				WorldPart->PlayFieldX = PlayFieldXin;
				WorldPart->PlayFieldY = PlayFieldYin;
				if(WorldPart->X < WorldPart->PlayFieldX*TileWidth)
				{
					WorldPart->Xi = WorldPart->MoveSpeed;
					if(BackWards)
					{
						WorldPart->AnimBase = 0;
					}
					else
					{
						WorldPart->AnimBase = 4;
						if (WorldPart->ParentList)
						{
							for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
							{
								if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && ((WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX) && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)))
								{
									CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX+1,WorldPart->PlayFieldY,false);
									break;
								}
							}
						}
					}
					
				}
				if(WorldPart->X > WorldPart->PlayFieldX*TileWidth)
				{
					WorldPart->Xi = -WorldPart->MoveSpeed;
					if(BackWards)
					{
						WorldPart->AnimBase = 4;
					}
					else
					{
						WorldPart->AnimBase = 0;
						if (WorldPart->ParentList)
						{
							for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
							{
								if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && ((WorldPart->PlayFieldX == WorldPart->ParentList->Items[Teller]->PlayFieldX )  && (WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)))
								{
									CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX-1,WorldPart->PlayFieldY,false);
									break;
								}
							}
						}
						
					}
				}

				if(WorldPart->Y > WorldPart->PlayFieldY*TileHeight)
				{
					WorldPart->Yi = -WorldPart->MoveSpeed;
					if(BackWards)
					{
						WorldPart->AnimBase = 12;
					}
					else
					{
						WorldPart->AnimBase = 8;
						if (WorldPart->ParentList)
						{
							for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
							{
								if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && ((WorldPart->PlayFieldY == WorldPart->ParentList->Items[Teller]->PlayFieldY)  && (WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX)))
								{
									CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX,WorldPart->PlayFieldY-1,false);
									break;
								}						
							}
						}
					}
				}
				if(WorldPart->Y < WorldPart->PlayFieldY*TileHeight)
				{
					WorldPart->Yi = WorldPart->MoveSpeed;
					if(BackWards)
					{
						WorldPart->AnimBase = 8;
					}
					else
					{
						WorldPart->AnimBase = 12;
						if(WorldPart->ParentList)
						{
							for(Teller=0;Teller<WorldPart->ParentList->ItemCount;Teller++)
							{
								if(((WorldPart->ParentList->Items[Teller]->Type == IDBox) || (WorldPart->ParentList->Items[Teller]->Type == IDWall)) && ((WorldPart->ParentList->Items[Teller]->PlayFieldY == WorldPart->PlayFieldY)  && (WorldPart->ParentList->Items[Teller]->PlayFieldX == WorldPart->PlayFieldX )))
								{
									CWorldPart_MoveTo(WorldPart->ParentList->Items[Teller], WorldPart->PlayFieldX,WorldPart->PlayFieldY+1,false);
									break;
								}
							}
						}
					}
				}
				CAudio_PlaySound(Sounds[SND_MOVE],0);
				WorldPart->IsMoving = true;
			}
			else
			{
				WorldPart->AnimPhases = 0;
				WorldPart->AnimCounter = 0;

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
					if (WorldPart->AnimCounter >= WorldPart->AnimPhases)
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
				if(CWorldPart_CanMoveTo(WorldPart,PlayFieldXin,PlayFieldYin) || BackWards)
				{
					if(WorldPart->Type == IDBox)
					{
						if(WorldPart->ParentList)
						{
							if(BackWards)
								WorldPart->ParentList->Pushes--;
							else
								WorldPart->ParentList->Pushes++;
						}
					}
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
					CWorldPart_Event_LeaveCurrentSpot(WorldPart);
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
	if (WorldPart->Image)
	{
		CWorldPart_Event_BeforeDraw(WorldPart);
		drawTexture(WorldPart->Image,WorldPart->AnimPhase,WorldPart->X + 8, WorldPart->Y);
	}
}

void CWorldPart_Destroy(CWorldPart* WorldPart)
{
	if(WorldPart)
	{
		if(WorldPart->BHistory)
			CHistory_Destroy(WorldPart->History);
		free(WorldPart);
		WorldPart = NULL;
	}
}

void CWorldPart_HistoryAdd(CWorldPart* WorldPart) 
{ 
	if (WorldPart->BHistory) 
		CHistory_Add(WorldPart->History,WorldPart->PlayFieldX,WorldPart->PlayFieldY); 
}


void CHistory_GoBack(CHistory* History)
{
	if(History->ItemCount > 0)
	{
		History->ItemCount--;
		CWorldPart_MoveTo(History->Part, History->Items[History->ItemCount].X,History->Items[History->ItemCount].Y,true);
	}
}

void CWorldPart_HistoryGoBack(CWorldPart* WorldPart) 
{ 
	if(WorldPart->BHistory) 
		CHistory_GoBack(WorldPart->History);
}



CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = (CWorldParts*) malloc(sizeof(CWorldParts));
	Result->ItemCount = 0;
	Result->DisableSorting = false;
	Result->Player = NULL;
	return Result;
}

void CWorldParts_RemoveAll(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
	{
		CWorldPart_Destroy(WorldParts->Items[Teller]);
		WorldParts->Items[Teller] = NULL;
	}
	for(int i = 0; i < NrOfCols*NrOfRows; i++)
	{
		WorldParts->LevelSpots[i] = false;
		WorldParts->LevelWalls[i] = false;
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

void CWorldParts_RemoveType(CWorldParts* WorldParts, int PlayFieldXin,int PlayFieldYin,int Type)
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



void CWorldParts_HistoryAdd(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_HistoryAdd(WorldParts->Items[Teller]);
}

void CWorldParts_HistoryGoBack(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_HistoryGoBack(WorldParts->Items[Teller]);
}

int compareWorldParts(CWorldPart* a, CWorldPart* b) {
    return a->Z - b->Z;
}

#define TIMSORTRUN 32

// Function to merge two subarrays
void CWorldParts_merge(CWorldPart** array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    CWorldPart** leftArray = (CWorldPart**)malloc(n1 * sizeof(CWorldPart*));
    CWorldPart** rightArray = (CWorldPart**)malloc(n2 * sizeof(CWorldPart*));

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    // Merge the temporary arrays back into array[left..right]

    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        int leftDepth;
		if(leftArray[i] == NULL) 
			leftDepth = INT_MAX;
		else
		  leftDepth = leftArray[i]->Z;
        int rightDepth;
		if (rightArray[j] == NULL) 
			rightDepth =  INT_MAX; 
		else
			rightDepth = rightArray[j]->Z;

        if (leftDepth <= rightDepth) {
            array[k] = leftArray[i];           
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(leftArray);
    free(rightArray);
}

// Function to implement merge sort
void CWorldParts_mergeSort(CWorldPart** array, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        CWorldParts_mergeSort(array, left, mid);
        CWorldParts_mergeSort(array, mid + 1, right);

        // Merge the sorted halves
        CWorldParts_merge(array, left, mid, right);
    }
}


// Utility function to perform insertion sort on the array
void insertionSort(CWorldPart** array, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        CWorldPart* temp = array[i];
        int depth;
        if (temp == NULL) {
            depth = INT_MAX;
        } else {
            depth = temp->Z;
        }

        int j = i - 1;

        while (j >= left) {
            int currentDepth;
            if (array[j] == NULL) {
                currentDepth = INT_MAX;
            } else {
                currentDepth = array[j]->Z;
            }

            if (currentDepth <= depth) {
                break;
            }

            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = temp;
    }
}

// Merge function merges the sorted runs
void merge(CWorldPart** array, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    CWorldPart** left = (CWorldPart**)malloc(len1 * sizeof(CWorldPart*));
    CWorldPart** right = (CWorldPart**)malloc(len2 * sizeof(CWorldPart*));

    for (int i = 0; i < len1; i++) {
        left[i] = array[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = array[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        int leftDepth;
        if (left[i] == NULL) {
            leftDepth = INT_MAX;
        } else {
            leftDepth = left[i]->Z;
        }

        int rightDepth;
        if (right[j] == NULL) {
            rightDepth = INT_MAX;
        } else {
            rightDepth = right[j]->Z;
        }

        if (leftDepth <= rightDepth) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < len2) {
        array[k] = right[j];
        j++;
        k++;
    }

    free(left);
    free(right);
}

// Iterative Timsort function to sort the array[0...n-1]
void timSort(CWorldPart** array, int n) {
    // Sort individual subarrays of size TIMSORTRUN
    for (int i = 0; i < n; i += TIMSORTRUN) {
        int right;
		if (i + TIMSORTRUN - 1 < n - 1) 
			right = (i + TIMSORTRUN - 1);
		else
			right = (n - 1);
        insertionSort(array, i, right);
    }

    // Start merging from size TIMSORTRUN (or 32). It will merge to form size 64, 128, 256 and so on...
    for (int size = TIMSORTRUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right;
			if (left + 2 * size - 1 < n - 1) 
				right = (left + 2 * size - 1); 
			else
				right = (n - 1);

            // Merge subarray array[left...mid] and array[mid+1...right]
            if (mid < right) {
                merge(array, left, mid, right);
            }
        }
    }
}


void CWorldParts_Sort(CWorldParts* WorldParts)
{
	if (!WorldParts->DisableSorting)
	{
		timSort(WorldParts->Items, WorldParts->ItemCount);
	}

}

// void CWorldParts_Sort(CWorldParts* WorldParts)
// {
// 	if (!WorldParts->DisableSorting)
// 	{
// 		int Teller1,Teller2,Index;
// 		CWorldPart *Part;
// 		for (Teller1 = 1; Teller1 <WorldParts->ItemCount;Teller1++)
// 		{
// 			Index = WorldParts->Items[Teller1]->Z;
// 			Part = WorldParts->Items[Teller1];
// 			Teller2 = Teller1;
// 			while ((Teller2 > 0) && (WorldParts->Items[Teller2-1]->Z > Index))
// 			{
// 				WorldParts->Items[Teller2] = WorldParts->Items[Teller2 - 1];
// 				Teller2--;
// 			}
// 			WorldParts->Items[Teller2] = Part;
// 		}
// 	}
// }

void CWorldParts_Add(CWorldParts* WorldParts, CWorldPart *WorldPart)
{
	if( WorldParts->ItemCount < NrOfRows*NrOfCols*3 )
	{
		WorldPart->ParentList = WorldParts;
		WorldParts->Items[WorldParts->ItemCount] = WorldPart;
		WorldParts->ItemCount++;
		if(WorldPart->Type == IDWall)
			WorldParts->LevelWalls[(WorldPart->PlayFieldY * NrOfCols) + WorldPart->PlayFieldX] = true;
		if(WorldPart->Type == IDSpot)
			WorldParts->LevelSpots[(WorldPart->PlayFieldY * NrOfCols) + WorldPart->PlayFieldX] = true;
	}
}


// bool CWorldParts_ItemExists(CWorldParts* WorldParts, int PlayFieldXin,int PlayFieldYin, int Type)
// {
// 	for (int Teller1=0;Teller1<WorldParts->ItemCount;Teller1++)
// 	{
// 		if ((WorldParts->Items[Teller1]->PlayFieldX == PlayFieldXin) && (WorldParts->Items[Teller1]->PlayFieldY == PlayFieldYin) && (WorldParts->Items[Teller1]->Type == Type))
// 			return true;
// 	}
// 	return false;
// }

// Recursive Floodfill function
void FloodFill(CWorldParts *aWorldParts, bool **visited, int X, int Y)
{
    // Check bounds and whether the tile has been visited
    if (X < 0 || X >= NrOfCols || Y < 0 || Y >= NrOfRows || visited[Y][X])
	{
        return;
	}

	if(aWorldParts->LevelWalls[(Y * NrOfCols) + X])
	{
        return;
	}

    // Mark the tile as visited
    visited[Y][X] = true;

	// Draw the floor tile
    CWorldParts_Add(aWorldParts, CWorldPart_Create(X, Y, false, IDFloor));

    // Recur for neighboring tiles
    FloodFill(aWorldParts, visited, X + 1, Y);
    FloodFill(aWorldParts, visited, X - 1, Y);
    FloodFill(aWorldParts, visited, X, Y + 1);
    FloodFill(aWorldParts, visited, X, Y - 1);
}

void  CWorldParts_AddFloors(CWorldParts* WorldParts, CWorldPart* Player)
{
	if(!Player)
		return;
    // Allocate memory for the visited array using malloc
    bool **visited = (bool**)malloc(NrOfRows * sizeof(bool*));
    for (int i = 0; i < NrOfRows; ++i)
    {
        visited[i] = (bool*)malloc(NrOfCols * sizeof(bool));
        for (int j = 0; j < NrOfCols; ++j)
            visited[i][j] = false; // Initialize the array to false
    }

	FloodFill(WorldParts, visited, Player->PlayFieldX, Player->PlayFieldY);

    // Free the allocated memory for the visited array
    for (int i = 0; i < NrOfRows; ++i)
        free(visited[i]);
    free(visited);
}


bool CWorldParts_CenterLevel(CWorldParts* WorldParts)
{
	int MinX = NrOfCols-1;
	int MinY = NrOfRows-1;
	int MaxX = 0;
	int MaxY = 0;
	for (int Teller = 0;Teller<WorldParts->ItemCount;Teller++)
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
	int Xi = ((NrOfCols-1) / 2) - (MaxX + MinX) / 2;
	int Yi = ((NrOfRows-1) / 2) - (MaxY + MinY) / 2;
	for (int Teller = 0;Teller<WorldParts->ItemCount;Teller++)
	{
		CWorldPart_SetPosition(WorldParts->Items[Teller], WorldParts->Items[Teller]->PlayFieldX + Xi, WorldParts->Items[Teller]->PlayFieldY + Yi);
	}
	if (Xi != 0 || Yi!=0)
		return true;
	return false;
}

void CWorldParts_Move(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_Move(WorldParts->Items[Teller]);
}


bool CWorldParts_LoadFromLevelPackFile(CWorldParts* WorldParts, CLevelPackFile* LPFile, int level, bool doCenterLevel)
{
#ifdef DEBUG
	StartDebugSpeed(1);
#endif	
	WorldParts->isLevelPackFileLevel = true;
	CWorldParts_RemoveAll(WorldParts);
	if(level <= LPFile->LevelCount)
	{
		int lvl = level-1;
		LevelMeta* meta = &LPFile->LevelsMeta[lvl];
		WorldParts->DisableSorting=true;
		WorldParts->Pushes = 0;
		WorldParts->Moves = 0;
		int Xi = ((NrOfCols-1) / 2) - ( meta->maxx +  meta->minx) / 2;
		int Yi = ((NrOfRows-1) / 2) - ( meta->maxy +  meta->miny) / 2;
		if(!doCenterLevel)
		{
			Xi = 0;
			Yi = 0;
		}

		int i = 0;
		LevelPart * Part = &LPFile->Levels[lvl][i];
		while (i< meta->parts)
		{
			switch(Part->id)
			{
				case IDWall:
					CWorldParts_Add(WorldParts, CWorldPart_Create(Part->x + Xi,Part->y + Yi,false,Part->id));
					break;				
				case IDBox:
					CWorldParts_Add(WorldParts, CWorldPart_Create(Part->x + Xi,Part->y + Yi,true,Part->id));
					break;
				case IDSpot:
					CWorldParts_Add(WorldParts, CWorldPart_Create(Part->x + Xi,Part->y + Yi,false,Part->id));
					break;
				case IDPlayer:
					WorldParts->Player = CWorldPart_Create(Part->x + Xi,Part->y + Yi,true,Part->id);
					CWorldParts_Add(WorldParts, WorldParts->Player);
					break;
			}
			i++;
			Part++;
		}
		CWorldParts_AddFloors(WorldParts, WorldParts->Player);
		WorldParts->DisableSorting=false;
		CWorldParts_Sort(WorldParts);
		//move once to highlight boxes on spots
		CWorldParts_Move(WorldParts);
#ifdef DEBUG
		StopDebugSpeed(1);
#endif
		return true;
	}
#ifdef DEBUG
	StopDebugSpeed(1);
#endif
	return false;
}


void CWorldParts_Draw(CWorldParts* WorldParts)
{
	int Teller;
	for (Teller=0;Teller<WorldParts->ItemCount;Teller++)
		CWorldPart_Draw(WorldParts->Items[Teller]);
}

void CWorldParts_Destroy(CWorldParts* WorldParts)
{
	if(WorldParts)
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
}


#endif