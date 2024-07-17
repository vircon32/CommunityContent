#ifndef CBOARDPARTS_H
#define CBOARDPARTS_H

#include "video.h"
#include "math.h"
#include "commonvars.h"
#include "texture.h"

struct CBoardParts;

//Base Class that defines a Cboardpart, it's only a peg
struct CPeg
{
 	int Type,X,Y,PlayFieldX,PlayFieldY,AnimPhase; //Animphase holds the current selected frame of the tile
 	Texture * Image;
 	CBoardParts *ParentList; // the parentlist, points to a CBoardParts class
} ;

void* CPeg_Create(int PlayFieldXin,int PlayFieldYin)
{
	CPeg* Result = malloc(sizeof(CPeg));
	Result->Type = IDPeg; // Id, isn't actually used in the game but if u have diffrent boardparts, u can identify it by this
    Result->Image = IMGPeg; // set the image
    Result->AnimPhase = 0; // current frame = 0 (a red dot)
 	Result->PlayFieldX=PlayFieldXin; // Set the current playfield position
 	Result->PlayFieldY=PlayFieldYin;
 	Result->X=XOffSet + PlayFieldXin*TileWidth; //set the screen position (for drawing)
 	Result->Y=YOffSet + PlayFieldYin*TileHeight;
 	Result->ParentList = NULL;
	return Result;
}


struct CBoardParts
{
 	CPeg* [NrOfCols*NrOfRows*3]  Items; // array of Cboardparts (nrofrows * norofcols*3)
 	int ItemCount; //how many objects (pegs)
};

//---------------------------------------------------------------------------------------------------------------------------------------------
// CBoardParts funcs
//---------------------------------------------------------------------------------------------------------------------------------------------


//constructor of boardparts, we start with 0 items
CBoardParts* CBoardParts_Create()
{
	CBoardParts* Result = malloc(sizeof(CBoardParts));
	Result->ItemCount = 0;
	return Result;
}


// returns a boardpart if it's found with the same coordinate otherwise return null
CPeg* CBoardParts_GetPart(CBoardParts* BoardParts,  int PlayFieldXin, int PlayFieldYin)
{
	
    // int Teller;
    // for (Teller=0;Teller < BoardParts->ItemCount;Teller++)
    //     if((BoardParts->Items[Teller]->PlayFieldX == PlayFieldXin) && (BoardParts->Items[Teller]->PlayFieldY == PlayFieldYin))
    //         return BoardParts->Items[Teller];
	// return NULL;
	
	//hack!! In initboard the pieces are added from topleft to bottomright and i added NULL values also for non board pieces!
	//so we don't have to loop through the list to get the piece like we did in code above but can directly get the piece
	//we just need to check if the requested positions are within bounds
	if((PlayFieldYin < 0) || (PlayFieldYin >= NrOfRows) || (PlayFieldXin < 0) || (PlayFieldXin >= NrOfCols))
		return NULL;

	return(BoardParts->Items[PlayFieldYin * NrOfCols + PlayFieldXin]);
   
}

// Remove all board parts
void CBoardParts_RemoveAll(CBoardParts* BoardParts)
{
	int Teller;
	for (Teller=0;Teller<BoardParts->ItemCount;Teller++)
	{
		if(BoardParts->Items[Teller])
			free(BoardParts->Items[Teller]);
		BoardParts->Items[Teller] = NULL;
	}
	BoardParts->ItemCount=0;
}

// Add a partboart, and set the boardparts parentlist to this (class/instance)
void CBoardParts_Add(CBoardParts* BoardParts, CPeg *BoardPart)
{
	if( BoardParts->ItemCount < NrOfCols * NrOfRows * 3)
	{
		if(BoardPart)
			BoardPart->ParentList = BoardParts;
		BoardParts->Items[BoardParts->ItemCount] = BoardPart;
		BoardParts->ItemCount++;
	}
}

// draw all boarparts
void CBoardParts_Draw(CBoardParts* BoardParts)
{
	int Teller;
	CPeg *Peg;
	for (Teller=0;Teller<BoardParts->ItemCount;Teller++)
	{
		Peg = BoardParts->Items[Teller];
		if(Peg)
		{
			if (Peg->Image)
			{
				drawTexture(Peg->Image, Peg->AnimPhase, Peg->X, Peg->Y); // blit it to the specified surface
			}
		}
	}
}

// this will ceate the initial board state, io a cross of pegs, with the middle on being empty (=animphase 6)
void CBoardParts_InitBoard(CBoardParts* BoardParts)
{
	CBoardParts_RemoveAll(BoardParts);
    int X,Y;
    for (Y=0;Y < NrOfRows;Y++)
        for (X=0;X < NrOfCols;X++)
        {
            if (Y < 3)
				if ((X > 2) && (X < 6))
                	CBoardParts_Add(BoardParts,CPeg_Create(X,Y));
				else
					CBoardParts_Add(BoardParts,NULL);
			
			if ((Y > 2) && (Y < 6))
               	CBoardParts_Add(BoardParts,CPeg_Create(X,Y));

			if (Y > 5) 
				if ((X > 2) && (X < 6))
					CBoardParts_Add(BoardParts,CPeg_Create(X,Y));			
				else
					CBoardParts_Add(BoardParts,NULL);
			
        }
     CBoardParts_GetPart(BoardParts,4,4)->AnimPhase = 6;
}

void CBoardParts_Destroy(CBoardParts* BoardParts)
{
	CBoardParts_RemoveAll(BoardParts);
	free(BoardParts);
	BoardParts = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// CPEG funcs
//---------------------------------------------------------------------------------------------------------------------------------------------

void CPeg_SetPosition(CPeg* Peg, int PlayFieldXin,int PlayFieldYin)
{
	if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
	{
		Peg->PlayFieldX=PlayFieldXin;
		Peg->PlayFieldY=PlayFieldYin;
		Peg->X=XOffSet + PlayFieldXin*TileWidth;
		Peg->Y=YOffSet + PlayFieldYin*TileHeight;
	}
}

bool CPeg_CanMoveTo(CPeg* Peg, int PlayFieldXin,int PlayFieldYin,bool erase) 
{
	bool temp;
	temp = true;
	float Xi,Yi;
	int LowX,LowY;
	
	//if the peg is really a peg (and not NULL)
	if(!Peg)
		return false;	
	// if the current frame isn't either a red peg or a blue peg
	if (!(Peg->AnimPhase <2))
		return false;

	// if there isn't a boardpart on the specified target location
	CPeg *tmpPeg = CBoardParts_GetPart(Peg->ParentList,PlayFieldXin,PlayFieldYin);
	if (!tmpPeg)
		return false;
	
	//if the place we wan't to move to is an empty peg (animphase = 6)
	if (tmpPeg->AnimPhase == 6)
	{
		//calculate the diffrence between the 2 points as a float
		Xi = (float)abs(PlayFieldXin - Peg->PlayFieldX)/2;
		Yi = (float)abs(PlayFieldYin - Peg->PlayFieldY)/2;

		if((Difficulty == VeryHard ) || (Difficulty == Hard))
			// here we see if xi, or yi quals 1 io movement is vertical or horintal and
			// xi or yi is 1. if it isn't 1 this means the new position isn't
			// exactly 2 pegs further away
			temp = temp &&  (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)));
		else
			// same as above except we add a diagonal
			temp = temp && (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)) || ((Xi==1) && (Yi == 1)));
		if (temp)
		{
			// calculate the lowest X & Y coordinate
			// will be used to find the middle peg (io the one we jumped over)
			if (PlayFieldXin <= Peg->PlayFieldX)
				LowX = PlayFieldXin;
			else
				LowX = Peg->PlayFieldX;
			if (PlayFieldYin <= Peg->PlayFieldY)
				LowY = PlayFieldYin;
			else
				LowY = Peg->PlayFieldY;
			// if the middle peg doesn't exists
			tmpPeg = CBoardParts_GetPart(Peg->ParentList, LowX+(int)Xi,LowY+(int)Yi);
			if (!tmpPeg)
				return false;

			// If the middle peg is either a blue (will never happen) or a red peg
			if (tmpPeg->AnimPhase < 2)
			{
				// simple hack to specify we want the middle peg to be emptied (animpahse = 6)
				// i did this so i didn't need to do the above calcultions again in Game()
				if (erase)
					tmpPeg->AnimPhase = 6;
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

void CPeg_Destroy(CPeg* Peg)
{
	if(Peg)
		free(Peg);
	Peg = NULL;
}



#endif