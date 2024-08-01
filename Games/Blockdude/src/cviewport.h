#ifndef CVIEWPORT_H
#define CVIEWPORT_H

#include "commonvars.h"
#include "misc.h"

struct CViewPort
{
	int VPMinX;
	int VPMinY;
	int VPMaxX;
	int VPMaxY;
	int MinScreenX;
	int MinScreenY;
	int MaxScreenX;
	int MaxScreenY;
	int Width;
	int Height;
	int VPLimitMinX;
	int VPLimitMaxX;
	int VPLimitMinY;
	int VPLimitMaxY;
	int BackgroundX;
	int BackgroundY;
};


//accepts level positions (starting from 0)
void CViewPort_SetVPLimit(CViewPort* self, int MinX, int MinY, int MaxX, int MaxY)
{
	if ((MinX < NrOfCols) && (MinX >= 0) && (MaxX + 1 < NrOfCols) && (MaxX + 1 >= 0) &&
		(MinY < NrOfRows) && (MinY >= 0) && (MaxY + 1 < NrOfRows) && (MaxY + 1 >= 0))
	{
		self->VPLimitMinX = MinX;
		self->VPLimitMinY = MinY;
		self->VPLimitMaxX = MaxX + 1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		self->VPLimitMaxY = MaxY + 1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
	}
	else
	{
		self->VPLimitMinX = 0;
		self->VPLimitMinY = 0;
		self->VPLimitMaxX = NrOfCols; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		self->VPLimitMaxY = NrOfRows; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
	}
	if (self->VPLimitMaxX - self->VPLimitMinX < self->Width)
	{
		if (self->VPLimitMaxX - self->Width >= 0)
			self->VPLimitMinX = self->VPLimitMaxX - (self->Width);
		else
		{
			self->VPLimitMinX = 0;
			self->VPLimitMaxX = self->VPLimitMinX + (self->Width);
		}
	}
	if (self->VPLimitMaxY - self->VPLimitMinY < self->Height)
	{
		if (self->VPLimitMaxY - self->Height >= 0)
			self->VPLimitMinY = self->VPLimitMaxY - (self->Height);
		else
		{
			self->VPLimitMinY = 0;
			self->VPLimitMaxY = self->VPLimitMinY + (self->Height);
		}
	}

}


bool CViewPort_Move(CViewPort* self, int Xi, int Yi)
{
	bool Result = false;
	if ((self->MinScreenX + Xi <= TileWidth * (self->VPLimitMaxX)) && (self->MinScreenX + Xi >= self->VPLimitMinX * TileWidth) && (self->MaxScreenX + Xi <= TileWidth * (self->VPLimitMaxX)) && (self->MaxScreenX + Xi >= self->VPLimitMinX * TileWidth) &&
		(self->MinScreenY + Yi <= TileHeight * (self->VPLimitMaxY)) && (self->MinScreenY + Yi >= self->VPLimitMinY * TileHeight) && (self->MaxScreenY + Yi <= TileHeight * (self->VPLimitMaxY)) && (self->MaxScreenY + Yi >= self->VPLimitMinY * TileHeight))
	{
		Result = true;
		self->MinScreenX += Xi;
		self->MaxScreenX += Xi;
		self->MinScreenY += Yi;
		self->MaxScreenY += Yi;
		self->VPMinX = self->MinScreenX / TileWidth;
		self->VPMinY = self->MinScreenY / TileHeight;
		self->VPMaxX = self->MaxScreenX / TileWidth;
		self->VPMaxY = self->MaxScreenY / TileHeight;
		self->BackgroundX += (Xi / 2);
		self->BackgroundY += (Yi / 2);
	}
	return Result;
}

void CViewPort_SetViewPort(CViewPort* self, int MinX, int MinY, int MaxX, int MaxY)
{
	if ((MinX <= self->VPLimitMaxX) && (MinX >= self->VPLimitMinX) && (MaxX + 1 <= self->VPLimitMaxX) && (MaxX + 1 >= self->VPLimitMinX) &&
		(MinY <= self->VPLimitMaxY) && (MinY >= self->VPLimitMinY) && (MaxY + 1 <= self->VPLimitMaxY) && (MaxY + 1 >= self->VPLimitMinY))
	{
		self->VPMinX = MinX;
		self->VPMinY = MinY;
		self->VPMaxX = MaxX + 1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		self->VPMaxY = MaxY + 1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		self->MinScreenX = self->VPMinX * TileWidth;
		self->MinScreenY = self->VPMinY * TileHeight;
		self->MaxScreenX = self->VPMaxX * TileHeight;
		self->MaxScreenY = self->VPMaxY * TileWidth;
	}
	else
	{
		self->VPMinX = MinX;
		self->VPMinY = MinY;
		self->VPMaxX = MaxX + 1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		self->VPMaxY = MaxY + 1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		if (self->VPMinX < self->VPLimitMinX)
		{
			self->VPMinX = self->VPLimitMinX;
			self->VPMaxX = self->VPLimitMinX + NrOfColsVisible;

		}
		if (self->VPMaxX > self->VPLimitMaxX)
		{
			self->VPMinX = self->VPLimitMaxX - NrOfColsVisible;
			self->VPMaxX = self->VPLimitMaxX;
		}
		if (self->VPMinY < self->VPLimitMinY)
		{
			self->VPMaxY = self->VPLimitMinY + NrOfRowsVisible;
			self->VPMinY = self->VPLimitMinY;
		}
		if (self->VPMaxY > self->VPLimitMaxY)
		{
			self->VPMinY = self->VPLimitMaxY - NrOfRowsVisible;
			self->VPMaxY = self->VPLimitMaxY;
		}
		self->MinScreenX = self->VPMinX * TileWidth;
		self->MinScreenY = self->VPMinY * TileHeight;
		self->MaxScreenX = self->VPMaxX * TileHeight;
		self->MaxScreenY = self->VPMaxY * TileWidth;
	}
	self->Width = self->VPMaxX - self->VPMinX;
	self->Height = self->VPMaxY - self->VPMinY;
}

CViewPort* CViewPort_Create(int MinX, int MinY, int MaxX, int MaxY, int MinX2, int MinY2, int MaxX2, int MaxY2)
{
	CViewPort* Result = malloc(sizeof(CViewPort));
	if (Result)
	{
		if ((MinX < NrOfCols) && (MinX >= 0) && (MaxX + 1 < NrOfCols) && (MaxX >= 0) &&
			(MinY < NrOfRows) && (MinY >= 0) && (MaxY + 1 < NrOfRows) && (MaxY >= 0))
		{
			Result->VPMinX = MinX;
			Result->VPMinY = MinY;
			Result->VPMaxX = MaxX + 1;
			Result->VPMaxY = MaxY + 1;
			Result->MinScreenX = Result->VPMinX * TileWidth;
			Result->MinScreenY = Result->VPMinY * TileHeight;
			Result->MaxScreenX = Result->VPMaxX * TileHeight;
			Result->MaxScreenY = Result->VPMaxY * TileWidth;
		}
		else
		{
			Result->VPMinX = 0;
			Result->VPMinY = 0;
			Result->VPMaxX = NrOfColsVisible;
			Result->VPMaxY = NrOfRowsVisible;
			Result->MinScreenX = 0;
			Result->MinScreenY = 0;
			Result->MaxScreenX = WINDOW_WIDTH;
			Result->MaxScreenY = WINDOW_HEIGHT;
		}
		if ((MinX2 < NrOfCols) && (MinX2 >= 0) && (MaxX2 +1< NrOfCols) && (MaxX2 >= 0) &&
			(MinY2 < NrOfRows) && (MinY2 >= 0) && (MaxY2 +1< NrOfRows) && (MaxY2 >= 0))
		{
			Result->VPLimitMinX = MinX2;
			Result->VPLimitMinY = MinY2;
			Result->VPLimitMaxX = MaxX2+1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
			Result->VPLimitMaxY = MaxY2+1; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		}
		else
		{
			Result->VPLimitMinX = 0;
			Result->VPLimitMinY = 0;
			Result->VPLimitMaxX = NrOfCols; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
			Result->VPLimitMaxY = NrOfRows; //needs to be one more, need to get max element + 1 as we need to get the ending of the previous tile
		}
		Result->BackgroundX = 0;
		Result->BackgroundY = 0;
		Result->Width = Result->VPMaxX - Result->VPMinX;
		Result->Height = Result->VPMaxY - Result->VPMinY;
	}
	return Result;
}

void CViewPort_deinit(CViewPort* self)
{
	if(!self)
		return;
	free(self);
	self = NULL;
}

#endif
