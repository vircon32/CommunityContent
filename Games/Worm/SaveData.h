#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "Worm.h"
#include "memcard.h"

struct SaveData {
	int[MaxGameModes] highScores;
};

game_signature GameSignature;

SaveData save;

void LoadSavedData()
{
	for (int i = 0; i < MaxGameModes; i++)
		save.highScores[i] = 0;
	if(card_is_connected())
		if(card_signature_matches( &GameSignature ))
		{
			 card_read_data( &save, sizeof(game_signature), sizeof(save) );
		}
}

void SaveSavedData()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{			
			card_write_signature( &GameSignature );
    		card_write_data( &save, sizeof(game_signature), sizeof(save) );
		}
}

#endif