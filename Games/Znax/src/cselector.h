#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "texture.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "common.h"

struct CSelector
{
    SPoint SelectedPoint,CurrentPoint; //variables to hold the current position and the selected position
    bool HasSelection;
};

CSelector* CSelector_Create(int PlayFieldXin,int PlayFieldYin)
{
    CSelector* Result = (CSelector*) malloc(sizeof(CSelector));
    Result->SelectedPoint.X = 0; // there's no selection set it 0
    Result->SelectedPoint.Y = 0;
    Result->CurrentPoint.X = PlayFieldXin; // set current position
    Result->CurrentPoint.Y = PlayFieldYin;
    Result->HasSelection = false; // No selection when it's created
    return Result;
}

// Will set the position only if it layes within the board boundary
void CSelector_SetPosition(CSelector* Selector, int PlayFieldXin,int PlayFieldYin)
{
    // check if the new position is inside the board, if so set the new position as the currentposition
    if ((PlayFieldYin>=0) && (PlayFieldYin < NrOfRows) && (PlayFieldXin >= 0) && (PlayFieldXin <NrOfCols))
    {
        Selector->CurrentPoint.X = PlayFieldXin;
        Selector->CurrentPoint.Y = PlayFieldYin;
    }
    else
    {
        if(PlayFieldYin < 0)
        {
            Selector->CurrentPoint.X = PlayFieldXin;
            Selector->CurrentPoint.Y = NrOfRows-1;
        }

        if(PlayFieldYin >= NrOfRows)
        {
            Selector->CurrentPoint.X = PlayFieldXin;
            Selector->CurrentPoint.Y = 0;
        }

        if(PlayFieldXin < 0)
        {
            Selector->CurrentPoint.X = NrOfCols-1;
            Selector->CurrentPoint.Y = PlayFieldYin;
        }

        if(PlayFieldXin >= NrOfCols)
        {
            Selector->CurrentPoint.X = 0;
            Selector->CurrentPoint.Y = PlayFieldYin;
        }

    }
}
// Select will set the current position as the selected position
void CSelector_Select(CSelector* Selector)
{
    Selector->SelectedPoint.X = Selector->CurrentPoint.X;
    Selector->SelectedPoint.Y = Selector->CurrentPoint.Y;
    Selector->HasSelection = true;
}


//deselect selection
void CSelector_DeSelect(CSelector* Selector)
{
    Selector->HasSelection = false;
}

// Draw the blue box on the current position, with the offsets in mind
void CSelector_Draw(CSelector* Selector)
{
    drawTexture(IMGCursor, 0, Selector->CurrentPoint.X * TileWidth+5, Selector->CurrentPoint.Y * TileHeight+5);
}

//destructor
void CSelector_Destroy(CSelector* Selector)
{
    free(Selector);
    Selector = NULL;
}


#endif