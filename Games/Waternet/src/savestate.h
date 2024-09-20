#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "commonvars.h"

#define levelLocksSavePosition 100
#define SoundSavePosition (sizeof(game_signature))
#define MusicSavePosition (SoundSavePosition + sizeof(int))
#define SkinSavePosition (MusicSavePosition + sizeof(int))
#define MainSkinSavePosition (SkinSavePosition + sizeof(int))

int[gmCount][diffCount] levelLocks;
int musicOn = 1;
int soundOn = 1;
int skin = 1;
int mainSkin = 0;
int valid = 0;


void saveSaveState()
{
	if(card_is_connected())
		if(card_is_empty() || card_signature_matches( &GameSignature ))
		{
			card_write_signature(&GameSignature);
			card_write_data(&musicOn, MusicSavePosition, sizeof (musicOn));
			card_write_data(&soundOn, SoundSavePosition, sizeof (soundOn));
			card_write_data(&skin, SkinSavePosition, sizeof (skin));
			card_write_data(&mainSkin, MainSkinSavePosition, sizeof (mainSkin));
			for (int i = 0; i < gmCount; i++)
			{
				for (int j=0; j < diffCount; j++ )
					card_write_data(&levelLocks[i][j], levelLocksSavePosition + (i * diffCount + j) * sizeof (levelLocks[i][j]), sizeof (levelLocks[i][j]));
			}
		}
}

void validateSaveState()
{
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

    if ((skin > maxSkins-1) || (skin < 0) || !valid)
    {
        valid = 0;
        skin = 1;
    }

	if ((mainSkin > maxMainSkins-1) || (mainSkin < 0) || !valid)
    {
        valid = 0;
        mainSkin = 0;
    }

    for (int j = 0; j < gmCount; j++)
    {
        for (int i = 0; i < diffCount; i++)
        {
            if ((levelLocks[j][i] < 1) || (levelLocks[j][i] > levelCount) || !valid)
            {
                levelLocks[j][i] = 1;
                if (valid)
                {
                    j = 0;
                    i = 0;
                    valid = 0;
                }
            }
        }
    }

    if (!valid)
    {
        saveSaveState();
    }
}


void loadSaveState()
{
	if(card_is_connected())
		if(card_signature_matches(&GameSignature))
		{
			card_read_data(&musicOn, MusicSavePosition, sizeof (musicOn));
			card_read_data(&soundOn, SoundSavePosition, sizeof (soundOn));
			card_read_data(&skin, SkinSavePosition, sizeof (skin));
			card_read_data(&mainSkin, MainSkinSavePosition, sizeof (mainSkin));
			for (int i = 0; i < gmCount; i++)
			{
				for (int j=0; j < diffCount; j++ ) 
				{
					card_read_data(&levelLocks[i][j], levelLocksSavePosition + (i * diffCount + j) * sizeof (levelLocks[i][j]), sizeof (levelLocks[i][j]));
				}
				
			}
		}
	validateSaveState();
}

void initSaveState()
{
    valid = 1;
	musicOn = 1;
	soundOn = 1;
	skin = 1;
	mainSkin = 0;
	for (int i = 0; i < gmCount; i++)
	{
		for (int j=0; j < diffCount; j++ )
			levelLocks[i][j] = 1;
	}
    loadSaveState();
    validateSaveState();
}

void setSkinSaveState(int value)
{
    skin = value;
    saveSaveState();
}

int skinSaveState()
{
    return skin;
}

void setMainSkinSaveState(int value)
{
	mainSkin = value;
	saveSaveState();
}

int mainSkinSaveState()
{
	return mainSkin;
}

void setMusicOnSaveState(int value)
{
    musicOn = value;
    saveSaveState();
}

int isMusicOnSaveState()
{
    return musicOn;
}

void setSoundOnSaveState(int value)
{
    soundOn = value;
    saveSaveState();
}

int isSoundOnSaveState()
{
    return soundOn;
}

void unlockLevel(int mode, int diff, int aLevel)
{
    levelLocks[mode][diff] = aLevel + 1;
    saveSaveState();
}

int levelUnlocked(int mode, int diff, int aLevel)
{
    return (levelLocks[mode][diff] > aLevel);
}

int lastUnlockedLevel(int mode, int diff)
{
    return levelLocks[mode][diff];
}
#endif