#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "video.h"
#include "misc.h"
#include "string.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "commonvars.h"


// A struct that holds x & y coordinate
struct SPoint
{
    int X,Y;
};

struct CSelector
{
	SPoint SelectedPoint,CurrentPoint; //variables to hold the current position and the selected position
    bool HasSelection;
};

#include "commonvars.h"

CSelector* CSelector_Create(int PlayFieldXin, int PlayFieldYin)
{
	CSelector* Result = malloc(sizeof(CSelector));
	Result->SelectedPoint.X = 0; // there's no selection set it 0
	Result->SelectedPoint.Y = 0;
	Result->CurrentPoint.X = PlayFieldXin; // set current position
	Result->CurrentPoint.Y = PlayFieldYin;
	Result->HasSelection = false; // No selection when it's created
	return Result;
}

void CSelector_SetPosition(CSelector *Selector, int PlayFieldXin, int PlayFieldYin)
{
	// check if the new position is inside the board, if so set the new position as the currentposition
	if (((PlayFieldYin>=0) && (PlayFieldYin < 3) && (PlayFieldXin > 2) && (PlayFieldXin < 6)) ||
		((PlayFieldYin > 2) && (PlayFieldYin<6) && (PlayFieldXin >=0) && (PlayFieldXin <NrOfCols)) ||
		((PlayFieldYin > 5)&& (PlayFieldYin < NrOfRows) && (PlayFieldXin > 2) && (PlayFieldXin <6)))
		{
			Selector->CurrentPoint.X = PlayFieldXin;
			Selector->CurrentPoint.Y = PlayFieldYin;
		}
}

//set the current point as the selected point
void CSelector_Select(CSelector *Selector)
{
	Selector->SelectedPoint.X = Selector->CurrentPoint.X;
	Selector->SelectedPoint.Y = Selector->CurrentPoint.Y;
	Selector->HasSelection = true;
}

//deselect current selection (only resets flag)
void CSelector_DeSelect(CSelector *Selector)
{
	Selector->HasSelection = false;
}

//draw the selector, it's white rectangle with black outlines
void CSelector_Draw(CSelector *Selector)
{
	set_multiply_color(color_black);
	draw_rectangle(XOffSet - 1 + Selector->CurrentPoint.X * (TileWidth), YOffSet - 1 + Selector->CurrentPoint.Y * (TileHeight), 
		XOffSet - 1 + Selector->CurrentPoint.X * (TileWidth) + (TileWidth + 2), YOffSet - 1 + Selector->CurrentPoint.Y * (TileHeight) + (TileHeight + 2));
	set_multiply_color(color_white);
	draw_rectangle(XOffSet + Selector->CurrentPoint.X * (TileWidth), YOffSet+ Selector->CurrentPoint.Y * (TileHeight), 
		XOffSet + Selector->CurrentPoint.X * (TileWidth) + TileWidth, YOffSet+ Selector->CurrentPoint.Y * (TileHeight) + TileHeight);
	draw_rectangle(XOffSet + 1 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 1 + Selector->CurrentPoint.Y * (TileHeight),
		XOffSet + 1 + Selector->CurrentPoint.X * (TileWidth) + (TileWidth-2), YOffSet + 1 + Selector->CurrentPoint.Y * (TileHeight) + (TileHeight-2));
	draw_rectangle(XOffSet + 2 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 2 + Selector->CurrentPoint.Y * (TileHeight), 
		XOffSet + 2 + Selector->CurrentPoint.X * (TileWidth) + (TileWidth-4), YOffSet + 2 + Selector->CurrentPoint.Y * (TileHeight)+ (TileHeight-4));
	set_multiply_color(color_black);
	draw_rectangle(XOffSet + 3 + Selector->CurrentPoint.X * (TileWidth), YOffSet + 3 + Selector->CurrentPoint.Y * (TileHeight), 
		XOffSet + 3 + Selector->CurrentPoint.X * (TileWidth) + (TileWidth-6), YOffSet + 3 + Selector->CurrentPoint.Y * (TileHeight) + (TileHeight-6));
	set_multiply_color(color_white);
}

//free the selector
void CSelector_Destroy(CSelector *Selector)
{
	if (Selector)
		free(Selector);
	Selector = NULL;
}

#endif