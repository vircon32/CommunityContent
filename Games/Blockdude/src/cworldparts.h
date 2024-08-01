#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include "commonvars.h"
#include "cviewport.h"
#include "sound.h"
#include "math.h"
#include "debugspeed.h"

struct SPoint {
    int X, Y;
};


struct CWorldParts;
struct CWorldPart;

struct CWorldPart {
	Texture* Img;
	CWorldPart* AttachedPart;
	int MoveDelayCounter;
	bool FirstArriveEventFired;
	int Type, MoveSpeed, MoveDelay, Xi, Yi, X, Y, AnimPhase, PlayFieldX, PlayFieldY, Z, Group;
	int MoveQueBack;
	int MoveQueFront;
	SPoint* [MOVEQUESIZE] MoveQue;
	bool PickupLeft, PickupRight;
	CWorldPart *Player;
	CWorldParts *ParentList;
	bool IsMoving;
	bool Selected;
	bool NeedToMoveLeft;
	bool ItemAttached;
	bool NeedToMoveRight;
	int AnimCounter, AnimBase, AnimDelay, AnimDelayCounter, AnimPhases;
};

struct CWorldParts {
	bool DisableSorting;
	bool AttchedBoxQuedOrMoving;
	CViewPort* ViewPort;
	CWorldPart* [NrOfRows*NrOfCols] Items;
	CWorldPart* [NrOfGroups][NrOfRows][NrOfCols] PositionalItems;
	CWorldPart* Player;
	CWorldPart* IgnorePart;
	int[NrOfGroups] PositionalItemsCount;
	int ItemCount;
	int DrawCount;
	int NumPartsMoving;
	int NumPartsMovingQueued;
	int NumPartsAttachedToPlayer;
	int NumBoxesAttachedToPlayer;
};

CWorldPart* CWorldParts_PartAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return NULL;
	CWorldPart* Part;
	for (int Teller = 0; Teller < NrOfGroups; Teller++)
	{
		Part = self->PositionalItems[Teller][PlayFieldYin][PlayFieldXin];
		if (Part)
		{
			if (Part != self->IgnorePart)
			{
				return Part;
			}
		}
	}

	return NULL;
}

CWorldPart* CWorldPart_create(int PlayFieldXin, int PlayFieldYin, int Typein,  int GroupIn)
{
	CWorldPart* Result = malloc(sizeof(CWorldPart));
	if (Result)
	{
		Result->MoveQueFront = -1;
		Result->MoveQueBack = -1;
		Result->Player = NULL;
		Result->AttachedPart = NULL;
		Result->NeedToMoveLeft = false;
		Result->NeedToMoveRight = false;
		Result->PickupLeft = false;
		Result->PickupRight = false;
		Result->AnimCounter = 0;
		Result->AnimBase = 0;
		Result->AnimDelay = 0;
		Result->AnimDelayCounter = 0;
		Result->AnimPhases = 0;
		Result->PlayFieldX = PlayFieldXin;
		Result->PlayFieldY = PlayFieldYin;
		Result->Xi = 0;
		Result->Yi = 0;
		Result->X = PlayFieldXin * TileWidth;
		Result->Y = PlayFieldYin * TileHeight;
		Result->Type = Typein;
		Result->MoveDelay = 0;
		Result->MoveDelayCounter = 0;
		Result->IsMoving = false;
		Result->MoveSpeed = 0;
		Result->ParentList = NULL;
		Result->AnimPhase = 0;
		Result->Selected = false;
		Result->FirstArriveEventFired = false;
		Result->Group = GroupIn;


		if (Typein == IDPlayer)
		{
			Result->AnimBase = AnimBaseLeft;
			Result->AnimPhases = 4;
			Result->AnimCounter = 1;
			Result->AnimDelay = PlayerAnimDelay;
			Result->MoveSpeed = GameMoveSpeed;
			Result->AnimDelayCounter = 0;
		}

		if (Typein == IDBox)
		{
			Result->MoveSpeed = GameMoveSpeed;
		}

		switch (Typein)
		{
			case IDEmpty:
				Result->Img = IMGEmpty;
				break;
			case IDBox:
				Result->Img = IMGBox;
				break;
			case IDPlayer:
				Result->Img = IMGPlayer;
				break;
			case IDFloor:
				Result->Img = IMGFloor;
				break;
			case IDExit:
				Result->Img = IMGExit;
				break;
			case IDEarthGrassLeft:
				Result->Img = IMGEarthGrassLeft;
				break;
			case IDEarthGrassRight:
				Result->Img = IMGEarthGrassRight;
				break;
			case IDEarthLeft:
				Result->Img = IMGEarthLeft;
				break;
			case IDEarthMiddle:
				Result->Img = IMGEarthMiddle;
				break;
			case IDEarthRight:
				Result->Img = IMGEarthRight;
				break;
			case IDFloatingFloor:
				Result->Img = IMGFloatingFloor;
				break;
			case IDFloatingFloorLeft:
				Result->Img = IMGFloatingFloorLeft;
				break;
			case IDFloatingFloorMiddle:
				Result->Img = IMGFloatingFloorMiddle;
				break;
			case IDFloatingFloorRight:
				Result->Img = IMGFloatingFloorRight;
				break;
			case IDFloorLeft:
				Result->Img = IMGFloorLeft;
				break;
			case IDFloorRight:
				Result->Img = IMGFloorRight;
				break;
			case IDTower:
				Result->Img = IMGTower;
				break;
			case IDStartTower:
				Result->Img = IMGStartTower;
				break;
			case IDTowerShaft:
				Result->Img = IMGTowerShaft;
				break;
			case IDRoof1:
				Result->Img = IMGRoof1;
				break;
			case IDRoof2:
				Result->Img = IMGRoof2;
				break;
			case IDRoofCornerLeft:
				Result->Img = IMGRoofCornerLeft;
				break;
			case IDRoofCornerRight:
				Result->Img = IMGRoofCornerRight;
				break;
			case IDRoofCornerBoth:
				Result->Img = IMGRoofCornerBoth;
				break;
			case IDRoofDownRight:
				Result->Img = IMGRoofDownRight;
				break;
			case IDRoofDownLeft:
				Result->Img = IMGRoofDownLeft;
				break;
		}
	}
	return Result;
}



void CWorldPart_MoveQueClear(CWorldPart* self)
{
	self->MoveQueBack = -1;
	self->MoveQueFront = -1;
}

void CWorldPart_MoveQuePopBack(CWorldPart* self)
{
	if (self->MoveQueBack > -1)
		self->MoveQueBack--;

	if (self->MoveQueBack == -1)
		self->MoveQueFront = -1;
}

void CWorldPart_MoveQuePushBack(CWorldPart* self, SPoint* point)
{
	if (self->MoveQueBack < MOVEQUESIZE - 1)
	{
		if (self->MoveQueFront == -1)
			self->MoveQueFront = 0;
		self->MoveQueBack++;
		self->MoveQue[self->MoveQueBack] = point;
	}
}

void CWorldPart_MoveQueInsert(CWorldPart* self, int pos, SPoint* point)
{
	if ((self->MoveQueBack < MOVEQUESIZE - 1) && (pos <= self->MoveQueBack))
	{
		if (self->MoveQueFront == -1)
			self->MoveQueFront = 0;
		self->MoveQueBack++;

		for (int i = self->MoveQueBack; i > pos; i--)
		{
			self->MoveQue[i] = self->MoveQue[i - 1];
		}

		self->MoveQue[pos] = point;
	}
}

void CWorldPart_AddToMoveQue(CWorldPart* self, int PlayFieldXIn, int PlayFieldYIn)
{
	SPoint* Temp =  malloc(sizeof(SPoint)); 
	Temp->X = PlayFieldXIn;
	Temp->Y = PlayFieldYIn;

	if (self->MoveQueBack == -1)
		CWorldPart_MoveQuePushBack(self, Temp);
	else
		CWorldPart_MoveQueInsert(self, self->MoveQueFront, Temp);
}


bool CWorldPart_MovesInQue(CWorldPart* self)
{
	return (self->MoveQueBack > -1);
}

void CWorldPart_AttachToPlayer(CWorldPart* self, CWorldPart* PlayerIn)
{
	PlayerIn->AttachedPart = self;
	self->Player = PlayerIn;
}

void CWorldPart_DeattachFromPlayer(CWorldPart* self, CWorldPart* PlayerIn)
{
	PlayerIn->AttachedPart = NULL;
	self->Player = NULL;
}

void CWorldPart_SetAnimPhase(CWorldPart* self, int AnimPhaseIn)
{
	self->AnimPhase = AnimPhaseIn;
}

bool CWorldPart_CanMoveTo(CWorldPart* self, int PlayFieldXin, int PlayFieldYin)
{
	switch (self->Type)
	{
		case IDPlayer:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (self->ParentList)
				{
					//if we move up
					if (PlayFieldYin - self->PlayFieldY < 0)
					{
						//we're facing left
						if (self->AnimBase == AnimBaseLeft)
						{
							//part left from player
							CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, self->PlayFieldY);
							if (Part)
							{
								//its an exit (can't jump onto it)
								if (Part->Group == GroupExit)
									return false;

								//it's a box
								if (Part->Group == GroupBox)
								{
									//check part below it
									CWorldPart* Part2 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, self->PlayFieldY + 1);
									if (Part2)
									{
										//it's not a floor kind so can't jump onto it
										if (!((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit)))
										{
											return false;
										}
									}
									else
										return false;

								}

								//check part on final position
								CWorldPart* Part3 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, PlayFieldYin);
								if (Part3)
								{
									//it's something else than exit
									if (Part3->Group != GroupExit)
									{
										return false;
									}
								}
							}
							else
								//nothing on the left
								return false;
						}
						else
						{
							//we're facing right
							if (self->AnimBase == AnimBaseRight)
							{
								//check part on right of player
								CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, self->PlayFieldY);
								if (Part)
								{
									//its an exit can't jump onto that
									if (Part->Group == GroupExit)
										return false;

									//it's a box
									if (Part->Group == GroupBox)
									{
										//check part below it
										CWorldPart* Part2 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, self->PlayFieldY + 1);
										if (Part2)
										{
											//it's not a floor kind so can't jump onto it
											if (!((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit)))
											{
												return false;
											}

										}
										else
											return false;
									}

									//check part on final position
									CWorldPart* Part3 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, PlayFieldYin);
									if (Part3)
									{
										//anything but exit and we can't jump onto it
										if (Part3->Group != GroupExit)
										{
											return false;
										}
									}
								}
								else
									//nothing on the right
									return false;
							}
						}
					}

					CWorldPart* Part4 = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin);
					if (Part4)
					{
						if (Part4->Group == GroupFloor)
						{
							return false;
						}
						else
						{
							if (Part4->Group == GroupBox)
							{
								//we're moving horizontal or falling down so we can't move into the box
								if (PlayFieldYin - self->PlayFieldY >= 0)
								{
									return false;
								}
								//were moving up
								//check to see if there are no stackboxes or other things on top of the player blocking the jump
								else
								{
									if ((self->AnimBase == AnimBaseLeft) || (self->AnimBase == AnimBaseRight))
									{
										CWorldPart* Part5 = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin - 1);
										if (Part5)
										{
											if ((Part5->Group == GroupFloor) || (Part5->Group == GroupBox) || (Part5->Group == GroupExit))
											{
												return false;
											}
										}
									}
								}
							}
						}
					}

					//check to see if our attached box has a queue if so we can't move either
					if (self->AttachedPart)
					{
						if (self->AttachedPart->Group == GroupBox)
						{
							if (self->AttachedPart->MoveQueBack > -1)
							{
								return false;
							}
						}
					}
				}
				else
					return false;
			}
			else
				return false;

			//if we want to move up
			if (PlayFieldYin - self->PlayFieldY < 0)
				//only allow jump if we are not on top position
				return self->PlayFieldY - 1 > 0;
			return true;
			break;
		}
		case IDBox:
		{
			if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
			{
				if (self->ParentList)
				{
					CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin);
					if (Part)
					{
						if ((Part->Group == GroupFloor) || (Part->Group == GroupBox) || (Part->Group == GroupExit))
						{
							return false;
						}
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			return true;
			break;
		}
		default:
			return false;
			break;
	}
}

bool CWorldPart_MoveTo(CWorldPart* self, int PlayFieldXin, int PlayFieldYin)
{
	bool Result = false;
	if (!self->IsMoving && ((PlayFieldXin != self->PlayFieldX) || (PlayFieldYin != self->PlayFieldY)))
	{
		if (self->Type == IDPlayer)
		{
			if (CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin))
			{
				Result = true;
				if (self->ParentList && (self != self->ParentList->IgnorePart) && (self->Group != GroupNone))
				{
					if ((self->PlayFieldX >= 0) && (self->PlayFieldY >= 0))
					{
						self->ParentList->PositionalItems[self->Group][self->PlayFieldY][self->PlayFieldX] = NULL;
					}
					self->ParentList->PositionalItems[self->Group][PlayFieldYin][PlayFieldXin] = self;
				}

				self->PlayFieldX = PlayFieldXin;
				self->PlayFieldY = PlayFieldYin;
				self->IsMoving = true;
				//Right
				if (self->X < self->PlayFieldX * TileWidth)
				{
					//this comes from a jump and falling down
					if (!self->NeedToMoveRight)
					{
						CWorldPart* Tmp = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin + 1);
						if (Tmp != NULL)
						{
							if ((Tmp->Group == GroupFloor) || (Tmp->Group == GroupBox))
								playWalkSound();
						}
					}

					self->Xi = self->MoveSpeed;
					if (self->AnimBase != AnimBaseRight)
					{
						self->AnimBase = AnimBaseRight;
					}

					if (self->ParentList)
					{
						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX - 1, self->PlayFieldY - 1);
						if(Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}
				//left
				if (self->X > self->PlayFieldX * TileWidth)
				{
					if (!self->NeedToMoveLeft)
					{
						CWorldPart* Tmp = CWorldParts_PartAtPosition(self->ParentList, PlayFieldXin, PlayFieldYin + 1);
						if (Tmp)
						{
							if ((Tmp->Group == GroupFloor) || (Tmp->Group == GroupBox))
								playWalkSound();
						}
					}

					self->Xi = -self->MoveSpeed;
					if (self->AnimBase != AnimBaseLeft)
					{
						self->AnimBase = AnimBaseLeft;
					}

					if (self->ParentList)
					{
						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX + 1, self->PlayFieldY - 1);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}

				//up
				if (self->Y > self->PlayFieldY * TileHeight)
				{
					playJumpSound();
					self->Yi = -self->MoveSpeed;
					//animbase = 0 is start of animation for going left, 2 is start for going right
					if (self->AnimBase == AnimBaseLeft)
					{
						self->NeedToMoveLeft = true;
						self->AnimBase = AnimBaseLeftJump;
					}
					else
						if (self->AnimBase == AnimBaseRight)
						{
							self->AnimBase = AnimBaseRightJump;
							self->NeedToMoveRight = true;
						}

					if (self->ParentList)
					{
						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}
				//down
				if (self->Y < self->PlayFieldY * TileHeight)
				{
					playFallSound();
					self->Yi = self->MoveSpeed;
					if (self->ParentList)
					{

						//check for a box on top of the player.
						CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY - 2);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								//if one is found move it to the players X position
								CWorldPart_MoveTo(Part, self->PlayFieldX, self->PlayFieldY - 1);
								//AnimBase = 6;
							}
						}
					}
				}
			}
			else
			{
				//Right
				if ((self->AnimBase != AnimBaseRight) && (PlayFieldXin > self->PlayFieldX))
				{
					self->MoveDelayCounter = -TileWidth / self->MoveSpeed;
					self->IsMoving = true;
					Result = true;
					self->AnimBase = AnimBaseRight;
					self->AnimCounter = 0;
				}
				//Left
				if ((self->AnimBase != AnimBaseLeft) && (PlayFieldXin < self->PlayFieldX))
				{
					self->MoveDelayCounter = -TileWidth / self->MoveSpeed;
					self->IsMoving = true;
					Result = true;
					self->AnimBase = AnimBaseLeft;
					self->AnimCounter = 0;
				}
				if (self->AnimPhase != self->AnimBase)
				{
					Result = true;
					self->AnimPhase = self->AnimBase;
				}
			}

		}
		else
		{
			if (self->Group == GroupBox)
				if (CWorldPart_CanMoveTo(self, PlayFieldXin, PlayFieldYin))
				{
					Result = true;
					if (self->ParentList && (self != self->ParentList->IgnorePart) && (self->Group != GroupNone))
					{
						if ((self->PlayFieldX >= 0) && (self->PlayFieldY >= 0))
						{
							self->ParentList->PositionalItems[self->Group][self->PlayFieldY][self->PlayFieldX] = NULL;
						}
						self->ParentList->PositionalItems[self->Group][PlayFieldYin][PlayFieldXin] = self;
					}
					self->PlayFieldX = PlayFieldXin;
					self->PlayFieldY = PlayFieldYin;
					if (self->X < self->PlayFieldX * TileWidth)
						self->Xi = self->MoveSpeed;
					if (self->X > self->PlayFieldX * TileWidth)
						self->Xi = -self->MoveSpeed;
					if (self->Y > self->PlayFieldY * TileHeight)
						self->Yi = -self->MoveSpeed;
					if (self->Y < self->PlayFieldY * TileHeight)
						self->Yi = self->MoveSpeed;
					self->IsMoving = true;
				}
		}
	}
	return Result;
}

void CWorldPart_Event_ArrivedOnNewSpot(CWorldPart* self)
{
	switch (self->Type)
	{
		case IDPlayer:
		{
			//check for floor so we can drop down if not found
			bool FloorFound = false;

			//in case the block was attached to a player but blocked by wall the player moved under
			if (self->AttachedPart) 
			{
				if(self->AttachedPart->Group == GroupBox)
				{
					CWorldPart_Event_ArrivedOnNewSpot(self->AttachedPart);
				}
			}

			if (self->PlayFieldY == NrOfRows - 1)
			{
				self->AnimPhases = 4;
				FloorFound = true;
			}

			if (!FloorFound)
			{
				CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY + 1);
				if (Part)
				{
					if ((Part->Group == GroupFloor) || (Part->Group == GroupBox))
					{
						self->AnimPhases = 4;
						FloorFound = true;
					}
				}
			}

			if (!FloorFound)
			{
				CWorldPart* Part2 = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY);
				if (Part2)
				{
					//to catch floating exits
					if (Part2->Group == GroupExit)
					{
						self->AnimPhases = 4;
						FloorFound = true;
					}
				}
			}

			if (self->NeedToMoveLeft)
			{
				CWorldPart_MoveTo(self, self->PlayFieldX - 1, self->PlayFieldY);
				self->NeedToMoveLeft = false;
			}

			if (self->NeedToMoveRight)
			{
				CWorldPart_MoveTo(self, self->PlayFieldX + 1, self->PlayFieldY);
				self->NeedToMoveRight = false;
			}

			if (!FloorFound && self->ParentList)
			{
				self->AnimCounter = 0;
				self->AnimPhases = 1;
				CWorldPart_MoveTo(self, self->PlayFieldX, self->PlayFieldY + 1);
			}

			break;
		}
		case IDBox:
		{
			bool PlayerBelow = false;
			bool SomethingBelow = (self->PlayFieldY == NrOfRows - 1);

			CWorldPart* Part = CWorldParts_PartAtPosition(self->ParentList, self->PlayFieldX, self->PlayFieldY + 1);
			if (Part)
			{
				if (Part->Type == IDPlayer)
				{
					SomethingBelow = true;
					PlayerBelow = true;
				}

				if ((Part->Group == GroupFloor) || (Part->Group == GroupBox) || (Part->Group == GroupPlayer) || (Part->Group == GroupExit))
				{
					SomethingBelow = true;
				}
			}
			
			if (PlayerBelow)
				CWorldPart_AttachToPlayer(self, self->ParentList->Player);
			else
				if ((self->Player) && !CWorldPart_MovesInQue(self))
					CWorldPart_DeattachFromPlayer(self, self->Player);

			//if nothing is below and there are no moves in the queue move it down
			if ((!SomethingBelow) && (!CWorldPart_MovesInQue(self)))
			{
				if (self->Player)
				{
					/*if (!self->Player->IsMoving)
					{
						self->AttachedToPlayer = false;
						self->Player = NULL;
					}*/
					//CWorldPart_Event_ArrivedOnNewSpot(self);
				}
				/*if ((!CWorldPart_CanMoveTo(self, self->PlayFieldX, self->PlayFieldY + 2)) && (self->PlayFieldY < NrOfRows - 1))
				{
					playDropSound();
				}*/
				CWorldPart_MoveTo(self, self->PlayFieldX, self->PlayFieldY + 1);
			}

			
			break;
		}
	}
}

void CWorldPart_Event_BeforeDraw(CWorldPart* self)
{
	if (self->IsMoving)
	{
		self->AnimPhase = self->AnimBase + self->AnimCounter;
		self->AnimDelayCounter++;
		if (self->AnimDelayCounter == self->AnimDelay)
		{
			self->AnimDelayCounter = 0;
			self->AnimCounter++;
			if (self->AnimCounter == self->AnimPhases)
				self->AnimCounter = 0;
		}
	}
	else
	{
		//i commented it normally we should go to animbase
		//	but the walking animation shows weird if do this
		// because there is a single frame where ismoving is false
		// when the player arrived on a new spot and this made the animation look weird
		// side effect is that walking animation remain visible but thats not a big issue
		// people could think it's as designed
		//if (self->AnimPhase != self->AnimBase)
		//{
		//	//self->AnimPhase = self->AnimBase;
		//	self->AnimDelayCounter = 0;
		//}
	}
}

void CWorldPart_Event_Moving(CWorldPart* self, int ScreenPosX, int ScreenPosY)
{
	if (self->Type == IDPlayer)
	{
		if (self->ParentList)
		{
			if ((ScreenPosX > (self->ParentList->ViewPort->MaxScreenX) - HALFWINDOWWIDTH) && (self->Xi > 0))
			{
				CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi);
			}
			if ((ScreenPosX < (self->ParentList->ViewPort->MaxScreenX) - HALFWINDOWWIDTH) && (self->Xi < 0))
			{
				CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi);
			}
			if ((ScreenPosY > (self->ParentList->ViewPort->MaxScreenY) - HALFWINDOWHEIGHT) && (self->Yi > 0))
			{
				CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi);
			}
			if ((ScreenPosY < (self->ParentList->ViewPort->MaxScreenY) - HALFWINDOWHEIGHT) && (self->Yi < 0))
			{
				CViewPort_Move(self->ParentList->ViewPort, self->Xi, self->Yi);
			}
		}
	}
}

bool CWorldPart_SetPosition(CWorldPart* self, int PlayFieldXin, int PlayFieldYin)
{
	bool Result = false;
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		if ((self->PlayFieldX != PlayFieldXin) || (self->PlayFieldY != PlayFieldYin))
		{
			if (self->ParentList && (self != self->ParentList->IgnorePart) && (self->Group != GroupNone))
			{
				if ((self->PlayFieldX >= 0) && (self->PlayFieldY >= 0))
				{
					self->ParentList->PositionalItems[self->Group][self->PlayFieldY][self->PlayFieldX] = NULL;
				}
				self->ParentList->PositionalItems[self->Group][PlayFieldYin][PlayFieldXin] = self;
			}
			self->PlayFieldX = PlayFieldXin;
			self->PlayFieldY = PlayFieldYin;
			self->X = PlayFieldXin * TileWidth;
			self->Y = PlayFieldYin * TileHeight;
			//Event_ArrivedOnNewSpot();
			Result = true;
		}
	}
	return Result;
}


bool CWorldPart_Move(CWorldPart* self)
{
	bool Result = false;
	//floors & exits don't move
	if ((self->Group == GroupFloor) || (self->Group == GroupExit))
	{
		if (!self->FirstArriveEventFired)
		{
			self->FirstArriveEventFired = true;
			Result = true;
		}
	}
	else
	{
		if (!self->FirstArriveEventFired)
		{
			CWorldPart_Event_ArrivedOnNewSpot(self);
			self->FirstArriveEventFired = true;
			Result = true;
		}

		if (self->IsMoving)
		{
			if (self->MoveDelayCounter == self->MoveDelay)
			{
				Result = true;
				self->X += self->Xi;
				self->Y += self->Yi;
				CWorldPart_Event_Moving(self, self->X, self->Y);
				if ((abs(self->X - (self->PlayFieldX * TileWidth)) < GameMoveSpeed) && (abs(self->Y - (self->PlayFieldY * TileHeight)) < GameMoveSpeed))
				{
					self->IsMoving = false;
					self->Xi = 0;
					self->Yi = 0;
					self->X = self->PlayFieldX * TileWidth;
					self->Y = self->PlayFieldY * TileHeight;
					CWorldPart_Event_ArrivedOnNewSpot(self);
				}

				self->MoveDelayCounter = -1;
			}
			self->MoveDelayCounter++;
		}
		else
		{
			if (self->MoveQueBack > -1)
			{
				if (CWorldPart_CanMoveTo(self, self->MoveQue[self->MoveQueBack]->X, self->MoveQue[self->MoveQueBack]->Y))
				{
					CWorldPart_MoveTo(self, self->MoveQue[self->MoveQueBack]->X, self->MoveQue[self->MoveQueBack]->Y);
					CWorldPart_MoveQuePopBack(self);
					Result = true;
				}
				else
				{
					if (self->Player)
					{
						CWorldPart_DeattachFromPlayer(self, self->Player);
					}
					CWorldPart_MoveQueClear(self);
				}
			}
		}
	}
	return Result;
}

void CWorldPart_Draw(CWorldPart* self)
{
	int x, y;
	if (self->Img)
	{
		CWorldPart_Event_BeforeDraw(self);

		if (self->ParentList)
		{
			x = WINDOW_OFFSET + self->X - self->ParentList->ViewPort->MinScreenX;
			y = self->Y - self->ParentList->ViewPort->MinScreenY;
		}
		else
		{
			x = self->X;
			y = self->Y;
		}

		drawTexture(self->Img, self->AnimPhase, x, y);

	}
}


//-----------------------------------------------------------------------------------------

void CWorldParts_ClearPositionalItems(CWorldParts* self)
{
	for (int i = 0; i < NrOfGroups; i++)
	{
	// 	self->PositionalItemsCount[i] = 0;
	// 	for (int y = 0; y < NrOfRows; y++)
	// 		for (int x = 0; x < NrOfCols; x++)
	// 			self->PositionalItems[i][y][x] = NULL;
		
		self->PositionalItemsCount[i] = 0;
 	   	//NULL = -1 in vircon32 c compiler
		memset(self->PositionalItems[i], -1, NrOfRows * NrOfCols * sizeof(self->PositionalItems[i][0][0]));
	}
}	


CWorldParts* CWorldParts_Create()
{
	CWorldParts* Result = malloc(sizeof(CWorldParts));
	if (Result)
	{
		CWorldParts_ClearPositionalItems(Result);
		Result->ItemCount = 0;
		Result->Player = NULL;
		Result->IgnorePart = NULL;
		Result->DisableSorting = false;
		Result->AttchedBoxQuedOrMoving = false;
		Result->NumPartsMoving = 0;
		Result->DrawCount = 0;
		Result->NumPartsMovingQueued = 0;
		Result->NumBoxesAttachedToPlayer = 0;
		Result->NumPartsAttachedToPlayer = 0;
		Result->ViewPort = CViewPort_Create(0, 0, NrOfColsVisible -1, NrOfRowsVisible - 1, 0, 0, NrOfCols - 1, NrOfRows - 1);
	}
	return Result;
}

void CWorldParts_FindPlayer(CWorldParts* self)
{
	CWorldPart* Part;
	for (int i = 0; i < self->ItemCount; i++)
	{
		Part = self->Items[i]; 
		if ((Part->Group == GroupPlayer) && (Part != self->IgnorePart))
		{
			self->Player = Part;
			break;
		}
	}
}


void CWorldParts_CenterVPOnPlayer(CWorldParts* self)
{
	if (self->Player == NULL)
		CWorldParts_FindPlayer(self);

	if (self->Player)
	{
		CViewPort_SetViewPort(self->ViewPort, self->Player->PlayFieldX - ((NrOfColsVisible) >> 1), self->Player->PlayFieldY - ((NrOfRowsVisible) >> 1), self->Player->PlayFieldX + ((NrOfColsVisible) >> 1), self->Player->PlayFieldY + ((NrOfRowsVisible) >> 1));
	}
	else
	{
		CViewPort_SetViewPort(self->ViewPort, (NrOfCols >> 1) - ((NrOfColsVisible) >> 1), (NrOfRows >> 1) - ((NrOfRowsVisible) >> 1), (NrOfCols >> 1) + ((NrOfColsVisible) >> 1), (NrOfRows >> 1) + ((NrOfRowsVisible) >> 1));
	}
}

void CWorldParts_LimitVPLevel(CWorldParts* self)
{
	int MinX = NrOfCols, MinY = NrOfRows, MaxX = -1, MaxY = -1;
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if (self->Items[Teller]->PlayFieldX < MinX)
			MinX = self->Items[Teller]->PlayFieldX;
		if (self->Items[Teller]->PlayFieldY < MinY)
			MinY = self->Items[Teller]->PlayFieldY;
		if (self->Items[Teller]->PlayFieldX > MaxX)
			MaxX = self->Items[Teller]->PlayFieldX;
		if (self->Items[Teller]->PlayFieldY > MaxY)
			MaxY = self->Items[Teller]->PlayFieldY;
	}
	CViewPort_SetVPLimit(self->ViewPort, MinX, MinY, MaxX, MaxY);
	CWorldParts_CenterVPOnPlayer(self);
}

void CWorldParts_RemoveAll(CWorldParts* self)
{
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if (self->Items[Teller])
		{
			free(self->Items[Teller]);
			self->Items[Teller] = NULL;
		}
	}
	CWorldParts_ClearPositionalItems(self);
	self->Player = NULL;
	self->ItemCount = 0;
}

void CWorldParts_Remove(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	CWorldPart* Part;
	for (int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		Part = self->Items[Teller1];
		if (Part && (Part != self->IgnorePart))
		{
			if ((Part->PlayFieldX == PlayFieldXin) && (Part->PlayFieldY == PlayFieldYin))
			{

				if (Part->Group == GroupPlayer)
				{
					self->Player = NULL;
				}
				
				if (Part->Group != GroupNone)
				{
					self->PositionalItemsCount[Part->Group]--;
					self->PositionalItems[Part->Group][Part->PlayFieldY][Part->PlayFieldX] = NULL;
				}

				
				//now clear memory & remove for item list
				free(Part);
				self->Items[Teller1] = NULL;
				for (int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
}

void CWorldParts_RemoveType(CWorldParts* self, int Type)
{
	CWorldPart* Part;
	for (int Teller1 = 0; Teller1 < self->ItemCount; Teller1++)
	{
		Part = self->Items[Teller1];
		if (Part && (Part != self->IgnorePart))
		{
			if (Part->Type == Type)
			{
				if (Type == IDPlayer)
				{
					Part->Player = NULL;
					self->Player = NULL;
				}
				
				if (Part->Group != GroupNone)
				{
					self->PositionalItemsCount[Part->Group]--;
					self->PositionalItems[Part->Group][Part->PlayFieldY][Part->PlayFieldX] = NULL;
				}

				//now clear memory & remove for item list
				free(Part);
				self->Items[Teller1] = NULL;
				for (int Teller2 = Teller1; Teller2 < self->ItemCount - 1; Teller2++)
					self->Items[Teller2] = self->Items[Teller2 + 1];
				self->ItemCount--;
				Teller1--;
			}
		}
	}
}


int compareWorldParts(CWorldPart* a, CWorldPart* b) {
    if (a->Group != b->Group) {
        return a->Group - b->Group;
    }
    return b->PlayFieldY - a->PlayFieldY;
}

int isSorted(CWorldPart** arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (compareWorldParts(arr[i], arr[i + 1]) > 0) {
            return 0; // Array is not sorted
        }
    }
    return 1; // Array is sorted
}

int partition(CWorldPart** arr, int low, int high) {
    CWorldPart* pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compareWorldParts(arr[j], pivot) <= 0) {
            i++;
            // Swap arr[i] and arr[j]
            CWorldPart* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Swap arr[i + 1] and arr[high]
    CWorldPart* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quickSort(CWorldPart** arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Sorting function
void CWorldParts_Sort(CWorldParts* self)
{
	//LEVELS ARE SAVED PRESORTED 
	//AND CAN NOT CHANGE HENCE THE RETURN
	return;
	int count = self->ItemCount;
    if (count <= 1) 
		return;
    if (!self->DisableSorting)
    {
	    // Check if the array is already sorted
   		if (isSorted(self->Items, count)) {
			return; // No need to sort if already sorted
   		 }

    	// Perform Quick Sort
    	quickSort(self->Items, 0, count - 1);
    }
}


// void CWorldParts_Sort(CWorldParts* self)
// {
// 	int Teller2, Group, Y;
// 	CWorldPart* Part;
// 	if (!self->DisableSorting)
// 	{
// 		for (int Teller1 = 1; Teller1 < self->ItemCount; Teller1++)
// 		{
// 			Part = self->Items[Teller1];
// 			Group = Part->Group;
// 			Y = Part->PlayFieldY;
			
// 			Teller2 = Teller1;
// 			//need to sort on group for drawing but also on playfieldY for same Z so that 1st item is the highest one, otherwise blocks don't fall at same time
// 			while ((Teller2 > 0) && ((self->Items[Teller2 - 1]->Group > Group) || ((self->Items[Teller2 - 1]->Group == Group) && (self->Items[Teller2-1]->PlayFieldY < Y))))
// 			{
// 				self->Items[Teller2] = self->Items[Teller2 - 1];
// 				Teller2--;
// 			}
// 			self->Items[Teller2] = Part;
// 		}
// 	}

// }

void CWorldParts_Add(CWorldParts* self, CWorldPart* WorldPart)
{
	if (self->ItemCount < NrOfRows * NrOfCols)
	{
		if (WorldPart->Type == IDPlayer)
			self->Player = WorldPart;
		WorldPart->ParentList = self;
		self->Items[self->ItemCount] = WorldPart;
		if (WorldPart->Group != GroupNone)
		{
			self->PositionalItems[WorldPart->Group][WorldPart->PlayFieldY][WorldPart->PlayFieldX] = WorldPart;
			self->PositionalItemsCount[WorldPart->Group]++;
		}
		self->ItemCount++;
		CWorldParts_Sort(self);
	}
}

void CWorldParts_Load(CWorldParts* self, int* Level)
{
   	StartDebugSpeed(2);
    int X, Y, Type;

    // Clear existing world parts
    CWorldParts_RemoveAll(self);
    self->DisableSorting = true;

    // Load parts from the Level array
    while (true)
    {
        Type = (*Level++);
        X = (*Level++);
        Y = (*Level++);
        
        // Break if the terminating condition is met
        if (Type == 0 && X == 0 && Y == 0)
            break;

        // Determine the group
        int group;
        switch (Type)
        {
            case IDEmpty:
                group = GroupNone;
                break;
            case IDBox:
                group = GroupBox;
                break;
            case IDPlayer:
                group = GroupPlayer;
                break;
            case IDExit:
                group = GroupExit;
                break;
            case IDEarthGrassLeft:
            case IDEarthGrassRight:
            case IDEarthLeft:
            case IDEarthMiddle:
            case IDEarthRight:
            case IDFloatingFloor:
            case IDFloatingFloorLeft:
            case IDFloatingFloorMiddle:
            case IDFloatingFloorRight:
            case IDFloorLeft:
            case IDFloorRight:
            case IDTower:
            case IDStartTower:
            case IDTowerShaft:
            case IDRoof1:
            case IDRoof2:
            case IDRoofCornerLeft:
            case IDRoofCornerRight:
            case IDRoofCornerBoth:
            case IDRoofDownRight:
            case IDRoofDownLeft:
            case IDFloor:
                group = GroupFloor;
                break;
        }

        // Add the part to the world
        CWorldParts_Add(self, CWorldPart_create(X, Y, Type, group));
    }

    // Re-enable sorting and perform additional operations
    self->DisableSorting = false;
    CWorldParts_Sort(self);
    CWorldParts_LimitVPLevel(self);
    CWorldParts_CenterVPOnPlayer(self);

    // Debug calculation
	StopDebugSpeed(2);
}


bool CWorldParts_Move(CWorldParts* self)
{
	bool result = false;
	self->NumPartsMoving = 0;
	self->NumPartsMovingQueued = 0;
	self->NumPartsAttachedToPlayer = 0 ;
	self->NumBoxesAttachedToPlayer = 0;
	self->AttchedBoxQuedOrMoving = false;
	CWorldPart* Part;
	
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		Part = self->Items[Teller];
		result |= CWorldPart_Move(Part);

		if (Part->IsMoving)
		{
			self->NumPartsMoving++;
		}
		
		if (Part->Player)
		{
			self->NumPartsAttachedToPlayer++;

			if (Part->Type == IDBox)
			{			
				self->NumBoxesAttachedToPlayer++;
				self->AttchedBoxQuedOrMoving = (Part->MoveQueBack > -1) || Part->IsMoving;
			}
		}

		if (Part->MoveQueBack > -1)
			self->NumPartsMovingQueued++;
			
	}
	return result;
}

int CWorldParts_Draw(CWorldParts* self)
{
	StartDebugSpeed(1);
	self->DrawCount = 0;
		int startx, starty, endx, endy;
		int numitems;
		startx = self->ViewPort->VPMinX;
		starty = self->ViewPort->VPMinY;
		endx = self->ViewPort->VPMaxX + 1;
		endy = self->ViewPort->VPMaxY + 1;
		//just a safety
		if (startx < 0)
			startx = 0;
		if (starty < 0)
			starty = 0;
		if (endx > NrOfCols - 1)
			endx = NrOfCols - 1;
		if (endy > NrOfRows - 1)
			endy = NrOfRows - 1;
		numitems = ((endx - startx) * (endy - starty) * (NrOfGroups - 1)) + 1; //there is only 1 player
		
		CWorldPart* Part;
		int x,y;
		if (true && (self->ItemCount < numitems))
		{
			for (int Teller = 0; Teller < self->ItemCount; Teller++)
			{
				Part = self->Items[Teller];
				if (Part && 
					((Part->PlayFieldX >= self->ViewPort->VPMinX) && (Part->PlayFieldX - 1 <= self->ViewPort->VPMaxX) &&
					(Part->PlayFieldY >= self->ViewPort->VPMinY) && (Part->PlayFieldY - 1 <= self->ViewPort->VPMaxY)))
				{

					if (Part->Img)
					{
						if(Part->IsMoving)
							CWorldPart_Event_BeforeDraw(Part);

						if (Part->ParentList)
						{
							x = WINDOW_OFFSET + Part->X - Part->ParentList->ViewPort->MinScreenX;
							y = Part->Y - Part->ParentList->ViewPort->MinScreenY;
						}
						else
						{
							x = Part->X;
							y = Part->Y;
						}
						
						drawTexture(Part->Img, Part->AnimPhase, x, y);

					}
					//CWorldPart_Draw(Part);
					self->DrawCount++;
				}
			}
		}
		else
		{
						
				for (int y = starty; y <= endy; y++)
				{
					for (int x = startx; x <= endx; x++)
					{
						//draw respecting order of groups
						Part = self->PositionalItems[GroupExit][y][x];
						if (Part && (Part != self->IgnorePart))
						{
							CWorldPart_Draw(Part);
							self->DrawCount++;
						}

						Part = self->PositionalItems[GroupFloor][y][x];
						if (Part && (Part != self->IgnorePart))
						{
							CWorldPart_Draw(Part);
							self->DrawCount++;
						}

						Part = self->PositionalItems[GroupBox][y][x];
						if (Part && (Part != self->IgnorePart))
						{
							CWorldPart_Draw(Part);
							self->DrawCount++;
						}
					}
				}

				//player needs to be last and we can draw it directly
				if (self->Player)
				{
					CWorldPart_Draw(self->Player);
					self->DrawCount++;
				}

			
		}
	// Debug calculation
	StopDebugSpeed(1);
	return self->DrawCount;
}

int CWorldParts_GroupCount(CWorldParts* self, int GroupIn)
{
	if (GroupIn == GroupNone)
		return 0;

	return (self->PositionalItemsCount[GroupIn]);
}


int CWorldParts_TypeAtPosition(CWorldParts* self, int PlayFieldXin, int PlayFieldYin)
{
	if ((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return 0;
	CWorldPart *Part;
	for(int Teller = 0; Teller < NrOfGroups; Teller++)
	{
		Part = self->PositionalItems[Teller][PlayFieldYin][PlayFieldXin];
		if (Part)
		{
			if (Part != self->IgnorePart)
			{
				return Part->Type;
			}
		}
	}

	return 0;
}

void CWorldParts_UpdateGraphics(CWorldParts* self)
{
	for (int Teller = 0; Teller < self->ItemCount; Teller++)
	{
		if(self->Items[Teller])
		{
			switch (self->Items[Teller]->Type)
			{
				case IDEmpty:
					self->Items[Teller]->Img = IMGEmpty;
					break;
				case IDBox:
					self->Items[Teller]->Img = IMGBox;
					break;
				case IDPlayer:
					self->Items[Teller]->Img = IMGPlayer;
					break;
				case IDFloor:
					self->Items[Teller]->Img = IMGFloor;
					break;
				case IDExit:
					self->Items[Teller]->Img = IMGExit;
					break;
				case IDEarthGrassLeft:
					self->Items[Teller]->Img = IMGEarthGrassLeft;
					break;
				case IDEarthGrassRight:
					self->Items[Teller]->Img = IMGEarthGrassRight;
					break;
				case IDEarthLeft:
					self->Items[Teller]->Img = IMGEarthLeft;
					break;
				case IDEarthMiddle:
					self->Items[Teller]->Img = IMGEarthMiddle;
					break;
				case IDEarthRight:
					self->Items[Teller]->Img = IMGEarthRight;
					break;
				case IDFloatingFloor:
					self->Items[Teller]->Img = IMGFloatingFloor;
					break;
				case IDFloatingFloorLeft:
					self->Items[Teller]->Img = IMGFloatingFloorLeft;
					break;
				case IDFloatingFloorMiddle:
					self->Items[Teller]->Img = IMGFloatingFloorMiddle;
					break;
				case IDFloatingFloorRight:
					self->Items[Teller]->Img = IMGFloatingFloorRight;
					break;
				case IDFloorLeft:
					self->Items[Teller]->Img = IMGFloorLeft;
					break;
				case IDFloorRight:
					self->Items[Teller]->Img = IMGFloorRight;
					break;
				case IDTower:
					self->Items[Teller]->Img = IMGTower;
					break;
				case IDStartTower:
					self->Items[Teller]->Img = IMGStartTower;
					break;
				case IDTowerShaft:
					self->Items[Teller]->Img = IMGTowerShaft;
					break;
				case IDRoof1:
					self->Items[Teller]->Img = IMGRoof1;
					break;
				case IDRoof2:
					self->Items[Teller]->Img = IMGRoof2;
					break;
				case IDRoofCornerLeft:
					self->Items[Teller]->Img = IMGRoofCornerLeft;
					break;
				case IDRoofCornerRight:
					self->Items[Teller]->Img = IMGRoofCornerRight;
					break;
				case IDRoofCornerBoth:
					self->Items[Teller]->Img = IMGRoofCornerBoth;
					break;
				case IDRoofDownRight:
					self->Items[Teller]->Img = IMGRoofDownRight;
					break;
				case IDRoofDownLeft:
					self->Items[Teller]->Img = IMGRoofDownLeft;
					break;
			}
		}
	}
}

void CWorldParts_deinit(CWorldParts* self)
{
	if(!self)
		return;
	CWorldParts_RemoveAll(self);
	CViewPort_deinit(self->ViewPort);
	free(self);
	self = NULL;
}

#endif