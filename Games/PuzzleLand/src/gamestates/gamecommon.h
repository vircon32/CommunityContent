#ifndef GAMECOMMON_H
#define GAMECOMMON_H

#include "time.h"
#include "string.h"
#include "../helperfuncs.h"
#include "../texture.h"
#include "../libs/DrawPrimitives/draw_primitives.h"
#include "../commonvars.h"
#include "../sound.h"

#define SoundSavePosition (sizeof(game_signature))
#define MusicSavePosition (SoundSavePosition + sizeof(bool))

int GetLevel(int *Password)
{
	int Result,Teller;
	Result = -1;
	for (Teller = 0;Teller < 36;Teller++)
	{
		if (strcmp(Password,LevelPasswords[Teller]) ==0)
		{
			Result = Teller;
			break;
		}
	}
	return Result;
}

void DrawPanel()
{
	int[100] ChrText;
	int[10] Nr;
	strcpy(ChrText, "Room Number: ");
	itoa(Level, Nr, 10);
	strcat(ChrText, Nr);
	textfont_print_from_left_zoomed(Ash, ScreenXOffset + 30 * xscale, 4 *yscale, ChrText, xscale, yscale);
	
	strcpy(ChrText, "Time: ");
	itoa((EndTime - StartTime) / 3600, Nr, 10);
	if(strlen(Nr) < 2)
		strcat(ChrText, "0");
	strcat(ChrText, Nr);
	strcat(ChrText, ":");

	itoa(((EndTime - StartTime) % 3600) / 60, Nr, 10);
	if(strlen(Nr) < 2)
		strcat(ChrText, "0");
	strcat(ChrText, Nr);
	strcat(ChrText, ":");

	itoa((EndTime - StartTime) % 60, Nr, 10);
	if(strlen(Nr) < 2)
		strcat(ChrText, "0");
	strcat(ChrText, Nr);
		
	textfont_print_from_left_zoomed(Ash, ScreenXOffset + 180 *xscale, 4 *yscale, ChrText, xscale, yscale);
}

void DrawPlayField()
{
	int Layers,X,Y;
	for (Layers = 0;Layers <= 1;Layers++)
		for (X=Cols-1;X>=0;X--)
			for(Y=Rows-1;Y>=0;Y--)
			{
				if (PlayField[Layers][X][Y] > 0)
				{
					//simple line drawing of same type of blocks, this will form shapes which is way better than what i had before
					if(Layers == 1)
						drawTextureZoomed(BlockActiveImage, 0, ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight);
					else
						drawTextureZoomed(BlockImage, 0, ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight);
					set_multiply_color(color_black);
					if ((X == 0) || ((X > 0) && (PlayField[Layers][X - 1][Y] != PlayField[Layers][X][Y])))
					{
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight, ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight);
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth +1, YOffsetGame + Y * BlockHeight, ScreenXOffset + XOffsetGame + X * BlockWidth+1, YOffsetGame + Y * BlockHeight + BlockHeight);
					}
					if ((X == Cols-1) || ((X < Cols-1) && (PlayField[Layers][X + 1][Y] != PlayField[Layers][X][Y])))
					{
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth , YOffsetGame + Y * BlockHeight, ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight);
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight, ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight + BlockHeight);
					}
					if ((Y == 0) || ((Y > 0) && (PlayField[Layers][X][Y-1] != PlayField[Layers][X][Y])))
					{
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight ,  ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight);
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight+1, ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight+1);
					}
					if ((Y == Rows-1) || ((Y < Rows-1) && (PlayField[Layers][X][Y + 1] != PlayField[Layers][X][Y])))
					{
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight + BlockHeight);
						draw_line(ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight-1, ScreenXOffset + XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight + BlockHeight-1);
					}
					set_multiply_color(color_white);
				}

				if (PlayField[Layers][X][Y] < 0)
				{
					drawTextureZoomed(BorderImages[abs(PlayField[Layers][X][Y]) - 1], 0, ScreenXOffset + XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight);
				}
			}
}


void LoadImages()
{
	int teller;
	int[50] FileName;
	BlockImage = loadImageAtPath("graphics/blockimage");
	BlockActiveImage = loadImageAtPath("graphics/blockactiveimage");
	Border = loadImageAtPath("graphics/border");
	for (teller=0;teller<BorderCount;teller++)
	{
		int[10] Nr;
		strcpy(FileName, "graphics/border");
		itoa(teller+1, Nr, 10);
		strcat(FileName, Nr);
		BorderImages[teller] = loadImageAtPath(FileName);
	}
    RoomBackground = loadImageAtPath("graphics/roombackground");
 	StageClearKader = loadImageAtPath("graphics/stageclearkader");
 	Bridge = loadImageAtPath("graphics/bridge");
}

void UnloadImages()
{
	int teller;
	for (teller=0;teller<BorderCount;teller++)
	{
		freeTexture(BorderImages[teller]);
	}
	freeTexture(BlockImage);
	freeTexture(BlockActiveImage);
	freeTexture(RoomBackground);
	freeTexture(StageClearKader);
	freeTexture(Bridge);
	freeTexture(Border);
}

int getSecondsSinceEpoch()
{
	return (int)(get_frame_counter() / 60.0);
}

void LoadSettings()
{
	bool MusicEnabled = true;
	bool SoundEnabled = true;
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&MusicEnabled, MusicSavePosition, sizeof (MusicEnabled));
			card_read_data(&SoundEnabled, SoundSavePosition, sizeof (SoundEnabled));
		}
	setSoundOn(SoundEnabled);
	setMusicOn(MusicEnabled);
}

void SaveSettings()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			int SoundEnabled = isSoundOn();
			int MusicEnabled = isMusicOn();
			card_write_data(&MusicEnabled, MusicSavePosition, sizeof (MusicEnabled));
			card_write_data(&SoundEnabled, SoundSavePosition, sizeof (SoundEnabled));
		}
}


#endif