#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "Mazethingie.h"
#include "memcard.h"

struct SaveData {
	int w;
	int h;
};

game_signature GameSignature;

void LoadSettings()
{
	SaveData save;
	save.w = MaxMazeWidth;
	save.h = MaxMazeHeight; 	
	if(card_is_connected())
		if(card_signature_matches( &GameSignature ))
		{
			 card_read_data( &save, sizeof(game_signature), sizeof(save) );
		}
	MazeWidth = save.w;
	MazeHeight = save.h;
	if (MazeWidth > MaxMazeWidth)
		MazeWidth = MaxMazeWidth;
	if(MazeHeight > MaxMazeHeight)
		MazeHeight = MaxMazeHeight;
}

void SaveSettings()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			SaveData save;
			save.w = MazeWidth;
			save.h = MazeHeight;
			card_write_signature( &GameSignature );
    		card_write_data( &save, sizeof(game_signature), sizeof(save) );
		}
}

#endif