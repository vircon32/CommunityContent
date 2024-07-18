#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "memcard.h"

int hiScore;
game_signature GameSignature;

void loadSaveState(void)
{
    if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&hiScore, sizeof(game_signature), sizeof(hiScore));
		}
}

void saveSaveState(void)
{
    if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature( &GameSignature );
    		card_write_data(&hiScore, sizeof(game_signature), sizeof(hiScore));
		}
}

void initSaveState(void)
{
    hiScore = 0;
    loadSaveState();
}

int getHiScore(void)
{
    return hiScore;
}

void setHiScore(int value)
{
    hiScore = value;
    saveSaveState();
}


#endif