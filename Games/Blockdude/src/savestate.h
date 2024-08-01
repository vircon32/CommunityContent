#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "time.h"
#include "memcard.h"

game_signature GameSignature;

int[MaxLevelPacks] levelLocks = {0,0};
int musicOn;
int soundOn;
int skin;
int valid;
int gamehelpbar;

#define LevelLockPosition 1000 //in case i ever add any new levels or options
#define optionMusicPosition (sizeof(game_signature))
#define optionSoundPosition (optionMusicPosition + sizeof(music_on))
#define optionSkinPosition (optionSoundPosition + sizeof(sound_on))
#define optionGameHelpBarPosition (optionSkinPosition + sizeof(skin))

void loadSaveState(void)
{
	//set defaults in case no card is card_is_connected
	levelLocks[0] = 1;
	levelLocks[1] = 1;
	musicOn = 1;
	soundOn = 1;
	gamehelpbar = 1;
	skin = 0;

	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&levelLocks, LevelLockPosition , sizeof(levelLocks));
			card_read_data(&musicOn, optionMusicPosition, sizeof(musicOn));
			card_read_data(&soundOn, optionSoundPosition, sizeof(soundOn));
			card_read_data(&skin, optionSkinPosition, sizeof(skin));
			card_read_data(&gamehelpbar, optionGameHelpBarPosition, sizeof(gamehelpbar));
		}
}

void saveSaveState(void)
{
    valid = 1;

	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature( &GameSignature );

    		card_write_data(&levelLocks, LevelLockPosition, sizeof(levelLocks));
    		card_write_data(&musicOn, optionMusicPosition, sizeof(musicOn));
			card_write_data(&soundOn, optionSoundPosition , sizeof(soundOn));
			card_write_data(&skin, optionSkinPosition , sizeof(skin));
			card_write_data(&gamehelpbar, optionGameHelpBarPosition, sizeof(gamehelpbar));
		}
}

void validateSaveState(void)
{
    
    if ((gamehelpbar  > 1) || (gamehelpbar < 0) || !valid)
	{
		valid = 0;
		gamehelpbar = 1;
	}

    if ((soundOn > 1) || (soundOn < 0) || !valid)
    {
        valid = 0;
        soundOn = 1;
    }

    if ((musicOn > 1) || (musicOn < 0) || !valid)
    {
        valid = 0;
        musicOn = 1;
    }

    if ((skin >= MAXSKINS) || (skin < 0) || !valid)
    {
        valid = 0;
        skin = 0;
    }

	for (int i = 0; i < MaxLevelPacks; i++)
		if ((levelLocks[i] < 1) || (levelLocks[i] > MaxLevels[i]) || !valid)
		{
			levelLocks[i] = 1;
			if (valid)
			{
				valid = 0;
			}
		}

    if (!valid)
    {
        saveSaveState();
    }
}

void initSaveState(void)
{
    memset( &GameSignature, 0, sizeof( game_signature ) );
    strcpy( GameSignature, "BLOCKDUDE_V1" );
    valid = 1;
    loadSaveState();
    validateSaveState();
}

void setGameHelpBarSaveState(int value)
{
	gamehelpbar = value;
	saveSaveState();
}

int gameHelpBarSaveState()
{
	return gamehelpbar;
}

void setSkinSaveState(int value)
{
    skin = value;
    saveSaveState();
}

int skinSaveState(void)
{
    return skin;
}


void setMusicOnSaveState(int value)
{
    musicOn = value;
    saveSaveState();
}

int isMusicOnSaveState(void)
{
    return musicOn;
}

void setSoundOnSaveState(int value)
{
    soundOn = value;
    saveSaveState();
}

int isSoundOnSaveState(void)
{
    return soundOn;
}

void unlockLevel(int aLevel)
{
    if ((aLevel > levelLocks[CurrentLevelPackIndex]) && (aLevel <= MaxLevels[CurrentLevelPackIndex]))
    {
        levelLocks[CurrentLevelPackIndex] = aLevel;
        saveSaveState();
    }
}

int levelUnlocked(int aLevel)
{
    return (levelLocks[CurrentLevelPackIndex] >= aLevel);
}

int lastUnlockedLevel()
{
    return levelLocks[CurrentLevelPackIndex];
}

#endif